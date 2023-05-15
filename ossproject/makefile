CC = g++
CFLAGS = -Wall -g -I./include
OBJS = crud.o data.o main.o extrafunction.o
SRCS = crud.cpp data.cpp main.cpp extrafunction.cpp
HEADERS = $(wildcard include/*.h)

all: stocktrading

stocktrading: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o stocktrading

$(OBJS): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	rm -f $(OBJS) stocktrading
