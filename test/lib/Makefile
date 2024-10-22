CC            = gcc
CFLAGS        = -O4 -Wall -I/usr/local/include -I../../api
LDFLAGS       = -L/usr/local/lib
AR            = ar

TARGET = ../test.a
INTERMED = test_intermediate.a
LINKAGES = ../../yges_c.a
OBJS   = trash/dummy2.o 

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

$(TARGET): $(INTERMED) $(LINKAGES)
	rm -f $(TARGET)
	ar crsT $(TARGET) $(LINKAGES) $(INTERMED)

$(INTERMED): $(OBJS) $(LINKAGES)
	ar r $(INTERMED) $(OBJS)

%.o: %.c $(LINKAGES)
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: all clean
