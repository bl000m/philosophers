# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 11:56:12 by mpagani           #+#    #+#              #
#    Updated: 2023/01/30 14:50:48 by mpagani          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	= philo

# mandatory srcs / obj files
SRCS	= main.c error_management.c settings.c utils.c memory.c lifecycle.c \
		checking_the_end.c time_passing.c activities.c lifecycle_utils.c

OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

# compile
CC 			= cc -pthread
CFLAGS 		= -Wall -Werror -Wextra

# directories
SRCS_DIR	= ./srcs
INCS_DIR	= ./includes
OBJDIR 		= ./obj

# others
RM 			= rm -rf

all: obj $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -lm -o $(NAME)

$(OBJDIR)/%.o: $(SRCS_DIR)/%.c Makefile $(INCS_DIR)/philo.h
	$(CC) $(CFLAGS) -I $(INCS_DIR) -c $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
