CC = clang
CFLAGS = -Wall -Werror -o cassette-tape
DEBUGFLAGS = -D DEBUG -g 
LDFLAGS = main.c todo.c

all: clean build

all_debug: clean build_debug

clean: 
	rm -f cassette-tape

build:
	$(CC) $(CFLAGS) $(LDFLAGS)

build_debug:
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(LDFLAGS)
