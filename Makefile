CC      = g++
CFLAGS  = -g -Wall -std=c++11
LDFLAGS =
LIBRARY =
INCLUDE =

EXEC = main
SRCS = main.cpp csv.cpp
OBJS = main.o csv.o

all : $(EXEC)

$(EXEC) : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o : %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean, mrproper

clean :
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)