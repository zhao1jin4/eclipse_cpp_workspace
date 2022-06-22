CC=gcc
DEST=hello.c
CFLAGS= -Wall -O2
LIB=mymath.a
SOURCES=min.c max.c avg.c
OBJECTS=${SOURCES:.c=.o}
all : hello
hello : mathlib
	${CC} -o ${DEST:.c=} ${DEST} ${LIB}
mathlib : min.o max.o avg.o
	ar crs ${LIB} ${OBJECTS} 
.PHONY :clean 
.PHONY :install uninstall

clean:
	rm -f ${OBJECTS} ${LIB}
install:
	cp hello /usr/bin/hello 
uninstall:
	rm -f /usr/bin/hello
