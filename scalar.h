#ifndef SCALAR_H_   /* Include guard */
#define SCALAR_H_

#include"top.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct scalar{
	unsigned char number;
	char key;
	char length;
	struct scalar *left;
	struct scalar *right;
};

struct data{
	unsigned int number;
	char key;
	char length;
	char mask;
};



void delete_tree(struct scalar **root);

void recourse_print_tree(struct scalar *tmp, int number, char length);

void print_tree(struct scalar *root);

struct scalar* create_top(unsigned char number, char key, char length);

struct scalar* build_top(struct data info, struct scalar *add_ver);

struct scalar* remake(struct scalar *tmp);

unsigned char length_prefix(struct scalar *tmp, struct data info, char *flag);

void break_top(struct scalar **tmp, struct data info, char length, char bit);

void add_in_scalar_tree(struct scalar **head, struct data info);

void insert_in_scalar_tree(struct scalar **head, struct data info);

char search_in_scalar_tree(struct scalar *head, struct data info);

void del_from_scalar_tree(struct scalar **head, struct data info);

void delete_from_scalar_tree(struct scalar **head, struct data info)



#endif // SCALAR_H_