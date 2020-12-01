#ifndef GESTORVUELOSPLANEADOS_H
#define GESTORVUELOSPLANEADOS_H
#include <iostream>
#include <fstream>
#include "Estructuras.h"
#include <stdlib.h> 


using namespace std;

Lista<VueloPlaneadosTotal> listaVuelosPlaneados;

Lista<VueloPlaneadosTotal> crearListaVuelosPlaneadosTotales(Sistema *sistema){	
	Lista<VueloPlaneadosTotal> listaVuelosPlaneadosAux;
	for(int i=0;i<sistema->aerolineas.getTam();i++){//							i=aerolinea
		Aerolinea aero=sistema->aerolineas.buscarElemento(i+1);			
		for(int j=0;j<aero.itinerarios.vuelosPlaneados.getTam();j++){//			j=vuelos planeados
			VueloPlaneado vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(j+1);
			VueloPlaneadosTotal aux;						//guarda la ubicacion en la multilista del vuelo planeado, y guarda la lista junto con la informacion
			aux.idAerolinea=aero.idAerolinea;	
			aux.idPlanTrayecto=aero.itinerarios.idPlan;			
			aux.ctdadVuelosPlaneados=aero.itinerarios.vuelosPlaneados.getTam();			
			aux.vuelosP.insertarFinal(vueloP);			
			listaVuelosPlaneadosAux.insertarFinal(aux);
		}
	}
	listaVuelosPlaneados=listaVuelosPlaneadosAux;
	return listaVuelosPlaneados;
}

int obtenerIdPlaneados(Sistema *sistema){
	int retorno=crearListaVuelosPlaneadosTotales(sistema).getTam()+1;;
	return retorno;
}

void guardarVuelosPlaneados(Lista<VueloPlaneadosTotal> vuelosP, string archivo){
	ofstream fs(archivo.c_str()); 	
	fs<<vuelosP.getTam()<<endl;//escribe la cantidad de vuelos totales
	for(int i=0;i<vuelosP.getTam();i++){
		VueloPlaneadosTotal aux=vuelosP.buscarElemento(i+1);
		fs<<aux.idAerolinea<<endl<<aux.ctdadVuelosPlaneados<<endl;//escribe la aerolinea y la cantidad de vuelos que tiene
		int cantidad=aux.vuelosP.getTam();
		for(int j=0;j<cantidad;j++){
			VueloPlaneado vueloAr=aux.vuelosP.buscarElemento(j+1);//escribe luego cada atributo del vuelo			
			fs<<vueloAr.codigoVuelo<<endl;
			fs<<vueloAr.idDestino<<endl;
			fs<<vueloAr.idOrigen<<endl;	
			if(vueloAr.vueloMultiple){
				fs<<1<<endl;
			}else{
				fs<<0<<endl;
			}
			if(vueloAr.vueloMultiple){				//si es vuelo multiple no escribe todo, solo lo necesario
				fs<<vueloAr.vuelosDirectos.getTam()<<endl;
				for(int i=0;i<vueloAr.vuelosDirectos.getTam();i++){
					fs<<vueloAr.vuelosDirectos.buscarElemento(i+1)<<endl;
				}				
			}else{
				for(int k=0;k<8;k++){
					fs<<vueloAr.diaDeLaSemana[k]<<endl;
				}			
				fs<<vueloAr.duracion<<endl;
				fs<<vueloAr.salida.hora<<"-"<<vueloAr.salida.minuto<<endl;//guarda las horas en formato HH-MM
				fs<<vueloAr.llegada.hora<<"-"<<vueloAr.llegada.minuto<<endl;
			}	
				
		}
	}
	fs.close();//cierra el archivo despues de escribir todos los vuelos planeados de todas las aerolineas
}



void leerVuelosPlaneados(Sistema *sistema,string archivo){
	char cadena[128];
	ifstream fe(archivo.c_str());	
		fe.getline(cadena, 128);				
		int cantidadVuelosPlaneados = atoi(cadena);		
		//for cantidadVuelosPlaneados
		for(int i=0;i<cantidadVuelosPlaneados;i++){//total de todos los vuelos planeados que va a leer
			fe.getline(cadena,128);
			int idAerolinea=atoi(cadena);		
			fe.getline(cadena,128);						
			int ctdadVuelosPlaneadosPorAerolinea=atoi(cadena);			
			VueloPlaneado vuelos[ctdadVuelosPlaneadosPorAerolinea];
			for(int j=0;j<ctdadVuelosPlaneadosPorAerolinea;j++){//vuelos planeados en la aerolinea
				string aux;
				string hora;
				string minuto;				
				fe.getline(cadena,128);
				vuelos[j].codigoVuelo=atoi(cadena);
				fe.getline(cadena,128);
				vuelos[j].idDestino=atoi(cadena);
				fe.getline(cadena,128);
				vuelos[j].idOrigen=atoi(cadena);
				fe.getline(cadena,128);				
				if(atoi(cadena)==1){	//si es vuelo multiple, lee solo lo que se escribio del multiple
					vuelos[j].vueloMultiple=true;
					fe.getline(cadena,128);
					int cantidadVuelosDirectos=atoi(cadena);
					for(int k=0;k<cantidadVuelosDirectos;k++){
						fe.getline(cadena,128);
						vuelos[j].vuelosDirectos.insertarFinal(atoi(cadena));
					}	
					vuelos[j].duracion=0;					
					vuelos[j].llegada.hora=0;		
					vuelos[j].llegada.minuto=0;	
					vuelos[j].salida.hora=0;		
					vuelos[j].salida.minuto=0;
					for(int k=0;k<8;k++){						
						vuelos[j].diaDeLaSemana[k]=0;
					}			

				}else{//si no es vuelo multiple lee todo lo demas
					vuelos[j].vueloMultiple=false;
					for(int k=0;k<8;k++){
						fe.getline(cadena,128);
						vuelos[j].diaDeLaSemana[k]=atoi(cadena);
					}				
					fe.getline(cadena,128);
					vuelos[j].duracion=atoi(cadena);
					//separa la hora y los minutos por el -
					fe.getline(cadena,128);	
					aux=cadena;			
					if(aux[2]=='-'){					
						hora=aux[0];
						hora=hora+ aux[1];					
						if(aux.length()==4){
							minuto=aux[3];
						}else if(aux.length()==5){
							minuto=aux[3];
							minuto=minuto+aux[4];						
						}
					}else if(aux[1]=='-'){
						hora=aux[0];
						if(aux.length()==3){
							minuto=aux[2];
						}else if(aux.length()==4){
							minuto=aux[2];
							minuto=minuto+aux[3];
						}
					}				
					vuelos[j].salida.hora=atoi(hora.c_str());
					vuelos[j].salida.minuto=atoi(minuto.c_str());
					//separa la hora y los minutos por el -
					fe.getline(cadena,128);
					aux=cadena;			
					if(aux[2]=='-'){					
						hora=aux[0];
						hora=hora+ aux[1];					
						if(aux.length()==4){
							minuto=aux[3];
						}else if(aux.length()==5){
							minuto=aux[3];
							minuto=minuto+aux[4];						
						}
					}else if(aux[1]=='-'){
						hora=aux[0];
						if(aux.length()==3){
							minuto=aux[2];
						}else if(aux.length()==4){
							minuto=aux[2];
							minuto=minuto+aux[3];
						}
					}
					vuelos[j].llegada.hora=atoi(hora.c_str());				
					vuelos[j].llegada.minuto=atoi(minuto.c_str());
					
				}
				
				
				
				//empieza a saltar lineas
				if(j!=ctdadVuelosPlaneadosPorAerolinea-1){
					fe.getline(cadena,128);//salta aerolinea							
					fe.getline(cadena,128);//salta cantidad vuelos planeados por aerolinea
				}
				//guardar en la lista original que recibio
				//cout<<vuelos[i].codigoVuelo;				
				Aerolinea aero=sistema->aerolineas.buscarElemento(idAerolinea);					
				aero.itinerarios.vuelosPlaneados.insertarFinal(vuelos[j]);								
				sistema->aerolineas.modificarElemento(idAerolinea,aero);				
				if(j!=ctdadVuelosPlaneadosPorAerolinea-1){
					i++;
				}				
			}				
		}
	fe.close();
}

#endif    
