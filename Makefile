TARGET	= game
SYMLINK	= launch
CC 	= gcc

CFLAGS	= -std=gnu99 -Wall -I$(INCDIR) -lm

SRCDIR 	= src
OBJDIR	= obj
BINDIR	= bin
INCDIR	= include

SOURCES	= $(wildcard $(SRCDIR)/*.c)
OBJECTS	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
BINARIES= $(wildcard $(BINDIR)/*)

all: init install

install: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(BINDIR)/$(TARGET) `pkg-config --cflags --libs allegro-5.0 allegro_image-5.0 allegro_audio-5.0 allegro_acodec-5.0`

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
