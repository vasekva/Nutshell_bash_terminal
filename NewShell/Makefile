NAME		=	minishell

INCLUDES		=	-I ./includes/
LIBFT_DIR		=	./libft/
LIBRARY			=	./libft/libft.a
SRCS_DIR		=	./srcs/
COMMANDS_DIR	=	./srcs/commands/
PARSER_DIR		=	./srcs/parser/
OBJS_DIR		=	./objs/

BACK_GRAY		=	\033[47m
NORM			=	\033[0m
BOLD			=	\033[1m
GREEN			=	\033[32m
YELLOW			=	\033[33m
BLUE			=	\033[34m
PURPLE			=	\033[35m
BRIGHT_BLUE		=	\033[36m
NONE			=	\033[37m

WALL			=	$(BOLD)$(PURPLE)|
F_WALL			=	$(WALL)$(BOLD)
B_WALL			=	$(WALL)$(NORM)
ROOF			=	$(BOLD)$(WALL)===============================================$(WALL)

SRCS_NAME		=	exception.c			\
					main.c				\
					deff_curr_cmd.c		\
					utils_for_array.c	\
					utils_for_list.c	\
					init.c				\

COMMAND_SRCS	=	ft_echo.c		\
                 	ft_cd.c			\
                 	ft_cd_updir.c	\
                  	ft_pwd.c		\
                  	ft_export.c		\
					ft_unset.c		\
					ft_env.c		\
					ft_execve.c		\
					ft_exit.c		\

PARSER_SRCS		=	syntax_checker.c		\
					ft_split_arguments.c	\
					ft_preparser.c			\
					ft_lexer.c				\
					ft_lexer_utils.c		\


OBJS_NAME	=	$(SRCS_NAME:.c=.o) $(COMMAND_SRCS:.c=.o) $(PARSER_SRCS:.c=.o)

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_NAME)) $(addprefix $(COMMANDS_DIR), $(COMMAND_SRCS)) $(addprefix $(PARSER_DIR), $(PARSER_SRCS))
OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_NAME))

CC			=	gcc -g
CFLAGS		=	-Wall -Wextra -Werror -g

OS_NAME	= $(shell uname -s | tr A-Z a-z)

ifeq	($(OS_NAME), linux)
			RL_FLAGS	= -lreadline
else
			RL_FLAGS	=	-L/Users/$(USER)/.brew/Cellar/readline/8.1/lib -lreadline
endif

.PHONY:			all, clean, fclean, re, test

all: 			$(NAME)

$(NAME):		$(OBJS)
				@echo	"$(ROOF)"
				@echo	"$(F_WALL) $(YELLOW)COMPILATION MINISHELL...\t\t\t$(B_WALL)"
				@$(MAKE)	-C			$(LIBFT_DIR)
				@$(CC)	$(OBJS)	$(LIBRARY) -o $(NAME) $(RL_FLAGS)
				@echo	"$(ROOF)"
				@echo	"$(F_WALL)$(PURPLE)======\t $(GREEN)MINISHELL IS READY TO LAUNCH$(PURPLE)\t =======$(B_WALL)"

$(OBJS):		$(SRCS)
				@$(CC)	$(INCLUDES)	-c	$(SRCS)
				@mkdir	-p				$(OBJS_DIR)
				@mv		$(OBJS_NAME)	$(OBJS_DIR)

test:
				@echo "$(BOLD) $(YELLOW)COMPILATION TESTS..."
				@$(MAKE)	-C			./test_dir
				@echo "$(BOLD) $(PURPLE)TESTS COMPILATION HAS BEEN $(GREEN)SUCCESFULLY"
				@echo	"$(NONE)"

clean:
				@echo	"$(F_WALL)======= $(BLUE)REMOVING ALL OBJS FILES $(PURPLE)=======$(B_WALL)"
				@echo	"$(F_WALL) $(BRIGHT_BLUE)REMOVING LIBFT OBJS...\t\t$(B_WALL)"
				@$(MAKE)	clean	-C		$(LIBFT_DIR)
				@echo	"$(F_WALL) $(GREEN)OK\t\t\t\t\t$(B_WALL)"
				@echo	"$(F_WALL) $(BRIGHT_BLUE)REMOVING MINISHELL OBJS...\t\t$(B_WALL)"
				@rm -rf	$(OBJS)
				@echo	"$(F_WALL) $(GREEN)OK\t\t\t\t\t$(B_WALL)"
				@echo	"$(F_WALL)=============$(GREEN) SUCCESSFULLY $(BOLD)$(PURPLE)============$(B_WALL)"
				@echo	"$(NONE)"

fclean:			clean
				@echo	"$(ROOF)"
				@echo	"$(F_WALL)==== $(BLUE)DELETING DIRECTORIES AND BINARY FILES $(PURPLE)====$(B_WALL)"
				@($(MAKE)	fclean	-C		$(LIBFT_DIR))
				@rm -rf	$(NAME)
				@echo	"$(F_WALL) $(BRIGHT_BLUE)REMOVING minishell\t\t\t\t$(B_WALL)"
				@echo	"$(F_WALL) $(GREEN)OK\t\t\t\t\t\t$(B_WALL)"
				@(rm -rf	$(OBJS_DIR))
				@echo	"$(F_WALL) $(BRIGHT_BLUE)REMOVING ./objs\t\t\t\t$(B_WALL)"
				@echo	"$(F_WALL) $(GREEN)OK\t\t\t\t\t\t$(B_WALL)"
				@echo	"$(F_WALL)===$(BRIGHT_BLUE) ALL FILES HAVE BEEN $(GREEN)DELETED SUCCESSFULLY$(PURPLE)===$(B_WALL)"
				@echo	"$(ROOF)"
				@echo	"$(NONE)"

re:				fclean all
