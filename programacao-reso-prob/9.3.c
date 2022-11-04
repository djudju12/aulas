#include <stdio.h>
#include <string.h>
#define MAX 100

void titleStr(char str[], char strTitled[]);

int main(){
	char str[MAX], strTitled[MAX];
	
	printf("Digite a string (ateh %d caracteres): ", MAX);
	fgets(str, MAX, stdin);
	titleStr(str, strTitled);
	
	printf("String original:\n%s\n", str);
	printf("String modificada:\n%s", strTitled);
	return 0;
}

void titleStr(char str[], char strTitled[])
{
	int i;
	strcpy(strTitled, str);
	for(i=0;i<strlen(str);i++)
	{
		if((isspace(str[i-1]) || i==0) && isalpha(str[i]))
			strTitled[i] = toupper(str[i]);
	}
}
