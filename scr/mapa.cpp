# include "mapa.h"

Mapa::Mapa(int filaRecibida, int columnaRecibida, char dificultadRecibida){

	this-> dimFila = filaRecibida;
	this-> dimColumna = columnaRecibida;
	this-> dificultad = dificultadRecibida;

	crearListaMinasYAsignarPuntero();
	crearListaCasillasYAsignarPuntero();
	crearListaBanderasYAsignarPuntero();

	Minero minero(dimFila,dimColumna,dificultad,pMinas);
	minero.sembrarMinas();

	Diseniador diseniador(dimFila,dimColumna);
	this->baseMapa = diseniador.obtenerDisenio();

}

uint Mapa::obtenerFila(){
	return this->dimFila;
}
uint Mapa::obtenerColumna(){
	return this->dimColumna;
}
char Mapa::obtenerDificultad(){
	return this->dificultad;
}

uint Mapa::obtenerTamanioDeLaListaDeMinas(){
	return this->pMinas->contarElementos();
}

uint Mapa::obtenerCantidadDeCasillasOcultas(){
	long int casillasTotales=this->dimFila()*this->dimColumna();
	int casillasYaDestapadas=pCasillasDestapadas->contarElementos();
	return casillasTotales-casillasYaDestapadas;
}

 unsigned int calcularAncho(unsigned int dimColumnas){

	 unsigned int ancho = 0;
	 ancho = (CELDAS * dimColumnas) + (2 * BORDES);
	 return ancho;

 }

unsigned int calcularAlto(unsigned int dimFilas){

	unsigned int alto =0;
	alto = (CELDAS * dimFilas) + (2 * BORDES);
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
	return this-> pMinas;
}

Lista<Casilla>* Mapa::obtenerPunteroCasillas(){
	return this-> pCasillasDestapadas;
}

Lista<Bandera>* Mapa::obtenerPunteroBanderas(){
	return this-> pBanderas;

}

void Mapa::cambiarEnBMP(char valor, uint fila, uint columna){

	BMP tipoDeCasilla;
	if(valor == BANDERA){
		tipoDeCasilla = tipoDeCasilla.ReadFromFile(archivoBandera);
	}
	else if (valor == VACIO){
		tipoDeCasilla = tipoDeCasilla.ReadFromFile(archivoVacio);
	}
	else if (valor == MINA){
		tipoDeCasilla = tipoDeCasilla.ReadFromFile(archivoMina);
	}
	else if (valor == '1'){
		tipoDeCasilla = tipoDeCasilla.ReadFromFile(archivo1);
	}
	else if (valor == '2'){
		tipoDeCasilla = tipoDeCasilla.ReadFromFile(archivo2);
	}
	else if (valor == '3'){
		tipoDeCasilla = tipoDeCasilla.ReadFromFile(archivo3);
	}
	else if (valor == '4'){
		tipoDeCasilla = tipoDeCasilla.ReadFromFile(archivo4);
	}
	else if (valor == '5'){
		tipoDeCasilla = tipoDeCasilla.ReadFromFile(archivo5);
	}
	else if (valor == '6'){
		tipoDeCasilla = tipoDeCasilla.ReadFromFile(archivo6);
	}
	else if (valor == '7'){
		tipoDeCasilla = tipoDeCasilla.ReadFromFile(archivo7);
	}
	else if (valor == '8'){
		tipoDeCasilla = tipoDeCasilla.ReadFromFile(archivo8);
	}

	RangedPixelToPixelCopy(tipoDeCasilla,1,16,1,16,this->baseMapa,
			1+BORDES+((columna-1)*CELDAS),1+BORDES+((this->dimFila-(fila-1))*CELDAS));

}

void Mapa::llenarMapaBanderas(Lista<Bandera>* banderas){

	banderas->iniciarCursor();
	while(banderas->avanzarCursor()){

		Bandera banderaActual();
		banderaActual = banderas->obtenerCursor();

		if(!banderaActual.seDestapoEnTablero()){
			cambiarEnBMP(BANDERA, banderaActual.obtenerFila(),
				                          banderaActual.obtenerColumna());

		}
	}

}

void Mapa::llenarMapaCasillasDestapadas(Lista<Casilla>* casillas){

       casillas->iniciarCursor();
       while(casillas->avanzarCursor()){
			Casilla casillaActual();
			casillaActual = casillas->obtenerCursor();
			if(!casillaActual.seDestapoEnTablero()){
				char valor;
				valor = casillaActual->obtenerValor();
				cambiarEnBMP(this->baseMapa, valor, casillaActual.obtenerFila(),
											  casillaActual.obtenerColumna());
			}
	   }
}
void Mapa::mostrarMapa(){
	llenarMapaBanderas(this->pCasillasDestapadas);
	llenarMapaCasillasDestapadas(this->pBanderas);

	this->baseMapa.WriteToFile(archivoDeJuego);
}


/*Método que estaba en "Minas" (un poco cambiado), xq "Minas" es una clase que no existe más.*/
char Mapa::calcularValorDeCasilla(uint filaCasilla, uint columnaCasilla){
	char valor = '0';
	pMinas->iniciarCursor();

	Mina minaActual;
	if (pMinas->avanzarCursor())
		minaActual = pMinas->obtenerCursor();


	//MIs OJOS!!!!!! XD hay que revisar acá
	if (minaActual.esMina(filaCasilla, columnaCasilla)){
		valor = MINA;
	} else {/*jajaja sí, no se entiende un carajo ;D*//*<'9' xq 8 es la máxima cantidad de bombas que puede tener alrededor*/
		while(pMinas->avanzarCursor() && !minaActual.esMina(filaCasilla, columnaCasilla) && valor < '9'){
			Mina minaActual = pMinas->obtenerCursor();
			if(minaActual.estaJuntoAMina(filaCasilla , columnaCasilla))
				valor++;
		}
	}
	return valor;
}

void Mapa::agregarCasillaDestapada(int filaRecibida,int columnaRecibida,char valorRecibido){ // modificando
	Casilla casillaPorAgregar(filaRecibida, columnaRecibida, valorRecibido);
	this -> pCasillasDestapadas -> agregar(casillaPorAgregar);
}

char Mapa::obtenerValorCasilla(int filaRecibida,int columnaRecibida){
	char valor=this->calcularValorDeCasilla(filaRecibida,columnaRecibida);
	return valor;
}

void Mapa::colocarMarca(int filaRecibida,int columnaRecibida){
	Bandera banderaAColocar(filaRecibida, columnaRecibida);
	this -> pBanderas -> agregar(banderaAColocar);
}

bool Mapa::removerYDevolverSiHabiaMarca(unsigned int fila, unsigned int columna){ // validarYRemoverMarcaSiHay(this->fila , this->columna)
	uint posicion=0;

	Buscador buscador(this->pBanderas);
	bool seEncuentra=buscador.buscar(fila, columna, posicion);

	if (seEncuentra)
		pBanderas->remover(posicion);

	return seEncuentra;
}

bool Mapa::validarMina(unsigned int fila, unsigned int columna){

	Buscador buscador(this->pMinas);
	bool seEncuentra=buscador.buscar(fila, columna);
	return seEncuentra;

}

bool Mapa::estaDestapadaLaCasilla(unsigned int fila, unsigned int columna){
	Buscador buscador(this->pCasillasDestapadas);
	bool seEncuentra=buscador.buscar(fila, columna);
	return seEncuentra;
}
