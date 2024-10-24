CC            = gcc
CFLAGS        = -O4 -Wall -I/usr/local/include
LDFLAGS       = -L/usr/local/lib
AR            = ar

TARGET = ../yges_c.a
OBJS   = \
	system/emergency_trap.o \
	memory/safe_alloc.o \
	trash/dummy.o

all: $(TARGET)
	ar r $(TARGET) $(OBJS)

clean:
	rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)


%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean
