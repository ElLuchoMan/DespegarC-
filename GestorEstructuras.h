#ifndef GESTORESTRUCTURAS_H
#define GESTORESTRUCTURAS_H
#include <iostream>
#include <fstream>
#include "Estructuras.h"
#include "GestorAerolineas.h"
#include "GestorUsuarios.h"
#include "GestorVuelosPlaneados.h"
#include "GestorViajes.h"
#include "GestorReservas.h"
#include "GestorVuelosEspecificos.h"
#include "GestorAviones.h"
#include "GestorSillas.h"
#include "GestorCiudades.h"
#include <stdlib.h>


using namespace std;

string carpeta="archivos\\" //ruta de la carpeta donde se guardara todo
,backup="backup\\"
,sillas="sillas.txt" //nombre de los archivos para cada tipo de dato que se guardara
,vuelosEspecificos="vuelosEspecificos.txt"
,vuelosPlaneados="vuelosPlaneados.txt"
,aerolineas="aerolineas.txt"
,reservas="reservas.txt"
,viajes="viajes.txt"
,usuarios="usuarios.txt"
,aviones="aviones.txt"
,ciudades="ciudades.txt";


void cargarArchivos(int caso){//crear cada uno de los archivos si no existen, si ya existen no pasa nada. caso 0 fin programa, caso 1 backup
	string carpetaG;
	if(caso==0){
		carpetaG=carpeta;
	}else if(caso==1){
		carpetaG=carpeta+backup;
	}
	ofstream fs((carpetaG+aviones).c_str()); 
	fs.close();
	ofstream fs1((carpetaG+sillas).c_str()); 
	fs1.close();
	ofstream fs2((carpetaG+vuelosEspecificos).c_str()); 
	fs2.close();
	ofstream fs3((carpetaG+vuelosPlaneados).c_str()); 
	fs3.close();	
	ofstream fs4((carpetaG+aerolineas).c_str()); 
	fs4.close();
	ofstream fs5((carpetaG+reservas).c_str()); 
	fs5.close();
	ofstream fs6((carpetaG+viajes).c_str()); 
	fs6.close();
	ofstream fs7((carpetaG+usuarios).c_str()); 
	fs7.close();
	ofstream fs8((carpetaG+ciudades).c_str()); 
	fs8.close();
}

void guardarTodo(Sistema *sistema,int caso){//si el caso es 0 se finalizo el programa, guarda en la carpeta principal,
	string carpetaG="";						// si es 1 guardara en el backup
	if(caso==0){
		carpetaG=carpeta;
	}else if(caso==1){
		carpetaG=carpeta+backup;
	}
	cargarArchivos(caso);
	guardarAerolineas(sistema,carpetaG+aerolineas);	
	guardarUsuarios(sistema,carpetaG+usuarios);	
	guardarCiudades(sistema,carpetaG+ciudades);
	guardarVuelosPlaneados(crearListaVuelosPlaneadosTotales(sistema),carpetaG+vuelosPlaneados);
	guardarViajes(crearListaViajesTotales(sistema),carpetaG+viajes);
	guardarReservas(crearListaReservasTotales(sistema),carpetaG+reservas);
	guardarVuelosEspecificos(crearListaVuelosEspecificosTotales(sistema),carpetaG+vuelosEspecificos);
	guardarAviones(crearListaAvionesTotales(sistema),carpetaG+aviones);
	guardarSillas(crearListaSillasTotales(sistema),carpetaG+sillas);
	
}

void cargarTodo(Sistema *sistema,int caso){//si el caso es 0 se inicia el programa, carga en la carpeta de archivos principal, si es 1 cargara el backup
	string carpetaG="";
	if(caso==0){
		carpetaG=carpeta;
	}else if(caso==1){
		carpetaG=carpeta+backup;
	}
	leerAerolineas(sistema,carpetaG+aerolineas);
	leerUsuarios(sistema,carpetaG+usuarios);
	leerCiudades(sistema,carpetaG+ciudades);
	leerVuelosPlaneados(sistema,carpetaG+vuelosPlaneados);
	leerViajes(sistema,carpetaG+viajes);
	leerReservas(sistema,carpetaG+reservas);	
	leerAviones(sistema,carpetaG+aviones);
	leerSillas(sistema,carpetaG+sillas);
	leerVuelosEspecificos(sistema,carpetaG+vuelosEspecificos);
}


//manejo de archivos de backup
bool eliminarBackup(){//si algun archivo no se puede eliminar retornara falso, mientras no haya error seguira eliminando hasta dar true
	string carpetaG=carpeta+backup;	
	if(remove((carpetaG+aviones).c_str())!=0){	
		return false;
	}
	if(remove((carpetaG+sillas).c_str())!=0){	
		return false;
	}
	if(remove((carpetaG+vuelosEspecificos).c_str())!=0){
		return false;
	}
	if(remove((carpetaG+vuelosPlaneados).c_str())!=0){	
		return false;
	}
	if(remove((carpetaG+aerolineas).c_str())!=0){
		return false;
	}
	if(remove((carpetaG+reservas).c_str())!=0){	
		return false;
	}
	if(remove((carpetaG+viajes).c_str())!=0){
		return false;
	}
	if(remove((carpetaG+usuarios).c_str())!=0){	
		return false;
	}
	if(remove((carpetaG+ciudades).c_str())!=0){	
		return false;
	}
	return true;
}

bool hayBackup(){//abre y cierra todos los archivos del backup, si falta alguno no lo detecta como backup valido y retorna false
	string carpetaG=carpeta+backup;	
	FILE *f1=fopen((carpetaG+sillas).c_str(),"r");
	FILE *f2=fopen((carpetaG+vuelosEspecificos).c_str(),"r");
	FILE *f3=fopen((carpetaG+vuelosPlaneados).c_str(),"r");
	FILE *f4=fopen((carpetaG+aerolineas).c_str(),"r");
	FILE *f5=fopen((carpetaG+reservas).c_str(),"r");
	FILE *f6=fopen((carpetaG+viajes).c_str(),"r");
	FILE *f7=fopen((carpetaG+usuarios).c_str(),"r");
	FILE *f8=fopen((carpetaG+aviones).c_str(),"r");
	FILE *f9=fopen((carpetaG+ciudades).c_str(),"r");
	if(f1){
		fclose(f1);
		if(f2){	
			fclose(f2);
			if(f3){
				fclose(f3);
				if(f4){	
					fclose(f4);
					if(f5){
						fclose(f5);
						if(f6){	
							fclose(f6);
							if(f7){
								fclose(f7);								
								if(f8){
									fclose(f8);
									if(f9){
										fclose(f9);
										return true;
									}																									
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

#endif

