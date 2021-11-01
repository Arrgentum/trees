#ifndef READ_H_   /* Include guard */
#define READ_H_


struct bit32;

struct bit128;

struct all;



void input(int* bit, int* line_number, int* octet);


char* add_strings(char** str);


char* from_int_make_char(int number);


char* create_name_file(int *bit, int *line_number);


void print_node128(struct bit128 *head, int len);


char read_word32(FILE* file, unsigned int *number32, char* flag);


char read_word128(FILE* file, unsigned long long int *number128, char* flag);


struct bit128* add_to_struct128(struct bit128* node, FILE *name_file, char *flag);


struct bit128* open128(char* name_file, char *flag, int line_number);


void print_node32(struct bit32 *head, int len);


struct bit32* add_to_struct32(struct bit32* node, FILE *name_file, char *flag);


struct bit32* open32(char* name_file, char *flag, int line_number);


int read(void);


#endif // READ_H_
