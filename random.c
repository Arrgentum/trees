#include <stdio.h>   // чтобы пользоваться функцией printf
#include <stdlib.h>  // чтобы пользоваться функцией rand


//mask = 32/128, number_of_ips - количество элементов в базе данных, digits - количество изменяемых октетов
int main(int argc, char const *argv[])
{
	int mask = 0, number_of_ips = 0, i = 0, random = 0, digits = 0, j = 0;
	char buffer[4] = "10.", flag = 0;
	scanf("%d %d %d", &mask, &number_of_ips, &digits);
	//printf("%d %d %d\n\n\n", mask, number_of_ips, digits);
	for(i = 0; i < number_of_ips; i++)
	{
		if(mask == 32 && digits < 5 && digits > 0)
		{
			for( j = 0; j < 4 - digits; j++)
			{
				printf("%s", buffer);
			}
			for (j = 0; j < digits; j++)
			{
				random = rand()%255;
				printf("%d", random);
				if(j != digits - 1)
				{
					printf(".");
				}
				else
				{
					printf(" ");
				}
			}
			j = 32 - digits*8;
			random = j + rand()%(digits*8);
			printf("%d", random);
			flag = 1;
		}

		if(mask == 128 && digits < 17 && digits > 0)
		{
			for( j = 0; j < 17 - digits; j++)
			{
				printf("%s", buffer);
			}
			for (j = 0; j < digits; j++)
			{
				random = rand()%255;
				printf("%d", random);
				if(j != digits - 1)
				{
					printf(".");
				}
				else
				{
					printf(" ");
				}
			}
			j = 128 - digits*8;
			random = j + rand()%(digits*8);
			printf("%d", random);
			flag = 1;
		}
		if (!flag)
			break;

		random = rand()%100;
		printf(" %d\n", random);
	}
	return 0;
}