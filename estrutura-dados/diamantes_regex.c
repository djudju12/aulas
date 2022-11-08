#include <stdio.h>
#include <regex.h>
#include <string.h>
#define N_MAX 1000


int offsets_reg(char str[]){
    regex_t preg;
    char regex[] = "<[^>]*>";
    int ret, cflags = REG_ICASE;
    regmatch_t pmatch[2] = {{-1,-1},{-1,-1}};
    int result = 0;
    ret = regcomp(&preg, regex, cflags);
    
    do{
        ret = regexec(&preg, str, 2, pmatch, 0);
        if(ret)
            break;
        
        int inicio = pmatch[0].rm_so, fim=pmatch[0].rm_eo - 1;
        str[inicio] = '0';
        str[fim] = '0';
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
