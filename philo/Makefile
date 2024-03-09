NAME = philo

SRC_DIR := .

SRCS = \
	main.c\
	philo.c\
	tools.c\

BUILD_DIR := .build

SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CC := gcc
CFLAG := -Wall -Wextra -Werror
PTHREAD := -pthread

RM := rm -rf
DIR_DUP = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $(NAME) $(PTHREAD)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(DIR_DUP)
	$(CC) $(CFLAG) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all
