#include <stdio.h>
//////////////



//32 digits



//////////////


struct storage{
	int key;
};

struct information{
	char mask_left_edge;
	char mask_right_edge;
	struct storage *left_key;
	struct storage *right_key;
	bool flag;
	unsigned int number;
};



struct add_range_information{
	unsigned int left_edge;
	unsigned int right_edge;
	char mask;
	struct storage* key_range;	
};

/*
struct search32{
	unsigned int number;
	char mask_left_edge;
	char mask_right_edge;
	struct storage *left_key;
	struct storage *right_key;
};
*/

struct top{
	unsigned int number;
	char mask;
	struct top *left;
	struct top *right;
	struct storage *key_top;
	struct storage *key_range;
	char height;
};



//////////////
unsigned int create_mask(char digits_in_mask)
{
	unsigned int number = 1;
	for(int i = 1; i < digits_in_mask; i++)
	{

	}
}


//создание вершины
struct top* create_top(unsigned	int number, struct top *left, struct top *right, char key, char mask)
{
	int i = 0;
	struct top *new_struct = malloc(sizeof(struct top));
	if( mask < 32){
		for(i; i < 32 - mask; i++)
			number = number << 1;
		for(i=0; i < 32 - mask; i++)
			number = number >> 1;
	}
	new_struct->number = number;
	new_struct->mask = mask;
	new_struct->key_top = malloc(sizeof(struct storage));
	new_struct->key_top->key = key;
	if(mask < 32)
		new_struct->key_range = new_struct->key_top;
	else 
		new_struct->key_range = NULL;
	new_struct->height = 1;
	new_struct->left = left;
	new_struct->right = right;
	return new_struct;
}

//переделывание значений вершины
struct top* restruct_top(struct top *old_struct)
{
	int i = 0;
	unsigned number = old_struct->number;
	struct new_struct = malloc(sizeof(struct top));
	if( mask < 32){
		for(i; i < 32 - mask; i++)
			number = number << 1;
		for(i=0; i < 32 - mask; i++){
			number = number >> 1;
			number++;
		}
	}
	new_struct->number = number;
	new_struct->mask = old_struct->mask;
	new_struct->key_top = old_struct->key_top;
	new_struct->key_range = old_struct->key_range;
	new_struct->height = 1;
	new_struct->left = old_struct->left;
	new_struct->right = old_struct->right;
	return new_struct;
}

//блок функций балансировки открывается
//левое малое вращение
struct top* left_small_rotation(struct top* root)
{
	struct top top_right = root->right;
	root->right = top_right->left;
	top_right->left = root;
	return top_right;
}

//левое большое вращение
struct top left_big_rotation(struct top* root)
{
	struct top second_level = root->right, third_level = root->right->left;
	root->right = third_level->left;
	second_level->left = third_level->right;
	third_level->left = root;
	third_level->right = second_level;
	return third_level;
}

//правое малое вращение
struct top* right_small_rotation(struct top* root)
{
	struct top top_left = root->left;
	root->left = top_left->right;
	top_left->right = root;
	return top_left;
}

//правое большое вращение
struct top right_big_rotation(struct top* root)
{
	struct top second_level = root->left, third_level = root->left->right;
	root->left = third_level->right;
	second_level->right = third_level->left;
	third_level->right = root;
	third_level->left = second_level;
	return third_level;
}

//левая балансировка
struct top* left_rotation(struct top* root)
{
	if (root->right){
		if (root->left){
			if (root->right->height - root->left->height > 1)
				if (root->right->left){
					if(root->right->right){
						if (root->right->left->height <= root->right->right->height)
							root = left_small_rotation(root);
					} else {
						root = left_big_rotation(root);
					} 
				} else {
					root = left_small_rotation(root);
				}
		} else {
			if (root->right->height > 1)
				if (root->right->left){
					if(root->right->right){
						if (root->right->left->height <= root->right->right->height)
							root = left_small_rotation(root);
					} else {
						root = left_big_rotation(root);
					} 
				} else {
					root = left_small_rotation(root);
				}
		}
	}
	return root;
}

