#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "read.h"


void input(int* bit, int* line_number, int* octet)
{
	printf("Input number of bit\n");
	scanf("%d", bit);
	printf("Input number of line in file\n");
	scanf("%d", line_number);
	printf("Input number of mutable octets\n");
	scanf("%d", octet);
}


char* add_strings(char** str)
{
	char** str2 = str, *str3;
	int len = 0, i = 0, j = 0;
		while(*str2) {
		len += strlen(*str2);
		*str2++;
	}
	//printf("%d\n", len);
	str3 = malloc( (len+1) * sizeof(char));
	len = i = 0;
	while(str[i] != NULL) {
		j = 0;
		while(str[i][j] != '\0'){
			str3[len] = str[i][j];
			len++;
			j++;
		}
		i++;
	}
	str3[len] = '\0';
	return str3; 
}


char* from_int_make_char(int number)
{
	char* str = malloc(10 * sizeof(char)); 
    int v = 0; 
    while (number > 9)
    {
        str[v++] = (number % 10) + '0';
        number = number / 10;
    }
    str[v++] = number + '0';
    str[v] = '\0';
    char t;
    for (int i = 0; i < v / 2; i++)
    {
        t = str[i];
        str[i] = str[v - 1 - i];
        str[v - 1 - i] = t;
    }
    return str;
}


char* create_name_file(int *bit, int *line_number)
{
	int octet;
	input(bit, line_number, &octet);
	char **vector = malloc(sizeof(char*) * 7);
	char *bit_in_str = from_int_make_char(*bit), *line_number_in_str = from_int_make_char(*line_number), *octet_in_str = from_int_make_char(octet);
	vector[0] = "./data/bit";
	vector[1] = bit_in_str;
	vector[2] = "_num";
	vector[3] = line_number_in_str;
	vector[4] = "_";
	vector[5] = octet_in_str;
	vector[6] = NULL;
	char* str = add_strings(vector);
	free(vector[1]);
	free(vector[3]);
	free(vector[5]);
	free(vector);
	return str;
}


//часть с 128 бит начинается


void print_node128(struct bit128 *head)
{
	int len = head->line_number;
	for (int i = 0; i < len; i++){
		printf("%llu - ip, %c - mask, %c - key\n", (head->bit)[i], (head->mask)[i], (head->key)[i]);	
	}
}

char read_word32(FILE* file, unsigned int *number32, char* flag)
{
	unsigned int number = 0;
	unsigned char num = 0;
	char c, space = 0;
	while ( (c = fgetc(file)) != EOF && (c == ' ')) {};

	while ( (c != EOF) && (c != ' ') && ( c != '\n')){
        if (c == '.' ){
        	number *= 256;
        	number += num;
        	num = 0;
        } else if (c <= '9' && c >= '0') {
        	if(!space)
        		space = !space;
        	num *= 10;
        	num += c - '0';
        } else if (space) {
        	*flag = 0;
        	break;
        }
        c = fgetc(file);
    }
    number *= 256;
    number += num;
    *number32 = number;
    return c;
}

char read_word128(FILE* file, unsigned long long int *number128, char* flag)
{
	unsigned long long int number = 0;
	unsigned char num = 0;
	char c, space = 0;
	while ( (c = fgetc(file)) != EOF && (c == ' ')) {};

	while ( (c != EOF) && (c != ' ') && ( c != '\n')){
        if (c == '.'){
        	number *= 256;
        	number += num;
        	num = 0;
        } else if (c <= '9' && c >= '0') {
        	if(!space)
        		space = !space;
        	num *= 10;
        	num += c - '0';
        } else if (space) {
        	*flag = 0;
        	break;
        }
        c = fgetc(file);
    }
    number128 = &number;
    return c;
}


struct bit128* add_to_struct128(struct bit128* node, FILE *name_file, char *flag)
{
	unsigned long long int number128;
	unsigned int number32;
	int i = 0;
	char c = ' ';
	while(c != EOF){
  		c = read_word128(name_file, &number128, flag);
  		if(!flag) 
  			break;
  		node->bit[i] = number128;
  		c = read_word32(name_file, &number32, flag);
  		if(!flag)
  			break;
  		node->mask[i] = number32;
  		c = read_word32(name_file, &number32, flag);
  		if(!flag) 
  			break;
  		node->key[i] = number32;
  		i++;
  	}
  	return node;
};

struct bit128* open128(char* name_file, char *flag, int line_number)
{
	FILE *file;
	if ((file = fopen(name_file, "r")) == NULL){
	    printf("Не удалось открыть файл");
	    *flag = 0;
	    return NULL;
  	}
  	struct bit128 *node = malloc(sizeof(struct bit32));
  	node->key = malloc(sizeof(char) * (line_number + 1));
  	node->bit = malloc(sizeof(long long unsigned int) * (line_number +1));
  	node->mask = malloc(sizeof(char) * (line_number + 1));
  	node = add_to_struct128(node, file, flag);
  	node->line_number = line_number;
  	fclose(file);
  	if (!flag)
  		free(node);
  	return node;
}



//часть 128 бит закрывается


//часть 32 бит открывается


void print_node32(struct bit32 *head)
{
	int len = head->line_number;
	for (int i = 0; i < len; i++){
		printf("%u - ip, %d - mask, %d - key\n", head->bit[i], head->mask[i], head->key[i]);	
	}
}

struct bit32* add_to_struct32(struct bit32* node, FILE *name_file, char *flag)
{
	unsigned int number, i = 0;
	char c = ' ';
	while(c != EOF){
  		c = read_word32(name_file, &number, flag);
  		if(!(*flag))
  			break;
  		node->bit[i] = number;
  		c = read_word32(name_file, &number, flag);
  		if(!(*flag))
  			break;
  		node->mask[i] = number;s
  		c = read_word32(name_file, &number, flag);
  		if(!(*flag))
  			break;
  		node->key[i] = number;
  		i++;
  	}
  	return node;
}

struct bit32* open32(char* name_file, char *flag, int line_number)
{
	FILE *file;
	if ((file = fopen(name_file, "r")) == NULL){
	    printf("Не удалось открыть файл");
	    *flag = 0;
	    return NULL;
  	}
  	struct bit32 *node = malloc(sizeof(struct bit32));
  	node->key = malloc(sizeof(char) * (line_number + 1));
  	node->bit = malloc(sizeof(int) * (line_number +1));
  	node->mask = malloc(sizeof(char) * (line_number + 1));
  	node = add_to_struct32(node, file, flag);
  	node->line_number = line_number;
  	fclose(file);
  	if (!flag)
  		free(node);
  	return node;
}


//часть 32 бита закрыта


struct all* read(int *len)
{
	struct bit32 *head32 = NULL;
	struct bit128 *head128 = NULL;
	struct all *elem = NULL;
	int line_number, bit;
	char *name_file, flag = 1;
	name_file = create_name_file(&bit, &line_number);
	printf("name file == %s\n", name_file);
	if (bit == 32){
		head32 = open32(name_file, &flag, line_number);
		//print_node32(head32, line_number);
	}
	else if (bit == 128) {
		head128 = open128(name_file, &flag, line_number);
		//print_node128(head128, line_number);
	}
	elem = malloc(sizeof(struct all));
	elem->head128 = head128;
	elem->head32 = head32;
	len* = line_number;
	return elem;
	//return 0;
}