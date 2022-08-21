#pragma once
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <3ds.h>
#include <curl/curl.h>


struct NetworkResult {
	std::string redirected_url;
	bool fail = false; // whether some network error occured; receiving http error code like 404 is still counted as a 'success'
	std::string error;
	int status_code = -1;
	std::string status_message;
	std::vector<u8> data;
	std::map<std::string, std::string> response_headers;
	
	bool status_code_is_success() { return status_code / 100 == 2; }
	std::string get_header(std::string key);
};
struct HttpRequest { // including https
	std::string method;
	std::string url;
	std::map<std::string, std::string> headers;
	std::string body;
	bool follow_redirect; // ignored when method == POST (never follow redirects when posting)
	
	using progress_callback_t = std::function<void (u64, u64)>;
	progress_callback_t progress_func{};
	using on_finish_callback_t = std::function<void (NetworkResult &, int)>;
	on_finish_callback_t on_finish{};
	
	static std::map<std::string, std::string> default_headers_added(std::map<std::string, std::string> headers) {
		static const std::string DEFAULT_USER_AGENT = "Mozilla/5.0 (Linux; Android 11; Pixel 3a) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.101 Mobile Safari/537.36";
		static const std::map<std::string, std::string> default_headers = {
			{"Accept", "*/*"},
			{"Connection", "Keep-Alive"},
			{"User-Agent", DEFAULT_USER_AGENT}
		};
		for (auto default_header : default_headers) if (!headers.count(default_header.first)) headers[default_header.first] = default_header.second;
		return headers;
	}
	static HttpRequest GET(const std::string &url, const std::map<std::string, std::string> &headers, bool follow_redirect = true) {
		return HttpRequest{"GET", url, default_headers_added(headers), "", follow_redirect};
	}
	static HttpRequest POST(const std::string &url, const std::map<std::string, std::string> &headers, const std::string &body) {
		return HttpRequest{"POST", url, default_headers_added(headers), body, false};
	}
	HttpRequest with_progress_func(progress_callback_t progress_func) const {
		return HttpRequest{method, url, headers, body, follow_redirect, progress_func, on_finish};
	}
	HttpRequest with_on_finish_callback(on_finish_callback_t on_finish) const {
		return HttpRequest{method, url, headers, body, follow_redirect, progress_func, on_finish};
	}
};

struct NetworkSessionList { // one instance per thread
private :
	void deinit(); // will be called for each instance when the app exits
	
	void curl_add_request(const HttpRequest &request, NetworkResult *res);
	CURLMcode curl_perform_requests();
	void curl_clear_requests();
public :
	// used for libcurl
	CURLM* curl_multi = NULL; // curl manages sessions within a single CURL *
	struct RequestInternal {
		CURL *curl;
		NetworkResult *res;
		char *errbuf;
		std::string orig_url;
		HttpRequest::on_finish_callback_t on_finish;
	};
	std::vector<RequestInternal> curl_requests; // {curl context, corresponding result, error buffer}
	
	volatile bool inited = false;
	
	// this function does NOT perform any network/socket related operations
	void init();
	void close_sessions();
	
	// network operations
	NetworkResult perform(const HttpRequest &request);
	std::vector<NetworkResult> perform(const std::vector<HttpRequest> &requests);
	
	static void at_exit();
	static void exit_request();
};

void lock_network_state();
void unlock_network_state();

#define HTTP_STATUS_CODE_OK 200
#define HTTP_STATUS_CODE_NO_CONTENT 204
#define HTTP_STATUS_CODE_PARTIAL_CONTENT 206
#define HTTP_STATUS_CODE_FORBIDDEN 403
#define HTTP_STATUS_CODE_NOT_FOUND 404
