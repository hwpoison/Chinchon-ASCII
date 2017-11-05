

void imp_mano(int array_cartas[], int cantidad_mano,int arriba_abajo,int carta_sel)
{
	/*Permite imprimir cantidad determinada de cartas en horizontal
	* para evitar construir una mano fija hace un barrido de impresion
	* secuencial por un bucle y el uso de la funcion "fragmento_carta" */
	short			c;
	short			c1;
	
	for(c1=0;c1<8;c1++){
		for(c=0;c<cantidad_mano;c++){
			if(array_cartas[c] == 49 || array_cartas[c] == 50)/*Si es comodin*/
			{
				printf(" ");
				if(arriba_abajo)
				{
						fragmento_carta(0,c1,0,0);
				}else{
						fragmento_carta(-1,c1,5,0);
	
				}
			}else if(array_cartas[c] >= 1 && array_cartas[c] <= 48)
			{
				printf(" ");
				if(arriba_abajo)
				{
					if(carta_sel == c)
						fragmento_carta(numero_de_carta(array_cartas[c]),c1,palo_de_carta(array_cartas[c]),1);	
					else
						fragmento_carta(numero_de_carta(array_cartas[c]),c1,palo_de_carta(array_cartas[c]),0);	
				}else{
					fragmento_carta(-1,c1,5,0);
				}
			}else{
				fragmento_carta(-1,c1,5,0);
			}
		}
		printf("\n");
	}
}

void fragmento_carta(int numero,int parte,int tipo,int seleccionada)
{
		char dibujo_basto[4][39] = 
		{
							"|   X   | ",
							"|    XX | ",
							"|  XX>  | ",
							"| X     | "
		};
		
		char dibujo_espada[4][39] = 
		{
							"|   *   | ",
							"|   *   | ",
							"| <<*>> | ",
							"|   !   | "
		};
		
		char dibujo_copa[4][39] = 
		{
							"| XXXXX | ",
							"|  XXX  | ",
							"|   !   | ",
							"|  XXX  | "
		};
		
		char dibujo_oro[4][39] =
		{
							"|  ***  | ",
							"| ** ** | ",
							"| ** ** | ",
							"|  ***  | "
		};
		
		char dibujo_comodin[4][39] = 
		{
							"| ##### | ",
							"|#      | ",
							"|#      | ",
							"| ##### | "
		};
		
		char dibujo_abajo[4][39] = 
		{
							"|XXXXXXX| ",
							"|XXXXXXX| ",
							"|XXXXXXX| ",
							"|XXXXXXX| "
		};
		
		char dibujo_vacia[4][39] = 
		{
							"|       | ",
							"|       | ",
							"|       | ",
							"|       | "
		};
		
		switch(parte)
		{
			case 0:
				 if(seleccionada){
					printf(">-------< ");
				 }else if(numero == -2){
					 printf("/.......\\ ");
				 }else{
					printf("+-------+ ");
				 }
				 break;
				 
			case 1:
				 if(numero>=10){
					printf("|%d     | ",numero);
				 }else if(numero == 0){
					printf("|?      | ");
				 }else if(numero == -1){
					printf("|XXXXXXX| ");
				 }else if(numero == -2){
					 printf("|       | ");
				 }else{
					printf("|%d      | ",numero);
				 }
				 break;
				 
			case 2:
				switch(tipo){
					case 0:
						printf("%s",dibujo_comodin[0]);
						break;
					case 1:
						printf("%s",dibujo_basto[0]);
						break;
					case 2:
						printf("%s",dibujo_espada[0]);
						break;
					case 3:
						printf("%s",dibujo_copa[0]);
						break;
					case 4:
						printf("%s",dibujo_oro[0]);
						break;
					case 5:
						printf("%s",dibujo_abajo[0]);
						break;
					case 6:
						printf("%s",dibujo_vacia[0]);
						break;
					default:
						printf("|       | ");
						break;
				}
				 break;
				 
			case 3:
				switch(tipo){
					case 0:
						printf("%s",dibujo_comodin[1]);
						break;
					case 1:
						printf("%s",dibujo_basto[1]);
						break;
					case 2:
						printf("%s",dibujo_espada[1]);
						break;
					case 3:
						printf("%s",dibujo_copa[1]);
						break;
					case 4:
						printf("%s",dibujo_oro[1]);
						break;
					case 5:
						printf("%s",dibujo_abajo[1]);
						break;
					case 6:
						printf("%s",dibujo_vacia[1]);
						break;
					default:
						printf("|       | ");
						break;
				}
				 break;
				 
			case 4:
				switch(tipo){
					case 0:
						printf("%s",dibujo_comodin[2]);
						break;
					case 1:
						printf("%s",dibujo_basto[2]);
						break;
					case 2:
						printf("%s",dibujo_espada[2]);
						break;
					case 3:
						printf("%s",dibujo_copa[2]);
						break;
					case 4:
						printf("%s",dibujo_oro[2]);
						break;
					case 5:
						printf("%s",dibujo_abajo[2]);
						break;
					case 6:
						printf("%s",dibujo_vacia[2]);
						break;
					default:
						printf("|       | ");
						break;
				}
				 break;
				 
			case 5:
				switch(tipo){
					case 0:
						printf("%s",dibujo_comodin[3]);
						break;
					case 1:
						printf("%s",dibujo_basto[3]);
						break;
					case 2:
						printf("%s",dibujo_espada[3]);
						break;
					case 3:
						printf("%s",dibujo_copa[3]);
						break;
					case 4:
						printf("%s",dibujo_oro[3]);
						break;
					case 5:
						printf("%s",dibujo_abajo[3]);
						break;
					case 6:
						printf("%s",dibujo_vacia[3]);
						break;
					default:
						printf("|       | ");
						break;
				}
				 break;
				 
			case 6:
				 if(numero>=10){
					printf("|     %d| ",numero);
				 }else if(numero == 0){
					printf("|      ?| ");
				 }else if(numero == -1){
					 printf("|XXXXXXX| ");
				 }else if(numero == -2){
					 printf("|       | ");
				 }else{
					printf("|      %d| ",numero);
				 }
				 break;
				 
			case 7:
				 if(seleccionada){
					printf(">-------< ");
				 }else if(numero == -2){
					 printf("......... ");
				 }else{
					printf("+-------+ ");
				 }
				 break;
				 
		}
};

void imp_palo(int palo)//imprime palo str
{
	/*Imprime un string del palo tomando como parametro
	 * el id del palo correspondiente de la carta*/
	switch(palo)
	{
			case 1:
				printf("Basto ");
				break;
			case 2:
				printf("Espada ");
				break;
			case 3:
				printf("Copa ");
				break;
			case 4:
				printf("Oro");
				break;
			default:
				printf("Comodin?");
				break;
	}
}


void ver_mazo(int mazo[],int *c_actual){
	/*Imprime el mazo elegido*/
	short c;
	for(c=0;c<CANTIDAD_CARTAS;c++)
		printf("%d ",mazo[c]);
	printf("\n");
}


void ver_mano(int mano[]){
	/*Imprime la mano elegida*/
	short cnt;
	for(cnt=0;cnt<CANTIDAD_MANO;cnt++)
		printf("%d ",mano[cnt]);
	printf("\n");
}

void logo_principal()
{
 char titulo[15] = "El Chinchon";
 printf("              <-------------------------  %s   ------------------------->\n",titulo);
}
