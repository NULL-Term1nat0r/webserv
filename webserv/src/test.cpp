#include <iostream>
#include <cstring>
#include <cstdlib>
#include <dirent.h>

void test(int *socket) {
	*socket = 2;
}
int main() {
	int socket = 1;
	int *socketPointer = &socket;
	printf("socket: %d\n", *(&socket));
	printf("socket: %d\n", *(socketPointer));
	test(&socket);
	printf("socket: %d\n", socket);

}
