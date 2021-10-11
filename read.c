#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct bit32
{
	unsigned int bit;
	char mask;
	char key;
	struct bit32* next;
};

struct bit128
{
	unsigned long long int bit;
	char mask;
	char key;
	struct bit128* next;
}


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
	printf("%d\n", len);
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


char* create_name_file(int bit, int line_number, int octet)
{
	char **vector = malloc(sizeof(char*) * 7);
	char *bit_in_str = from_int_make_char(bit), *line_number_in_str = from_int_make_char(line_number), *octet_in_str = from_int_make_char(octet);
	printf("%s, %s, %s\n", bit_in_str, line_number_in_str, octet_in_str);
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


void print_node128(bit128 *head){
	if(head){
		printf("%llu - ip, %c - mask, %c - key ", head->bit, head->mask, head->key);
		printf_node128(head->next);	
	} 
}


char read_word128(FILE* file, unsigned long long int *number128 = 0, bool* flag)
{
	unsigned long long int number = 0;
	unsigned char num = 0;
	bool space = false;
	char c;
	while (c = fgetc(file) != EOF && (c == ' ')) {};

	while ( (c != EOF) && (c != ' ') && ( c != '\n')){
        if (c == '.'){
        	number *= 256;
        	number += num;
        	num = 0;
        } else if (c <= '9' && c >= '0') {
        	if(!space)
        		space = !space;
        	num *= 10;
        	num += с - '0';
        } else if (space) {
        	*flag = false;
        	break;
        }
        c = fgetc(file);
    }
    number128 = &number;
    return c;
}


struct bit32* open32(char* name_file, bool *flag)
{
	FILE *file;
	unsigned int number32;
	unsigned long long int number128;
	char c = ' ';
	struct bit128 *node = NULL, *head = NULL;
	if ((fp = fopen(name, "r")) == NULL){
	    printf("Не удалось открыть файл");
	    *flag = false;
	    return NULL;
  	}
  	while(c != EOF){
  		node = malloc(sizeof(bit32));
  		c = read32(name_file, &number128, *flag);
  		if(!flag) 
  			break;
  		node->bit = number128;
  		c = read32(name_file, &number32, *flag);
  		if(!flag) 
  			break;
  		node->mask = number32;
  		c = read32(name_file, &number32, *flag);
  		if(!flag) 
  			break;
  		node->key = number32;
  		if(!head)
  			head = node;
  		node = node->nest;
  	}
  	if (!flag)
  		free(node);
  	fclose(file);
  	return head;
}



//часть 128 бит закрывается


//часть 32 бит открывается


void print_node32(bit128 *head){
	if(head){
		printf("%u - ip, %c - mask, %c - key", head->bit, head->mask, head->key);
		printf_node128(head->next);	
	} 
}


char read_word32(FILE* file, unsigned int *number32 = 0, bool* flag)
{
	unsigned int number = 0;
	unsigned char num = 0;
	bool space = false;
	char c;
	while (c = fgetc(file) != EOF && (c == ' ')) {};

	while ( (c != EOF) && (c != ' ') && ( c != '\n')){
        if (c == '.'){
        	number *= 256;
        	number += num;
        	num = 0;
        } else if (c <= '9' && c >= '0') {
        	if(!space)
        		space = !space;
        	num *= 10;
        	num += с - '0';
        } else if (space) {
        	*flag = false;
        	break;
        }
        c = fgetc(file);
    }
    number32 = &number;
    return c;
}


struct bit32* open32(char* name_file, bool *flag)
{
	FILE *file;
	unsigned int number;
	char c = ' ';
	struct bit32 *node = NULL, *head = NULL;
	if ((fp = fopen(name, "r")) == NULL){
	    printf("Не удалось открыть файл");
	    *flag = false;
	    return NULL;
  	}
  	while(c != EOF){
  		node = malloc(sizeof(bit32));
  		c = read32(name_file, &number, *flag);
  		if(!flag) 
  			break;
  		node->bit = number;
  		c = read32(name_file, &number, *flag);
  		if(!flag) 
  			break;
  		node->mask = number;
  		c = read32(name_file, &number, *flag);
  		if(!flag) 
  			break;
  		node->key = number;
  		if(!head)
  			head = node;
  		node = node->nest;
  	}
  	fclose(file);
  	if (!flag)
  		free(node);
  	return head;
}


//часть 32 бита закрыта


int main()
{
	struct bit32 *head32;
	struct bit128 *head128;
	int bit, line_number, octet;
	char* name_file;
	name_file = create_name_file(bit, line_number, octet);
	printf("%s\n", name_file);
	if (bit == 32){
		head32 = open32(name_file);
		print_node32(head32);
	}
	else (bit == 128){
		head128 = open128(name_file)
		print_node128(head128);
	}

	return 0;
}