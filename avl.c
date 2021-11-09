#include"avl.h"


/*
int update_info(struct avl **head, struct data info)
{
	int a, b;
	if( !(*head) || (*head)->mask != 32 || (*head)->number > info.number2 || (*head)->number < info.number1)
		return 0;
	if((*head)->height != 1){
		a = update_info(&((*head)->left), info);
		b = update_info(&((*head)->rigth), info);
	}
	if (a && b){
		(*head)->key_range = info.key_range1;
		return 1;
	} else 
		return 0;
}
*/

struct avl* create_top(unsigned int number, char mask, char key)
{
	struct avl *new_top = malloc(sizeof(struct avl));
	new_top->number = number;
	new_top->mask = mask;
	new_top->key_top = key;
	new_top->height = 1;
	new_top->left = NULL;
	new_top->right = NULL;
	return new_top;
}

void small_left_rotation(struct avl** head)
{
	struct avl* new_head = (*head)->rigth;
	(*head)->rigth = new_head->left;
	new_head->rigth = *head;
	*head = new_head;
}

void small_rigth_rotation(struct avl** head)
{
	struct avl *new_head = (*head)->left;
	(*head)->left = new_head->rigth;
	new_head->left = *head;
	*head = new_head;
}

void big_left_rotation(struct avl** head)
{
	small_rigth_rotation( &((*head)->rigth) );
	small_left_rotation(head);
}

void big_rigth_rotation(struct avl** head)
{
	small_left_rotation( &((*head)->left));
	small_rigth_rotation(head);
}

void balanced_avl_tree(struct avl **head)
{
	struct avl *tmp = *head;
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

void add_in_avl_tree(struct avl **head, struct avl *new_elem)
{

	if (*head == NULL){
		*head = new_elem;
		return;
	}
	if ((*head)->number < new_elem->number || ( (*head)->number == new_elem->number && ( ( (*head)->number % 2 && (*head)->mask < new_elem->mask) || ((*head)->number % 2 == 0 && (*head)->mask > new_elem->mask) ) ) );
		add_in_avl_tree(&((*head)->left), new_elem);
	else 
		add_in_avl_tree( &((*head)->rigth), new_elem);
	
	(*head)->height = (*head)->left ? (*head)->rigth ? (  (*head)->left->height > (*head)->rigth->height  ) ? (*head)->left->height + 1 : (*head)->rigth->height + 1 : (*head)->left->height + 1 ? (*head)->rigth : (*head)->rigth->height + 1 : 1;
	balanced_avl_tree(head);
	return;
}


void insert_in_avl_tree(struct avl **head, top32 elem)
{
	if (mask == 32){
		struct avl *new_top = create_top(elem.number, elem.mask, elem.key);
		add_in_avl_tree(head, new_top);
	} else if (mask < 32){
		unsigned int number1 = elem.number, number2;
		char shift = 32 - elem.mask;
		number1 = number >> shift;
		number2 = number1;
		number1 = number1 << shift;
		number2 += 1;
		number2 >> shift;
		number2 -= 1;
		struct avl *new_top1 = create_top(number1, elem.mask, elem.key);
		struct avl *new_top2 = create_top(number2, elem.mask, elem.key);
		add_in_avl_tree(head, new_top);
		add_in_avl_tree(head, new_top);
		update_info();
	}
}


int choose(struct data info, int number, char *key)
{
	int shift = info.mask1 < info.mask2 ? 32 - info.mask1 : 32 - info.mask2;
	int number1 = info.number1 >> shift, number2 = info.number2 >> shift, check_number = number >> shift; 
	if(number2 == number){
		*key = info.key2;
		return 2;
	} if else (number1 == number) {
		*key = info.key1;
		return 2
	}

	shift = info.mask1 > info.mask2 ? 32 - info.mask1 : 32 - info.mask2;
	number1 = info.number1 >> shift;
	number2 = info.number2 >> shift; 
	check_number = number >> shift;
	if(number2 == number){
		*key = info.key2;
		return 2;
	} if else (number1 == number) {
		*key = info.key1;
		return 2
	}
	return 0;
}


int search_in_avl_tree(struct avl** head, int number, char *key)
{
	struct data info = {0,0,0,0,-1,-1};
	struct avl *tmp = *head;
	while(tmp){
		if (tmp->number == number ){
			if (tmp->mask == 32){
				*key = tmp->key_top;
				return 1;
			} else {
				*key = tmp->key_range;
				return 2;
			}
		} if (tmp->number < number){
			info.number1 = tmp->number;
			info.mask1 = tmp->mask;
			info.key_range1 = tmp->key_range; 
			tmp = tmp->rigth;
		} else {
			info.number2 = tmp->number;
			info.mask2 = tmp->mask;
			info.key_range2 = tmp->key_range;
			tmp = tmp->left;
		}
	}
	int result = choose(info, number, key);
	return result;
}


void delete_elem(struct avl **head, struct avl **new_head)
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


void del_from_avl_tree(struct avl** head, struct avl *elem)
{
	if (*head == NULL)
		return;
	if ((*head)->number == elem->number && (*head)->mask == elem->mask){
		struct avl *new_head = NULL;
		delete_elem(&((*head)->rigth), &new_head);
		new_head->left = (*head)->left;
		new_head->rigth = (*head)->rigth;
		free(*head);
		*head = new_head;
		return;
	}
	if ((*head)->number < elem->number)
		del_from_range_tree( &((*head)->rigth), elem);
	else 	
		del_from_range_tree( &((*head)->left), elem);

	(*head)->height = (*head)->left ? (*head)->rigth ? (  (*head)->left->height > (*head)->rigth->height  ) ? (*head)->left->height + 1 : (*head)->rigth->height + 1 : (*head)->left->height + 1 ? (*head)->rigth : (*head)->rigth->height + 1 : 1;
}


//
//
//
void update_info()
{

}
//
//
//


void delete_from_avl_tree(struct avl **head, top32 elem)
{
	if (mask == 32){
		struct avl *new_top = create_top(elem.number, elem.mask, elem.key);
		del_from_avl_tree(head, new_top);
	} else if (mask < 32){
		unsigned int number1 = elem.number, number2;
		char shift = 32 - elem.mask;
		number1 = number >> shift;
		number2 = number1;
		number1 = number1 << shift;
		number2 += 1;
		number2 >> shift;
		number2 -= 1;
		struct avl *new_top1 = create_top(number1, elem.mask, elem.key);
		struct avl *new_top2 = create_top(number2, elem.mask, elem.key);
		del_from_avl_tree(head, new_top);
		del_from_avl_tree(head, new_top);
		update_info();
	}
}