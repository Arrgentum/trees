#include <stdio.h>

////////////



//general



/////////////

struct storage{
	int key;
};

struct information{
	char mask_left_edge;
	char mask_right_edge;
	struct storage *left_key;
	struct storage *right_key;
};

struct top32{
	unsigned int number;
	char mask;
	struct top32 *left;
	struct top32 *right;
	struct storage *key_top;
	struct storage *key_range;
	char height;
};

struct top128{
	unsigned long long int number;
	char mask;
	struct top128 *left;
	struct top128 *right;
	struct storage *key_top;
	struct storage *key_range;
	char height;
};

//
void read(){
	char buffer_names[27] = "";
	int number_of_file;
	char 
	FILE *file;
	file = fopen("./data/");
}

//
void scan_command(){

}

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

struct top32* add_info(struct top32 root, )

//функция вставки в дерево
struct top32* insert32(struct top32 root, struct top32 new_struct)
{
	char height;
	struct information data{0,0,NULL,NULL};
	root = add32(root, new_struct, &height, data);
	if (new_struct->mask < 32){
		struct top32 new_struct2 = restruct_top32(new_struct);
		root = add32(root, new_struct2, &height), data;	
	}
	root = balance32(root);
	if( new_struct->mask < 32)
		root = add_info(root);
	return root;
}
//блок функций добавления в дерево закончился



////////////



//128 digits



////////////
struct top128* create_top128(unsigned long long int number, struct top128 *left, struct top128 *right, char key, char mask)
{
	struct top128 *new_struct = malloc(sizeof(struct top32));
	new_struct->number = number;
	new_struct->mask = mask;
	new_struct->key = key;
	new_struct->height = 1;
	new_struct->left = left;
	new_struct->right = right;
	return new_struct;
}


int main(){
	read();
	scan_command();
}