#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>


void setColor(char * Color){
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
	
		if(strcmp(Color, "RED") == 0){
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		}
		
		else if(strcmp(Color, "GREEN") == 0){
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		}
		
		else if(strcmp(Color, "BLUE") == 0){
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		}
		else if(strcmp(Color, "DEFAULT") == 0){
			SetConsoleTextAttribute(hConsole, 15);
		}



}

int main(void){
	
	setlocale(LC_ALL, "portuguese");
	
	
	
	int option, i, j, k, count, num_flight, num_seat;
	
	bool flights[4][38];
	
	for(k = 0; k < 38; k++){
		
		flights[0][k] = "true";
		flights[1][k] = "true";
		flights[2][k] = "true";
		flights[3][k] = "true";
		
	}
	
	int size_flights = sizeof(flights) / sizeof(flights[0]);
	int size_flights_2 = sizeof(flights[0]) / sizeof(flights[0][0]);
	
	char * options[5] = { "0 - Consultar Trechos", "1 - Consultar assentos", "2 - Efetuar reserva", "3 - Cancelar reserva", "4 - Finalizar atendimento"};
	
	// declaração de variavel size para obter o valor do tamanho  do array, e variavel i para ser o contador no for
	int size = sizeof(options) / sizeof(options[0]);
	
	do{
	
		printf("Escolha uma opção ? \n");
		
		/*
			Menu De Opções ...
		*/
		
		//varre o array e imprime o valor de cada indice gerando o menu
		
		for(i = 0; i < size; i++){
			printf("%s\n\n", options[i]);
		}
		
		printf("opção escolhida : ");
		scanf("%d", &option);
		
		switch(option){
			
			case 0:
				
				/* LISTA DO VOOS */
				
				for(i = 0; i < size_flights; i++){
					
					printf("\n\nVOO %d : \n\n", i+1);
					
					for(j = 0, count = 1; j < size_flights_2; j++,count++){
					
					if(flights[i][j] == true)
						setColor("GREEN");
					else
						setColor("RED");
						
					if(count == 10){
						printf("%d%s   \n\n", j,flights[i][j] == true ? "[L]" : "[R]");
						count = 0;
					}
					else
						printf("%d%s   ", j, flights[i][j] == true ? "[L]" : "[R]");
					}
					setColor("DEFAULT");
				}
				printf("insira o numero do VOO : ");
				scanf("%d", &num_flight);
				printf("insira o numero do assendo em que quer reservar : ");
				scanf("%d", &num_seat);	
				
				flights[num_flight-1][num_seat] = false;
										
				
			break;
		}
	}while(option != 4);
	
	return 0;
}	

