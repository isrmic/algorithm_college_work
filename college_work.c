#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

// funcao para setar uma cor para a fonte do console
void setColor(const char * Color){
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//Cor vermelha
	if(strcmp(Color, "RED") == 0){
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	}
	
	//Cor Verde
	else if(strcmp(Color, "GREEN") == 0){
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	}
	
	//Cor Azul
	else if(strcmp(Color, "BLUE") == 0){
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	}
	
	//Cor amarela
	else if(strcmp(Color, "YELLOW") == 0){
		SetConsoleTextAttribute(hConsole, 6);
	}
	
	//Cor Padrão white(branco)
	else if(strcmp(Color, "DEFAULT") == 0){
		SetConsoleTextAttribute(hConsole, 15);
	}

}

//funcao para verificar em um array booleano se existe X condicao , sendo ela true ou false ...
bool in_array_bool(bool condiction, bool * param){
	int size = sizeof(param) / sizeof(param[0]), i;
	for(i = 0; i < size; i++){
		if(param[i] == condiction)
			return true;
	}
	
	//caso nao seja encontrado nenhuma condicao no array da qual foi passado por parametro retorna false
	return false;
	
}


//funcao para imprimir a lista de lugares de determinado VOO 
void showSeats(int size, bool * flights){
	
	int j, count, seat_vip;
	for(j = 0, count = 1,seat_vip = 1; j < size; j++,count++,seat_vip++){
						
				//se as poltronas não forem de primeira classe e não estiverem ocupadas são coloridas de verde
				if(flights[j] == true && seat_vip >8)
					setColor("GREEN");
				
				//se as poltronas são de primeira classe e não estão ocupadas são coloridas de amarelo
				else if(seat_vip <= 8 && flights[j] != false)
					setColor("YELLOW");
				
				// Não sendo nenhum dos casos acima colore de vermelho , pois está reservada
				else
					setColor("RED");
				
				// se ja foram 8 poltronas impressas haverá uma quebra de linha , isso a cada 8 poltronas impressas
				if(count == 8 && seat_vip == 8){
                         
                    printf("%d%s   \n\n", j+1, flights[j] == true ? "[L]" : "[R]");							
					//seta o numero de poltronas impressas para 0 para retornar a imprimir uma ao lado da outra
					count = 0;
				}

				// caso não forem 8 ao todo impressas continuam imprimindo uma ao lado da outra .
				else if(seat_vip <8){
                    
                    if(seat_vip == 2 || seat_vip == 6)
				    	printf("%d%s", j+1, flights[j] == true ? "[L]" : "[R]");
				    	
					else if(seat_vip == 4 || seat_vip == 8)
					    printf("%d%s  \n\n", j+1, flights[j] == true ? "[L]" : "[R]");
					    
                    else
					    printf("       %d%s ", j+1, flights[j] == true ? "[L]" : "[R]");
                }
                else{
                    
                    if(count == 3)
                        printf("%d%s       ", j+1, flights[j] == true ? "[L]" : "[R]");             
                    
                    else if(count == 6){

                        printf("%d%s \n\n", j+1, flights[j] == true ? "[L]" : "[R]");
                        count = 0;
                    }
                    
                    else
                        printf(j+1 == 9 ? " %d%s " : "%d%s ", j+1, flights[j] == true ? "[L]" : "[R]");
                }
                
       }
}

