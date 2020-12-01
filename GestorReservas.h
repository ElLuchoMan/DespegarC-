#ifndef GESTORESERVAS_H
#define GESTORESERVAS_H
#include <iostream>
#include <fstream>
#include "Estructuras.h"
#include "BaseDeDatos.h"
#include <stdlib.h>
using namespace std;

Lista<ReservaTotal> listaReservas;

Lista<ReservaTotal> crearListaReservasTotales(Sistema *sistema){
	Lista<ReservaTotal> listaReservasAux;
	for(int i=0;i<sistema->usuarios.getTam();i++){//							i=usuarios
		Usuario user=sistema->usuarios.buscarElemento(i+1);		
		for(int j=0;j<user.viajes.getTam();j++){//			j=viajes
			Viaje viaje=user.viajes.buscarElemento(j+1);
			for(int k=0;k<viaje.reservas.getTam();k++){//			k=reservas
				Reserva	reserva=viaje.reservas.buscarElemento(k+1);					
				ReservaTotal aux;
				aux.idUsuario=user.idUnico;
				aux.idViaje=viaje.idViaje;
				aux.ctdadReservas=viaje.reservas.getTam();				
				aux.reservas.insertarFinal(reserva);
				listaReservasAux.insertarFinal(aux);				
			}
			
		}
	}
	listaReservas=listaReservasAux;
	return listaReservas;
}

int obtenerIdReservas(Sistema *sistema){
	int retorno=crearListaReservasTotales(sistema).getTam()+1;;
	return retorno;
}

void guardarReservas(Lista<ReservaTotal> reservas,string archivo){
	ofstream fs(archivo.c_str()); 
	fs<<reservas.getTam()<<endl;
	for(int i=0;i<reservas.getTam();i++){
		ReservaTotal aux=reservas.buscarElemento(i+1);
		fs<<aux.idUsuario<<endl<<aux.idViaje<<endl<<aux.ctdadReservas<<endl;
		int cantidad=aux.reservas.getTam(); 
		for(int j=0;j<cantidad;j++){
			Reserva reservaAr=aux.reservas.buscarElemento(j+1);
			fs<<reservaAr.idReserva<<endl;
			fs<<reservaAr.idVuelo<<endl;
			fs<<reservaAr.fechaReserva<<endl;
			fs<<reservaAr.tipo<<endl;
			fs<<reservaAr.precioPagado<<endl;
		}
	}
	fs.close();

}

void leerReservas(Sistema *sistema,string archivo){
	char cadena[128];
	ifstream fe(archivo.c_str());	
		fe.getline(cadena, 128);				
		int cantidadReservas = atoi(cadena);
		//for reservas
		for(int i=0;i<cantidadReservas;i++){
			fe.getline(cadena,128);
			int idUsuario=atoi(cadena);
			fe.getline(cadena,128);
			int idViaje=atoi(cadena);
			fe.getline(cadena,128);		
			//for 
			int cantidadReservasPorViaje=atoi(cadena);
			Reserva reservas[cantidadReservasPorViaje];
			for(int j=0;j<cantidadReservasPorViaje;j++){
				fe.getline(cadena,128);
				reservas[j].idReserva=atoi(cadena);
				fe.getline(cadena,128);
				reservas[j].idVuelo=atoi(cadena);
				fe.getline(cadena,128);
				reservas[j].fechaReserva=cadena;
				fe.getline(cadena,128);
				reservas[j].tipo=cadena;
				fe.getline(cadena,128);
				reservas[j].precioPagado=atoi(cadena);				
				//empieza a saltar lineas
				if(j!=cantidadReservasPorViaje-1){
					fe.getline(cadena,128);//usuario
					fe.getline(cadena,128);//viaje					
					fe.getline(cadena,128);//cantidad reservas
				}
				
				//guardar en la lista original que recibio
				Usuario user=sistema->usuarios.buscarElemento(idUsuario);
				int posViaje=buscarPosViaje(idViaje,user.viajes);
				Viaje viaje=user.viajes.buscarElemento(posViaje);								
				viaje.reservas.insertarFinal(reservas[j]);
				user.viajes.modificarElemento(posViaje,viaje);				
				sistema->usuarios.modificarElemento(idUsuario,user);
				if(j!=cantidadReservasPorViaje-1){
					i++;
				}					
			}
				
			
		}
		
	fe.close();
	//}
}

#endif    
