CC = gcc
CFLAGS = -Wall -Wextra -pedantic -I include/
RM = rm -f
TARG = rcg
BINDIR = /usr/local/bin
SRCDIR = src
OBJDIR = obj
OBJ = $(shell find ./src -type f -iname "*.c" | sed -e 's/\.c/.o/' -e 's/$(SRCDIR)/$(OBJDIR)/')

all: $(TARG)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

run: $(TARG)
	./$(TARG)

clean:
	$(RM) $(OBJ) $(TARG)
