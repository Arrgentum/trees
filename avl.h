#ifndef AVL_H_   /* Include guard */
#define AVL_H_


#include"top.h"

struct data{
	unsigned int number1;
	unsigned int number2;
	char mask1;
	char mask2;
	char key_range1;
	char key_range2;
};

struct avl
{
	unsigned int number;
	char mask;
	char key_top;
	char key_range;
	unsigned char height;
	struct avl* left;
	struct avl* right;
};


#endif // AVL_H_
