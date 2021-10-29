NAME 				=	libft.a

INCLUDES			=	-I ../includes/

OBJS_DIR			=	./objs/
SRCS_DIR			=	./srcs/

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

SRCS_NAME			=	ft_calloc.c			\
						ft_itoa.c			\
						ft_split.c			\
						ft_strchr.c			\
						ft_strdup.c			\
						ft_strjoin.c		\
						ft_strlen.c			\
						ft_strncmp.c		\
						ft_strncmp_old.c	\
						ft_substr.c			\

OBJS_NAME			=	$(SRCS_NAME:.c=.o)

SRCS				=	$(addprefix $(SRCS_DIR), $(SRCS_NAME))
OBJS				=	$(addprefix $(OBJS_DIR), $(OBJS_NAME))

CC					=	gcc

CFLAGS				=	-Wall -Wextra -Werror

all:					$(NAME)

$(NAME):				$(OBJS)
						@echo "$(F_WALL) $(YELLOW)COMPILATION LIBFT...\t\t\t\t$(B_WALL)"
						@ar -rc		$(NAME)			$(OBJS)
						@ranlib		$(NAME)
						@echo	"$(F_WALL) $(GREEN)OK\t\t\t\t\t\t$(B_WALL)"

$(OBJS):				$(SRCS)
						@($(CC)		$(INCLUDES) -c	$(SRCS))
						@(mkdir 	-p 				$(OBJS_DIR))
						@(mv 		$(OBJS_NAME)	$(OBJS_DIR))

clean:
						@(rm -rf	$(OBJS))

fclean:					clean
						@(rm -rf	$(NAME))
						@echo	"$(F_WALL) $(BRIGHT_BLUE)REMOVING libft.a\t\t\t\t$(B_WALL)"
						@echo	"$(F_WALL) $(GREEN)OK\t\t\t\t\t\t$(B_WALL)"
						@(rm -rf	objs)
						@echo	"$(F_WALL) $(BRIGHT_BLUE)REMOVING ./libft/objs\t\t\t\t$(B_WALL)"
						@echo	"$(F_WALL) $(GREEN)OK\t\t\t\t\t\t$(B_WALL)"
						@echo	"$(F_WALL)$(PURPLE)=====$(BRIGHT_BLUE) LIBFT DIRECTORY CLEANED $(GREEN)SUCCESSFULLY$(PURPLE)=====$(B_WALL)"

re:						fclean all

.PHONY:					clean fclean re all