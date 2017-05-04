# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkalia <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/23 14:12:11 by jkalia            #+#    #+#              #
#*   Updated: 2017/05/04 11:21:26 by jkalia           ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME		:= ftdb
CLIENT		:= client
CC		:= gcc
CFLAGS		+= -Wall -Wextra -Werror
CFLAGS		+= -I includes/ -I libft/includes/
LDFLAGS		:= -L libft/ -lft

LIBFT		:= libft/libft.a

FILES		:= db_dispatch db_delete db_reply db_init db_set db_load \
			db_murmurhash db_get db_server db_getall db_files db_getval
SRC		:= $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ		:= $(SRC:.c=.o)

CLIENTFILES	:= db_client
CLIENTSRC	:= $(addprefix src/, $(addsuffix .c, $(CLIENTFILES)))
CLIENTOBJ	:= $(CLIENTSRC:.c=.o)

.PHONY = all clean fclean clean re

all: $(NAME) $(CLIENT)

$(LIBFT):
	@make -C libft	

$(OBJ): %.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@
	@echo "\033[32mCompiled Project Object Files\033[0m"

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(LDFLAGS) -o $@ $^
	@echo "\033[32mCreated Executable\033[0m"

$(CLIENTOBJ): %.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(CLIENT): $(LIBFT) $(CLIENTOBJ)
	@$(CC) $(LDFLAGS) -o $@ $^
	@echo "\033[32mCompiled Client\033[0m"

clean:
	@make -C libft clean
	@rm -rf $(OBJ) $(CLIENTOBJ)
	@echo "\033[32mRemoved Object Files\033[0m"

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME) client
	@echo "\033[32mRemoved Executable\033[0m"

re: fclean all
