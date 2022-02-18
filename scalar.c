#include "scalar.h"


//удаления дерева 
void delete_tree(struct scalar **root)
{
	if(*root){
		if((*root)->left)
			delete_tree(&(*root)->left);
		if((*root)->right)
			delete_tree(&(*root)->right);
		free(*root);
	}
}


//функция возвращает построенную вершину с заданными критериями
struct scalar* create_top(unsigned char number, char key, char length)
{
	struct scalar *new_top = malloc(sizeof(struct scalar));
	new_top->length = length;
	new_top->number = number;
	new_top->key = key;
	new_top->left = NULL;
	new_top->right = NULL;
	return new_top;
}

//функция строит череду из вершин
struct scalar* build_top(struct data elem, struct scalar *add_ver)
{
	if(elem.length < 0)
		return NULL;
	struct scalar *tmp;
	unsigned int number = elem.number;
	unsigned char flag = 0, num;
	if(elem.length > 8)  {
		number = number >> (elem.length - 9);
		if(number & 1)
			flag = 1;
		number = number >> 1;
		num = number;
		tmp = create_top(num, -1, 8);
	} else {
		num = ((1 << elem.length) - 1) & elem.number;
		tmp = create_top(num, elem.key, elem.length);
		if(add_ver != NULL){
			tmp->left = add_ver->left;
			tmp->right = add_ver->right;
		}
	}
	elem.length -= tmp->length;
	if(flag)
		tmp->right = build_top(elem, NULL);
	else
		tmp->left = build_top(elem, NULL);
	return tmp;
}


//функция переделывает вершину
struct scalar* remake(struct scalar *tmp)
{
	unsigned int number = 0;
	char key = -1 , length = 0;
	struct scalar* ver;
	while(tmp){
		number = number << tmp->length;
		number += tmp->number;
		length += tmp->length;
		ver = tmp;
		if(tmp->left && tmp->right)
			break;
		if(tmp->key != -1)
			key = tmp->key;
		if(tmp->left)
			tmp = tmp->left;
		else
			tmp = tmp->right;
		free(ver);
	}
	struct data info = {number, key, length, length};
	ver = build_top(info, tmp);
	if(tmp)
		free(tmp);
	return ver;
}


