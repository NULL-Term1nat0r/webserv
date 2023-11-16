NAME = webserv

#SRC = ${shell echo src/*.cpp}

SRC =   src/client.cpp \
	  	src/config.cpp \
		src/postRequest.cpp \
		src/getRequest.cpp \
		src/deleteRequest.cpp \
		src/serverConfig1.cpp \
		src/serverConfig2.cpp \
		src/request.cpp \
		src/response.cpp \
		src/server.cpp \
		src/Eike.cpp \
		src/parsing.cpp \
		src/cgiRequest.cpp




OBJ = $(patsubst %.cpp, %.o, $(SRC))

HEADER = ${shell echo includes/*.hpp}

HEADER = includes/config.hpp \
         includes/postRequest.hpp \
         includes/getRequest.hpp \
         includes/deleteRequest.hpp \
         includes/serverConf.hpp \
         includes/request.hpp \
         includes/response.hpp \
         includes/server.hpp \
         includes/parsing.hpp \
         includes/cgiRequest.hpp \
         includes/Header.h

CC =  c++

FLAGS = -g -Wextra -Wall -std=c++98

all: $(NAME)

$(NAME) : $(OBJ) # $(HEADER)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

src/%.o: src/%.cpp $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re