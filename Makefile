PREFIX=.
SRCDIR=$(PREFIX)/src
INCDIR=$(PREFIX)/include
BINDIR=$(PREFIX)/bin

CC=gcc
CPPFLAGS=-I$(INCDIR)
CFLAGS=-Wall -Wextra -std=c99 -lm -g
LDFLAGS=

EXEC=$(BINDIR)/GalaxY
SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(SRC:.c=.o)


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

command.o: planet.h rand.h memory.h

commerce.o: rand.h ship_util.h

drop.o: staff.h ship_util.h rand.h

main.o: starsystem.h menu.h player.h command.h memory.h

menu.o: memory.h

planet.o: rand.h crew.h player.h

player.o: rand.h memory.h menu.h planet.h drop.h

screen.o: memory.h

ship_util.o: rand.h

staff.o: rand.h screen.h

starsystem.o: rand.h portal.h memory.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

.PHONY: clean mrproper

clean:
	rm $(SRCDIR)/*.o

mrproper: clean
	rm $(EXEC)