int main(void){
	
	setlocale(LC_ALL, "portuguese");
	
	// declaracao de variaveis iniciais
	int option, i, j, k, count, seat_vip, num_flight, num_seat, access = 0, confirm, num_reserve;
	
	double value_passage;
	
	bool flights[4][38], isOk;
	
	//preenchimento dos lugares , sendo inicialmente quando compilar e executar o codigo true para todos (todos lugares disponiveis)
	for(k = 0; k < 38; k++){
		
		flights[0][k] = true;
		flights[1][k] = true;
		flights[2][k] = true;
		flights[3][k] = true;
		
	}
	
	//abaixo pegamos o tamanho do array (não em bytes) e o tamanho de cada indice do array
	int size_flights = sizeof(flights) / sizeof(flights[0]);
	int size_flights_2 = sizeof(flights[0]) / sizeof(flights[0][0]);
	
	const char * options[5] = { "1 - Consultar Trechos", "2 - Consultar assentos", "3 - Efetuar reserva", "4 - Cancelar reserva", "5 - Finalizar atendimento"};
	
	// declaração de variavel size para obter o valor do tamanho  do array, e variavel i para ser o contador no for
	int size = sizeof(options) / sizeof(options[0]);
	
	//imprime mensagem de boas vindas .
	system("Color 03");
	printf("            -------- Seja Bem Vindo A Aviação Trem De Pouso ------- \n\n");
    setColor("DEFAULT");
	
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
		
		//aqui usa-se switch case para filtrar as opcoes que foram dadas na entrada do usuário
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
			
			/* Aqui verifica-se os lugares dos voos e lista os para o usuário */
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
			
			/* Aqui é feito a reserva das poltronas podendo reservar no maximo duas vezes por cada acesso */
			case 3:
				
				value_passage = 0;

				printf("\n\ninsira quantas reservas deseja efetuar (1/2) ou -1 para sair : ");
				scanf("%d", &num_reserve);
				
				if(num_reserve <= 0 || num_reserve > 2)
					printf(num_reserve == -1 ? "\nOperação cancelada .\n\n" :"\nSó pode ser reservado 1 ou 2 poltronas .\n\n");
				
				else {
	
					//repete-se a escolha de opcoes caso a entrada for diferente de -1 e não estiver Ok a reserva de poltronas
					do{
						printf("\nreserva de número %d", access+1);											
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
								
								if(num_seat <= 0 || num_seat > 38 ){
								
									printf("Número De Assento Inexistente, Por Favor Escolha outro . \n");
									isOk = false;
								}
									
								else{
									
									if(flights[num_flight-1][num_seat-1] == false){
									
										printf("Este Assento Já Está Ocupado , Escolha Outro Por Favor .\n");
										isOk = false;
									}
										
									else{
										
										access += 1;							
										
											
										isOk = true;
										
										do{
											
												printf("Deseja Confirmar A Reserva ( 1 - Sim  2 - Não ? ) : ");
												scanf("%d", &confirm);
												
												if(confirm < 0 && confirm > 2)
													printf("Valor de entrada inválido .\n");
													
												else if(confirm == 1){
													
													flights[num_flight-1][num_seat-1] = false;
											
													if( num_seat <= 8 )
														value_passage += 150.00;
													else 
														value_passage += 80.00;
													if(access == num_reserve){
														printf("\nValor da(s) reserva(s) : R$ %.2f\n\n", value_passage);
													}	
												}
											
										}while(confirm != 1 && confirm != 2);
										
									}
								}
							}
						}
						
					}while(isOk != true && num_flight != -1 || num_flight != -1 && access != num_reserve);
				}
				access = 0;
					
				
			break;
			
			/* Aqui é aonde o usuário cancela uma reserva feito indicando o VOO e o numero do lugar reservado */
			case 4:
				
				// estrutura de repeticao , repete-se caso não for -1 a entrada do usuário ou não estiver Ok a cancela da reserva .
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
						
						if(num_seat <= 0 || num_seat > 38 ){
						
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
								printf("\nReserva cancelada com sucesso  .\n");
							}
						}
					}
					
				}while(isOk != true && num_flight != -1);
				printf("\n");
				
			break;
			
			/* Caso nenhuma das opcoes acima tiver sido a entrada então puala para cá e retorna para o menu de opcoes logo em seguida */
			default:
				printf(option != 5 ? "\nopção '%d' inexistente , tente novamente . \n\n" : "\n", option);
		}
		
	}while(option != 5);
	
	// ao finalizar toda a tarefa não tendo mais neccessidade de fazer algo no sistema o usuário pula para cá e pode-se finalizar o programa...
	printf("\nObrigado por utilizar a linha Aviação Trem de Pouso, tenha um bom dia .\n");
	//printf("\naperte qualquer tecla para sair !\n");
	
	//comentado por causa de outros dev c++ que não precisam de system("pause") e return 0 ...
	
		system("pause");
		return 0;
	
}	

