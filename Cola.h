#ifndef COLA_H
#define COLA_H
#include <iostream>
using namespace std;


template <class T>
struct nodoC{
	T info;
	nodoC<T> *sig=NULL,*ant=NULL;	
};

template<class T>
class Cola {
   public:
      Cola() : primero(NULL), ultimo(NULL) {}      

      void anadir(T elemento);
      T leer();
      int getTam();

   private:
      nodoC<T> *primero, *ultimo;
};
 


template<class T>
void Cola<T>::anadir(T elemento) {
   nodoC<T> *nuevo=new nodoC<T>; /* Crear un nodo nuevo */
   nuevo->info=elemento;
   
   /* Si la cola no estaba vac�a, a�adimos el nuevo a continuaci�n de ultimo */
   if(ultimo) ultimo->sig = nuevo;
   /* Ahora, el �ltimo elemento de la cola es el nuevo nodoC */
   ultimo = nuevo;
   /* Si primero es NULL, la cola estaba vac�a, ahora primero apuntar� tambi�n al nuevo nodoC */
   if(!primero) primero = nuevo;
}

template<class T>
T Cola<T>::leer() {
    nodoC<T> *Nodo; /* variable auxiliar para manipular nodoC */
    T v;      /* variable auxiliar para retorno */

   /* nodoC apunta al primer elemento de la pila */
   Nodo= primero;
   if(!Nodo) return v; /* Si no hay nodos en la pila retornamos 0 */
   /* Asignamos a primero la direcci�n del segundo nodo */
   primero = Nodo->sig;
   /* Guardamos el valor de retorno */
   v = Nodo->info;
   /* Borrar el nodo */
   delete Nodo;
   /* Si la cola qued� vac�a, ultimo debe ser NULL tambi�n*/
   if(!primero) ultimo = NULL;
   return v;
}

template<class T>
int Cola<T>::getTam() {
   	int contador=0;
   	if(primero){  
	   	contador=1; 
   		nodoC<T> *aux=primero;
   		while(aux!=ultimo){
	   		contador=contador+1;
   			aux=aux->sig;
   		}
   	}
   	return contador;
}


#endif    
