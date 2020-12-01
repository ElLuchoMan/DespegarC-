#ifndef GESTORVUELOSESPECIFICOS_H
#define GESTORVUELOSESPECIFICOS_H
#include <iostream>
#include <fstream>
#include "Estructuras.h"
#include "BaseDeDatos.h"
#include <stdlib.h>
using namespace std;

Lista<VueloEspecificoTotal> listaVuelosEspecificos;

Lista<VueloEspecificoTotal> crearListaVuelosEspecificosTotales(Sistema *sistema){
	Lista<VueloEspecificoTotal> listaVuelosEspecificosAux;	
	for(int i=0;i<sistema->aerolineas.getTam();i++){//							i=aerolineas
		Aerolinea aero=sistema->aerolineas.buscarElemento(i+1);		
		for(int j=0;j<aero.itinerarios.vuelosPlaneados.getTam();j++){//			j=vuelo planeado
			VueloPlaneado vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(j+1);
			for(int k=0;k<vueloP.vuelosEspecificos.getTam();k++){//			k=vuelos especificos
				VueloEspecifico	vueloe=vueloP.vuelosEspecificos.buscarElemento(k+1);					
				VueloEspecificoTotal aux;
				aux.idAerolinea=aero.idAerolinea;
				aux.idPlanTrayecto=aero.itinerarios.idPlan;
				aux.idVueloPlaneado=vueloP.codigoVuelo;
				aux.ctdadVuelosEspecificos=vueloP.vuelosEspecificos.getTam();				
				aux.vuelosE.insertarFinal(vueloe);
				listaVuelosEspecificosAux.insertarFinal(aux);				
			}
			
		}
	}
	listaVuelosEspecificos=listaVuelosEspecificosAux;
	return listaVuelosEspecificos;
}

int obtenerIdEspecificos(Sistema *sistema){
	int retorno=crearListaVuelosEspecificosTotales(sistema).getTam()+1;;
	return retorno;
}

void guardarVuelosEspecificos(Lista<VueloEspecificoTotal> vuelosE,string archivo){
	ofstream fs(archivo.c_str()); 
	fs<<vuelosE.getTam()<<endl;
	for(int i=0;i<vuelosE.getTam();i++){
		VueloEspecificoTotal aux=vuelosE.buscarElemento(i+1);
		fs<<aux.idAerolinea<<endl<<aux.idVueloPlaneado<<endl<<aux.ctdadVuelosEspecificos<<endl;
		int cantidad=aux.vuelosE.getTam(); 
		for(int j=0;j<cantidad;j++){
			VueloEspecifico vueloAr=aux.vuelosE.buscarElemento(j+1);
			fs<<vueloAr.idCodigoVueloEspecifico<<endl;
			fs<<vueloAr.idAvion<<endl;
			fs<<vueloAr.anio<<endl;
			fs<<vueloAr.mes<<endl;
			fs<<vueloAr.dia<<endl;
			fs<<vueloAr.cuposLibres<<endl;
			fs<<vueloAr.tarifaAdulto<<endl;
			fs<<vueloAr.tarifaNinio<<endl;			
		}
	}
	fs.close();

}

void leerVuelosEspecificos(Sistema *sistema,string archivo){
	char cadena[128];
	ifstream fe(archivo.c_str());	
		fe.getline(cadena, 128);				
		int cantidadVuelosEspecificos = atoi(cadena);
		//for reservas
		for(int i=0;i<cantidadVuelosEspecificos;i++){
			fe.getline(cadena,128);			
			int idAerolinea=atoi(cadena);
			fe.getline(cadena,128);
			int idVueloPlaneado=atoi(cadena);
			fe.getline(cadena,128);		
			//for 
			int ctdadVuelosEspecificosPorPlaneado=atoi(cadena);
			VueloEspecifico vuelosE[ctdadVuelosEspecificosPorPlaneado];
			for(int j=0;j<ctdadVuelosEspecificosPorPlaneado;j++){				
				fe.getline(cadena,128);
				vuelosE[j].idCodigoVueloEspecifico=atoi(cadena);
				fe.getline(cadena,128);
				vuelosE[j].idAvion=atoi(cadena);				
				fe.getline(cadena,128);
				vuelosE[j].anio=atoi(cadena);
				fe.getline(cadena,128);
				vuelosE[j].mes=atoi(cadena);
				fe.getline(cadena,128);				
				vuelosE[j].dia=atoi(cadena);	
				fe.getline(cadena,128);
				vuelosE[j].cuposLibres=atoi(cadena);
				fe.getline(cadena,128);
				vuelosE[j].tarifaAdulto=atoi(cadena);
				fe.getline(cadena,128);
				vuelosE[j].tarifaNinio=atoi(cadena);			
				//empieza a saltar lineas
				if(j!=ctdadVuelosEspecificosPorPlaneado-1){
					fe.getline(cadena,128);//aerolinea
					fe.getline(cadena,128);//vuelo planeado					
					fe.getline(cadena,128);//cantidad especificos
				}
				
				//guardar en la lista original que recibio
				Aerolinea aero=sistema->aerolineas.buscarElemento(idAerolinea);
				int posicionVueloP=buscarPosVueloPlaneado(idVueloPlaneado,aero.itinerarios.vuelosPlaneados);				
				VueloPlaneado vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(posicionVueloP);								
				vueloP.vuelosEspecificos.insertarFinal(vuelosE[j]);
				aero.itinerarios.vuelosPlaneados.modificarElemento(posicionVueloP,vueloP);								
				sistema->aerolineas.modificarElemento(idAerolinea,aero);
				if(j!=ctdadVuelosEspecificosPorPlaneado-1){
					i++;
				}					
			}
				
			
		}
		
	fe.close();
	//}
}

VueloEspecificoTotal encontrarVueloEspecifico(int idVuelo,Sistema *sistema){
	Lista<VueloEspecificoTotal> vuelos=crearListaVuelosEspecificosTotales(sistema);
	for(int i=0;i<vuelos.getTam();i++){
		VueloEspecificoTotal vuelo=vuelos.buscarElemento(i+1);
		VueloEspecifico vueloE=vuelo.vuelosE.buscarElemento(1);
		if(vueloE.idCodigoVueloEspecifico==idVuelo){
			return vuelo;
		}
	}
	
}

#endif    
