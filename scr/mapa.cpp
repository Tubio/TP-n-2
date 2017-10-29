# include "mapa.h"

Mapa::Mapa(int filaRecibida, int columnaRecibida, char dificultadRecibida){

	this-> dimFila = filaRecibida;
	this-> dimColumna = columnaRecibida;
	this-> dificultad = DificultadRecibida;
	
	crearListaMinasYAsignarPuntero();	
	crearListaCasillasYAsignarPuntero();
	crearListaBanderasYAsignarPuntero();
	
	Minero minero(dimFila,dimColumna,dificultad,pMinas);
	minero.sembrarMinas();
	this->baseMapa = crearBMP(dimFila, dimColumna);
	this->mapa.llenarMapaBloqueado(this->baseMapa);
	this->mapa.llenarEsquinas(this->baseMapa);
	this->mapa.llenarBordes(this->baseMapa);
}

/* Fuaaaa. Podemos hacer una clase DiosDelBMP y le pasamos un puntero al mapa, para no hacer todo esto acá así no queda
* tan grande.*/

void mapa::llenarEsquinas(this->baseMapa){

	llenarEsquinaSuperiorDerecha(this->baseMapa);
	llenarEsquinaSuperiorIzquierda(this->baseMapa);
	llenarEsquinaInferiorDerecha(this->baseMapa);
	llenarEsquinaInferiorIzquierda(this->baseMapa);

}
void llenarEsquinaSuperiorDerecha(BMP baseMapa){}
void llenarEsquinaSuperiorIzquierda(BMP baseMapa){}
void llenarEsquinaInferiorDerecha(BMP baseMapa){}
void llenarEsquinaInferiorIzquierda(BMP baseMapa){}

