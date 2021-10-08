#include <stdio.h>
#include <stdlib.h>


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
	char** str2 = str, str3;
	int len = 0
	while(*str2) {
		len += strlen(*str2);
		*str2++;
	}
	str3 = malloc(len+1);
	len = 0;
	str2 = str;
	while(*str2) {
		while(*(*str2)){
			str3[len] = *(*str2);
			len++;
			(*(*str2))++;
		}
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
        str[i] = c[v - 1 - i];
        str[v - 1 - i] = t;
    }
    return str;
}


void delete(char** vector)
{
	char** vector2 = vector;
	while(*vector2){
		free(*vector2);
		(*vector2)++;
	}
	free(vector);
}


char* create_name_file(int bit, int line_number, int octet)
{
	char **vector = malloc(sizeof(char*) * 8);
	char *bit_in_str = from_int_make_char(bit), *line_number_in_str = from_int_make_char(line_number), octet_in_str = from_int_make_charm(octet);
	
	vector[0] = "."

	vector[0] = "bit"
	vector[1] = bit_in_str;
	vector[2] = "_"
	vector[3] = "num"
	vector[4] = line_number_in_str;
	vector[5] = "_"
	vector[6] = octet_in_str;
	char* str = add_strings(vector);
	delete(vector);
	return str;
}


int main()
{
	int bit, line_number, octet;
	char* name_file;
	input(&bit, &line_number, &octet);
	//printf("%d, %d, %d\n", bit, line_number, octet);
	name_file = create_name_file(bit, line_number, octet);


	return 0;
}