#include "main.h"
/*=========================================================*/
//NOTAS DE VERSION
//16/03/17
//26/03/2017
//04/04/2017
//05/04/2017
/*=========================================================*/
/*
 * CODIGOS CARTA
1 - 12 < basto 1
13 -  24 < espada  2
25 - 36 < copa 3
37 - 48 < oro 4
* 49-50 < comodines 5
*/

int main(int argc, char *argv[])
{
	srand(time(NULL));
	/*Parametros ventana CMD Windows*/
	system("title El chinchon - v1 - srBill");//titulo
	system("@mode con cols=100 lines=50");//dimensiones ventana
	
	/*Se inicializa el mazo*/
	int c_actual = CANTIDAD_CARTAS-1;//Variable control de cartas en el mazo
	int mazo[CANTIDAD_CARTAS];//Mazo principal
	iniciar_mazo(mazo);
	mezclar_cartas(mazo, &c_actual);
	
	/*Se inicializan las manos*/
	int mano_jugador[CANTIDAD_MANO] = 
	{
			carta(3,"oro"),carta(4,"oro"),carta(5,"oro"),
			
			carta(8,"oro"),carta(8,"copa"),carta(8,"espada"),
			
			carta(5,"comodin")
			
	};
	int mano_computadora[CANTIDAD_MANO];
	/*Se reparten las cartas*/
	repartir(mazo, mano_computadora, &c_actual);
	//repartir(mazo, mano_jugador, &c_actual);//anula la definicion anterior
	short carta_en_mesa = sacar_carta_superior(mazo,&c_actual);
	/*Inicio de interfaz*/
	interfc Interfaz;
	Interfaz.ord_mano = 0;
	Interfaz.pos_flecha = 0;
	Interfaz.en_juego = 1;
	Interfaz.c_cartas_tiradas = 0;
	Interfaz.cartas_tiradas[Interfaz.c_cartas_tiradas] = carta_en_mesa;//se tira la carta inicial
	Interfaz.turno_actual = 2;
	Interfaz.vrf_mov = 1;
	Interfaz.carta_tomada = -1;
	Interfaz.menu_acciones_juego = 0;
	Interfaz.selec_mod = 0;
	Interfaz.pos_accion = 1;
	Interfaz.selec_accion = 0;
	Interfaz.carta_slot = 0;
	Interfaz.carta_en_slot = 0;
	
	
	/*El bucle principal junto a la funcion de impresion en pantalla
	 * controlan la logica y transcurso del juego*/
	while(Interfaz.en_juego)
	{
		imprimir_mesa(
					mano_computadora,
					mano_jugador,
					mazo,
					&c_actual,
					&Interfaz
				);
		if(!Interfaz.vrf_mov)
			Interfaz.vrf_mov = 1;
			
		Interfaz.tecla_actual = getch();
		//printf("%d\n",Interfaz.tecla_actual);
		switch(Interfaz.tecla_actual)//CONTROL TECLADO
		{
				case TECLA_DERECHA://Mover flecha a izq
						if(Interfaz.pos_flecha>0)
							Interfaz.pos_flecha--;
						else
							Interfaz.vrf_mov = 0;
						break;
			
				case TECLA_IZQUIERDA://Mover flecha a der
						if(Interfaz.pos_flecha < CANTIDAD_MANO-1)
							Interfaz.pos_flecha++;
						else
							Interfaz.vrf_mov = 0;
						break;
			
				case TECLA_ESCAPE://Salir
						Interfaz.en_juego = 0;
						system("cls");
						printf("Se salio del juego\n");
						break;
			
				case TECLA_O://Ordenar mano
						if(!Interfaz.ord_mano)
							Interfaz.ord_mano = 1;
						break;
				
				case TECLA_ESPACIO://Seleccionar carta
						if(Interfaz.selec_mod){
							Interfaz.selec_mod = 0;
						}else{
							Interfaz.selec_mod = 1;
						}
						break;
						
				case TECLA_ARRIBA://Abrir menu
						if(Interfaz.menu_acciones_juego)
							Interfaz.menu_acciones_juego = 0;
						else
							Interfaz.menu_acciones_juego = 1;
						break;
						
				case TECLA_ABAJO:
						/*Controla el menu de opciones*/
						if(Interfaz.menu_acciones_juego){
							if(Interfaz.pos_accion == 3)
								Interfaz.pos_accion = 1;
							else
								Interfaz.pos_accion++;
						}else{
							Interfaz.vrf_mov = 0;
						}
						break;
				case TECLA_ENTER:
						/*Controla seleccion de opcion en menu*/
						if(Interfaz.selec_accion)
							Interfaz.selec_accion = 0;
						else
							if(Interfaz.menu_acciones_juego)
								Interfaz.selec_accion = 1;
							
						break;
				default:
						Interfaz.vrf_mov = 0;
		};

	}
	return 0;
};


