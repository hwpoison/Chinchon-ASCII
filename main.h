/*=========================================================*/
	//nota:aplicar uso de comodin
	//quitar auto-ordenamiento en buscar_parejas()
	//comprobar cruces en parejas que autorizan el juego
/*=========================================================*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
   

#define CANTIDAD_CARTAS 50
#define CANTIDAD_MANO 7
#define CICLOS_MEZCLA 15000
#define LONG_PAREJAS 3
#define CANTIDAD_PAREJAS 2

#define TECLA_O 111
#define TECLA_DERECHA 75
#define TECLA_IZQUIERDA 77
#define TECLA_ESCAPE 27
#define TECLA_ESPACIO 32
#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define TECLA_ENTER 13
enum bool {False, True};


//propiedades mesa
typedef struct {
	short 		ord_mano;//si se ordena la mano
	short 		tecla_actual;//tecla actual pulsada
	short 		pos_flecha;//posicion de la flecha en la mano
	short 		en_juego;//si se esta jugando
	short 		turno_actual;//1 es pc, 2 es jugador
	short		vrf_mov;//verifica si se necesita re imprimir la pantalla
	short 		selec_mod;//modo seleccion - flecha horizontal
	short 		carta_tomada;//carta tomada por la flecha
	
	short 		menu_acciones_juego;//activacion de menu de opciones
	short 		selec_accion;//verifica si se selecciono alguna accion
	short 		pos_accion;//posicion de accion en menu
	short		carta_en_slot;//si el slot esta vacio o con una carta
	short   	carta_slot;//que carta contiene el slot
	
	short 		c_cartas_tiradas;//Lleva el control de las cartas tiradas, siempre va a ser la de arriba
	short 		cartas_tiradas[40];//cartas tiradas en la mesa
}interfc;


void imp_mano(int array_cartas[], int cantidad_mano, int arriba_abajo,int carta_sel);//imprime en pantalla mano del usuario
int imprimir_mesa(int mano_computadora[],int mano_jugador[], int mazo[], int *c_actual, interfc *Mesa);
void cambiar_posicion_carta(int mano[], int carta_uno, int carta_dos);//par aordenar la mano
void repartir(int mazo[], int mano[],int *c_actual);//reparte cartas a una mano
int  sacar_carta_superior(int mazo[], int *c_actual);//quita la carta superior del mazo
void mezclar_cartas(int mazo[], int *c_actual);//mezcla las cartas
void ver_mazo(int mazo[], int *c_actual);//imprime el mazo
int  numero_de_carta(int codigo_carta);//devuelve numero por codigo de carta
int  palo_de_carta(int codigo_carta);//devuelve el palo de carta por codigo
int carta(int numero, char *palo);//devuelve codigo de carta
void fragmento_carta(int,int,int,int);//imprime fragmento de carta
int buscar_pareja(int mano[],int ordenar, int log);
void ordenar_mano(int array[],int);
void iniciar_mazo(int mazo[]);//inicializa el mazo
void ver_mano(int mano[]);//imprime una mano
void imp_palo(int palo);
void logo_principal();//logo    
                     

#include "f_impresion.c"
#include "f_mazo.c"
