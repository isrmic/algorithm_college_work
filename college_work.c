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
	
	else if(strcmp(Color, "YELLOW") == 0){
		SetConsoleTextAttribute(hConsole, 6);
	}
	
	else if(strcmp(Color, "DEFAULT") == 0){
		SetConsoleTextAttribute(hConsole, 15);
	}

}


bool in_array_bool(bool condiction, bool * param){
	int size = sizeof(param) / sizeof(param[0]), i;
	for(i = 0; i < size; i++){
		if(param[i] == condiction)
			return true;
	}
	return false;
	
}

void showSeats(int size, bool * flights){
	
	int j, count, seat_vip;
	for(j = 0, count = 1,seat_vip = 1; j < size; j++,count++,seat_vip++){
						
						if(flights[j] == true && seat_vip >8)
							setColor("GREEN");
							
						else if(seat_vip <= 8 && flights[j] != false)
							setColor("YELLOW");
							
						else
							setColor("RED");
							
						if(count == 8){
							
							printf("%d%s   \n\n", j+1, flights[j] == true ? "[L]" : "[R]");
							count = 0;
						}
						else
							printf("%d%s   ", j+1, flights[j] == true ? "[L]" : "[R]");
						}
}

int main(void){
	
	setlocale(LC_ALL, "portuguese");
	
	
	int option, i, j, k, count, seat_vip, num_flight, num_seat, access = 0, confirm;
	
	double value_passage;
	
	bool flights[4][38], isOk;
	
	for(k = 0; k < 38; k++){
		
		flights[0][k] = true;
		flights[1][k] = true;
		flights[2][k] = true;
		flights[3][k] = true;
		
	}
	
	int size_flights = sizeof(flights) / sizeof(flights[0]);
	int size_flights_2 = sizeof(flights[0]) / sizeof(flights[0][0]);
	
	char * options[5] = { "1 - Consultar Trechos", "2 - Consultar assentos", "3 - Efetuar reserva", "4 - Cancelar reserva", "5 - Finalizar atendimento"};
	
	// declaração de variavel size para obter o valor do tamanho  do array, e variavel i para ser o contador no for
	int size = sizeof(options) / sizeof(options[0]);
	
	do{
	
		printf("Escolha uma opção : \n\n");
		
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
			
			case 1:
				
				/* LISTA DOS VOOS */
				
				for(i = 0; i < size_flights; i++){
					
					printf("\n\nVOO %d : \n\n", i+1);
					
					showSeats(size_flights_2, flights[i]);
					setColor("DEFAULT");
				}
				
				printf("\n\n");
				
			break;
			
			case 2:
				
				do{

					printf("\n\ninsira o numero do VOO ou -1 para cancelar : ");
					scanf("%d", &num_flight);
					
					if(num_flight <= 0 || num_flight > 4){
					
						printf(num_flight != -1 ? "Número De Voo Inexistente , tente novamente . \n" : "\n");
						isOk = false;
					}
							
					else{
						
						printf("\n\nVOO %d : \n\n", num_flight);
				
						showSeats(size_flights_2, flights[num_flight-1]);
						setColor("DEFAULT");
						
					}
					
					printf("\n\n");
					
				}while(isOk != true && num_flight != -1);
				
			break;
				
			case 3:
				
				value_passage = 0;
				do{
					
					
					printf("\n\ninsira o numero do VOO ou -1 para cancelar : ");
					scanf("%d", &num_flight);
					
					if(num_flight <= 0 || num_flight > 4){
					
						printf(num_flight != -1 ? "Número De Voo Inexistente , tente novamente . \n" : "\n");
						isOk = false;
					}
					
					
					
					else{
						
						bool hasVacancy = in_array_bool(true, flights[num_flight-1]);
						
						if(!hasVacancy){
							printf("Este Voo Não Possui Mais Vagas .");
						}
						
						else					
						{							
							
							printf("\ninsira o numero do assento que deseja reservar : ");
							scanf("%d", &num_seat);	
							
							if(num_seat <= 0 || num_seat > 37 ){
							
								printf("Número De Assento Inexistente, Por Favor Escolha outro . \n");
								isOk = false;
							}
								
							else{
								
								if(flights[num_flight-1][num_seat-1] == false){
								
									printf("Este Assento Já Está Ocupado , Escolha Outro Por Favor .\n");
									isOk = false;
								}
									
								else{
								
									flights[num_flight-1][num_seat-1] = false;
									
									if( num_seat <= 8 )
										value_passage += 150.00;
									else 
										value_passage += 80.00;
										
									isOk = true;
									
									access += 1;
								}
							}
						}
					}
					
					
					
				}while(isOk != true && num_flight != -1 || num_flight != -1 && access != 2);
				
				access = 0;
				
				printf("\nValor da compra : R$ %.2f\n\n", value_passage);	
					
								
			break;
			
			case 4:
				
				do{

					printf("\n\ninsira o numero do VOO ou -1 para voltar ao menu : ");
					scanf("%d", &num_flight);
					
					if(num_flight <= 0 || num_flight > 4){
					
						printf(num_flight != -1 ? "Número De Voo Inexistente , tente novamente . \n" : "\n");
						isOk = false;
					}
					
					else{
						
						printf("\ninsira o numero do assento que deseja cancelar a reserva : ");
						scanf("%d", &num_seat);	
						
						if(num_seat <= 0 || num_seat > 37 ){
						
							printf("Número De Assento Inexistente, Por Favor Escolha outro . \n");
							isOk = false;
						}
							
						else{
							
							if(flights[num_flight-1][num_seat-1] == true){
							
								printf("Este Assento Não Está Ocupado , Escolha Outro Por Favor .\n");
								isOk = false;
							}
								
							else{
							
								flights[num_flight-1][num_seat-1] = true;
								isOk = true;
							}
						}
					}
					
				}while(isOk != true && num_flight != -1);
				printf("\n");
				
			break;
			
			default:
				printf(option != 5 ? "\nopção '%d' inexistente , tente novamente . \n\n" : "\n", option);
		}
		
	}while(option != 5);
	
	printf("\nObrigado por utilizar a linha Aviação Trem de Pouso, tenha um bom dia .\n");
	printf("\naperte qualquer tecla para sair !");
	
	/*
		system("pause");
		return 0;
	*/
}	