//функция выводит длинну префикса и возвращает предыдущий бит 
unsigned char length_prefix(struct scalar *tmp, struct data info, char *flag)
{
	unsigned char number_node = tmp->number, car, number_search_2, shift;
	unsigned int number_search = info.number, i = tmp->length;
	if (info.length > tmp->length){
		number_search = number_search >> (info.length - tmp->length - 1);
		car = number_search & 1;
		number_search = number_search >> 1;
	}
	shift = 32 - info.length + tmp->length - info.mask;
	number_search_2 = number_search & ((1 << tmp->length) - 1); 
	if(info.mask != 32 && shift > 0 ){
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
void break_top(struct scalar **tmp, struct data info, char length, char bit)
{
	struct scalar *number_node = NULL, *any_node = NULL, *top_node = NULL; 
	unsigned char prefix = (*tmp)->number >> ((*tmp)->length - length);
	(*tmp)->number = (prefix << ((*tmp)->length - length)) ^ (*tmp)->number;
	(*tmp)->length -= length;
	info.number = info.number >> (32 - info.mask);
	info.length -= (32-info.mask);
	if(info.length > 0){
		top_node = create_top(prefix, -1, length);
		number_node = build_top(info, NULL);
	} else { 
		top_node = create_top(prefix, info.key, length);
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
void add_in_scalar_tree(struct scalar **head, struct data info)
{
	char bit;
	if(!(*head)){
		*head = build_top(info, NULL);
		return;
	}
	char length = length_prefix(*head, info, &bit);
	info.length -= length;
	if(length == (*head)->length){
		if(32 - info.length == info.mask)
			(*head)->key = info.key;
		else if(bit)
			add_in_scalar_tree(&((*head)->right), info);
		else
			add_in_scalar_tree(&((*head)->left), info);
	} else {
		break_top(head, info, length, bit);
	}
}


//вставляет вершину в дерево
void insert_in_scalar_tree(struct scalar **head, struct data info)
{
	if(!(*head)){
		(*head) = create_top(0,0,0);
	}
	if (info.number & 2147483648){
		add_in_scalar_tree(&((*head)->right), info);
	} else {
		add_in_scalar_tree(&((*head)->left), info);
	}
}

//поиск элемента, возвращает 1, если нашел с длиной маски 32, 2, если нашел в диапазоне, 0 - если не нашел
char search_in_scalar_tree(struct scalar *head, struct data info)
{
	struct scalar *tmp;
	char bit, key = -1;
	if(info.number & 2147483648)
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
void del_from_scalar_tree(struct scalar **head, struct data info)
{
	struct scalar *tmp = *head, *parent = *head, *grand = *head;
	char flag_parent, flag_grand, bit;
	while(tmp){
		unsigned char length = length_prefix(tmp, info, &bit);
		if(length == tmp->length) {
			info.length -= length;
			if(info.mask == 32 - info.length){
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
			return NULL;
	}
	if(tmp->left || tmp->right)
		tmp->key = -1;
	if(parent != *head){
		if(flag_parent){
			delete_tree(&(parent->right));
			parent->right = NULL;
		}else{
			delete_tree(&(parent->left));
			parent->left = NULL;
		}
		if(flag_grand)
			grand->right = remake(grand->right);
		else
			grand->left = remake(grand->left);
	} else 
		delete_tree(head);
}


void delete_from_scalar_tree(struct scalar **head, struct data info)
{
	if(info.number & 2147483648)
		del_from_scalar_tree(&((*head)->right), info);
	else
		del_from_scalar_tree(&((*head)->left), info);
}


//функция выводит все значния дерева левым обходом
void recourse_print_tree(struct scalar *tmp, int number, char length)
{
	if(tmp){
		printf("node_number = %d , length = %d\n", tmp->number, tmp->length);
		number = number << tmp->length;
		number += tmp->number;
		length += tmp->length;
		if(tmp->left){
			printf("left\n");
			recourse_print_tree(tmp->left, number, length);
		}
		if(tmp->right){
			printf("right\n");
			recourse_print_tree(tmp->right, number, length);
		}
		if(length != 32 && tmp->key > 0){
			number = number << (32 - length);
			printf("  number  = %d , mask = %d, key =  %d  &&&&&&&\n", number, length, tmp->key);
		}
	} 
}


void print_tree(struct scalar *root)
{
	printf("//////  start__print__tree_  ///////\n");
	recourse_print_tree(root, 0, 0);
	printf("//////  end__print__tree_  ///////\n");
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

struct scalar* make_root(void)
{
	struct scalar* new_node = malloc(sizeof(struct scalar));
	new_node->length = new_node->number = new_node->key = 0;
	new_node->left = new_node->right = NULL;
	return new_node;
}

int main()
{
	struct scalar *root = make_root();
	unsigned int* array_int = make_array_int(), i;
	struct data info = {0, 32, 0, 32};
	for(i = 0; i < 13; i++){
		info.number = array_int[i];
		info.key = i;
		if(i == 11)
			info.mask = 21;
		//printf("\n\n номер = %d  ,  ip = %d\n\n", i,array_int[i]);
		printf("before_insert\n");
		insert_in_scalar_tree(&root, info);
		printf("after_insert\n");
	}
	printf("\nEND_INSERT\n\n");
	print_tree(root);
	info.number = array_int[11];
	info.mask = 21;
	delete_from_scalar_tree(&root, info);
	print_tree(root);
	char search_key = search_in_scalar_tree(root, info);
	printf("ключ поиска = %d\n", search_key);
	delete_tree(&root);
	return 0;
}
