CC            = gcc
CFLAGS        = -O4 -Wall -I/usr/local/include -I../../api -I../lib
CPPFLAGS      = $(CFLAGS)
LDFLAGS       = -L/usr/local/lib
AR            = ar

TARGET = \
	system/emergency.exe system/emergency_pp.exe system/nullproof.exe \
	memory/safe_alloc.exe memory/memory_emergency.exe \
	file/quick_loader.exe file/quick_loader_pp.exe

all: $(TARGET)

clean:
	rm -f $(TARGET) *.o

%.exe: %.o ../../yges_c.a ../test.a
	$(CC) -o $@ $(LDFLAGS) -L../.. $< -l:yges_c.a -l:test/test.a -lstdc++

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
%.o: %.cpp
	$(CC) -o $@ -c $< $(CPPFLAGS)

.PHONY: clean
