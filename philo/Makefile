NAME = philo

SRC_DIR := .

SRCS = \
	main.c\
	philo.c\
	tools.c\

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

BUILD_DIR := .build

CC := gcc
CFLAG := -Wall -Wextra -Werror
PTHREAD := -pthread

LIBS = $(PTHREAD)

RM := rm -rf
MAKEFLAG += --no-print-directory
DIR_DUP = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(LOCKS_RULE) $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	$(info CREATED $(NAME))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CCFLAGS) -c $< -o $@
	$(info CREATED $@)

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all