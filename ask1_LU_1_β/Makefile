CC = gcc
CFLAGS = -Wall -Wextra -O2
SRCS = main.c matrix_operations.c memory_management.c lu_inverse.c
OBJS = $(SRCS:.c=.o)
TARGET = lu

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)