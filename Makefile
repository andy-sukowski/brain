# See LICENSE file for copyright and license details.

include config.mk

SRC = brain.c
OBJ = ${SRC:.c=.o}

all: options brain

options:
	@echo brain build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

brain: ${OBJ}
	${CC} -o $@ ${OBJ}

clean:
	rm -f brain ${OBJ}

install: all
	mkdir -p ${PREFIX}/bin
	cp -f brain ${PREFIX}/bin
	chmod 755 ${PREFIX}/bin/brain

uninstall:
	rm -f ${PREFIX}/bin/brain

.PHONY: all options clean install uninstall
