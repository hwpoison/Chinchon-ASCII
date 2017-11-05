void repartir(int mazo[], int mano[],int *c_actual)
{
	/*Quita cartas del mazo para repartirsela a una mano
	 * tomando en cuenta el maximo de reparte*/
	int c;
	for(c=0;c < CANTIDAD_MANO;c++)
	{
		mano[c] = sacar_carta_superior(mazo,c_actual);
	}
}


int sacar_carta_superior(int mazo[],int *c_actual)
{
	/*Saca la carta superior de la baraja*/
	int carta_superior = mazo[*c_actual];
	if(*c_actual == 0  || *c_actual < CANTIDAD_MANO)
	{
		printf("No hay mas cartas!");
		return 0;
	}
	mazo[*c_actual] = 0;
	*c_actual -=1;
	return carta_superior;
}


void mezclar_cartas(int mazo[],int *c_actual)
{
	/*Mezcla las cartas del mazo en un orden secuencial
	 * aleatorio la cantidad de ciclos que se especifique
	 * en el simbolico "CICLOS_MEZCLA"*/
	int cnt;//No puede ser short por que excede el umbral de 4 bytes con el conteo
	short tmp;
	int c_select1,c_select2;
	for(cnt=0;cnt<CICLOS_MEZCLA;cnt++)
	{
		/*Selecciona dos cartas al azar y las intercambia*/
		c_select1 = rand()% (*c_actual+1);
		c_select2 = rand()% (*c_actual+1);
		/*Si son iguales se busca otra al azar*/
		if(c_select1 == c_select2)
			c_select1 = rand()% (*c_actual+1);
		tmp = mazo[c_select1];
		mazo[c_select1] = mazo[c_select2];
		mazo[c_select2] = tmp;
	}
}


void ordenar_mano(int mano[], int codigo_numero)
{
	/*Ordena una mano por el numero de carta normal
	 * o por su codigo*/
	short cn1,cn2,buff;
	for(cn1=1;cn1<=CANTIDAD_MANO;cn1++){
		for(cn2=0;cn2<CANTIDAD_MANO-cn1;cn2++)
		{
			if(codigo_numero == 1)//Ordenar por numero de carta
			{
				if(numero_de_carta(mano[cn2]) > numero_de_carta(mano[cn2+1]))
				{
					buff = mano[cn2];
					mano[cn2] = mano[cn2+1];
					mano[cn2+1] = buff;
				}
			}
			else
			{
				if(mano[cn2] > mano[cn2+1])//Ordenar por codigo de carta
				{
					buff = mano[cn2];
					mano[cn2] = mano[cn2+1];
					mano[cn2+1] = buff;
				}
			}
		}
	}
}

int carta(int numero, char *palo)
{
	/*Devuelve codigo de carta predeterminada
	 * usando el numero real con el nombre
	 * para facilitar la obtencion de un codigo*/
	if(!strcmp(palo,"basto")){
		return numero;
				
	}else if(!strcmp(palo,"espada")){
		return 12+numero;
				
	}else if(!strcmp(palo,"copa")){
		return 24+numero;
				
	}else if(!strcmp(palo,"oro")){
		return 36+numero;
	
	}else if(!strcmp(palo,"comodin")){
		return 50;
		
	}else if(!strcmp(palo,"abajo")){
		return -1;
		
	}else{
		return 0;
	}
	return 0;
}


void cambiar_posicion_carta(int mano[], int carta_uno, int carta_dos)
{
	/*Intercambia la posicion de una carta dentro de una mano
	 * por otra*/
	short tmp;
	tmp = mano[carta_uno];
	mano[carta_uno] = mano[carta_dos];
	mano[carta_dos] = tmp;
}


void iniciar_mazo(int mazo[])
{
	short c_cartas;
	for(c_cartas=1;c_cartas < CANTIDAD_CARTAS+1;c_cartas++)
	{
		mazo[c_cartas-1] = c_cartas;
	};
}


int palo_de_carta(int codigo_carta)
{
	/*Devuelve el palo de la carta 
	 * tomando como entrada el codigo de la misma*/
	if(codigo_carta <= 12){
		return 1;/*Basto*/
	}else if(codigo_carta >= 13 && codigo_carta <= 24){
		return 2;/*Espada*/
	}else if(codigo_carta >= 25 && codigo_carta <= 36){
		return 3;/*Copa*/
	}else if(codigo_carta <= 48){
		return 4;/*Oro*/
	}
	return 0;/*comodin*/
}


int numero_de_carta(int codigo_carta)
{
	/*Devuelve el numero de la carta tomando
	 * como entrada el codigo de la misma*/
	if(codigo_carta >= 1 && codigo_carta <=12){
		return codigo_carta;
	}else if(codigo_carta >= 13 && codigo_carta <= 24){
		return codigo_carta  - 12;
	}else if(codigo_carta >= 25 && codigo_carta <= 36){
		return codigo_carta  - 12*2;
	}else if(codigo_carta >= 37 && codigo_carta <= 48){
		return codigo_carta  - 12*3;
	}else{
		return 0;
	}
	return 0;
}

