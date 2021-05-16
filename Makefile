# miniwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c miniwm.c util.c
OBJ = ${SRC:.c=.o}

all: options miniwm

options:
	@echo miniwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

miniwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f miniwm ${OBJ} miniwm-${VERSION}.tar.gz

dist: clean
	mkdir -p miniwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		miniwm.1 drw.h util.h ${SRC} miniwm.png transient.c miniwm-${VERSION}
	tar -cf miniwm-${VERSION}.tar miniwm-${VERSION}
	gzip miniwm-${VERSION}.tar
	rm -rf miniwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f miniwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/miniwm
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < miniwm.1 > ${DESTDIR}${MANPREFIX}/man1/miniwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/miniwm.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/miniwm\
		${DESTDIR}${MANPREFIX}/man1/miniwm.1

.PHONY: all options clean dist install uninstall
