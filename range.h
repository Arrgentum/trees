#ifndef RANGE_H_   /* Include guard */
#define RAHGE_H_

#include"top.h";


struct range{
	unsigned int begin;
	unsigned int end;
	unsigned int max;
	unsigned char height;
	char key;
	struct range *left;
	struct range *right;
};


void small_left_rotation(struct range** head);

void small_right_rotation(struct range** head);

void big_left_rotation(struct range** head);

void big_right_rotation(struct range** head);

void balanced_range_tree(struct range **head);

void add_in_range_tree(struct range **head, struct range *new_elem);

void insert_in_range_tree(struct range **head, struct top32 elem)

int search_in_range_tree(struct range **head, int number, char *key);

void delete_elem(struct range **head);

void del_from_range_tree(struct range** head, struct range *elem);

void delete_from_range_tree(struct range** head, struct top32 elem);

#endif // RANGE_H_
