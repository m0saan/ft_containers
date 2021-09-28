NAME=a.out
CC=clang++
CFLAGS=-Wall
CPP_VERSION=-std=c++98
SRCS = Vector_test.cpp


all: $(NAME)

$(NAME): $(SRCS)
	@ $(CC) $(CPP_VERSION) $(CFLAGS) $(SRCS) -o $(NAME) -g3 -fsanitize=address

run:
	./$(NAME)
clean:
	@ rm -f $(NAME)

fclean : clean

re : fclean all