//правая балансировка
struct top* left_rotation(struct top* root)
{
	if (root->left){
		if (root->right){
			if (root->left->height - root->right->height > 1)
				if (root->left->right){
					if(root->left->right){
						if (root->left->right->height <= root->left->left->height)
							root = right_small_rotation(root);
					} else {
						root = right_big_rotation(root);
					} 
				} else {
					root = right_small_rotation(root);
				}
		} else {
			if (root->left->height > 1)
				if (root->left->right){
					if(root->left->left){
						if (root->left->right->height <= root->left->left->height)
							root = right_small_rotation(root);
					} else {
						root = right_big_rotation(root);
					} 
				} else {
					root = right_small_rotation(root);
				}
		}
	}
	return root;
}

//балансировка дерева
struct top* balance(struct top *root)
{
	root->left = balance(root->left);
	root->right = balance(root->right);
	left_rotatio(root);
	right_rotatio(root);
	return root;
}
//блок функций баланксировки закрывается


//блок функций добавления элемента в дерево открывается
//функция добавления элемента в дерево
struct top add(struct top root, struct top new_struct, char *carry, struct information data)
{
	bool flag = false;
	unsigned int mask = create_mask(root->mask);
	if(mask & root->number == mask & new_struct->number)
		flag = true;

	if (root->number < new_struct->number){
		if(flag){
			data.mask_left_edge = mask;
			data.left_key = root->key_range->key;
		} else {
			data.mask_left_edge = 32;
			data.left_key = NULL;
		}
		if(root->left){
			root->left = add(root->left, new_struct, carry);
		} else {
			if(data	mask_right_edge == data.mask_left_edge)
				new_struct->key_range = data.right_key;
			root->left = new_struct;
			if(!root->right){
				*carry = 2;
			}
		}
	}

	else if(root->number < new_struct->number){
		if(flag){
			data.mask_right_edge = mask;
			data.right_key = root->key_range->key;
		} else {
			data.mask_right_edge = 32;
			data.right_key = NULL;
		}
		if(root->right){
			root->right = add(root->right, new_struct, carry);
		} else {
			if(data	mask_right_edge == data.mask_left_edge)
				new_struct->key_range = data.right_key;
			root->right = new_struct;
			if(!root->left){
				*carry = 2;
			}
		}
	}
	if (*carry > root->height)
		root->height = *carry;
	root->height = *carry;
	return root;
}

//добавление информации в элемнты дерева при добавлении дерева
struct top* add_info(struct top root, struct add_range_information info)
{
	if (root->number < info.right_edge && root->number > info.left_edge){
		root->key_range = info.key_range;
		root->left = add_info(root->left, info);
		root->right = add_info(root->right, info);
	}
	else if (root->number > info.right_edge)
		root->right = add_info(root->right, info);
	else if (root->number < info.left_edge)
		root->left = add_info(root->left, info);
	return root;
}

//функция вставки в дерево
struct top* insert(struct top *root, struct top *new_struct)
{
	char height;
	struct information data{0,0,NULL,NULL, false};
	root = add(root, new_struct, &height, data);
	if (new_struct->mask < 32){
		struct top new_struct2 = restruct_top(new_struct);
		root = add(root, new_struct2, &height), data;	
	}
	root = balance(root);
	if( new_struct->mask < 32){
		struct add_range_information range_info{new_struct->number, new_struct2->number, new_struct->mask, new_struct->key_range}
		root = add_info(root, range_info);
	}
	return root;
}
//блок функций добавления в дерево закончился


//блок функций поиска значения в дереве открывается
//поиск ключа в дереве
struct storage* search(struct top *root, struct information *info)
{
	struct storage* find;
	if (root->number == info.number)
		return root->key_top;
	if(!root->left && !root->right)
		if (info.mask_left_edge > info.mask_right_edge)
			return info.left_key;
		else 
			return infor.right_key;
	if(root->number > info.number){
		info.mask_right_edge = root->mask;
		info.right_key = root->key_range;
		find = search(root->left, info);
	}
	if(root->number < information.number){
		info.mask_left_edge = root->mask;
		info.left_key = root->key_range;
		find = search(root->right, info);
	}
	return find;
}
//блок функций поиска значений в дереве закрывается


