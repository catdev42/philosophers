# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 15:27:14 by myakoven          #+#    #+#              #
#    Updated: 2024/04/29 19:00:02 by myakoven         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo

#-----------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#

HEADERS 	:= ./include
OBJDIR		:= ./obj
SRC     	:= *.c
OBJS     	:= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC      	:= cc
CFLAGS  	:= -pthread -g -Wall -Wextra -Werror

LIBNAME = libft.a
LIBDIR = ./libft
LIBFT = ./libft/libft.a


#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
.SILENT:

all: $(NAME)

runlibft:
	$(MAKE) -C $(LIBDIR)

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(HEADERS)

$(NAME): runlibft $(OBJS) 
#	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	$(CC) $(CFLAGS) *.c $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS)
	make -C $(LIBDIR) clean

fclean: clean
	rm -rf $(OBJDIR)
	rm -f $(NAME)
	make -C $(LIBDIR) fclean
	
re: fclean all

.PHONY: all clean fclean re
