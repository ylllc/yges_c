CC            = gcc
CFLAGS        = -O4 -Wall -I/usr/local/include -I../../api -I../lib
LDFLAGS       = -L/usr/local/lib
AR            = ar

TARGET = test_always.exe trash/test_never.exe 

all: $(TARGET)

clean:
	rm -f $(TARGET) *.o

%.exe: %.o ../../yges_c.a ../test.a
	$(CC) -o $@ $(LDFLAGS) -L../.. $< -l:yges_c.a -l:test/test.a

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean
