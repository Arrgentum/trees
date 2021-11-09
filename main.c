


#include"top.h"

enum {insert = 1, delete = 2, search = 3, help = 4, stop = 0, error = 5};


struct top *create_top32(unsigned int number, char key, unsigned char mask)
{
	struct top new_top = {number, key, mask};
	return new_top;
}


void help_info(void)
{
	printf("if you want INSERT in tree - write 'add' , <ip>, <mask>, <key>\n");
	printf("-------------for example 'insert 10.10.10.82 29 73'-------------\n");

	printf("if you want DELETE from tree - write 'delete' , <ip>, <mask>, <key>\n");
	printf("-------------for example 'delete 10.10.10.82 29 73'-------------\n");

	printf("if you want SEARCH in tree - write 'search' , <ip>\n");
	printf("-------------for example 'search 10.10.10.82'-------------\n");

	printf("if you want HELP - 'help'\n");
	printf("-------------for example 'help'-------------\n");

	printf("if you want to STOP working - write 'stop' \n");
	printf("-------------for example 'stop'-------------\n");
}


int str_cmp(const char *str1, const char *str2)
{
	int i = 0;
	while( (str1[i] != '\0' ) && ( str2[i] != '\0' ) && ( str1[i] == str2[i++]) )

	if(str1[i] == '\0' && str2[i] == '\0')
		return 1;
	else 
		return 0;
}


int create_command(char *c)
{
	char word[10];
	int i = 0;
	while ( (*c = getchar()) != EOF && (c == ' ')) {};
		
	while( isalpha(*c) || i < 10){
		word[i++] = *c;
		*c = getchar();
	}
	word[i] = '\0';

	while( isalpha(input_char = getchar()))
	*c = input_char;

	if (str_cmp(word, "insert"))
		return insert;
	if (str_cmp(word, "delete"))
		return delete;
	if(str_cmp(word, "search"))
		return search;
	if(str_cmp(word, "help"))
		return help;
	if(str_cmp(word, stop))
		return stop;
	return error;
}


unsigned int read_int(char *c)
{
	unsigned int number = 0;
	unsigned char num = 0;
	char space = 0;
	while ( (*c = getchar()) != EOF && (*c == ' ')) {};

	while ( (*c != EOF) && (c != ' ') && ( *c != '\n')){
        if (*c == '.' ){
        	number *= 256;
        	number += num;
        	num = 0;
        } else if (*c <= '9' && *c >= '0') {
        	if(!space)
        		space = !space;
        	num *= 10;
        	num += *c - '0';
        } else if (space) {
        	return error;
        }
        *c = getchar();
    }
    number *= 256;
    number += num;
    return number;
}


int commands32(unsigned int *number, char *key, unsigned char *mask)
{
	char c;
	int condition = 0;
	condition = create_command(&c);
	if (condition == insert || condition == delete){
		*number = read_int(&c);
		*mask = read_int(&c);
		*key = read_int(&c);
	}
	if (condition == search)
		*number = read_int(&c);
	if (condition == help)
		help_info();
	if (condition == stop)
		return stop;
	return error;
}


void scalar_tree32(struct bit32 *data)
{
	int number;
	char key, mask;
	struct range *head = NULL;
	for(int i = 0; i < lines; i++){
		struct top32 tmp = create_top(data->bit[i], data->key[i], data->mask[i]);
		insert_in_scalar_tree(&head, tmp);
	}
	while(condition != stop){
		condition = commands(&number, &key, &mask)
		struct top32 tmp = create_top(number, key, mask);
		if(condition==insert)
			insert_in_scalar_tree(&head, tmp);
		if(condition==delete)
			delete_from_scalar_tree(&head, tmp);
		if(condition==search){
			key = search_in_scalar_tree(&head, number);
			printf("key = %d\n", key);
		if (condition==help)
			help_info();
		}
	}
}


void compressed_tree32(struct bit32 *data)
{
	struct range *head = NULL;
	char key;
	int len;
	for(int i = 0; i < lines; i++){
		struct top32 tmp = create_top(data->bit[i], data->key[i], data->mask[i]);
		insert_in_compressed_tree(&head, tmp);
	}
	while(condition!=0){
		condition = commands(int number, char key, char mask)
		struct top32 tmp = create_top(number, key, mask);
		if(condition==insert)
			insert_in_compressed_tree(&head, tmp);
		if(condition==delete)
			delete_from_compessed_tree(&head, tmp);
		if(condition==search){
			key = search_in_compessed_tree(&head, number);
			printf("key = %d\n", key);
		}
		if(condition==help)
			help_info();
	}
}


void range_tree32(struct bit32 *data)
{
	struct range *head = NULL;
	for(int i = 0; i < lines; i++){
		struct top32 tmp = create_top(data->bit[i], data->key[i], data->mask[i]);
		insert_in_range_tree(&head, tmp);
	}
	while(condition!=stop){
		condition = commands(int number, char key, char mask)
		struct top32 tmp = create_top(number, key, mask);
		if(condition==insert)
			insert_in_range_tree(&head, tmp);
		if(condition==delete)
			delete_from_range_tree(&head, tmp);
		if(condition==search){
			len = search_in_range_tree(&head, number, &key);
			if (len > 0)
				printf("key = %d\n", key);
			else 
				printf("mistake search\n");
		}
		if(condition==help)
			help_info();
	}
}


void range_tree_in_array32(struct bit32 *data)
{
	struct range *head = NULL;
	for(int i = 0; i < lines; i++){
		struct top32 tmp = create_top(data->bit[i], data->key[i], data->mask[i]);
		insert_in_range_tree_in_array(&head, tmp);
	}
	while(condition!=stop){
		condition = commands(int number, char key, char mask)
		struct top32 tmp = create_top(number, key, mask);
		if(condition==insert)
			insert_in_range_tree_in_array(&head, tmp);
		if(condition==delete)
			delete_from_range_tree_in_array(&head, tmp);
		if(condition==search){
			len = search_in_range_tree_in_array(&head, number, &key);
			printf("key = %d\n", key);
		}
		if(condition==help)
			help_info();	
	}
}


void avl_tree32(struct bit32 *data)
{
	struct avl *head = NULL;
	int lines = data->head32->line_number;
	for(int i = 0; i < lines; i++){
		struct top32 tmp = create_top(data->bit[i], data->key[i], data->mask[i]);
		insert_in_avl_tree(&head, tmp);
	}
	while(condition!=stop){
		condition = commands(int number, char key, char mask)
		struct top32 tmp = create_top(number, key, mask);
		if(condition==insert)
			insert_in_avl_tree(&head, tmp);
		if(condition==delete)
			delete_from_avl_tree(&head, tmp);
		if(condition==search){
			search_in_avl_tree(&head, number, &key);
			printf("key = %d\n", key);
		}
		if(condition==help)
			help_info();
	}
}


void error(void)
{
	printf("ERROR!!!!!");
}


int choose_tree(void)
{
	printf("Input '1' if you want to use scalar tree\n");
	printf("Input '2' if you want to use range tree\n");
	printf("Input '3' if you want to use range tree in array\n");
	printf("Input '4' if you want to use compressed tree\n");
	printf("Input '5' if you want to use avl tree\n");
	scanf("%d\n", &number);
	return number;
}


int main()
{
	int chooose_number = choose_tree(), lines = 0;
	struct all *data = read(&lines);
	if (data->head32){
		switch(chooose_number) {
			case 1: scalar_tree32(data);
			case 2: range_tree32(data);
			case 3: range_tree_in_array32(data);
			case 4: compressed_tree32(data);
			case 5: avl_tree32(data);
			default: error();
		}
	} else if (data->head128) {
		switch(chooose_number) {
			case 1: scalar_tree128(data);
			case 2: range_tree128(data);
			case 3: range_tree_in_array128(data);
			case 4: compressed_tree128(data);
			case 5: avl_tree128(data);
			default: error();
		}
	}
	return 1;
}