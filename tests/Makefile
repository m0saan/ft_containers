# ************************************************************************************************** #
#                                                                                                    #
#                                                         :::   ::::::::   ::::::::  :::::::::::     #
#    Makefile                                          :+:+:  :+:    :+: :+:    :+: :+:     :+:      #
#                                                       +:+         +:+        +:+        +:+        #
#    By: mamoussa <mamoussa@student.1337.ma>           +#+      +#++:      +#++:        +#+          #
#                                                     +#+         +#+        +#+      +#+            #
#    Created: Invalid date        by                 #+#  #+#    #+# #+#    #+#     #+#              #
#    Updated: 2021/10/13 11:44:22 by moboustt         ###   ########.fr        #
#                                                                                                    #
# ************************************************************************************************** #

COMPILER = clang++
FLAGS = --std=c++98 -fsanitize=address -g3

vector:
	@$(COMPILER) $(FLAGS)	Vector_tests.cpp -o vector.out 

map:
	@$(COMPILER) $(FLAGS) Map_tests.cpp -o map.out 
stack:
	@$(COMPILER) $(FLAGS) Stack_tests.cpp -o stack.out 

clean:
	rm -f vector.out map.out
