#include <stdlib.h>

#include"range.h"


//создание одной вершины
struct range* create_top(int number1, int number2, char key)
{
	struct range *top = malloc(sizeof(struct range));
	top->begin = number1;
	top->end = number2;
	top->key = key;
	top->height = 1;
	top->left + NULL;
	top->rigth = NULL;
	return top;
}


void small_left_rotation(struct range** head)
{
	struct range* new_head = (*head)->rigth;
	(*head)->rigth = new_head->left;
	new_head->rigth = *head;
	*head = new_head;
}

void small_rigth_rotation(struct range** head)
{
	struct range *new_head = (*head)->left;
	(*head)->left = new_head->rigth;
	new_head->left = *head;
	*head = new_head;
}

void big_left_rotation(struct range** head)
{
	small_rigth_rotation( &((*head)->rigth) );
	small_left_rotation(head);
}

void big_rigth_rotation(struct range** head)
{
	small_left_rotation( &((*head)->left));
	small_rigth_rotation(head);
}

void balanced_range_tree(struct range **head)
{
	struct range *tmp = *head;
	if (  (tmp->rigth && tmp->left && tmp->left->height - tmp->rigth->height == 2)  ||  (tmp->rigth && !tmp->left && tmp->left->height == 2)){
		if ((tmp->left->rigth && tmp->left->left && tmp->left->left->height >= tmp->left->rigth->height)  ||  (tmp->left->left && !tmp->left->rigth))
			small_rigth_rotation(head);
		else
			big_rigth_rotation(head);
	}
	if (  (tmp->rigth && tmp->left && tmp->rigth->height - tmp->left->height == 2)  ||  (tmp->left && !tmp->rigth && tmp->rigth->height == 2) ) {
		if ( (tmp->rigth->left && tmp->rigth->rigth && tmp->rigth->rigth->height >= tmp->rigth->rigth->height)  ||  (tmp->rigth->rigth && !tmp->rigth->left) )
			small_left_rotation(head);
		else
			big_left_rotation(head);
	}
}	

void add_in_range_tree(struct range **head, struct range *new_elem)
{

	if (*head == NULL){
		*head = new_elem;
		return;
	}
	if ((*head)->begin < new_elem->begin)
		add_in_range_tree(&((*head)->left), new_elem);
	else 
		add_in_range_tree( &((*head)->rigth), new_elem);
	
	(*head)->height = (*head)->left ? (*head)->rigth ? (  (*head)->left->height > (*head)->rigth->height  ) ? (*head)->left->height + 1 : (*head)->rigth->height + 1 : (*head)->left->height + 1 ? (*head)->rigth : (*head)->rigth->height + 1 : 1;
	balanced_range_tree(head);
	return;
}

void insert_in_range_tree(struct range **head, struct top32 elem)
{
	unsigned int number1 = elem.number, number2;
	char shift = 32 - elem.mask;
	number1 = number >> shift;
	number2 = number1;
	number1 = number1 << shift;
	number2 += 1;
	number2 >> shift;
	number2 -= 1;
	struct range *insert_top = create_top(number1, number2, elem.key);
	add_in_range_tree(head, insert_top);
}


int search_in_range_tree(struct range **head, int number, char *key)
{
	int len1 = 0, len2 = 0, len;
	char key1 = 0, key2 = 0;
	if (!*head)
		return 0;
	if ((*head)->left && (*head)->left->max > number)
		len2 = search_in_range_tree( &((*head)->left), number, &key2);
	if ((*head)->begin < number || (*head)->left->max < number)
		len1 = search_in_range_tree( &((*head)->rigth), number, &key1);
	len = ( ((*head)->begin <= number) && ((*head)->end >= number) ) ? (*head)->end - (*head)->begin : 0;

	if (len > 0){
		*key = ((len2>0) && (len2<len)) ? ((len1>0) && (len1<len2)) ?  key1  :  key2  :  ((len1>0) && (len1<len))  ?  key1  :  (*head)->key;
		return ((len2>0) && (len2<len)) ? ((len1>0) && (len1<len2)) ?  len1  :  len2  :  ((len1>0) && (len1<len))  ?  len1  :  len;
	} else if (len1 > 0){
		*key = ((len2>0) && (len2<len1))  ?  key2  :  key1;
		return ((len2>0) && (len2<len1))  ?  len2  :  len1;
	} else if (len2 > 0){
		*key = key2;
		return len2;
	} else
		return len;
}


void delete_elem(struct range **head, struct range **new_head)
{
	if (!(*head)->left){
		*new_head = *head;
		return;
	} else{ 
		delete_elem((*head)->left, new_head); 
	} 
	if (!(*head)->left->left) {
		(*head)->left = (*head)->left->rigth;
		(*head)->height = (*head)->left ? (*head)->rigth ? (  (*head)->left->height > (*head)->rigth->height  ) ? (*head)->left->height + 1 : (*head)->rigth->height + 1 : (*head)->left->height + 1 ? (*head)->rigth : (*head)->rigth->height + 1 : 1;
	}
	balanced_range_tree(head);
}


void del_from_range_tree(struct range** head, struct range *elem)
{
	if (*head == NULL)
		return;
	if ((*head)->begin == elem->begin && (*head)->end == elem->end){
		struct range *new_head = NULL;
		delete_elem(&((*head)->rigth), &new_head);
		new_head->left = (*head)->left;
		new_head->rigth = (*head)->rigth;
		free(*head);
		*head = new_head;
		return;
	}
	if ((*head)->begin < elem->begin)
		del_from_range_tree( &((*head)->rigth), elem);
	else 	
		del_from_range_tree( &((*head)->left), elem);

	(*head)->height = (*head)->left ? (*head)->rigth ? (  (*head)->left->height > (*head)->rigth->height  ) ? (*head)->left->height + 1 : (*head)->rigth->height + 1 : (*head)->left->height + 1 ? (*head)->rigth : (*head)->rigth->height + 1 : 1;
}

void delete_from_range_tree(struct range** head, struct elem)
{
	unsigned int number1 = elem.number, number2;
	char shift = 32 - elem.mask;
	number1 = number >> shift;
	number2 = number1;
	number1 = number1 << shift;
	number2 += 1;
	number2 >> shift;
	number2 -= 1;
	struct range *delte_top = malloc(sizeof(struct range));
	delete_top->begin = number1;
	delete_top->end = number2;
	delete_top->key = elem.key;
	del_from_range_tree(head, delete_top);
}