//блок удаления вершины из дерева открывается
//удаление вершины
void delete_struct(struct top *elem)
{
	if (elem->key_range){
		free(elem->key_range);
	}
	free(elem->key_range);
	free(elem);
}

//нахождения минимума
struct top* search_min(struct top *root, struct top** return_elem)
{
	if(root->left)
		if (root->left->left){
			root = search_min(root->left, );
		} else {
			*return_elem = root->left;
			root->left = NULL;
		}
	return root;
}

//удаление вершины из дерева
struct top* delete_from_struct(struct top *root, struct top *delete_struct, struct information info)
{
	struct new_root = NULL;
	if(root->mask == delete_struct->mask && root->number == delete_struct->number){
		if(root->left){
			root = search_min(root, &new_root);
			new_root->left = root->left;
			new_root->right = root->right;
		}
		delete_struct(root);
		return new_root;
	} else {
		if (root->number < delete_struct->number){
			if (!info.flag){
				info.mask_left_edge = root->mask;
				info.left_key = root->key_range
			}
			root->right = delete_from_struct(root->right, delete_struct);
		}
		else{
			if (info.flag){
				info.mask_right_edge = root->mask;
				info.right_key = root->key_range
			}
			root->left = delete_from_struct(root->left, delete_struct);
		}
	}
	return root;
}

//изменение ключей диапазона
struct top* rewrite_range_from_struct(struct top *root, struct add_range_information info)
{
	if (root->number < info.right_edge && root->number < info.left_edge){
		root->key_range = info.key_range;
		root->left = rewrite_range_from_struct(root->left, info);
		root->right = rewrite_range_from_struct(root->right, info);
	}
	if (root->number > info.right_edge)
		root->right = rewrite_range_from_struct(root->right, info);
	if (root->number < info.left_edge)
		root-.left = rewrite_range_from_struct(root->left, info);
	return root;
}

//удаление
struct top* delete(struct top *root, struct top delete_struct)
{
	if(delete_struct->mask == 32){
		root = delete_from_struct(root, delete_struct);
	} else {
		struct information range_info = {0,0,NULL,NULL,false};
		struct top delete_struct2 = restruct_top(delete_struct);
		root = delete_from_struct(root, delete_struct );
		root = delete_from_struct(root, delete_struct2);
		struct add_range_information add_info = {delete_struct->number, delete_struct2->number, 0, NULL};
		if (range_info.mask_left_edge = range_info.mask_right_edge){
			add_info.mask = range_info.mask_right_edge;
			add_info.key_range = range_info.key_range;
		}
		root = rewrite_range_from_struct(root, add_info);
	}
	root = balance(root);
	return root;
}
//блок удаления вершины из дерева закрывается


//удаление всего дерева
void delete_tree(struct top *root)
{
	free(root->key_range);
	free(root->key_top);
	if(root->left)
		delete_tree(root->left);
	if(root->right)
		delete_tree(root->right);
	free(root);
}
//операции с деревом закончены


//головные операции
//функция выбора файла для чтения
char* name_file(void)
{
	const char *files_name[14];
	files_name = ["bit32_num1000_1", "bit32_num1000_2", "bit32_num1000_3", "bit32_num100_1", "bit32_num100_2", "bit32_num100_3", "bit32_num30000_1", "bit32_num30000_2", "bit32_num30000_3", "bit32_num64000_1", "bit32_num64000_2", "bit32_num64000_3"];
	char number_of_file = 4;
	char *file = malloc(sizeof(char) * 25);
	file = "data/";
	for(int i = 0; i < sizeof(files_name[number_of_file]); i++)
		file[i+5] = files_name[number_of_file][i];
	printf("%s\n", file);
	return file;
}


//функция чтения с файла и занесения в структуру
struct top* read_and_create(void)
{
	char *file_name = name_file(), sym, mask, key;
	FILE *file = fopen(file_name, "r");
	int number;
	while( (sym = fgetc(file)) != EOF )
	{
		
	}
	fclose(file);
}


int main(int argc, char const *argv[])
{
	struct top *root = read_and_create();
	return 0;
}