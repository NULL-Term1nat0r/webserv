#!/bin/bash

# Initialize arrays for class names and source files
class_names=()
source_files=()

echo "
   ________                    ______                __
  / ____/ /___ ___________    / ____/_______  ____ _/ /_____  _____
 / /   / / __  / ___/ ___/   / /   / ___/ _ \/ __  / __/ __ \/ ___/
/ /___/ / /_/ (__  |__  )   / /___/ /  /  __/ /_/ / /_/ /_/ / /
\____/_/\__,_/____/____/____\____/_/   \___/\__,_/\__/\____/_/
                      /_____/
"

echo "Script completed successfully."

header_string=$(cat <<EOF
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estruckm <estruckm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:01:04 by estruckm          #+#    #+#             */
/*   Updated: 2023/09/12 12:02:31 by estruckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
EOF
)

while true; do
    read -p "Enter the class name without .hpp (or 'done' to finish): " user_input
    if [ "$user_input" = "done" ]; then
        break
    fi

while true; do
    read -p "Do you want a main.cpp and Makefile and Header.h for your new generated classes ?: " user_input2

    # Compare user input to two strings
    if [ "$user_input2" == "yes" ]; then
        echo "main.cpp, Header.h and Makefile will be generated"
        check=0
        break  # Exit the loop
    elif [ "$user_input2" == "no" ]; then
        echo "main.cpp, Header.h and Makefile will not be generated."
        check=1
        break  # Exit the loop
    else
        echo "provide valid input for setting up yout structure"
    fi
done

    # Append class name to the array
    class_names+=("$user_input")

    # Create .hpp and .cpp files for each class
    cat <<EOF > "${user_input}.hpp"

#ifndef ${user_input}_HPP
#define ${user_input}_HPP

#include <string>
#include <iostream>

class ${user_input}
{
private:
	// Class members

public:
	${user_input}();
	${user_input}(std::string type);
	${user_input}(const ${user_input} &other);
	~${user_input}();
	${user_input} &operator=(const ${user_input} &other);
};

#endif
EOF

    cat <<EOF > "${user_input}.cpp"

#include "Header.h"
#include "${user_input}.hpp"

// Implement class methods here

${user_input}::${user_input}()
{
	std::cout << "${user_input} default constructor called" << std::endl;
}

${user_input}::${user_input}(std::string type)
{
	std::cout << "${user_input} constructor with type called" << std::endl;
}

${user_input}::${user_input}(const ${user_input} &other)
{
	*this = other;
	std::cout << "${user_input} copy constructor called" << std::endl;
}

${user_input}::~${user_input}()
{
	std::cout << "${user_input} destructor called" << std::endl;
}

${user_input} &${user_input}::operator=(const ${user_input} &other)
{
	if (this == &other)
		return *this;
	std::cout << "${user_input} copy assignment constructor called" << std::endl;
	return *this;
}
EOF

    # Append source file to the array
    source_files+=("${user_input}.cpp")

    # Append include statement to the includes array
    includes+=("#include \"${user_input}.hpp\"")
done

# Close Header.h
if [ $check == 0 ]; then
cat <<EOF > "Header.h"
#ifndef HEADER_HPP
#define HEADER_HPP

#include <string>
#include <iostream>

#endif
EOF
fi

# Create Makefile
if [ $check == 0 ]; then
cat <<EOF > "Makefile"

NAME		:= program

SRCS		:= ${source_files[@]} main.cpp

OBJS		:= \$(SRCS:.cpp=.o)

CFLAGS		:= -Wall -Werror -Wextra -std=c++98

CC			:= c++

\$(NAME): \$(OBJS)
	\$(CC) \$(CFLAGS) \$^ -o \$@

%.o: %.cpp
	\$(CC) \$(CFLAGS) -c \$< -o \$@

.PHONY: clean all re fclean

clean:
	rm -rf \$(OBJS)

fclean: clean
	rm -rf \$(NAME)

re: fclean all

all: \$(NAME)
EOF
fi
# Create main.cpp with the generated includes
if [ $check == 0 ]; then
cat <<EOF > "main.cpp"
#include "Header.h"
${includes[@]} // Include all generated .hpp files

int main(){
	return 0;
}
EOF
fi

echo "You entered the following class names:"
for class_name in "${class_names[@]}"; do
    echo "$class_name"
done