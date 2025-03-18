CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRCS = src/zit.c \
       src/core/repository.c \
       src/commands/init.c \
       src/commands/add.c \
       src/commands/commit.c \
       src/commands/log.c \
       src/commands/checkout.c \
       src/commands/status.c \
       src/commands/tag.c \
       src/utils/utils.c

OBJS = $(SRCS:.c=.o)

zit: $(OBJS)
	$(CC) $(CFLAGS) -o zit $(OBJS)

clean:
	rm -f zit $(OBJS)
