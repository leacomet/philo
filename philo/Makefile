# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acomet <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 16:30:18 by acomet            #+#    #+#              #
#    Updated: 2023/07/08 00:03:08 by acomet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CC			=	clang

CFLAGS		=	-pthread -Wall -Wextra -Werror -g

MAND		=	mandatory
BUILD		=	build

SRCS		= 	$(MAND)/philo.c \
				$(MAND)/fill_params.c \
				$(MAND)/fill_philo.c \
				$(MAND)/routines.c \
				$(MAND)/sleep.c \
				$(MAND)/checker_philo.c \
				$(MAND)/utils.c \

OBJS 		= 	$(SRCS:$(MAND)/%.c=$(BUILD)/%.o)

all: $(NAME)
.PHONY: all

$(BUILD)/%.o: $(MAND)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(BUILD) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
.PHONY: clean

fclean: clean
	rm -f $(NAME)
.PHONY: fclean

run3:
	ls

re: fclean all
.PHONY: re
