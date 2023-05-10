CC = g++
CFLAGS = -Wall -g -I./include
OBJS = crud.o data.o main.o
SRCS = crud.cpp data.cpp main.cpp
HEADERS = $(wildcard include/*.h)

all: myprogram

myprogram: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o myprogram

$(OBJS): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	rm -f $(OBJS) myprogram
