
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/socket.h>


struct storage
{
	char key;
};

struct node
{
	struct node *left ;
	struct node *right ;
	unsigned int number;
	char length;
	struct storage *elem ;
};

struct info{
	unsigned int number;
	char length;
	char key;
	char mask;
};

//функция создает элемент storage с заданным key
struct storage* create_storage(char number)
{
	struct storage* new_storage = malloc(sizeof(struct storage));
	new_storage->key = number;
	return new_storage;
}

void print_node(struct node* tmp)
{
	if(tmp->left)
		printf("number = %d, len = %d, number_left = %d, len = %d\n", tmp->number, tmp->length, tmp->left->number, tmp->left->length);
	if(tmp->right)
		printf("number = %d, len = %d, number_left = %d, len = %d\n", tmp->number, tmp->length, tmp->right->number, tmp->right->length);
}


void recourse_print_tree(struct node *tmp, int number, char length)
{
	if(tmp){
		printf("node_number = %d , length = %d\n", tmp->number, tmp->length);
		number = number << tmp->length;
		number += tmp->number;
		length += tmp->length;
		if(tmp->elem){
			if(length != 32)
				number = number << (32 - length);
			printf("  number  = %d , mask = %d, key =  %d  &&&&&&&\n", number, length, tmp->elem->key);
		}
		if(tmp->left){
			//printf("left\n");
			recourse_print_tree(tmp->left, number, length);
		}
		if(tmp->right){
			//printf("right\n");
			recourse_print_tree(tmp->right, number, length);
		}
	} 
}


void print_tree(struct node *root)
{
	printf("//////  start__print__tree_  ///////\n");
	recourse_print_tree(root, 0, 0);
	printf("//////  end__print__tree_  ///////\n");
}


//определение нужной маски
unsigned int make_mask(char digit)
{
	unsigned int mask = 0;
	while(digit > 0){
		mask = mask << 1;
		mask++;
		digit--;
	}
	return mask;
}


struct node* build_node(struct info data)
{
	//printf("////  build_node   ////  number  = %d , length  = %d\n", data.number, data.length);
	if(!data.length)
		return NULL;
	struct node *tmp = malloc(sizeof(struct node));
	unsigned int mask = make_mask(data.length);
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->elem = NULL;
	tmp->length = data.length;
	tmp->number = data.number & mask;
	//printf("node_number = %d , node_length = %d ", tmp->number, tmp->length);
	return tmp;
}

//удаления дерева 
void delete_tree(struct node *root)
{
	if(root->elem)
		free(root->elem);
	if(root->right)
		delete_tree(root->right);
	if(root->left)
		delete_tree(root->left);
	free(root);
}

