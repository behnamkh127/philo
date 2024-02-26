CC = cc
CFLAGS = -Wall -Wextra -Werror

TARGET = philo
SRCS = src/main.c src/initialize.c src/routine.c src/death.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
