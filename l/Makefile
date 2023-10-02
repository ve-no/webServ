MAIN_SRC = ${addprefix src/, main.cpp Webserv.cpp autoindex.cpp Response.cpp Request.cpp}

# INC_DIR = inc

# INC = ${addprefix inc/, Webserv.hpp Request.hpp main.hpp}

SRC = ${MAIN_SRC}

NAME = webserv

CC = c++

CFLAGS = -Wall -Wextra -Werror  -fsanitize=address -g -std=c++98


all: ${NAME}

${NAME}: ${SRC} 
	${CC} ${CFLAGS} ${SRC}  -o ${NAME}

clean:
	rm -rf ${NAME}

fclean: clean

re: fclean all

.PHONY: all clean fclean re
