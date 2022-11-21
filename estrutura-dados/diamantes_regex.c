#include <stdio.h>
#include <regex.h>
#include <string.h>
#define N_MAX 1000


int offsets_reg(char str[]){
    regex_t preg;
    char regex[] = "<[.]*>";
    regmatch_t pmatch[2];
    int result = 0;
    int ret = regcomp(&preg, regex, 0);
    
    do{
        ret = regexec(&preg, str, 2, pmatch, 0);
        if(ret)
            break;
        
        int inicio = pmatch[0].rm_so;
        int fim = pmatch[0].rm_eo - 1;
        str[inicio] = '.';
        str[fim] = '.';
        result+=1;
        
    }while(1);
    
    return result;
}

int main() {
    char teste[N_MAX];
    int inputs;
    int i, resultado;
    
    fflush(stdin);
    scanf("%d", &inputs);
    for(i=0;i<inputs;i++){
        fflush(stdin);
        scanf("%s", teste);
        resultado = offsets_reg(teste);
        printf("%d\n", resultado);
    }

    return 0;
}
