#ifndef GESTORAEROLINEAS_h
#define GESTORAEROLINEAS_h
#include <iostream>
#include <fstream>
#include "Estructuras.h"
#include <stdlib.h>
using namespace std;

int obtenerIdAerolinea(Sistema *sistema){
	int retorno=sistema->aerolineas.getTam()+1;
	return retorno;
}


void guardarAerolineas(Sistema *sistema,string archivo){
	Lista<Aerolinea> aerolineas=sistema->aerolineas;
	ofstream fs(archivo.c_str()); //crear la conexion al archivo
	fs<<aerolineas.getTam()<<endl;//escribir la cantidad de registros que se escribiran
	for(int i=0;i<aerolineas.getTam();i++){
		Aerolinea aero=aerolineas.buscarElemento(i+1);	//tomar registro por registro y escribir sus caracteristicas sin contar listas hijas	
		fs<<aero.idAerolinea<<endl;
		fs<<aero.nombre<<endl;
		fs<<aero.avionesDisponibles<<endl;
		fs<<aero.itinerarios.idPlan<<endl;
		fs<<aero.numero_cuenta_bancaria<<endl;	
	}
	fs.close();

}


void leerAerolineas(Sistema *sistema, string archivo){
	Lista<Aerolinea> aerolineas=sistema->aerolineas;
	char cadena[128];
	ifstream fe(archivo.c_str());
	//leer la cantidad total de aerolineas	
		fe.getline(cadena, 128);				
		int cantidadAerolineas = atoi(cadena);
		//leer todas las aerolineas
		Aerolinea aero[cantidadAerolineas];
		for(int i=0;i<cantidadAerolineas;i++){			
			fe.getline(cadena,128);
			aero[i].idAerolinea=atoi(cadena);
			fe.getline(cadena,128);
			aero[i].nombre=cadena;
			fe.getline(cadena,128);
			aero[i].avionesDisponibles=atoi(cadena);
			fe.getline(cadena,128);
			aero[i].itinerarios.idPlan=atoi(cadena);
			fe.getline(cadena,128);
			aero[i].numero_cuenta_bancaria=cadena;			
				//guardar en la lista original que recibio
				aerolineas.insertarFinal(aero[i]);
				
		}
		sistema->aerolineas=aerolineas;	
	fe.close();
}


#endif    
