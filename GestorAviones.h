#ifndef GESTORAVIONES_H
#define GESTORAVIONES_H
#include <iostream>
#include <fstream>
#include "Estructuras.h"
#include <stdlib.h>
using namespace std;

Lista<AvionTotal> listaAvionesTotales;



Lista<AvionTotal> crearListaAvionesTotales(Sistema *sistema){	
Lista<AvionTotal> listaAvionesTotalesAux;
	for(int i=0;i<sistema->aerolineas.getTam();i++){//							i=aerolinea
		Aerolinea aero=sistema->aerolineas.buscarElemento(i+1);			
		for(int j=0;j<aero.aviones.getTam();j++){//			j=aviones
			Avion avion=aero.aviones.buscarElemento(j+1);
			AvionTotal aux;						//guarda la ubicacion en la multilista del avion, y guarda la lista junto con la informacion
			aux.idAerolinea=aero.idAerolinea;				
			aux.ctdadAviones=aero.aviones.getTam();			
			aux.aviones.insertarFinal(avion);			
			listaAvionesTotalesAux.insertarFinal(aux);
		}
	}
	listaAvionesTotales=listaAvionesTotalesAux;
	return listaAvionesTotales;
}

int obtenerIdAviones(Sistema *sistema){
	int retorno=crearListaAvionesTotales(sistema).getTam()+1;;
	return retorno;
}

void guardarAviones(Lista<AvionTotal> aviones, string archivo){
	ofstream fs(archivo.c_str()); 
	fs<<aviones.getTam()<<endl;//escribe la cantidad de aviones totales
	for(int i=0;i<aviones.getTam();i++){
		AvionTotal aux=aviones.buscarElemento(i+1);
		fs<<aux.idAerolinea<<endl<<aux.ctdadAviones<<endl;//escribe la aerolinea y la cantidad de aviones que tiene
		int cantidad=aux.aviones.getTam();
		for(int j=0;j<cantidad;j++){
			Avion avion=aux.aviones.buscarElemento(j+1);//escribe luego cada atributo del avion			
			fs<<avion.idAvion<<endl;
			fs<<avion.capacidad<<endl;
			fs<<avion.matricula<<endl;
			fs<<avion.modelo<<endl;				
		}
	}
	fs.close();//cierra el archivo despues de escribir todos los aviones de todas las aerolineas
}



void leerAviones(Sistema *sistema,string archivo){
	char cadena[128];
	ifstream fe(archivo.c_str());	
		fe.getline(cadena, 128);				
		int cantidadAviones = atoi(cadena);		
		//for 
		for(int i=0;i<cantidadAviones;i++){//total de todos los aviones que va a leer
		
			fe.getline(cadena,128);
			int idAerolinea=atoi(cadena);		
			fe.getline(cadena,128);						
			int ctdadAvionesPorAerolinea=atoi(cadena);			
			Avion aviones[ctdadAvionesPorAerolinea];
			for(int j=0;j<ctdadAvionesPorAerolinea;j++){//aviones en la aerolinea
						
				fe.getline(cadena,128);
				aviones[j].idAvion=atoi(cadena);
				fe.getline(cadena,128);
				aviones[j].capacidad=atoi(cadena);
				fe.getline(cadena,128);
				aviones[j].matricula=cadena;
				fe.getline(cadena,128);
				aviones[j].modelo=cadena;
				
				//empieza a saltar lineas
				if(j!=ctdadAvionesPorAerolinea-1){
					fe.getline(cadena,128);//salta aerolinea							
					fe.getline(cadena,128);//salta cantidad aviones por aerolinea
				}
				//guardar en la lista original que recibio
				//cout<<vuelos[i].codigoVuelo;				
				Aerolinea aero=sistema->aerolineas.buscarElemento(idAerolinea);				
				aero.aviones.insertarFinal(aviones[j]);								
				sistema->aerolineas.modificarElemento(idAerolinea,aero);				
				if(j!=ctdadAvionesPorAerolinea-1){
					i++;
				}				
			}				
		}
	fe.close();
}

#endif    
