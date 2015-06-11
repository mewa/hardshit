TARGET	= game
SYMLINK	= launch
CC 	= gcc

CFLAGS	= -std=c99 -Wall -I$(INCDIR)

SRCDIR 	= src
OBJDIR	= obj
BINDIR	= bin
INCDIR	= include

SOURCES	= $(wildcard $(SRCDIR)/*.c)
OBJECTS	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
BINARIES= $(wildcard $(BINDIR)/*)

all: init install

install: $(OBJECTS)
	$(CC) $^ -o $(BINDIR)/$(TARGET) `pkg-config --cflags --libs allegro-5.0`

ifeq ($(wildcard $(SYMLINK)),) # create symlink if it doesn't exist
	ln -s $(BINDIR)/$(TARGET) $(SYMLINK)
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

init:
	mkdir -p $(BINDIR) $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

uninstall: clean
	rm -rf $(BINDIR) $(SYMLINK)
