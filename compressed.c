#include "compressed.h"


//удаления дерева 
void delete_tree(struct compressed **root)
{
	if(*root != NULL){
		delete_tree(&(*root)->left);
		delete_tree(&(*root)->right);
		free(*root);
	}
}

//функция выводит все значния дерева левым обходом
void recourse_print_tree(struct compressed *tmp, int number, char length)
{
	if(tmp){
		printf("node_number = %d , length = %d\n", tmp->number, tmp->length);
		number = number << tmp->length;
		number += tmp->number;
		length += tmp->length;
		if(tmp->key >= 0){
			printf("ip = %u, mask = %d, key =  %d\n", number << (32-length), length,tmp->key);
		}
		if(tmp->left){
			printf("left\n");
			recourse_print_tree(tmp->left, number, length);
		}
		if(tmp->right){
			printf("right\n");
			recourse_print_tree(tmp->right, number, length);
		}
	} 
}

void print_tree(struct compressed *root)
{
	printf("//////  start__print__tree_  ///////\n\n");
	recourse_print_tree(root, 0, 0);
	printf("//////  end__print__tree_  ///////\n\n\n");
}




//функция возвращает построенную вершину с заданными критериями
struct compressed* create_top(unsigned int number, char key, char length)
{
	struct compressed *new_top = malloc(sizeof(struct compressed));
	new_top->length = length;
	new_top->number = number;
	new_top->key = key;
	new_top->left = NULL;
	new_top->right = NULL;
	return new_top;
}

//функция строит череду из вершин
struct compressed* build_top(struct data info, struct compressed *add_ver)
{
	if(/*info.length == 0 || */info.length + info.mask == 32)
		return NULL;
	unsigned int number = (info.length == 32) ? info.number : info.number & ((1 << info.length)-1);
	struct compressed *tmp = create_top(number, info.key, info.length);
	//printf("build top : ip = %u, mask = %d, len = %d\n", info.number, info.mask, info.length);
	//printf("num = %u, len = %d, key = %d\n", tmp->number, tmp->length, tmp->key);
	if(add_ver != NULL){
		tmp->left = add_ver->left;
		tmp->right = add_ver->right;
	}
	return tmp;
}


//функция переделывает вершину
struct compressed* remake(struct compressed *tmp)
{
	unsigned int number = 0;
	char key = -1 , length = 0;
	//print_tree(tmp);
	struct compressed* ver;
	while(tmp){
		number = number << tmp->length;
		number += tmp->number;
		length += tmp->length;
		ver = tmp;
		if(tmp->left && tmp->right)
			break;
		if(tmp->key != -1){
			key = tmp->key;
			break;
		}
		if(tmp->left)
			tmp = tmp->left;
		else
			tmp = tmp->right;
		free(ver);
	}
	struct data info = {number, key, length, length};
	//printf("num = %u, len = %d, mask = %d, key = %d\n", info.number, info.length, info.mask, info.key);
	ver = build_top(info, tmp);
	//print_tree(tmp);
	if(tmp)
		free(tmp);
	return ver;
}


//функция выводит длинну префикса и возвращает предыдущий бит 
unsigned char length_prefix(struct compressed *tmp, struct data info, char *flag)
{
	char shift, car, i = tmp->length;
	unsigned int number_search = info.number, number_node = tmp->number;
	if (info.length > tmp->length){
		number_search = number_search >> (info.length - tmp->length - 1);
		car = number_search & 1;
		number_search = number_search >> 1;
	}
	shift = 32 - info.length + tmp->length - info.mask;
	number_search = (info.length == 32) ? number_search : number_search & ((1 << tmp->length)-1);
	//number_search = number_search & ((1 << tmp->length) - 1);
	printf("number_search = %u, number_node = %u\n", number_search, number_node);
	if(info.mask != 32 && shift > 0 ){
		number_search = number_search >> shift;
		number_node = number_node >> shift;
		i-=shift;
	}
	while(number_node != number_search){
		car = number_search & 1;
		number_search = number_search >> 1;
		number_node = number_node >> 1;
		i--;
	}
	*flag = car;
	return i;
}

