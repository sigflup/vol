
CC = cc
LEX = lex
CFLAGS = -I./gui/ `sdl2-config --cflags` -O2 -Wall -ggdb 
LIBS= `sdl2-config --libs` -O2 -ggdb -lSDL2_image ./gui/libgui.a -lm
PROGNAME=vol


OBJS = main.o gui/libgui.a

vol: ${OBJS}
	${CC} -o ${PROGNAME}  ${OBJS} ${LIBS}

install: vol
	cp vol /usr/local/bin
	chown root /usr/local/bin/vol
	chmod +s /usr/local/bin/vol


main.o: main.c main.h
	${CC} -c ${CFLAGS} main.c

gui/libgui.a:
	cd gui && make
clean:
	cd gui && make clean
	rm -f vol ${OBJS}