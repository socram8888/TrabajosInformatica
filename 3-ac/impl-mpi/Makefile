# Compilator and flags
CC = mpicc
CFLAGS = -O3 -mavx -std=c99 -Wall -Wextra -pedantic -D_POSIX_C_SOURCE=200112
EXEC = main

HEADERS := $(wildcard *.h)
OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
EXECOBJ := $(EXEC:%=%.o)
LIBSOBJ := $(filter-out $(EXECOBJ),$(OBJECTS))

# Disable built-in wildcard rules
.SUFFIXES:

# Keep objects to speed up recompilation
.PRECIOUS: %.o

# Compilation targets

all: $(EXEC)

%: %.o $(LIBSOBJ)
	$(CC) $(LIBSOBJ) $< -o $@ $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(EXEC)
