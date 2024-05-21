NAME := weather_forecast.out
#TEST_MACRO :=NO_MACRO

SRC_DIR	:= src
OBJ_DIR := obj
SRCS := 			\
	main.c			\
	arg_parse.c		\
	time_helper.c		\
	data_downloader.c

SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries that need linking
LIBS := curl

CC := gcc
CFLAGS := -Wall -Wextra -Wconversion -g -I include/
LDLIBS := $(addprefix -l,$(LIBS))

RM := rm -f
MAKEFLAGS += --no-print-directory
DIR_DUP = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info CREATED $(NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(info CREATED $@)

#testing: fclean \
#	$(OBJS)
#	$(CC) $(OBJS) -o $(NAME) -D$(TEST_MACRO)
#	$(info CREATED $(NAME))

#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
#	$(DIR_DUP)
#	$(CC) $(CFLAGS) -D$(TEST_MACRO) -c -o $@ $<
#	$(CC) $(CFLAGS) -c -o $@ $<
#	$(info CREATED $@)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

.PHONY: clean fclean