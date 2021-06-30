#! /bin/sh

CC=cc
LIBICONV_PATH=../install/x86_64-freebsd
${CC} -Wall -Werror -o./app						\
	-I${LIBICONV_PATH}/include					\
	-L${LIBICONV_PATH}/lib						\
	-Wl,-rpath=\$ORIGIN/${LIBICONV_PATH}/lib	\
	./main.c									\
	-liconv
