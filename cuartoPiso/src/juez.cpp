#include "juez.h"
#include "constantes.h"
# include "listaCircular.h"
#include <fstream.h>

using namespace std;

Juez::Juez(unsigned int cantidadJugadores,Mapa* mapaRecibido){
	this->cantidadDeJugadores = cantidadJugadores;
	this->tableroDeJuego = mapaRecibido;
	
	crearYAsignarListaDeJugadores();
	
	crearJugadores();

}

void Juez::crearYAsignarListaDeJugadores(){
	Lista<Jugador*> listaDeJugadores;
	this-> jugadores = &listaDeJugadores;
}

void Juez::crearJugadores(){
	char alias = 'A';

		Jugador* entrante;
		for (int i=0; i<cantidadJugadores;i++){
			Jugador jugador(alias+i,mapaRecibido);
			entrante=&jugador;		
			insertarJugador(entrante);
		}

		this->jugadores->iniciarCursor();
}


/* Avanzar jugador hasta un jugador que siga jugando.*/
void Juez::avanzarJugador(){

	Jugador* siguiente;
	bool puedeJugar=false;

	do{
		this->jugadores->avanzarCursor();
		Jugador* siguiente = this->jugadores->obtenerCursor();

		if(siguiente->obtenerEstado() == SIGUE_JUGANDO)
			puedeJugar = true;

	}while(!puedeJugar);

}

void Juez::insertarJugador(Jugador* nuevo){

	this->jugadores->insertar(nuevo);
}
Jugador* encontrarJugadorQueGanoPorPuntaje(Lista<Jugador*>* jugadores, int cantidadDeJugadores){
	jugadores->inicializarCursor();
	Jugador* jugadorGanador;
	int puntajeMaximo = 0;
	while(jugadores<=cantidadDeJugadores){
		
		Jugador* jugadorActual;
		jugadorActual = jugadores->obtenerCursor();
		if(jugadorActual->obtenerPuntaje() > puntajeMaximo){
			puntajeMaximo = jugadorActual->obtenerPuntaje();
			jugadorGanador = jugadorActual;
		}
		
		
	}
	return jugadorGanador;
	
}
void crearArchivoConPuntajes(Lista<Jugador*>* jugadores, int cantidadDeJugadores){
   ofstream puntajes(archivoDePuntajes); 
       while(jugadores<=cantidadDeJugadores){
		char alias;
	    int puntaje;
		Jugador* jugadorActual;
		jugadorActual = jugadores->obtenerCursor();
		alias = jugadorActual->obtenerAlias();
		puntaje = jugadorActual->obtenerPuntaje();
	    puntajes << "el jugador" << alias << "obtuvo puntaje de: " << puntaje << endl;
	       
       }	
   puntajes.close();

}
void Juez::inicializarJuego(){
	uint casillasOcultas=tableroDeJuego->obtenerCantidadDeCasillasOcultas();
	uint minasPorDescubrir=tableroDeJuego->obtenerTamanioDeLaListaDeMinas();
	int jugadoresQuePerdieron = 0 ;

	this->jugadores->inicializarCursor(); //para la lista circular
	Jugador* jugadorActual;
	jugadores->avanzarCursor();
	bool terminoElJuego=false;


	while((jugadoresQuePerdieron<cantidadDeJugadores)&& (!terminoElJuego)){

		jugadorActual = this->jugadores->obtenerCursor();

		if(casillasOcultas>minasPorDescubrir){

			if (jugadorActual->obtenerEstado() == SIGUE_JUGANDO){
				sigueJugando(jugadorActual, jugadoresQuePerdieron, tableroDeJuego, minasPorDescubrir);
			}

			jugadores->avanzarCursor();

		}


		else{
			terminoLaPartida();
			terminoElJuego=true;
		}


	}
	

	Jugador* jugadorGanador = encontrarJugadorQueGanoPorPuntaje(this->jugadores, cantidadDeJugadores);
	mostrarFelicitaciones(jugadorGanador);
	crearArchivoConPuntajes(this->jugadores, cantidadDeJugadores);


}


void Juez::sigueJugando(Jugador* jugadorActual, int &jugadoresQuePerdieron, Mapa* tableroDeJuego, uint &minasPorDescubrir){

	jugadorActual->iniciarJugada();

		if(jugadorActual->obtenerEstado() == PERDIO_PARTIDA){

			jugadoresQuePerdieron++;
			minasPorDescubrir--;
						
			jugadorActual->asignarEstado(NO_ESTA_JUGANDO);

			mostrarPuntajeDeJugadorQueHaPerdido(jugadorActual);
		}
	 tableroDeJuego->mostrarMapa();
}

void Juez::mostrarPuntajeDeJugadorQueHaPerdido(Jugador* jugadorActual){
	int puntaje = 0;
	char alias;
	alias = jugadorActual->obtenerAlias();
	puntaje = jugadorActual->obtenerPuntaje();
	cout<<" El jugador " << alias << " ha perdido XD XD"<<endl;
	cout<< "Su puntaje es " << puntaje << endl;

}

void Juez::terminoLaPartida(){
	cout << "Juego terminado :)." << endl;
}

void Juez::mostrarFelicitaciones(Jugador* jugadorActual){
	cout << jugadorActual->obtenerAlias() << "!!! Ganaste !!!" << endl;
	cout << "Tu puntaje es: " << jugadorActual->obtenerPuntaje() << "."<< endl;
}


Juez::~Juez(){

	while( !(this->jugadores->estaVacia()) ){
		Jugador* jugadorActual;
		char alias;
		int puntaje;
		this->jugadores->inicializarCursor();
		jugadorActual = this->jugadores->obtenerCursor();
		alias = jugardorActual->obtenerAlias();
		puntaje = jugadorActual->obtenerPuntaje();

		cout<<"El jugador: " << alias << " tiene " << puntaje << " puntos." << endl;
		this->jugadores->remover(1);
	}

}
