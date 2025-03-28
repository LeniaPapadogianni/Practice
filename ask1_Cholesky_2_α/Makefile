CC = gcc
CFLAGS = -Wall -Wextra -O2
SRCS = main.c matrix_operations.c memory_management.c cholesky_decomposition.c matrix_norms.c
OBJS = $(SRCS:.c=.o)
TARGET = cholesky

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)