int imprimir_mesa(
		int mano_computadora[],
		int mano_jugador[],
		int mazo[],
		int *c_actual,
		interfc  *Interfaz)
{
	/*Descripcion:Esta parte se encarga de acomodar la secuencia de impresion
	 * asi como los estados del juego e interfaz tomando referencias de las variables 
	 * de la estructura "Interfaz"
	*/
	short 		cnt;
	short 		cnt2;
	char 		flecha_normal[7] 	= 	"/__\\";
	char 		flecha_pulsada[7] 	=	 "/\\";
	//ACCIONES DE LEVANTAR O TIRAR CARTA
	short 		accion 				= 	Interfaz->pos_accion;
	short 		selec 				= 	Interfaz->selec_accion;
	short 		s_carta				=	Interfaz->carta_en_slot;
	short 		turno 				=   Interfaz->turno_actual;
	short 		tmp;
	
	if(!Interfaz->vrf_mov)//Si no se apreto nada valido no se redibuja la pantalla
		return 0;

	system("cls");//Se limpia la pantalla primero

	//COLOR DURANTE SELECCION DE ACCION O CARTA
	if(Interfaz->selec_mod)
	{
		system("color f");
	}else{
		system("color 7");
	}
	//IMPRESION DE LOGO EN PANTALLA
	logo_principal();
	
	//ORDENAMIENTO DE CARTAS
	if(Interfaz->ord_mano)
	{
		Interfaz->selec_mod = 0;
		ordenar_mano(mano_jugador,1);
		Interfaz->ord_mano = 0;
	}
	
	//COMPUTADORA
	printf("  PC:\n");
	imp_mano(mano_computadora,CANTIDAD_MANO,1,-1);  //.var 3 para test boca arriba,cambiar
	printf("\n\n");
	
	//MENU Acciones JUEGO
	if(turno && Interfaz->menu_acciones_juego && !Interfaz->selec_accion){
		printf("Elegir una accion:\n");
		if(!Interfaz->carta_en_slot)
		{
			printf("  %sTomar carta de la mesa\n",				((Interfaz->pos_accion==1 )?">":""));
			printf("  %sTomar carta del mazo\n",				((Interfaz->pos_accion==2 )?">":""));
		}else{
			printf("  %sUsar/Cambiar\n",						((Interfaz->pos_accion==1 )?">":""));
			printf("  %sTirar carta adicional\n",				((Interfaz->pos_accion==2 )?">":""));
		}
		printf("  %sCortar con carta seleccionada de mano\n",	((Interfaz->pos_accion==3 )?">":""));
		
	}
	
	if(turno)//Si es turno del jugador
	{
		printf("Es tu turno!\n");
		//Se tira la carta del slot a  la mesa y finaliza turno
		if(Interfaz->menu_acciones_juego && accion == 2 && selec && s_carta)
		{	
				Interfaz->c_cartas_tiradas++;
				Interfaz->cartas_tiradas[Interfaz->c_cartas_tiradas] = Interfaz->carta_slot;
				Interfaz->carta_en_slot = 0;
				Interfaz->turno_actual = 0; 
		}
		//Se toma carta del mazo al slot
		if(Interfaz->menu_acciones_juego && accion == 2 && selec && !s_carta)
		{
				Interfaz->carta_slot = sacar_carta_superior(mazo, c_actual);
				Interfaz->carta_en_slot = 1;
		}
		//Cambiar carta seleccionada de mano por la del slot
		if(Interfaz->menu_acciones_juego && accion == 1 && selec && s_carta)
		{
				tmp = mano_jugador[Interfaz->pos_flecha];
				mano_jugador[Interfaz->pos_flecha] = Interfaz->carta_slot;
				Interfaz->carta_slot = tmp;
		}
		//Si se toma la carta de la mesa
		if(Interfaz->menu_acciones_juego && accion == 1 && selec && !s_carta )
		{
				printf("Se tomo la carta:%d\n",Interfaz->cartas_tiradas[Interfaz->c_cartas_tiradas]);
				Interfaz->carta_slot = Interfaz->cartas_tiradas[Interfaz->c_cartas_tiradas];
				Interfaz->carta_en_slot= 1;
				Interfaz->c_cartas_tiradas--;
				accion = 2;
		}
		//Cortar juego
		if(Interfaz->menu_acciones_juego && accion == 3 && selec && !s_carta)
		{
				tmp = buscar_pareja(mano_jugador,0,0);
				if(tmp)
				{
					int carta_cortar_seleccionada = mano_jugador[Interfaz->pos_flecha];
					if(carta_cortar_seleccionada == tmp)
					{
						printf("\nCortaste el juego con %d de ",numero_de_carta(carta_cortar_seleccionada));
						imp_palo(palo_de_carta(carta_cortar_seleccionada));
						printf(" HAZ GANADO!!");
						printf("\n");
					}else{
						printf("\nNo se puede cortar con %d de ",numero_de_carta(carta_cortar_seleccionada));
						imp_palo(palo_de_carta(carta_cortar_seleccionada));
						printf("\n");
					}
				}else{
					printf("No hay jeugo\n");
				}
		}else if(s_carta)
		{
			printf("No se puede cortar por que hay una carta por tirar!\n");
		}
	}
	if(!Interfaz->turno_actual)//Turno de la computadora
	{
		printf("Es turno de la computadora!\n");
		
	}
	
	//MAZO CENTRAL Y CARTA ADICIONAL DE MANO DE JUGADOR
	for(cnt=0;cnt < 8;cnt++){
		printf("%12s"," ");
		//DIBUJO DE MAZO
		fragmento_carta(-1,cnt,5,0);
		printf("%2s"," ");
		//CARTA BOCA ARRIBA EN MESA
		fragmento_carta(
				numero_de_carta(Interfaz->cartas_tiradas[Interfaz->c_cartas_tiradas]),
				cnt,
				palo_de_carta(Interfaz->cartas_tiradas[Interfaz->c_cartas_tiradas]),
				0
		);
		printf("%33s"," ");
		//SLOT DE CARTA DE JUGADOR
		if(Interfaz->carta_en_slot)//Se toma carta de la mesa
		{
				fragmento_carta(
								numero_de_carta(Interfaz->carta_slot),
								cnt,
								palo_de_carta(Interfaz->carta_slot),
								0
				);
				
		}else if(!Interfaz->carta_en_slot){
				//slot de carta vacio
				fragmento_carta(-2,cnt,6,0);
		}
		printf("\n");
	}
	
	//Luego de eleccion de accion
	if(Interfaz->menu_acciones_juego && Interfaz->selec_accion){
		printf("Se eligio una accion (la %d)\n",Interfaz->pos_accion);
		Interfaz->selec_accion = 0;//se setea a 0 luego de elegir
		Interfaz->menu_acciones_juego = 0;
	}
	//JUGADOR
	printf("\n  JUGADOR:\n");
	
	/*Seleccionar y mover carta*/
	if(Interfaz->carta_tomada>=0){//Acomodo de cartas en la mano
			cambiar_posicion_carta(mano_jugador, Interfaz->carta_tomada, Interfaz->pos_flecha);
			Interfaz->carta_tomada = Interfaz->pos_flecha;
	}
	
	/*Resaltar carta seleccionada*/
	if(Interfaz->selec_mod){
		if(!Interfaz->carta_tomada>=0){
				Interfaz->carta_tomada = Interfaz->pos_flecha;
		}
		imp_mano(mano_jugador, CANTIDAD_MANO,1,Interfaz->carta_tomada);
	}else{
		Interfaz->carta_tomada = -1;
		imp_mano(mano_jugador, CANTIDAD_MANO,1,-1);
		
	}

	/*Movimiento de la flecha*/
	for(cnt=0;cnt < CANTIDAD_MANO;cnt++){
		if(Interfaz->pos_flecha == cnt){
			for(cnt2=0;cnt2<11*cnt;cnt2++)
			{
				printf(" ");
			}
			if(Interfaz->selec_mod)
			{
				printf("%4s%s\n"," ",flecha_pulsada);

			}
			else
			{
				printf("%4s%s\n"," ",flecha_normal);
			}
		}
	}
	printf("\n");

	buscar_pareja(mano_jugador,1,1);
	return 0;
}


