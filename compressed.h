#ifndef COMPRESSED_H_   /* Include guard */
#define COMPRESSED_H_

#include"top.h";

struct compressed{
	unsigned int number;
	char key;
	char length;
	struct scalar left;
	struct scalar right;
};

struct data{
	unsigned int number;
	char key;
	char length;
	char mask;
}

#endif // COMPRESSED_H_