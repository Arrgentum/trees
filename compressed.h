#ifndef COMPRESSED_H_   /* Include guard */
#define COMPRESSED_H_

#include"top.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct compressed{
	unsigned int number;
	char key;
	char length;
	struct compressed *left;
	struct compressed *right;
};

struct data{
	unsigned int number;
	char key;
	char length;
	char mask;
};

#endif // COMPRESSED_H_