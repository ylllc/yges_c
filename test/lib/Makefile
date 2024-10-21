CC            = gcc
CFLAGS        = -O4 -Wall -I/usr/local/include -I../../api
LDFLAGS       = -L/usr/local/lib
AR            = ar

TARGET = ../test.a
OBJS   = trash/dummy2.o 

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	ar r test_tmp.a $(OBJS)
	ar crsT $(TARGET) ../../yges_c.a test_tmp.a

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean
