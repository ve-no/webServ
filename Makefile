SRC = ${addprefix src/, main.cpp ConfigFile.cpp Location.cpp ServConf.cpp ParseConfigFile.cpp Webserv.cpp}

# REQUEST_SRC = ${addprefix src/request/, Request.cpp RequestParser.cpp}

# TEST_SRC = ${addprefix src/, example.cpp}

INC_DIR = inc

INC = ${addprefix inc/, ConfigFile.hpp Location.hpp ServConf.hpp ParseConfigFile.hpp Webserv.hpp}

# SRC = ${MAIN_SRC} ${REQUEST_SRC}

NAME = webserv

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98


all: ${NAME}

${NAME}: ${SRC} ${INC}
	${CC} ${CFLAGS} ${SRC} -I ${INC_DIR} -o ${NAME}

clean:
	rm -rf ${NAME}

fclean: clean

re: fclean all

.PHONY: all clean fclean re
