CC = g++
CFLAGS = -Wall -g -I./include
OBJS = crud.o data.o main.o portfolio.o
SRCS = crud.cpp data.cpp main.cpp portfolio.cpp
HEADERS = $(wildcard include/*.h)

all: myprogram

myprogram: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o myprogram

$(OBJS): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	rm -f $(OBJS) myprogram
