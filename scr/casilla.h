typedef unsigned int uint;

class Casilla{
private:
  uint fila;
  uint columna;
  char valor;
  
public:

 /* Pre: Recibe fila y columna dentro del rango indicado por el usuario.
  * Post: Crea un objeto Casilla, con la fila y columna recibidas.*/
  Casilla(uint fila, uint columna, char valor);
  
  /* Post: Crea un objeto Casilla, con fila y columna 0.*/
  Casilla();
  
  /* Post: Devuelve la fila de la Casilla.*/
  uint obtenerFila();
  
  /* Post: Devuelve la columna de la Casilla.*/
  uint obtenerColumna();
  
  /* Post: Devuelve el valor de la Casilla.*/
  char obtenerValor();
  
 /* Pre: Recibe una fila dentro del rango válido.
  * Post: Asigna la fila pasada como parámetro a la Casilla.*/
  void asignarFila(uint fila);

 /* Pre: Recibe una columna dentro del rango válido.
  * Post: Asigna la columna pasada como parámetro a la Casilla.*/
  void asignarColumna(uint columna);
  
 /* Pre: Recibe una variable "valor" de tipo char..
  * Post: Asigna el valor pasado como parámetro a la Casilla.*/
  void asignarValor(char valor);

};
