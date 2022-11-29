/*Biblioteca de fun��es para utilizar na Parte pr�tica da Prova 2 de PRP
Prof. Ivan L. Suptitz - 29/11/2022*/

///retorna a matriz c preechida com os dias do m�s
///passado por par�metro (zero nas posi��es que n�o pertencem ao m�s
void calendario(int mes, int ano, int c[6][7]){
	int dia_s = dia_semana(1, mes, ano);
	int ultimo_dia = ultimo_dia_mes(mes, ano);
	
	int i, j, k=0, dia=0;
	for(i=0; i<6; i++){//linhas s�o as semanas
		for(j=0; j<7; j++){//colunas s�o os dias da semana
			if(k >= dia_s-1)
				dia++;//posso come�ar a contar os dias
				
			k++;
			if(dia <= ultimo_dia)
				c[i][j] = dia;
			else
				c[i][j] = 0;//n�o pertence mais ao m�s
			
		}
	}
	
}	

///retorna o dia da semana no qual esse dia caiu
///domingo=1, segunda=2, ter�a=3, quarta=4, quinta=5, sexta=6 e s�bado=7
int dia_semana(int d, int m, int y){
	int weekday  = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;
	return weekday + 1;
}

//retorna 30 para os meses de 4, 6, 9, 11
//retorna 29 para fevereiro se � bissexto, sen�o 28
//sen�o retorna 31
int ultimo_dia_mes(int mes, int ano){	
	if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
		return 30;	//abril, junho, setembro e novembro tem 30 dias
	}
	else if(mes == 2){//fevereiro
		if(ano%4 == 0 && (ano % 400 == 0 || ano % 100 != 0)){
			return 29;//pois � bissexto
		}
		else{
			return 28;//n�o � bissexto
		}
	}
	else{
		return 31;//todos os demais meses
	}
}

