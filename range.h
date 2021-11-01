#ifndef RANGE_H_   /* Include guard */
#define RAHGE_H_


struct range;


void small_left_rotation(struct range** head);

void small_rigth_rotation(struct range** head);

void big_left_rotation(struct range** head);

void big_rigth_rotation(struct range** head);

void balanced_range_tree(struct range **head);

void insert_in_range_tree(struct range **head, struct range *new_elem);

int search_in_range_tree(struct range **head, int number, char *key);

void delete_elem(struct range **head);

void delete_from_range_tree(struct range** head, struct range *elem);



#endif // RANGE_H_
