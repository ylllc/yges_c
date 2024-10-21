all:
	make -C api
	make -C test

clean:
	make -C api clean
	make -C test clean

.PHONY: all clean
