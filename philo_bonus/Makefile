NAME = philo_bonus

SRC_DIR := .

SRCS = \
	main.c\
	philo_bonus.c\

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

BUILD_DIR := .build

CC := gcc
CFLAG := -Wall -Wextra -Werror
PTHREAD := -pthread

TOOLS = tools
TOOLS_DIR = ../tools
TOOLS_RULE = $(TOOLS_DIR)/lib$(TOOLS).a
TOOLS_L = -L $(TOOLS_DIR)
TOOLS_H = -I $(TOOLS_DIR)
TOOLS_A = -l $(TOOLS)

INCLUDES = $(TOOLS_H)
LIBS_DIR = $(TOOLS_L)
LIBS = $(PTHREAD) $(TOOLS_A)

RM := rm -rf
MAKEFLAG += --no-print-directory
DIR_DUP = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(LOCKS_RULE) $(TOOLS_RULE) $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $(NAME) $(INCLUDES) $(LIBS_DIR) $(LIBS)
	$(info CREATED $(NAME))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CCFLAGS) -c $< -o $@
	$(info CREATED $@)

$(TOOLS_RULE):
	echo make $(TOOLS_RULE)
	@$(MAKE) -C $(TOOLS_DIR)
	$(info CREATED $@)

clean:
	@$(MAKE) -C $(TOOLS_DIR) clean
	$(RM) $(BUILD_DIR)


fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(TOOLS_DIR) fclean

re:
	$(MAKE) fclean
	$(MAKE) all