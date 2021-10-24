@set CC=%MINGW_HOME%\bin\gcc.exe
@set ICONV_PATH=..\install\i686-windows-mingw
@%CC% -Wall -Werror -o%ICONV_PATH%\bin\app.exe .\main.c ^
	-I%ICONV_PATH%\include ^
	-L%ICONV_PATH%\lib ^
	-liconv.dll

