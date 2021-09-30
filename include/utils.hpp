#ifndef UTILS_HPP
# define UTILS_HPP

#include <deque>
#include <stdlib.h>
#include <string>
#include <iostream>

#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#endif
