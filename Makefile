# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkalia <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/23 14:12:11 by jkalia            #+#    #+#              #
#*   Updated: 2017/05/05 21:24:15 by jkalia           ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME		:= ftdb
CLIENT		:= client
TEST		:= test
CC			:= gcc
CFLAGS		+= -Wall -Wextra -Werror
CFLAGS		+= -I includes/ -I libft/includes/
LDFLAGS		:= -L libft/ -lft

LIBFT		:= libft/libft.a

FILES		:= db_dispatch db_delete db_reply db_init db_set db_load \
			db_murmurhash db_get db_server db_getall db_files db_getval
SRC		:= $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ		:= $(SRC:.c=.o)

CLIENTFILES	:= db_client_main
CLIENTSRC	:= $(addprefix util/, $(addsuffix .c, $(CLIENTFILES)))
CLIENTOBJ	:= $(CLIENTSRC:.c=.o)

TESTFILES	:= db_test_main db_test_buff
TESTSRC		:= $(addprefix util/, $(addsuffix .c, $(TESTFILES)))
TESTOBJ		:= $(TESTSRC:.c=.o)


.PHONY = all clean fclean clean re

all: $(NAME) $(CLIENT) $(TEST)

$(LIBFT):
	@make -C libft	

$(OBJ): %.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(LDFLAGS) -o $@ $^
	@echo "\033[32mCreated FTDB\033[0m"

$(CLIENTOBJ): %.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(CLIENT): $(LIBFT) $(CLIENTOBJ)
	@$(CC) $(LDFLAGS) -o $@ $^
	@echo "\033[32mCreated CLIENT\033[0m"

$(TESTOBJ): %.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(TEST): $(LIBFT) $(TESTOBJ)
	@$(CC) $(LDFLAGS) -o $@ $^
	@echo "\033[32mCreated TEST\033[0m"

clean:
	@make -C libft clean
	@rm -f $(OBJ) $(CLIENTOBJ) $(TESTOBJ)
	@echo "\033[32mRemoved Object Files\033[0m"

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME) $(CLIENT) $(TEST)
	@echo "\033[32mRemoved Executable\033[0m"

re: fclean all
