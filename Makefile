CC = gcc
CFLAGS = -O3 -Wall -Wextra -Iinclude

SRCS = src/zit.c \
       src/core/repository.c \
       src/commands/init.c \
       src/commands/add.c \
       src/commands/commit.c \
       src/commands/log.c \
       src/commands/checkout.c \
       src/commands/status.c \
       src/commands/tag.c \
       src/commands/cat_file.c \
       src/commands/check_ignore.c \
       src/commands/ls_files.c \
       src/commands/hash_object.c \
       src/commands/ls_tree.c \
       src/commands/rev_parse.c \
       src/commands/rm.c \
       src/commands/show_ref.c \
       src/utils/utils.c

OBJS = $(SRCS:.c=.o)

zit: $(OBJS)
	$(CC) $(CFLAGS) -o zit $(OBJS)

clean:
	rm -f zit $(OBJS)
