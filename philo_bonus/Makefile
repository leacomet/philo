# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acomet <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 16:30:18 by acomet            #+#    #+#              #
#    Updated: 2023/07/08 02:36:45 by acomet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_bonus

CC			=	clang

CFLAGS		=	-pthread -Wall -Wextra -Werror -g

BNS			=	bonus
BUILD		=	build

SRCS		= 	$(BNS)/philo_bonus.c \
				$(BNS)/fill_params_bonus.c \
				$(BNS)/fill_philo_bonus.c \
				$(BNS)/routines_bonus.c \
				$(BNS)/sleep_bonus.c \
				$(BNS)/checker_philo_bonus.c \
				$(BNS)/utils_bonus.c \

OBJS 		= 	$(SRCS:$(BNS)/%.c=$(BUILD)/%.o)

all: $(NAME)
.PHONY: all

$(BUILD)/%.o: $(BNS)/%.c
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
