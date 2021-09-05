NAME	=	test

INCLUDES	= -I ./includes/ -I ../includes/

OBJS_DIR	=	./objs/
SHELL_DIR	=	../srcs/

SHELL_SRCS	=	utils_for_array_3.c	\

SHELL_OBJS	=	$(SHELL_SRCS:.c=.o)

SRCS_NAME	=	main.c	\

# shell	srcs with path
SHELL_SRCSPATH	=	$(addprefix $(SHELL_DIR), $(SHELL_SRCS))

# all objects
OBJS_NAME	=	$(SRCS_NAME:.c=.o) $(SHELL_OBJS)

# path to dir with all objects
OBJS_PATH	= $(addprefix $(OBJS_DIR), $(OBJS_NAME))

CC	= gcc

all:
	@$(CC)	$(INCLUDES)	-c $(SRCS_NAME) $(SHELL_SRCSPATH)
	@$(MAKE)	-C			../libft/
	@mkdir -p	$(OBJS_DIR)
	@mv		$(OBJS_NAME)	$(OBJS_DIR)
	@$(CC) ../libft/libft.a $(OBJS_PATH) -o $(NAME)

clean:
	rm -rf $(OBJS_PATH)

fclean:		clean
	rm -rf $(NAME)
	rm -rf $(OBJS_DIR)

.PHONY: clean fclean all