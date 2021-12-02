# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiwchoi <jiwchoi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/07 15:47:51 by jiwchoi           #+#    #+#              #
#    Updated: 2021/11/13 17:32:39 by jiwchoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET		= minishell

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra #-fsanitize=address -g
#CFLAGS		= -fsanitize=address -g
RM			= rm -rf

LIBFT_DIR	= ./libft/
LIBFT_FILE	= libft.a

INCS_DIR	= ./includes/
SRCS_DIR	= ./srcs/
OBJS_DIR	= ./objs/

SRC			= error.c \
			  main.c \
			  parse_command.c \
			  parse_line.c \
			  replace.c \
			  utils_cmd.c \
			  utils_redir.c \
			  	signal.c \
				redirect.c \
				exe_process.c \
				exe_env.c \
				exe_cd.c \
				exe_echo.c \
				exe_pwd.c \
				exe_export.c \
				exe_unset.c \
				exe_exit.c \
				utils.c \
				builtin.c \
				list.c \
				add_export.c


SRCS		= $(addprefix $(SRCS_DIR), $(SRC))
OBJS		= $(addprefix $(OBJS_DIR), $(SRC:.c=.o))

$(TARGET) : $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -I $(INCS_DIR) -L$(LIBFT_DIR) -lft -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include 
	#cluster : -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include 
	#home : -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS_DIR) -I ~/.brew/opt/readline/include
	#cluster : -I ~/.brew/opt/readline/include 
	#home : -I/usr/local/opt/readline/include

all : $(TARGET)

clean :
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS_DIR)

fclean : clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(TARGET)

re : clean all

bonus : 

.PHONY : all clean fclean re bonus
