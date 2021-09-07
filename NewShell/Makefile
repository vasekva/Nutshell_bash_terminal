NAME		=	minishell

INCLUDES		=	-I ./includes/
LIBFT_DIR		=	./libft/
LIBRARY			=	./libft/libft.a
SRCS_DIR		=	./srcs/
COMMANDS_DIR	=	./srcs/commands/
OBJS_DIR		=	./objs/

SRCS_NAME		=	get_next_line.c		\
					exception.c			\
					main.c				\
					deff_curr_cmd.c		\
					array_resize.c		\
					utils_for_array_1.c	\
					utils_for_array_2.c	\
					utils_for_array_3.c	\
					init.c				\

COMMANDS_SRCS	=	ft_echo.c		\
					ft_echo_utils.c	\
                 	ft_cd.c			\
                  	ft_pwd.c		\
                  	ft_export.c		\
					ft_unset.c		\
					ft_env.c		\
					ft_env_utils.c	\
					ft_execve.c		\
					ft_exit.c		\

OBJS_NAME	=	$(SRCS_NAME:.c=.o) $(COMMANDS_SRCS:.c=.o)

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_NAME)) $(addprefix $(COMMANDS_DIR), $(COMMANDS_SRCS))
OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_NAME))

CC			=	gcc -g
CFLAGS		=	-Wall -Wextra -Werror -g

OS_NAME	= $(shell uname -s | tr A-Z a-z)

ifeq	($(OS_NAME), linux)
			RL_FLAGS	= -lreadline
else
			RL_FLAGS	=	-L/Users/$(USER)/.brew/Cellar/readline/8.1/lib -lreadline
endif

.PHONY:			all	clean	fclean	re

all: 			$(NAME)

$(NAME):		$(OBJS)
				@echo "\033[1m\033[35m===	COMPILATION MINISHELL...			\033[1m==="
				@$(MAKE)	-C			$(LIBFT_DIR)
				@$(CC)	$(LIBRARY)	$(OBJS)	-o $(NAME) $(RL_FLAGS)
				@echo "\033[1m\033[35m===	MINISHELL COMPILATION WAS \033[32mSUCCESFULL		\033[1m\033[35m===\n"

$(OBJS):		$(SRCS)
				@$(CC)	$(INCLUDES)	-c	$(SRCS)
				@mkdir	-p				$(OBJS_DIR)
				@mv		$(OBJS_NAME)	$(OBJS_DIR)

test:
				@echo "\033[1m\033[35m===	COMPILATION TESTS...			\033[1m==="
				@$(MAKE)	-C			./test_dir
				@echo "\033[1m\033[35m===	TESTS COMPILATION WAS \033[32mSUCCESFULL		\033[1m\033[35m===\n"

clean:
				@echo "\033[1m\033[35m===	CLEANING ALL OBJS FILES ...			\033[1m==="
				@echo "\033[1m\033[36m	===	CLEANING LIBFT OBJS ...				\033[1m==="
				@$(MAKE)	clean	-C		$(LIBFT_DIR)
				@echo "\033[1m\033[36m	===	CLEANING LIBFT OBJS \033[32mOK				\033[36m\033[1m==="
				@echo "\033[1m\033[36m	===	CLEANING MINISHELL OBJS ...			\033[1m==="
				@rm -rf	$(OBJS)
				@echo "\033[1m\033[36m	===	CLEANING MINISHELL OBJS \033[32mOK			\033[1m\033[36m==="
				@echo "\033[1m\033[35m===	ALL OBJS FILES HAVE BEEN CLEANED \033[32mSUCCESSFULLY	\033[35m\033[1m===\n"

fclean:			clean
				@echo "\033[1m\033[35m===	DELETING DIRECTORIES AND OTHER FILES...		===\033[0m"
				@$(MAKE)	fclean	-C		$(LIBFT_DIR)
				@rm -rf	$(NAME)
				@echo "\033[1m\033[36m	===	REMOVING minishell 	\033[32mOK			\033[1m\033[36m==="
				@rm -rf	$(OBJS_DIR)
				@echo "\033[1m\033[36m	===	REMOVING ./objs		\033[32mOK			\033[1m\033[36m==="
				@echo	"\033[1m\033[35m===	ALL CREATED FILES HAVE BEEN \033[32mDELETED SUCCESSFULLY \033[1m\033[35m==="

re:				fclean all
