#ifndef GESTORSILLAS_H
#define GESTORSILLAS_H
#include <iostream>
#include <fstream>
#include "Estructuras.h"
#include "BaseDeDatos.h"
#include <stdlib.h>
using namespace std;

Lista<SillaTotal> listaSillasTotales;

Lista<SillaTotal> crearListaSillasTotales(Sistema *sistema){
	Lista<SillaTotal> listaSillasTotalesAux;	
	for(int i=0;i<sistema->aerolineas.getTam();i++){//							i=aerolineas
		Aerolinea aero=sistema->aerolineas.buscarElemento(i+1);		
		for(int j=0;j<aero.aviones.getTam();j++){//			j=aviones
			Avion avion=aero.aviones.buscarElemento(j+1);
			for(int k=0;k<avion.sillas.getTam();k++){//			k=sillas
				Silla silla=avion.sillas.buscarElemento(k+1);					
				SillaTotal aux;
				aux.idAerolinea=aero.idAerolinea;
				aux.idAvion=avion.idAvion;
				aux.ctdadSillas=avion.sillas.getTam();				
				aux.sillas.insertarFinal(silla);
				listaSillasTotalesAux.insertarFinal(aux);				
			}
			
		}
	}
	listaSillasTotales=listaSillasTotalesAux;
	return listaSillasTotales;
}

bool verificarIdSillaDisponibleEnAvion(Lista<Silla> sillas,string id){
	Silla silla;
	for(int i=0;i<sillas.getTam();i++){
		silla=sillas.buscarElemento(i+1);
		if(silla.idSilla==id){
			return false;
		}
	}
	return true;
}

void guardarSillas(Lista<SillaTotal> sillas,string archivo){
	ofstream fs(archivo.c_str()); 
	fs<<sillas.getTam()<<endl;
	for(int i=0;i<sillas.getTam();i++){
		SillaTotal aux=sillas.buscarElemento(i+1);
		fs<<aux.idAerolinea<<endl<<aux.idAvion<<endl<<aux.ctdadSillas<<endl;
		int cantidad=aux.sillas.getTam(); 
		for(int j=0;j<cantidad;j++){
			Silla silla=aux.sillas.buscarElemento(j+1);
			fs<<silla.idSilla<<endl;
			fs<<silla.estado<<endl;
			if(silla.estado){						
				fs<<silla.pasajero.identificacion<<endl;
				fs<<silla.pasajero.nombre<<endl;
				fs<<silla.pasajero.apellido<<endl;
				fs<<silla.pasajero.fechaNacimiento<<endl;
				fs<<silla.pasajero.tipo<<endl;			
				fs<<silla.pasajero.numeroReserva<<endl;			
			}
		}
	}
	fs.close();

}

void leerSillas(Sistema *sistema,string archivo){
	char cadena[128];
	ifstream fe(archivo.c_str());	
		fe.getline(cadena, 128);				
		int cantidadSillas = atoi(cadena);		
		for(int i=0;i<cantidadSillas;i++){
			fe.getline(cadena,128);
			int idAerolinea=atoi(cadena);
			fe.getline(cadena,128);
			int idAvion=atoi(cadena);
			fe.getline(cadena,128);				
			int ctdadSillasPorAvion=atoi(cadena);
			Silla sillas[ctdadSillasPorAvion];
			for(int j=0;j<ctdadSillasPorAvion;j++){
				fe.getline(cadena,128);			
				sillas[j].idSilla=cadena;
				fe.getline(cadena,128);				
				if(atoi(cadena)==1){									
					sillas[j].estado=true;
					fe.getline(cadena,128);
					sillas[j].pasajero.identificacion=cadena;
					fe.getline(cadena,128);
					sillas[j].pasajero.nombre=cadena;
					fe.getline(cadena,128);				
					sillas[j].pasajero.apellido=cadena;
					fe.getline(cadena,128);
					sillas[j].pasajero.fechaNacimiento=cadena;
					fe.getline(cadena,128);
					sillas[j].pasajero.tipo=cadena;
					fe.getline(cadena,128);
					sillas[j].pasajero.numeroReserva=atoi(cadena);	
				}else if(atoi(cadena)==0){					
					sillas[j].estado=false;
				}				
						
				//empieza a saltar lineas
				if(j!=ctdadSillasPorAvion-1){
					fe.getline(cadena,128);//aerolinea
					fe.getline(cadena,128);//vuelo planeado					
					fe.getline(cadena,128);//cantidad especificos
				}
				
				//guardar en la lista original que recibio
				Aerolinea aero=sistema->aerolineas.buscarElemento(idAerolinea);
				int posAvion=buscarPosAvion(idAvion,aero.aviones);
				Avion avion=aero.aviones.buscarElemento(posAvion);								
				avion.sillas.insertarFinal(sillas[j]);
				aero.aviones.modificarElemento(posAvion,avion);
				sistema->aerolineas.modificarElemento(idAerolinea,aero);
				if(j!=ctdadSillasPorAvion-1){
					i++;
				}					
			}
				
			
		}
		
	fe.close();
	//}
}

#endif    
