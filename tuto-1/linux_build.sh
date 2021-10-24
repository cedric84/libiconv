#! /bin/bash

CC=cc
LIBICONV_PATH=../install/x86_64-linux
${CC} -Wall -Werror -o${LIBICONV_PATH}/bin/app	\
	-I${LIBICONV_PATH}/include					\
	-L${LIBICONV_PATH}/lib						\
	-Wl,-rpath=\$ORIGIN/${LIBICONV_PATH}/lib	\
	./main.c									\
	-liconv
