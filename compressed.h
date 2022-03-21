#ifndef COMPRESSED_H_   /* Include guard */
#define COMPRESSED_H_

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



void delete_tree(struct compressed **root);

void recourse_print_tree(struct compressed *tmp, int number, char length);

void print_tree(struct compressed *root);

struct compressed* create_top(unsigned int number, char key, char length);

struct compressed* build_top(struct data info, struct compressed *add_ver);

struct compressed* remake(struct compressed *tmp);

unsigned char length_prefix(struct compressed *tmp, struct data info, char *flag);

void break_top(struct compressed **tmp, struct data info, char length, char bit);

void add_in_compressed_tree(struct compressed **head, struct data info);

void insert_in_compressed_tree(struct compressed **head, struct data info);

char search_in_compressed_tree(struct compressed *head, struct data info);

void del_from_compressed_tree(struct compressed **head, struct data info);

void delete_from_compressed_tree(struct compressed **head, struct data info);



#endif // COMPRESSED_H_