int buscar_pareja(int mano_[], int ordenar, int log) 
{
	/*Busca parejas o posibles parejas dentro de una mano
	 * para formar el juego, retorna 1 si hay juego y -1 si no
	 * La carta a cortar es solo para la pc
	 * */
	int 	mano[8];//Declara el array para tomar una copia de la mano en caso de no formalizarla en el juego
	//contadores
	short		cnt;//contador reutilizable
	short 	aux;
	short 	cn;
	short 	verificacion = False;//comprueba si se encontro una forma de ganar
	short 	carta_cortar;
	//pos comodines
	short comodin_1 = 0;
	short comodin_2 = 0;
	for(cnt=0;cnt < CANTIDAD_MANO;cnt++)
		mano[cnt] = mano_[cnt];
	
	int c_parejas = 0;//cantidad total parejas
	int c_buff;//coincidencias
	
	//Extraccion de posicion de los comodines (si hay)
	ordenar_mano(mano,2);
	for(cnt=0;cnt < CANTIDAD_MANO;cnt++)//SOPORTE 2 COMODINES
	{
		if(mano[cnt] >= 49)
		{
			if(!comodin_1)
				comodin_1 = cnt;
			else
				comodin_2 = cnt;
		}
	}
	

	//Localizar escalera
	for(cnt=0; cnt < CANTIDAD_MANO; cnt++)
	{
		if(c_buff == CANTIDAD_MANO-2)
		{
			printf("Escalera\n");
			verificacion = True;
		}
		if(mano[cnt] == mano[cnt+1]-1)
		{
			c_buff++;
		}else{
			c_buff = 0;
		}
	}
	
	//Localizar parejas ascendentes
	/*En conjuncion con el codigo de deteccion de parejas iguales
	 * va intercalando posiciones y buscando coincidencias con el consiguiente
	 * codigo o numero en orden, si el siguiente del siguiente no es valido
	 * se asume que es inconcluso y si falta se completa con un comodin
	 * Luego de la deteccion se setean los x elementos de la pareja del array
	 * de "mano" y se continua al siguiente paso*/
	if(verificacion == False)
	{
		for(cnt=0; cnt < CANTIDAD_MANO; cnt++)
		{
			if(c_buff == LONG_PAREJAS-1)
			{
				if(log){
					printf("[+]Pareja ascendente de ");
					imp_palo(palo_de_carta(mano[cnt]));
					printf(" encontrada.\n");
				}
				c_parejas++;
				c_buff = 0;
				for(cn=0,aux=cnt;cn < LONG_PAREJAS;aux--,cn++)
					mano[aux] = 0;
			}
			if(mano[cnt] == mano[cnt+1]-1)
			{
				c_buff++;
			}else{
				if(c_buff == 1 && mano[cnt] != mano[cnt+1]-1)
				//if(c_buff == 1 && mano[cnt+1] != mano[cnt+2]-1)
				{
					if(comodin_1)
					{
						if(log)
						{
							printf("[+]Pareja ascendente de ");
							imp_palo(palo_de_carta(mano[cnt]));
							printf(" completada con un comodin\n");
						}
						cambiar_posicion_carta(mano, cnt+1, comodin_1);
						comodin_1 = 0;
						c_parejas++;
						for(cn=0,aux=cnt+1;cn < LONG_PAREJAS;aux--,cn++)
							mano[aux] = 0;
					}
					else
					{
						if(comodin_2)
						{
							if(log)
							{
								printf("[+]Pareja ascendente de "); 
								imp_palo(palo_de_carta(mano[cnt]));
								printf(" completada con un comodin\n");
							}
							cambiar_posicion_carta(mano, cnt+1, comodin_2);
							comodin_2 = 0;
							c_parejas++;
							for(cn=0,aux=cnt+1;cn < LONG_PAREJAS;aux--,cn++)
								mano[aux] = 0;
						}
					}
					
				c_buff = 0;
				}
			}
		}
		
		//Localizar Parejas de iguales
		ordenar_mano(mano,1);
		c_buff = 0;
		for(cnt=0;cnt < CANTIDAD_MANO; cnt++)
		{
			//iguales
			if(c_buff == LONG_PAREJAS-1)
			{
				if(log)printf("[+]Pareja Igual de %d's encontrada\n", numero_de_carta(mano[cnt]));
				c_parejas++;
				c_buff = 0;
				for(cn=0,aux=cnt;cn < LONG_PAREJAS;aux--,cn++)
				{
					mano[aux] = 0;
				}
			}
			if(mano[cnt] != 0 && numero_de_carta(mano[cnt]) == numero_de_carta(mano[cnt+1]))
			{
				c_buff++;
			}
			else
			{
				if(c_buff == 1 && numero_de_carta(mano[cnt]) != numero_de_carta(mano[cnt+1])) 
				{
					if(comodin_1)
					{
						if(log)printf("[+]Pareja de %d completada con comodin\n", numero_de_carta(mano[cnt]));
						cambiar_posicion_carta(mano, cnt+1, comodin_1);
						comodin_1 = 0;
						c_parejas++;
						for(cn=0,aux=cnt+1;cn < LONG_PAREJAS;aux--,cn++)
						{
							mano[aux] = 0;
						}
					}
					else
					{
						if(comodin_2)
						{
							if(log)printf("[+]Pareja %d completada con comodin\n", numero_de_carta(mano[cnt]));
							ver_mano(mano);
							cambiar_posicion_carta(mano, cnt+1, comodin_2);
							comodin_2 = 0;
							c_parejas++;
							for(cn=0,aux=cnt;cn < LONG_PAREJAS;aux--,cn++)
							{
								mano[aux] = 0;
							}
							ver_mano(mano);
						}
					}
				c_buff = 0;
				}
			}
		}
	}
	//Verificacion final
	if(verificacion == True || c_parejas == CANTIDAD_PAREJAS)
	{
		for(cnt=0;cnt < CANTIDAD_MANO;cnt++)//Se define la carta cortante
		{
			mano[cnt] != 0?(carta_cortar = mano[cnt]):0;
		}
		if(log)
		{
			printf("[+]Hay juego, se puede cortar con %d de ",numero_de_carta(carta_cortar));
			imp_palo(palo_de_carta(carta_cortar));
			printf("!!\n");
		}
		return carta_cortar;
	}else{
		if(log)
			printf("[-]No hay juego posible.\n");
		return 0;
	}
	return 0;
};

