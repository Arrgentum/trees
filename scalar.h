#ifndef SCALAR_H_   /* Include guard */
#define SCALAR_H_

#include"top.h";

struct scalar{
	unsigned char number;
	char key;
	char length;
	struct scalar left;
	struct scalar right;
};

struct data{
	unsigned char number;
	char key;
	char length;
	char mask;
}

#endif // SCALAR_H_