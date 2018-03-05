CC=g++
CFLAGS=-Wall -o $(EXECUTABLE)
EXECUTABLE=decomp

decomp: Dictionary.cpp Decompressor.cpp
	$(CC) $(CFLAGS) Dictionary.cpp Decompressor.cpp

.PHONY: clean
clean:
	rm decomp

