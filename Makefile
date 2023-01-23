NAME = minishell

SRC = src/main.c src/lexer.c src/token.c src/parser.c src/execution.c src/exe.c

OBJ = ${SRC:%.c=%.o}

FLAGS =  -Wall -Wextra -Werror  #-fsanitize=address

READLINE = -lreadline

%.o:%.c
	gcc $(FLAGS)  -c $< -o $@

all : $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS)  $(OBJ) lib_ft/libft.a $(READLINE)  -o $(NAME)

clean :
	rm -rf $(OBJ) 

fclean : clean
	rm -rf  $(NAME) 
re : fclean all
