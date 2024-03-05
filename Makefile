CC      = g++
CFLAGS  = -g -Wall -std=c++11
LDFLAGS =
LIBRARY =
INCLUDE =

EXEC = main
SRCS = test.cpp algogenetique.cpp
OBJS = test.o algogenetique.o

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