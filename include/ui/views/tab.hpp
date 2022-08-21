#pragma once
#include "view.hpp"
#include "../ui_common.hpp"

struct TabView : public FixedSizeView {
private :
	std::vector<UI::FlexibleString<TabView> > tab_texts;
public :
	using CallBackFuncType = std::function<void (const TabView &value)>;
	TabView (double x0, double y0, double width, double height) : View(x0, y0), FixedSizeView(x0, y0, width, height) {}
	virtual ~TabView () {}
	
	std::vector<View *> views;
	double tab_selector_height = 20;
	double tab_selector_selected_line_height = 3;
	int selected_tab = 0;
	int tab_holding = -1;
	bool stretch_subview = false;
	bool lr_tab_switch_enabled = true;
	double tab_font_size = 0.5;
	
	int get_tab_num() const { return std::min(tab_texts.size(), views.size()); }
	float tab_width() const { return (x1 - x0) / get_tab_num(); }
	float tab_pos_x(int tab) const { return x0 + (x1 - x0) * tab / get_tab_num(); }
	
	template<typename T> TabView *set_tab_texts(const std::vector<T> &tab_texts) {
		this->tab_texts = std::vector<UI::FlexibleString<TabView> >(tab_texts.begin(), tab_texts.end());
		return this;
	}
	TabView *set_views(const std::vector<View *> &views, int selected_tab = 0) {
		this->views = views;
		this->selected_tab = selected_tab;
		return this;
	}
	TabView *set_stretch_subview(bool stretch_subview) {
		this->stretch_subview = stretch_subview;
		return this;
	}
	TabView *set_tab_font_size(double tab_font_size) {
		this->tab_font_size = tab_font_size;
		return this;
	}
	TabView *set_lr_tab_switch_enabled(bool lr_tab_switch_enabled) {
		this->lr_tab_switch_enabled = lr_tab_switch_enabled;
		return this;
	}
	void on_scroll() override {
		tab_holding = -1;
	}
	void reset_holding_status_() override {
		tab_holding = -1;
	}
	void recursive_delete_subviews() override {
		for (auto view : views) {
			view->recursive_delete_subviews();
			delete view;
		}
		views.clear();
	}
	
	
	void draw_() const override {
		int tab_num = get_tab_num();
		if (!tab_num) return;
		
		if (stretch_subview) {
			FixedHeightView *cur_view = dynamic_cast<FixedHeightView *>(views[selected_tab]);
			if (cur_view) cur_view->update_y_range(0, y1 - tab_selector_height - y0);
		}
		views[selected_tab]->draw(x0, y0);
		
		Draw_texture(var_square_image[0], LIGHT1_BACK_COLOR, x0, y1 - tab_selector_height, x1 - x0, tab_selector_height);
		Draw_texture(var_square_image[0], LIGHT2_BACK_COLOR, tab_pos_x(selected_tab), y1 - tab_selector_height, tab_width(), tab_selector_height);
		Draw_texture(var_square_image[0], LIGHT3_BACK_COLOR, tab_pos_x(selected_tab), y1 - tab_selector_height, tab_width(), tab_selector_selected_line_height);
		for (int i = 0; i < tab_num; i++) {
			float y = y1 - tab_selector_height + (tab_selector_height - Draw_get_height(tab_texts[i], 0.5)) / 2;
			if (i == selected_tab) y -= 2;
			else y -= 3;
			Draw_x_centered(tab_texts[i], tab_pos_x(i), tab_pos_x(i + 1), y, tab_font_size, tab_font_size, DEFAULT_TEXT_COLOR);
		}
	}
	void update_(Hid_info key) override {
		if (lr_tab_switch_enabled) {
			if (key.p_r) {
				selected_tab++;
				if (selected_tab >= (int) views.size()) selected_tab -= views.size();
				var_need_reflesh = true;
			}
			if (key.p_l) {
				selected_tab--;
				if (selected_tab < 0) selected_tab += views.size();
				var_need_reflesh = true;
			}
		}
		int tab_holded = -1;
		if (key.touch_y >= y1 - tab_selector_height && key.touch_y < y1)
			tab_holded = std::max(0, std::min<int>(get_tab_num() - 1, (key.touch_x - x0) * get_tab_num() / (x1 - x0)));
		
		if (key.p_touch) tab_holding = tab_holded;
		if (key.touch_x == -1 && tab_holding != -1) selected_tab = tab_holding, var_need_reflesh = true;
		if (tab_holded != tab_holding) tab_holding = -1;
		
		if (stretch_subview) {
			FixedHeightView *cur_view = dynamic_cast<FixedHeightView *>(views[selected_tab]);
			if (cur_view) cur_view->update_y_range(0, y1 - tab_selector_height - y0);
		}
		views[selected_tab]->update(key, x0, y0);
	}
};
