

#include"scalar.h"


//удаления дерева 
void delete_tree(struct compressed *root)
{
	if(root){
		if(root->left)
			delete_tree(root->left);
		if(root->right)
			delete_tree(root->right);
		free(root);
	}
}


//функция возвращает построенную вершину с заданными критериями
struct compressed* create_top(unsigned int number, char key, char length)
{
	if (!length)
		return NULL;
	struct scalar *new_top = malloc(sizeof(struct scalar));
	new_top->length = length;
	new_top->number = number & ((1 << length) - 1);
	new_top->key = key;
	tmp->left = NULL;
	tmp->right = NULL;
	return new_top;
}


//функция переделывает вершину
struct compressed* remake(struct compressed *tmp)
{
	unsigned int number = 0;
	char key = -1 , length = 0;
	struct node* ver;
	while(tmp){
		number = number << tmp->length;
		number += tmp->number;
		length += tmp->length;
		ver = tmp;
		if(tmp->left && tmp->right)
			break;
		if(tmp->key != -1)
			key = tmp->elem->key;
		if(tmp->left)
			tmp = tmp->left;
		else
			tmp = tmp->right;
		free(ver);
	}
	struct data info = {number, key, length, length};
	ver = build_top(data, top);
	if(tmp)
		free(tmp);
	return ver;
}


//функция выводит длинну префикса и возвращает предыдущий бит 
unsigned char length_prefix(struct compressed *tmp, struct data elem, char *flag)
{
	unsigned char car, shift;
	unsigned int number_search = elem.number, i = tmp->length, number_node = tmp->number, number_search_2 = elem.number;
	if (data.length > tmp->length){
		number_search = number_search >> (elem.length - tmp->length - 1);
		car = number_search & 1;
		number_search = number_search >> 1;
	}
	shift = 32 - elem.length + tmp->length - elem.mask;
	number_search_2 = number_search & ((1 << tmp->length) - 1); 
	if(elem.mask != 32 && shift > 0 ){
		number_search_2 = number_search_2 >> shift;
		number_node = number_node >> shift;
		i-=shift;
	}
	while(number_node != number_search_2){
		car = number_search_2 & 1;
		number_search_2 = number_search_2 >> 1;
		number_node = number_node >> 1;
		i--;
	}
	*flag = car;
	return i;
}

//функция разбивает вершину и добавляемую вершину на 3 вершины - общую (родительскую) и 2 дочерних
void break_top(struct compressed **tmp, struct data elem, char length, char bit)
{
	struct compressed *number_node = NULL, any_node = NULL, top_node = NULL; 
	unsigned int prefix = tmp->number >> ((*tmp)->length - length);
	(*tmp)->number = (prefix << ((*tmp)->length - length)) ^ (*tmp)->number;
	(*tmp)->length -= length;
	elem.number = elem.number >> (32 - elem.mask);
	elem.length -= (32-elem.mask);
	if(elem.length > 0){
		top_node = create_top(prefix, -1, length);
		number_node = build_top(data);
	} else { 
		top_node = create_top(prefix, elem,key, length);
	}	
	any_node = remake(*tmp);
	if (bit){
		top_node->left = any_node;
		top_node->right = number_node;
	} else {
		top_node->right = any_node;
		top_node->left = number_node;
	}
	*tmp = top_node;
}


//ищет места для добавления вершины в дерево
void add_in_compressed_tree(struct compressed **head, struct data elem)
{
	char bit;
	if(!(*head)){
		*head = build_top(elem, NULL);
		return;
	}
	char length = length_prefix(tmp, data, &bit);
	elem.length -= length;
	if(length == tmp->length){
		if(32 - data.length == elem.mask)
			(*tmp)->key = elem.key;
		else if(bit)
			add_in_compressed_tree(&((*head)->right), elem);
		else
			add_in_compressed_tree(&((*head)->left), elem);
	} else {
		break_top(head, elem, length, bit);
	}
}


//вставляет вершину в дерево
void insert_in_compressed_tree(struct scalar **head, struct top32 elem)
{
	if(!(*head)){
		(*head) = create_top(0,0,0);
	}
	struct data info = {elem.number, elem.key, elem.mask, elem.mask};
	if (elem.number & 2147483648){
		add_in_compressed_tree(&((*head)->right), info);
	} else {
		add_in_compressed_tree(&((*head)->left), info);
	}
}

//поиск элемента, возвращает 1, если нашел с длиной маски 32, 2, если нашел в диапазоне, 0 - если не нашел
char search_in_compressed_tree(struct compressed **head, struct data info, char *key)
{
	struct compressed *tmp;
	char bit, flag = 0;
	if(data.number & 2147483648)
		tmp = (*head)->right;
	else
		tmp = (*head)->left;
	while(tmp){
		unsigned char length = length_prefix(tmp, data, &bit);
		if(length == tmp->length){ 
			info.length -= length;
			if(tmp->key != -1){
				*key = tmp->elem->key;
				flag = info.length == 0 ? 1 : 2;
			}
			if(bit)
				tmp = tmp->right;
			else
				tmp = tmp->left;
		} else 
			break;
	}
	return flag;
}

//поиск элемента для удаления и удаление
void del_from_compressed_tree(struct compressed **head, struct data info)
{
	struct compressed *tmp = *head, *parent = *head, *grand = *head;
	char flag_parent, flag_grand, bit;
	while(tmp){
		unsigned char length = length_prefix(tmp, data, &bit);
		if(length == tmp->length) {
			data.length -= length;
			if(data.mask == 32 - data.length){
				break;
			}
			if(tmp->left && tmp->right){
				grand = parent;
				parent = tmp;
				flag_grand = flag_parent;
				flag_parent = bit;
			}
			if(bit)
				tmp = tmp->right;
			else
				tmp = tmp->left;
		} else 
			return root;
	}
	if(tmp->left || tmp->right)
		tmp->key == -1;
	if(parent != root){
		if(flag_parent){
			delete_tree(parent->right);
			parent->right = NULL;
		}else{
			delete_tree(parent->left);
			parent->left = NULL;
		}
		if(flag_grand)
			grand->right = remake(grand->right);
		else
			grand->left = remake(grand->left);
	} else 
		delete_tree(root);
}


void delete_from_compressed_tree(struct **head, struct top32 elem)
{
	struct data info = {elem.number, elem.key, elem.mask, elem.mask};
	if(data.number & 2147483648)
		del_from_scalar_tree(&(*(head)->right), data);
	else
		del_from_scalar_tree(&(*(head)->left), data);
	return root;
}