//функция разбивает вершину и добавляемую вершину на 3 вершины - общую (родительскую) и 2 дочерних
void break_top(struct compressed **tmp, struct data info, char length, char bit)
{
	struct compressed *number_node = NULL, *any_node = NULL, *top_node = NULL; 
	unsigned int prefix = (*tmp)->number >> ((*tmp)->length - length);
	(*tmp)->number = (prefix << ((*tmp)->length - length)) ^ (*tmp)->number;
	(*tmp)->length -= length;
	if(/*info.length > 0*/ info.length + info.mask != 32){
		top_node = create_top(prefix, -1, length);
		number_node = build_top(info, NULL);
	} else
		top_node = create_top(prefix, info.key, length);
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
void add_in_compressed_tree(struct compressed **head, struct data info)
{
	char bit;
	if(!(*head)){
		*head = build_top(info, NULL);
		return;
	}
	//printf("top_number = %d, top_len = %d,  ", (*head)->number, (*head)->length);
	unsigned char length = length_prefix(*head, info, &bit);
	printf("prefix = %d\n", length);
	info.length -= length;
	if(length == (*head)->length){
		if(32 - info.length == info.mask)
			(*head)->key = info.key;
		else if(bit)
			add_in_compressed_tree(&((*head)->right), info);
		else
			add_in_compressed_tree(&((*head)->left), info);
	} else {
		break_top(head, info, length, bit);
	}
}


//вставляет вершину в дерево
void insert_in_compressed_tree(struct compressed **head, struct data info)
{
	if ( info.mask >> 31 & 1/*info.number & 2147483648*/){
		add_in_compressed_tree(&((*head)->right), info);
	} else {
		add_in_compressed_tree(&((*head)->left), info);
	}
}

//поиск элемента, возвращает 1, если нашел с длиной маски 32, 2, если нашел в диапазоне, 0 - если не нашел
char search_in_compressed_tree(struct compressed *head, struct data info)
{
	struct compressed *tmp;
	char bit, key = -1;
	if(info.number >> 31 & 1)
		tmp = head->right;
	else
		tmp = head->left;
	while(tmp){
		unsigned char length = length_prefix(tmp, info, &bit);
		if(length == tmp->length){ 
			info.length -= length;
			if(tmp->key != -1)
				key = tmp->key;
			if(bit)
				tmp = tmp->right;
			else
				tmp = tmp->left;
		} else 
			break;
	}
	return key;
}

//поиск элемента для удаления и удаление
void del_from_compressed_tree(struct compressed **head, struct data info)
{
	struct compressed *tmp = *head, *parent = *head, *grand = *head;
	char flag_parent, flag_grand, bit;
	while(tmp){
		unsigned char length = length_prefix(tmp, info, &bit);
		//printf("number_node = %d, node_len = %d\n", tmp->number, tmp->length);
		if(length != tmp->length)
			return;
		info.length -= length;
		if(info.mask == 32 - info.length)
			break;
		if(tmp->left && tmp->right){
			grand = parent;
			parent = tmp;
			flag_grand = flag_parent;
			flag_parent = bit;
		}
		if(tmp == *head)
			flag_parent = bit;
		if(bit)
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}
	//print_tree(grand);
	//print_tree(parent);
	if(tmp->left || tmp->right){
		tmp->key = -1;
		*head = remake(parent);
		return;
	} else if(flag_parent) {
		delete_tree(&(parent->right));
		parent->right = NULL;
	} else {
		delete_tree(&(parent->left));
		parent->left = NULL;
	}
	if (tmp == parent)
		delete_tree(head);
	else if(parent == *head)
		*head = remake(*head);
	else if(flag_grand)
		grand->right = remake(grand->right);
	else
		grand->left = remake(grand->left);
}


void delete_from_compressed_tree(struct compressed **head, struct data info)
{
	if(info.number >> 31 & 1)
		del_from_compressed_tree(&((*head)->right), info);
	else
		del_from_compressed_tree(&((*head)->left), info);
}










int make_int_from_bin(char* vector)
{
	char *c = vector;
	unsigned int number = 0;
	while(*c){
		if(*c != '.'){
			number = number << 1;
			number += *c - '0';
		}
		*c++;
	}
	return number;
}


int make_int_from_ip(char* vector)
{
	char *c = vector;
	unsigned int number = 0, k = 0;
	while(*c){
		if( *c >= '0' && *c <= '9')
			k = k*10 + *c - '0';
		if(*c == '.'){
			number = number*256 + k;
			k = 0;
		}
	}
	number = number*256 + k;
	return number;
}


unsigned int* make_array_int(void)
{
	unsigned int* array_int = malloc(14 * sizeof(int)), i, num;
	char* array_char[13] = 
	{"0101.1001.0010.1010.0101.0110.1111.0100", 
	"0101.1001.0010.1010.0101.0111.0010.0001",
	"0101.1001.0010.1010.0101.0111.0010.0010",
	"0101.1011.1011.1010.0111.0111.1001.0010",
	"0101.1011.1011.1010.0111.0111.1001.0101",
	"0101.1011.1011.1010.0111.0111.1101.0101",
	"0101.1011.1011.1010.0111.1110.0000.0001",
	"0101.1011.1011.1010.0111.1111.0100.0000",
	"0101.1011.1011.1010.0111.1111.0100.0001",
	"0101.1011.1011.1010.1111.0111.1011.1001",
	"0101.1011.1011.1010.1111.0111.1011.0110",
	"0101.1011.1011.1010.1111.0000.0000.0000",
	"0101.1011.1011.1111.1111.1100.0000.0000"};
	for(i = 0; i < 13; i++){
		num = make_int_from_bin(array_char[i]);
		array_int[i] = num;
	}
	return array_int;
}

int main()
{
	struct compressed *root = create_top(0,-1,0);
	unsigned int* array_int = make_array_int(), i;
	struct data info = {0, 0, 32, 32};
	for(i = 0; i < 3; i++){
		info.number = array_int[i];
		info.key = i;
		switch(i){
			case 1: info.mask = 10; break;
			case 4: info.mask = 14; break;
			case 8: info.mask = 24; break;
			case 10: info.mask = 20; break;
			default: info.mask = 32;
		}
		printf("\n\n номер = %d  ,  ip = %u  ,  len  =  %d,  mask =  %d\n\n", i, info.number, info.length, info.mask);
		insert_in_compressed_tree(&root, info);
		print_tree(root);
	}
	printf("\nEND_INSERT\n\n");
	/*
	for (i = 0; i < 2; i++){
		info.number = array_int[i];
		delete_from_compressed_tree(&root, info);
		print_tree(root);
	}
	*/
	//print_tree(root);
	info.number = array_int[2];
	info.mask = 20;
	//delete_from_compressed_tree(&root, info);
	//print_tree(root);
	char search_key = search_in_compressed_tree(root, info);
	printf("ключ поиска = %d\n", search_key);
	delete_tree(&root);
	//print_tree(root);
	return 0;
}
