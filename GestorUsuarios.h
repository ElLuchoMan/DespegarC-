#ifndef GESTORUSUARIOS_h
#define GESTORUSUARIOS_h
#include <iostream>
#include <fstream>
#include "Estructuras.h"
#include <stdlib.h>
using namespace std;

int obtenerIdUsuarios(Sistema *sistema){
	int retorno=sistema->usuarios.getTam()+1;
	return retorno;
}

void guardarUsuarios(Sistema *sistema,string archivo){
	Lista<Usuario> usuarios=sistema->usuarios;
	ofstream fs(archivo.c_str()); //crear la conexion al archivo
	fs<<usuarios.getTam()<<endl;//escribir la cantidad de registros que se escribiran
	for(int i=0;i<usuarios.getTam();i++){
		Usuario user=usuarios.buscarElemento(i+1);	//tomar registro por registro y escribir sus caracteristicas sin contar listas hijas	
		fs<<user.idUnico<<endl;
		fs<<user.identificacion<<endl;
		fs<<user.nombre<<endl;
		fs<<user.sexo<<endl;
		fs<<user.edad<<endl;	
	}
	fs.close();//cerrar el archivo

}

void leerUsuarios(Sistema *sistema, string archivo){
	Lista<Usuario> usuarios=sistema->usuarios;
	char cadena[128];
	ifstream fe(archivo.c_str());
	//leer la cantidad total de usuarios	
		fe.getline(cadena, 128);				
		int cantidadUsuarios = atoi(cadena);
		//leer todos los usuarios		
		Usuario user[cantidadUsuarios];
		for(int i=0;i<cantidadUsuarios;i++){			
			fe.getline(cadena,128);
			user[i].idUnico=atoi(cadena);
			fe.getline(cadena,128);
			user[i].identificacion=cadena;
			fe.getline(cadena,128);
			user[i].nombre=cadena;
			fe.getline(cadena,128);
			user[i].sexo=cadena;
			fe.getline(cadena,128);
			user[i].edad=atoi(cadena);						
				//guardar en la lista original que recibio
				usuarios.insertarFinal(user[i]);
				
		}	
		sistema->usuarios=usuarios;
	fe.close();
}


#endif    
