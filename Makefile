# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 22:02:04 by guillsan          #+#    #+#              #
#    Updated: 2025/10/14 20:13:45 by guillsan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# if TEST_BONUS is set to 1, compile tests with HAVE_BONUS to register bonus groups
ifeq ($(TEST_BONUS),1)
CFLAGS += -DHAVE_BONUS
endif

TESTS_DIR = tests

# wildcard all test sources
ALL_TEST_SRCS = $(wildcard $(TESTS_DIR)/*.c)

# explicitly list bonus test sources
BONUS_TEST_SRCS = 						\
    $(TESTS_DIR)/test_lstnew.c			\
    $(TESTS_DIR)/test_lstadd_front.c	\
    $(TESTS_DIR)/test_lstsize.c			\
    $(TESTS_DIR)/test_lstlast.c			\
    $(TESTS_DIR)/test_lstadd_back.c		\
    $(TESTS_DIR)/test_lstdelone.c		\
    $(TESTS_DIR)/test_lstclear.c		\
    $(TESTS_DIR)/test_lstiter.c			\
    $(TESTS_DIR)/test_lstmap.c

# If TEST_BONUS != 1, filter out bonus tests from the compile list
TEST_SRCS = $(ALL_TEST_SRCS)
ifeq ($(TEST_BONUS),1)
# include bonus tests (already present in ALL_TEST_SRCS if they live in tests/)
# If for some reason bonus files are in a different dir, you can append $(BONUS_TEST_SRCS)
else
TEST_SRCS := $(filter-out $(BONUS_TEST_SRCS), $(TEST_SRCS))
endif

TEST_OBJS = $(TEST_SRCS:.c=.o)
ORCH = tests_libft.c
NAME = libft_tests

# libft.a should be present in this directory (run_tests.sh copies it)
LIBFT_ARCHIVE = libft.a
INCLUDES = -I.

RM = rm -f

all: $(NAME)

$(NAME): $(TEST_OBJS) $(ORCH) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_OBJS) $(ORCH) -L. -lft -lbsd -o $(NAME)

# compile test sources
$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(TESTS_DIR) -I. -c $< -o $@

clean:
	@$(RM) $(TEST_OBJS)
	@$(RM) $(TESTS_DIR)/*.o

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT_ARCHIVE)
	@$(RM) libft_test

re: fclean all
