PREFIX=.
SRCDIR=$(PREFIX)/src
INCDIR=$(PREFIX)/include
BINDIR=$(PREFIX)/bin
OBJDIR=$(PREFIX)/obj

EXEC=$(BINDIR)/GalaxY
SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -lm -g
CPPFLAGS=-I$(INCDIR)
LDFLAGS=

vpath %.c src
vpath %.h include

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJDIR)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

.PHONY: clean mrproper

clean:
	rm $(OBJDIR)/*.o

mrproper: clean
	rm $(EXEC)
