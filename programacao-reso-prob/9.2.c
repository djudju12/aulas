#include <stdio.h>
#include <string.h>
#define MAX 100

void capitalizeString(char str[]);

int main(){
	char str[MAX];
	
	printf("Digite a string (ateh %d caracteres): ", MAX);
	fgets(str, MAX, stdin);
	capitalizeString(str);
	
	printf("%s", str);
	return 0;
}

void capitalizeString(char str[])
{
	int count=0;
	for(count=0;count<strlen(str);count++)
	{
		str[count] = toupper(str[count]);
	}
	
}