//функция добавляет информацию в вершину; если задан add_ver - добавляет в листоую вершину root влево и вправо значения add_ver, если add_ver не задан - добавляет ключ
struct node* add_information(struct node *root, struct node* add_ver, char key)
{
	//printf(" /////  ADD  information //////\n");
	//print_tree(root);
	struct node* tmp = root;
	while(tmp){
		if(!tmp->left && !tmp->right){
			if(add_ver){
				tmp->left = add_ver->left;
				tmp->right = add_ver->right;
			} else {
				//printf("///   elem  = %d///\n", key);
				tmp->elem = create_storage(key);
			}
			break;
		}
		if(tmp->left)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return root;
}

//функция переделывает вершину
struct node* remake(struct node *tmp)
{
	//printf("/////  remake   //////\n");
	unsigned int number = 0;
	char key = -1 , length = 0;
	struct node* ver;
	while(tmp){
		//printf("number   ==  %d  tmp->number  =  %d  ", number, tmp->number);
		number = number << tmp->length;
		number += tmp->number;
		length += tmp->length;
		ver = tmp;
		if(tmp->left && tmp->right)
			break;
		if(tmp->elem){
			key = tmp->elem->key;
			free(tmp->elem);
		}
		if(tmp->left)
			tmp = tmp->left;
		else
			tmp = tmp->right;
		free(ver);
	}
	struct info data = {number, length, 0, length};
//	printf("\n data.number = %d , data.length = %d \n", data.number , data.length);
	ver = build_node(data);
	//print_tree(ver);
	ver = add_information(ver, tmp, key);
	if(tmp)
		free(tmp);
	return ver;
}

//функция создает и / или меняет вершину; если tmp = NULL и заполнена data - создает, если есть tmp - переделывает
struct node* create_node(struct node* tmp, struct info data)
{
	struct node* new_node;
	if (!tmp){
		new_node = build_node(data);
		new_node = add_information(new_node, NULL, data.key);
	} else {
		new_node = remake(tmp);
	}
	return new_node;
}

//функция выводит длинну префикса и возвращает предыдущий бит 
int length_prefix(struct node *tmp, struct info data, char *flag)
{
	//printf("/////  length_prefix  //////\n");
	//printf("number_search = %d , number_node = %d , data.len = %d , len_node = %d\n", data.number, tmp->number, data.length, tmp->length);
	unsigned int number_node = tmp->number, number_search =  data.number, mask = make_mask(tmp->length);
	unsigned char car, i;
	if (data.length > tmp->length){
		for(i = 0; i < data.length - tmp->length - 1; i++)
			 number_search = number_search >> 1;
		car = number_search & 1;
		number_search = number_search >> 1;
	}
	i = tmp->length;
	//printf("number_search = %d , number_node = %d , data.len = %d , len_node = %d\n", number_search, tmp->number, data.length, tmp->length);
	char num = 32 - data.length + tmp->length - data.mask, j = 0;
	number_search = number_search & mask;
	if(data.mask != 32 && num > 0 ){
		//printf("num = %d\n", num);
		for(j = 0; j < num; j++){
			number_search = number_search >> 1;
			number_node = number_node >> 1;
			i--;
		}
	}
	//printf("number_node = %d , number_search_2 = %d , data.len = %d , car = %d , mask = %d ", number_node, number_search_2, data.length, car, mask);
	while(number_node != number_search){
		car = number_search & 1;
		number_search = number_search >> 1;
		number_node = number_node >> 1;
		i--;
	}
	*flag = car;
	//printf(" flag = %d\n", *flag);
	return i;
}

//функция поиска для добавления в дерево
struct node* search_for_add(struct node *tmp, struct info data)
{
	char bit;
	//printf("//////  search_for_add   ///// ");
	if(!tmp){
		//printf("  tmp no\n");
		tmp = create_node(NULL, data);
	} else {
		//printf("  tmp yes\n");
		int length = length_prefix(tmp, data, &bit);
		//printf("length =  %d , bit = %d \n", length, bit);
		data.length -= length;
		if(length == tmp->length){
			if(32 - data.length == data.mask){
				tmp->elem = create_storage(data.key);
				return tmp;
			}
			if(bit){
				//printf("right \n");
				tmp->right = search_for_add(tmp->right, data);
			}
			else{
				//printf("left \n");
				tmp->left = search_for_add(tmp->left, data);
			}
		} else {
			unsigned int prefix = tmp->number >> (tmp->length - length);
			tmp->number = (prefix << (tmp->length - length)) ^ tmp->number;
			tmp->length -= length;
			data.number = data.number >> (32 - data.mask);
			data.length -= (32-data.mask);
			struct node *number_node = create_node(NULL, data);
			struct node *any_node = create_node(tmp, data);
			struct node *top_node = malloc(sizeof(struct node));
			top_node->number = prefix;
			top_node->length = length;
			//printf("tmp_number = %d, top_node_number = %d \n",tmp->number, top_node->number);
			if (bit){
				top_node->left = any_node;
				top_node->right = number_node;
			} else {
				top_node->right = any_node;
				top_node->left = number_node;
			}
			return top_node;
		}
	}
	return tmp;
}

//функция добавления в дерево 
struct node* insert(struct node* root, struct info data)
{
	if(data.number & 2147483648){
		root->right = search_for_add(root->right, data);
	}
	else{
		root->left = search_for_add(root->left, data);
	}
	return root;
}

//поиск и вывод ключа 
char search(struct node *root, struct info data, char *flag)
{
	struct node *tmp;
	char bit, result;
	if(data.number & 2147483648)
		tmp = root->right;
	else
		tmp = root->left;
	*flag = 0;
	while(tmp){
		unsigned char length = length_prefix(tmp, data, &bit);
		if(length == tmp->length){ 
			data.length -= length;
			if(tmp->elem){
				result = tmp->elem->key;
				*flag = 1;
			}
			if(bit)
				tmp = tmp->right;
			else
				tmp = tmp->left;
		} else 
			break;
	}
	return result;
}

//сначала поиск, потом удаление и обновление вершин дерева
struct node* search_for_delete(struct node * root , struct info data)
{
	//printf("////// search_for_delete //////\n");
	struct node *tmp = root, *parent = root, *grand = root;
	char flag_parent, flag_grand, bit;
	while(tmp){
		unsigned char length = length_prefix(tmp, data, &bit);
		if(length == tmp->length) {
			data.length -= length;
			if(data.mask == 32 - data.length)
				break;
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
	if(tmp->left || tmp->right){
		if(tmp->elem)
			free(tmp->elem);
	}
	//printf("parent->number = %d, grand->number = %d, flag_parent = %d, flag_grand = %d\n", parent->number, grand->number, flag_parent, flag_grand);
	if(parent != root){
		if(flag_parent){
			delete_tree(parent->right);
			parent->right=NULL;
		}else{
			delete_tree(parent->left);
			parent->left =NULL;
		}
	} else {
		delete_tree(root);
		return NULL;
	}
	struct info data1 = {0,0,0,0};
	if(flag_grand)
		grand->right = create_node(grand->right, data1);
	else
		grand->left = create_node(grand->left, data1);
	return root;
}


//удаление дерева
struct node* delete_key(struct node* root, struct info data)
{
	if(data.number & 2147483648)
		root->right = search_for_delete(root->right, data);
	else
		root->left = search_for_delete(root->left, data);
	return root;
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
	"0101.1011.1011.1010.1111.0100.0000.0000",
	"0101.1011.1011.1111.1111.1100.0000.0000"};
	for(i = 0; i < 13; i++){
		num = make_int_from_bin(array_char[i]);
		array_int[i] = num;
	}
	return array_int;
}

struct node* make_root(void)
{
	struct node* new_node = malloc(sizeof(struct node));
	new_node->length = new_node->number = 0;
	new_node->left = new_node->right = NULL;
	new_node->elem = NULL;
	return new_node;
}


int main()
{
	struct node *root = make_root();
	read_file();
	

}

/*
int main()
{
	struct node *root = make_root();
	unsigned int* array_int = make_array_int(), i;
	struct info data = {0, 32, 0, 32};
	for(i = 0; i < 13; i++){
		data.number = array_int[i];
		data.key = i;
		if(i == 11)
			data.mask = 22;
		//printf("\n\n номер = %d  ,  ip = %d\n\n", i,array_int[i]);
		root = insert(root, data);
	}
	//print_tree(root);
	//printf("\nEND_INSERT\n\n");
	char flag = 0;
	data.mask = 32;
	data.number = array_int[3];
	//root = delete_key(root, data);
	//print_tree(root);
	char search_key = search(root, data, &flag);
	if (flag)
		printf("ключ поиска = %d\n", search_key);
	delete_tree(root);
	return 0;
} 