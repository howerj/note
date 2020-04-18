# PROJECT: pickle, a TCL like interpreter
# LICENSE: BSD (see 'pickle.c' or 'LICENSE' file)
# SITE:    https://github.com/howerj/pickle
#
TARGET  = note
CFLAGS  = -std=c99 -Wall -Wextra -pedantic -O2 ${DEFINES} ${EXTRA}
DESTDIR = install

.PHONY: all clean install dist

all: ${TARGET}

${TARGET}: ${TARGET}.o
	${CC} ${CFLAGS} $^ -o $@
	-strip ${TARGET}

${TARGET}.1: readme.md
	pandoc -s -f markdown -t man $< -o $@

install: ${TARGET} ${TARGET}.1 .git
	install -p -D ${TARGET} ${DESTDIR}/bin/${TARGET}
	-install -p -m 644 -D ${TARGET}.1 ${DESTDIR}/man/${TARGET}.1
	mkdir -p ${DESTDIR}/src
	cp -a .git ${DESTDIR}/src
	cd ${DESTDIR}/src && git reset --hard HEAD

dist: install
	tar zcf ${TARGET}-${VERSION}.tgz ${DESTDIR}

check:
	-scan-build make
	-cppcheck --enable=all *.c

clean:
	git clean -dffx

