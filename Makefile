PROGNAME=mysort
PREFIX=/home/kodopp/mysort-install
WERROR_FLAG=

OBJS = \
src/main.o \

LIBS = \
-lc -lm \

CC?=cc
LDFLAGS?=
CFLAGS=-std=c99 -Wall -Wextra -pedantic $(WERROR_FLAG)

.PHONY: all clean distclean install uninstall ee bee run

all: $(PROGNAME)
clean:
	rm -vf $(PROGNAME) src/*.o
distclean: clean
	rm -vf Makefile
install: $(PROGNAME) install.sh
	./install.sh
uninstall: uninstall.sh
	./uninstall.sh

$(PROGNAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(PROGNAME)

# Debug targets
run: $(PROGNAME)
	./$(PROGNAME)
ee: clean run
bee: clean all
