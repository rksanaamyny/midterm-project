CC = g++
CFLAGS = -Wall -Wextra -std=c++11

SRCS = main.cpp Genome.cpp Cell.cpp Animal.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = test_genome

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
