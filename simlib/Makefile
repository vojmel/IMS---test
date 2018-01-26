#xmeluz04
#

CFLAGS=-g -O2 -Wall -Wextra
CC=g++
LDFLAGS=-lsimlib -lm
SOURCES=projekt.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=project

all:
	$(CC) $(CFLAGS) $(LDFLAGS) projekt.cc  -o $(EXECUTABLE)_RAM256
	$(CC) $(CFLAGS) -DUSE_RAM512 $(LDFLAGS) projekt.cc  -o $(EXECUTABLE)_RAM512	
	$(CC) $(CFLAGS) -DUSE_RAM1024 $(LDFLAGS) projekt.cc -o $(EXECUTABLE)_RAM1024
	$(CC) $(CFLAGS) -DUSE_RAM2048 $(LDFLAGS) projekt.cc -o $(EXECUTABLE)_RAM2048
	$(CC) $(CFLAGS) -DUSE_RAM4048 $(LDFLAGS) projekt.cc -o $(EXECUTABLE)_RAM4048
	$(CC) $(CFLAGS) -DUSE_RAM8096 $(LDFLAGS) projekt.cc -o $(EXECUTABLE)_RAM8096

run:
	@rm -rf ./exper
	@mkdir exper 2>/dev/null	
	./$(EXECUTABLE)_RAM256 > ./exper/RAM256.output
	./$(EXECUTABLE)_RAM512 > ./exper/RAM512.output
	./$(EXECUTABLE)_RAM1024  > ./exper/RAM1024.output
	./$(EXECUTABLE)_RAM2048 > ./exper/RAM2048.output	
	./$(EXECUTABLE)_RAM4048 > ./exper/RAM4048.output
	./$(EXECUTABLE)_RAM8096 > ./exper/RAM8096.output

test:
	$(CC) $(CFLAGS) $(LDFLAGS) test.cc  -o test



clean:
	@rm -rf $(EXECUTABLE)* *.o* ./exper