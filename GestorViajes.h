#ifndef GESTORVIAJES_H
#define GESTORVIAJES_H
#include <iostream>
#include <fstream>
#include "Estructuras.h"
#include <stdlib.h>
using namespace std;

Lista<ViajeTotal> listaViajes;

Lista<ViajeTotal> crearListaViajesTotales(Sistema *sistema){
	Lista<ViajeTotal> listaViajesAux;
	for(int i=0;i<sistema->usuarios.getTam();i++){//							i=usuarios
		Usuario user=sistema->usuarios.buscarElemento(i+1);			
		for(int j=0;j<user.viajes.getTam();j++){//			j=viajes
			Viaje viaje=user.viajes.buscarElemento(j+1);			
			ViajeTotal aux;						//guarda la ubicacion en la multilista del viaje, y guarda la lista junto con la informacion
			aux.idUsuario=user.idUnico;							
			aux.ctdadViajes=user.viajes.getTam();			
			aux.viajes.insertarFinal(viaje);			
			listaViajesAux.insertarFinal(aux);
		}
	}
	listaViajes=listaViajesAux;
	return listaViajes;
}

int obtenerIdViajes(Sistema *sistema){
	int retorno=crearListaViajesTotales(sistema).getTam()+1;;
	return retorno;
}

void guardarViajes(Lista<ViajeTotal> viajes, string archivo){
	ofstream fs(archivo.c_str()); 
	fs<<viajes.getTam()<<endl;//escribe la cantidad de viajes totales
	for(int i=0;i<viajes.getTam();i++){
		ViajeTotal aux=viajes.buscarElemento(i+1);
		fs<<aux.idUsuario<<endl<<aux.ctdadViajes<<endl;//escribe el usuario y la cantidad de viajes que tiene
		int cantidad=aux.viajes.getTam();
		for(int j=0;j<cantidad;j++){
			Viaje viajeAr=aux.viajes.buscarElemento(j+1);//escribe luego cada atributo del viaje			
			fs<<viajeAr.idViaje<<endl;
			fs<<viajeAr.tipoDeViaje<<endl;	
			fs<<viajeAr.nombre<<endl;		
		}
	}
	fs.close();//cierra el archivo despues de escribir todos los viajes de todos los usuarios
}

void leerViajes(Sistema *sistema,string archivo){
	char cadena[128];
	ifstream fe(archivo.c_str());
	//while(!fe.eof()) {	
		fe.getline(cadena, 128);				
		int cantidadViajesPlaneados = atoi(cadena);		
		//for cantidadVuelosPlaneados
		for(int i=0;i<cantidadViajesPlaneados;i++){//total de todos los vuelos planeados que va a leer
			fe.getline(cadena,128);
			int idUsuario=atoi(cadena);
			//cout<<"aerolinea:"<<cadena<<endl;
			fe.getline(cadena,128);	
			int ctdadViajesPorUsuario=atoi(cadena);
			//cout<<"cantidad:"<<cadena<<endl;
			Viaje viajes[ctdadViajesPorUsuario];
			for(int j=0;j<ctdadViajesPorUsuario;j++){//viajes del usuario 
				fe.getline(cadena,128);
				viajes[j].idViaje=atoi(cadena);
				fe.getline(cadena,128);
				viajes[j].tipoDeViaje=cadena;	
				fe.getline(cadena,128);
				viajes[j].nombre=cadena;
				//empieza a saltar lineas
				if(j!=ctdadViajesPorUsuario-1){
					fe.getline(cadena,128);//salta usuario							
					fe.getline(cadena,128);//salta cantidad viajes planeados por usuario
				}
				//guardar en la lista original que recibio							
				Usuario user=sistema->usuarios.buscarElemento(idUsuario);					
				user.viajes.insertarFinal(viajes[j]);								
				sistema->usuarios.modificarElemento(idUsuario,user);				
				if(j!=ctdadViajesPorUsuario-1){
					i++;
				}				
			}				
		}
	fe.close();
}

#endif    