void mapa::llenarBordes(this->baseMapa){

	llenarBordeSuperior(this->baseMapa);
	llenarBordeInferior(this->baseMapa);
	llenarBordeIzquierdo(this->baseMapa);
	llenarBordeDerecho(this->baseMapa);

}
void llenarBordeSuperior(BMP baseMapa){

	for(int i= 0; (i<this->dimColumna)*2; i++){

			RangedPixelToPixelCopy(##,1,16,16,1,##baseMapa,(BORDES+1+(i*BORDES),1);
		}

}
void llenarBordeInferior(BMP baseMapa){

	for(int i= 0; (i<this->dimFila)*2; i++){

			RangedPixelToPixelCopy(##,1,16,16,1,##baseMapa,
					BORDES+1+(i*BORDES),BORDES+1(CASILLAS*this->dimFila),);
		}
}
void llenarBordeIzquierdo(BMP baseMapa){

	for(int i= 0; i<this->dimFila; i++){

		RangedPixelToPixelCopy(##,1,16,16,1,##baseMapa,1,(BORDES+1+(BORDES*i)));
	}

}
void llenarBordeDerecho(BMP baseMapa){

	for(int i= 0; i<this->dimFila; i++){

			RangedPixelToPixelCopy(##,1,16,16,1,##baseMapa,
					BORDES+1+((this->dimFila)*CASILLAS),BORDES+1+(CASILLAS+i));
		}
}

void mapa::llenarMapaBloqueado(BMP &baseMapa){

	for(int i=0; i<this->dimFila; i++){

		for(int j=0; j<this->dimColumna; i++){

			RangedPixelToPixelCopy(ARcasillasBloqueadas,1,16,16,1,basemapa,
					(BORDES+1)+(i*CASILLAS),(BORDES+1)+(i+CASILLAS))
		}
	}


}
BMP Mapa::crearBMP(unsigned int dimFila, unsigned int dimColumna){
	 unsigned int ancho = 0;
	 unsigned int alto = 0;
	ancho = calcularAncho(dimColumna);
	alto = calcularAlto(dimFila);

	BMP mapaVacio();
	mapaVacio.setSize(ancho, alto);

}
 unsigned int calcularAncho(unsigned int dimColumnas){

	 unsigned int ancho = 0;
	 ancho = (CASILLAS * dimColumnas) + (2 * BORDES);
	 return ancho;

 }

unsigned int calcularAlto(unsigned int dimFilas){

	unsigned int alto =0;
	alto = (CASILLAS * dimFilas) + (2 * BORDES);
	return alto;

}

void Mapa::crearListaMinasYAsignarPuntero(){
	Lista<Mina> minas;
	this->pMinas=&minas;
}

void Mapa::crearListaCasillasYAsignarPuntero(){
	Lista<Casilla> casillasDestapadas;
	this->pCasillasDestapadas=&casillasDestapadas;
}

void Mapa::crearListaBanderasYAsignarPuntero(){
	Lista<Bandera> banderas;
	this->pBanderas=&banderas;
}	


Lista<Mina>* Mapa::obtenerPunteroMinas(){
	return this-> pMinas
}

Lista<Casilla>* Mapa::obtenerPunteroCasillas(){
	return this-> pCasillasDestapadas;
}

Lista<Bandera>* Mapa::obtenerPunteroBanderas(){
	return this-> pBanderas;
}


void Mapa::mostrarMapa(){

	vector = new char[this->dimColumna];
	
	for(int i = 0; i < dimFila; i++ ){
		llenarVectorFila(i + 1, vector);
		mostrarVector(vector);
	}
		
}
	
void llenarVectorFila(unsigned int fila, char* vector[]){
	llenarVectorDeNoMostrado(vector);
	llenarVectorDeCasillasDestapadas(fila, vector);
	llenarVectorDeBanderas(fila, vector);
	
}
	
void llenarVectorDeNoMostrado(char* vector[]){
	for(int i = 0; i< this-> dimColumna; i++)
		vector[i] = '*';
}

	
void llenarVectorDeCasillasDestapadas(unsigned int fila,char* vector[]){

	this-> pCasillasDestapadas -> iniciarCursor();

	Casilla casillaActual;
		
	int casillasAsignadas = 0;
	while(this->pCasillasDestapadas->avanzarCursor() && casillasAsignadas =<this->dimFila){

		casillaActual = pCasillasDestapadas->obtenerCursor();

		if (casillaActual.obtenerFila() == fila){
			vector[casillaActual.obtenerColumna() - 1] = casillaActual.obtenerValor();
			casillasAsignadas++;
		}
	}	
}
void llenarVectorDeBanderas(unsigned int fila,char* vector[]){
	
	this->pBanderas->iniciarCursor();
	
	Bandera banderaActual;
	
	int banderasAsignadas = 0;
	
	while(this->pBanderas->avanzarCursor() && banderasAsignadas =< this->dimFila){
	
		banderaActual = pBanderas->obtenerCursor();
		
		if(banderaActual.obtenerColumna() == fila){
		
			vector[banderaActual.obtenerColumna() - 1] = '9';
			banderasAsignadas++;
		}
	}
}
void mostrarVector(char* vector[]){
	
	for (unsigned int i = 0; i< this->columna; i++){

			if(vector[i] == '9')
				std::cout<<Bandera<<;
			else if (vector[i] == 0) 
				std::cout<<'*';
			else 
				std::cout<< vector[i];
			std::endl;
	}
}
/*Método que estaba en "Minas" (un poco cambiado), xq "Minas" es una clase que no existe más.*/
char Mapa::calcularValorDeCasilla(uint filaCasilla, uint columnaCasilla){
	char valor = '0';
	pMinas->iniciarCursor();
	
	Mina minaActual;
	if (pMinas->avanzarCursor())
		minaActual = pMinas->ObtenerCursor();

	
	//MIs OJOS!!!!!! XD hay que revisar acá
	if (minaActual.esMina(filaCasilla, columnaCasilla)){
		valor = MINA;
	} else {/*jajaja sí, no se entiende un carajo ;D*//*<'9' xq 8 es la máxima cantidad de bombas que puede tener alrededor*/
		while(pMinas->avanzarCursor() && !minaActual.esMina(filaCasilla, columnaCasilla) && valor < '9'){
			Mina minaActual = pMinas->obtenerCursor();
			if(minaActual.estaJuntoAMina(filaCasilla , columnaCasilla))
				valor++;
		}
	
	return valor;
}

void Mapa::agregarCasillaDestapada(int filaRecibida,int columnaRecibida,char valorRecibido){ // modificando
	Casilla casillaPorAgregar(filaRecibida, columnaRecibida, valorRecibido);
	this -> pMinas -> agregar(casillaPorAgregar);
}

char Mapa::obtenerValorCasilla(int filaRecibida,int columnaRecibida){
	valor=this->calcularValorDeCasilla(filaRecibida,columnaRecibida);
	return valor;
}
	
void Mapa::colocarMarca(int filaRecibida,int columnaRecibida){
	Bandera banderaAColocar(filaRecibida, columnaRecibida);
	this -> pBanderas -> agregar(banderaAColocar);
}


bool Mapa::RemoverYDevolverSiHabiaMarca(unsigned int fila, unsigned int columna){ // validarYRemoverMarcaSiHay(this->fila , this->columna)
	bool seEncuentra=seEncuentraEnListaDeBanderas(fila, columna);
	if (seEncuentra) {remover(fila, columna)}; // Acá se debería remover el actual, para no recorrer dos veces la lista.
	return seEncuentra;
}	

bool Mapa::seEncuentraEnListaDeBanderas(uint &fila, uint &columna){
	return (seEncuentraEnLista('b', fila, columna));
}

/* Busca en una de las tres listas, según indicado x parámetro.*/
bool Mapa::seEncuentraEnLista(char lista, uint &filaBuscada, uint &columnaBuscada){
	if (lista=='b'){
		Lista<Bandera>* pLista=pBanderas;
		Bandera elementoActual;
	}
	else if (lista=='c'){
		Lista<Casilla>* pLista=pCasillasDestapadas;
		Casilla elementoActual;
	}
	else {// lista es 'm'
		Lista<Mina>* pLista=pMinas;
		Mina elementoActual;
	}

	bool encontrado=false;
	
	while(pLista->avanzarCursor() && not encontrado){
		elementoActual=pLista->obtenerCursor();
		if (elementoActual.obtenerFila()==filaBuscada && elementoActual.obtenerColumna()==columnaBuscada)
			encontrado=true;
		
	}
	
	//removerActual(); // acá es necesario un remover actual.
	return encontrado;
}

/*validarMina, estaDestapadaLaCasilla, Hay que buscar en las listas*/
bool Mapa::validarMina(unsigned int fila, unsigned int columna){
	return(seEncuentraEnLista('m', fila, columna)); // ver, recibe uint.
}

bool Mapa::estaDestapadaLaCasilla(unsigned int fila, unsigned int columna){
	return(seEncuentraEnLista('c', fila, columna));

}
