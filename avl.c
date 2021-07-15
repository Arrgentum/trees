#include <stdio.h>
//////////////



//32 digits



//////////////
unsigned int create_mask(char digits_in_mask)
{
	unsigned int number = 1;
	for(int i = 1; i < digits_in_mask; i++)
	{

	}
}


//создание вершины
struct top32* create_top32(unsigned	int number, struct top32 *left, struct top32 *right, char key, char mask)
{
	int i = 0;
	struct top32 *new_struct = malloc(sizeof(struct top32));
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
struct top32* restruct_top32(struct top32 *old_struct)
{
	int i = 0;
	unsigned number = old_struct->number;
	struct new_struct = malloc(sizeof(struct top32));
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
struct top32* left_small_rotation32(struct top32* root)
{
	struct top32 top_right = root->right;
	root->right = top_right->left;
	top_right->left = root;
	return top_right;
}

//левое большое вращение
struct top32 left_big_rotation(struct top32* root)
{
	struct top32 second_level = root->right, third_level = root->right->left;
	root->right = third_level->left;
	second_level->left = third_level->right;
	third_level->left = root;
	third_level->right = second_level;
	return third_level;
}

//правое малое вращение
struct top32* right_small_rotation32(struct top32* root)
{
	struct top32 top_left = root->left;
	root->left = top_left->right;
	top_left->right = root;
	return top_left;
}

//правое большое вращение
struct top32 right_big_rotation(struct top32* root)
{
	struct top32 second_level = root->left, third_level = root->left->right;
	root->left = third_level->right;
	second_level->right = third_level->left;
	third_level->right = root;
	third_level->left = second_level;
	return third_level;
}

//левая балансировка
struct top32* left_rotatio32(struct top32* root)
{
	if (root->right){
		if (root->left){
			if (root->right->height - root->left->height > 1)
				if (root->right->left){
					if(root->right->right){
						if (root->right->left->height <= root->right->right->height)
							root = left_small_rotation32(root);
					} else {
						root = left_big_rotation(root);
					} 
				} else {
					root = left_small_rotation32(root);
				}
		} else {
			if (root->right->height > 1)
				if (root->right->left){
					if(root->right->right){
						if (root->right->left->height <= root->right->right->height)
							root = left_small_rotation32(root);
					} else {
						root = left_big_rotation(root);
					} 
				} else {
					root = left_small_rotation32(root);
				}
		}
	}
	return root;
}

//правая балансировка
struct top32* left_rotatio32(struct top32* root)
{
	if (root->left){
		if (root->right){
			if (root->left->height - root->right->height > 1)
				if (root->left->right){
					if(root->left->right){
						if (root->left->right->height <= root->left->left->height)
							root = right_small_rotation32(root);
					} else {
						root = right_big_rotation(root);
					} 
				} else {
					root = right_small_rotation32(root);
				}
		} else {
			if (root->left->height > 1)
				if (root->left->right){
					if(root->left->left){
						if (root->left->right->height <= root->left->left->height)
							root = right_small_rotation32(root);
					} else {
						root = right_big_rotation(root);
					} 
				} else {
					root = right_small_rotation32(root);
				}
		}
	}
	return root;
}

//балансировка дерева
struct top32* balance32(struct top32 *root)
{
	root->left = balance32(root->left);
	root->right = balance32(root->right);
	left_rotatio32(root);
	right_rotatio32(root);
	return root;
}
//блок функций баланксировки закрывается


//блок функций добавления элемента в дерево открывается
//функция добавления элемента в дерево
struct top32 add32(struct top32 root, struct top32 new_struct, char *carry, struct information data)
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
			root->left = add32(root->left, new_struct, carry);
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
			root->right = add32(root->right, new_struct, carry);
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
struct top32* add_info(struct top32 root, struct add_range_information32 info)
{
	if (root->number < info.mask_right_edge && root->number > info.mask_left_edge){
		root->key_range = info.key_range;
		root->left = add_info(root->left, info);
		root->right = add_info(root->right, info);
	}
	else if (root->number > info.mask_right_edge)
		root->right = add_info(root->right, info);
	else if (root->number < info.mask_left_edge)
		root->left = add_info(root->left, info);
	return root;
}

//функция вставки в дерево
struct top32* insert32(struct top32 *root, struct top32 *new_struct)
{
	char height;
	struct information data{0,0,NULL,NULL};
	root = add32(root, new_struct, &height, data);
	if (new_struct->mask < 32){
		struct top32 new_struct2 = restruct_top32(new_struct);
		root = add32(root, new_struct2, &height), data;	
	}
	root = balance32(root);
	if( new_struct->mask < 32){
		struct add_range_information32 range_info{new_struct->number, new_struct2->number, new_struct->mask, new_struct->key_range}
		root = add_info(root, range_info);
	}
	return root;
}
//блок функций добавления в дерево закончился


//блок функций поиска значения в дереве открывается
//поиск ключа в дереве
struct storage* search32(struct top32 *root, struct search32 *information)
{
	struct storage* find;
	if (root->number == information.number)
		return root->key_top;
	if(!root->left && !root->right)
		if (information.mask_left_edge > information.mask_right_edge)
			return information.left_key;
		else 
			return information.right_key;
	if(root->number > information.number){
		information.mask_right_edge = root->mask;
		information.right_key = root->key_range;
		find = search32(root->left, information);
	}
	if(root->number < information.number){
		information.mask_left_edge = root->mask;
		information.left_key = root->key_range;
		find = search32(root->right, information);
	}
	return find;
}
//блок функций поиска значений в дереве закрывается

//блок удаления вершины из дерева открывается
//удаление вершины
void delete_struct(struct top32 *elem)
{

}

//нахождения минимума
struct top32* search_min(struct top32 *root, struct top32** return_elem)
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
struct top32* delete_from_struct(struct top32 *root, struct top32 delete_struct)
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
		if (root->number < delete_struct->number)
			root->right = delete_from_struct(root->right, delete_struct);
		else
			root->left = delete_from_struct(root->left, delete_struct);
	}
}

//удаление
struct top32* delete32(struct top32 *root, struct top32 delete_struct)
{
	if(delete_struct->mask == 32){
		root = delete_from_struct(root, delete_struct);
	} else {
		struct delete_struct2 = restruct_top32(delete_struct);
		root = delete_from_struct(root, delete_struct);
		root = delete_from_struct(root, delete_struct2);
		root = delete_range_from_struct(root, delete_struct);
	}
	root = balance32();
}
//блок удаления вершины из дерева закрывается
