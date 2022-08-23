# ThirdTube-ES

Un cliente de YouTube homebrew en progreso para 3DS 

## Aviso de inestabilidad

Como esta aplicación aún se encuentra en la etapa alfa, es posible que encuentre bloqueos y otros errores.
Si encuentra uno de esos, sería útil abrir un problema en este repositorio de GitHub. 

## Descripción
Utiliza algunas API de YouTube no documentadas para obtener la URL del video sin procesar y reproduce la transmisión usando el decodificador tomado de [Video player for 3DS de Core-2-Extreme](https://github.com/Core-2-Extreme/Video_player_for_3DS).  
No ejecuta javascripts ni renderiza html/css, por lo que es significativamente más rápido que YouTube en el navegador.
El nombre se deriva del hecho de que es el tercer cliente de YouTube en 3DS, después de la aplicación oficial de YouTube (descontinuada) y el nuevo navegador 3DS..  

## Código QR
Puede usar el código qr a continuación para descargar e instalar .cia desde 3ds

<img src="https://raw.githubusercontent.com/JustSofter/ThirdTube-ES/main/images/qr_code.png" width="200" height="200">

## Capturas de pantalla
<img src="https://github.com/windows-server-2003/ThirdTube/blob/main/images/0.jpg" width="400" height="480"> ![](https://github.com/windows-server-2003/ThirdTube/blob/main/images/1.bmp)  
![](https://github.com/windows-server-2003/ThirdTube/blob/main/images/3.bmp) ![](https://github.com/windows-server-2003/ThirdTube/blob/main/images/4.bmp)  

## Funciones

- Reproducción de video hasta 360p
   480p podría ser posible y podría considerarse en el desarrollo futuro
 - Soporte de transmisiones en vivo y videos de estreno
 - Buscando
 - Sugerencia de video
 - Comentarios
 - Subtítulos
 - Historial de reproducción local y suscripción al canal
 - Sin anuncios
   Es más como "los anuncios no están implementados" en lugar de "una funcionalidad de bloqueo de anuncios".
   Por supuesto, nunca lo "implementaré" :)

## Controles

- Botón B: volver a la escena anterior
 - C-pad arriba/abajo: desplazamiento
 - L/R: cambiar entre pestañas
 - Seleccionar + Inicio: oscurecer la pantalla inferior
 - En reproductor de video
    - Flecha izquierda/derecha: 10 s buscar

A continuación se muestran para fines de depuración.

 - Seleccionar + X: alternar registro de depuración
 - Seleccionar + Y: alternar el monitor de uso de memoria
 - Seleccione + R + A: alternar monitor FPS



## Requisitos
Un 3DS (incluido 2DS) con [Luma3DS](https://github.com/LopezTutoriales/Luma3DS_3GX_Loader_ESP.git) instalado y [DSP1](https://github.com/LopezTutoriales/DSP1-Spanish) en ejecución.
No he probado la versión mínima del sistema, pero se necesita al menos 8.1.0-0.  

## FAQs

- ¿Tiene sentido?
   La **peor** pregunta en la scene homebrew de la consola. ¿No es emocionante ver tus videos favoritos en una 3DS?

## Buildeo
Necesitas:

 - devkitPro con devkitARM r58  
 - ```3ds-zlib``` y ```3ds-mbedtls``` instalado en portlibs de devkitPro
   Puede instalarlo abriendo devkitPro msys2 y escribiendo ```pacman -S [nombre del paquete]```.

Inserte ```make``` (si estás en linux) o ```make all_win``` (si estás en windows) para buildearlo.  

- Construcción de bibliotecas de dependencia (opcional)
   Para ffmpeg, libbrotli y libcurl, siga build.txt en cada directorio
   Para libctru, simplemente escriba ```make``` en biblioteca\libctru\source\libctru

## Licenscia
Puede usar el código según los términos de la Licencia pública general de GNU GPL v3 o según los términos de cualquier revisión posterior de la GPL. Consulte el archivo de LICENCIA proporcionado para obtener más información.

## Licencias Third-party

### [FFmpeg](https://ffmpeg.org/)
por los desarrolladores de FFmpeg bajo GNU Lesser General Public License (LGPL) versión 2.1
El código fuente modificado se puede encontrar en https://github.com/windows-server-2003/FFmpeg/tree/3ds.  
### [rapidjson](https://github.com/Tencent/rapidjson)
por Tencent y Milo Yip bajo licencia MIT 
### [libctru](https://github.com/devkitPro/libctru)
por devkitPro bajo licencia zlib
### [libcurl](https://curl.se/)
por Daniel Stenberg y muchos colaboradores bajo la licencia curl
### [libbrotli](https://github.com/google/brotli)  
por los autores de Brotli bajo licencia MIT
### [stb](https://github.com/nothings/stb/)
por Sean Barrett bajo licencia MIT y dominio público 

## Créditos
* Core 2 Extreme  
  De [Video player for 3DS](https://github.com/Core-2-Extreme/Video_player_for_3DS) en el que se basa esta aplicación.
  No hace falta decir que la funcionalidad de reproducción de video es esencial para esta aplicación, y no hubiera sido posible desarrollar este software sin él, dedicó su tiempo a optimizar el código, a veces incluso con el ensamblaje, y analizó la decodificación HW en el nuevo 3DS.
* dixy52-bip 
  Para texturas en la aplicación
* [PokéTube](https://github.com/Poketubepoggu)  
  Por el icóno y el banner
* Los contribuyentes de [youtube-dl](https://github.com/ytdl-org/youtube-dl)  
  Como referencia sobre el análisis de páginas web de YouTube. Fue especialmente útil para la desofuscación de firmas cifradas.
* Los contribuyentes def [pytube](https://github.com/pytube/pytube)  
  Como referencia sobre el análisis de páginas web de YouTube. Gracias a su estricta política libre de dependencias, pude portar parte del código sin dificultad.  

