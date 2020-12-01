#ifndef GESTORCIUDADES_H
#define GESTORCIUDADES_H
#include <iostream>
#include <fstream>
#include "Estructuras.h"
#include <stdlib.h>
using namespace std;

int obtenerIdCiudad(Sistema *sistema){
	int retorno=sistema->ciudades.getTam()+1;
	return retorno;
}

void guardarCiudades(Sistema *sistema,string archivo){
	Lista<Ciudad> ciudades=sistema->ciudades;
	ofstream fs(archivo.c_str()); //crear la conexion al archivo
	fs<<ciudades.getTam()<<endl;//escribir la cantidad de registros que se escribiran
	for(int i=0;i<ciudades.getTam();i++){
		Ciudad ciudad=ciudades.buscarElemento(i+1);	//tomar registro por registro y escribir sus caracteristicas sin contar listas hijas	
		fs<<ciudad.idCiudad<<endl;
		fs<<ciudad.nombreCiudad<<endl;	
	}
	fs.close();//cerrar el archivo

}

void leerCiudades(Sistema *sistema, string archivo){
	Lista<Ciudad> ciudades=sistema->ciudades;
	char cadena[128];
	ifstream fe(archivo.c_str());
	//leer la cantidad total de usuarios	
		fe.getline(cadena, 128);				
		int cantidadCiudades = atoi(cadena);
		//leer todos los usuarios		
		Ciudad ciudad[cantidadCiudades];
		for(int i=0;i<cantidadCiudades;i++){			
			fe.getline(cadena,128);
			ciudad[i].idCiudad=atoi(cadena);
			fe.getline(cadena,128);
			ciudad[i].nombreCiudad=cadena;								
				//guardar en la lista original que recibio
			ciudades.insertarFinal(ciudad[i]);
				
		}	
		sistema->ciudades=ciudades;
	fe.close();
}


#endif    
