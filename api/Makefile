CC            = gcc
CFLAGS        = -O4 -Wall -I/usr/local/include
CPPFLAGS      = $(CFLAGS)
LDFLAGS       = -L/usr/local/lib
AR            = ar

TARGET = ../yges_c.a
OBJS   = \
	system/emergency_trap.o system/nullproof.o \
	system/emergency_trap_pp.o \
	memory/safe_alloc.o

all: $(TARGET)
	ar r $(TARGET) $(OBJS)

clean:
	rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)


%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
%.o: %.cpp
	$(CC) -o $@ -c $< $(CPPFLAGS)

.PHONY: clean
