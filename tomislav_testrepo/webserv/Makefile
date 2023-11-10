# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnguyen <dnguyen@student.42wolfsburg.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 17:24:49 by vfuhlenb          #+#    #+#              #
#    Updated: 2023/09/14 09:17:00 by dnguyen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv
TESTSERV = testserv

CC = c++

CFLAGS = -Wall -Wextra -std=c++98 -g

SRCS =	src/Eike.cpp \
		src/request.cpp \
		src/parsing.cpp \
		src/response.cpp \
		src/server.cpp \
		src/server2.cpp \
		src/server3.cpp \
		src/config.cpp \
		src/getRequest.cpp \
		src/postRequest.cpp \
		src/cgi.cpp \
		src/deleteRequest.cpp

OBJS = ${SRCS:.cpp=.o}

RM = rm -rf

MKDIR = mkdir -p

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

testing: $(TESTSERV)

$(TESTSERV): $(OBJS)
	$(CC) $(CFLAGS) -D Debug=1 -o $(NAME) $(OBJS)
	@echo "Testserv created: \033[32;1m./$(TESTSERV)\033[0m"

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "executable created: \033[32;1m./$(NAME)\033[0m"

clean:
	$(RM) $(OBJS)
	@echo "\033[34mclean success\033[0m"

fclean:
	$(RM) $(OBJS) $(NAME) $(TESTSERV) siegeResult
	@echo "\033[34mfclean success\033[0m"

re: fclean all

run: fclean all
	$(RM) $(OBJS) $(TESTSERV) siegeResul
	./webserv

test:testing
	./webserv ./data/conf/test.conf

siege:
	./tests/siege10.sh

siegebig:
	./tests/siege10000.sh

.PHONY: all clean fclean re build start stop
.NOTPARALLEL: all clean fclean re build start stop