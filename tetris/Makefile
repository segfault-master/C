FLAGS	=	
NAME	=	tetris
SRCS	=	tetris.c		\
			tetromino_util.c\
			const_util.c
OBJ		=	$(SRCS:.c=.o)
HEADER	=	./
LIBS    = -lSDL2

$(NAME):
			gcc -c $(FLAGS) $(SRCS) -I $(HEADER)
			gcc -o $(NAME) $(OBJ) $(LIBS)
			

all:		$(NAME)

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean	all

.PHONY:		clean
			fclean