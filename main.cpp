#include <iostream>
#include "Menus.h"
#include "GestorEstructuras.h"
#include "BaseDeDatos.h"
#include "Cola.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void detectarBackup(){//detecta si existen los archivos de backup, lo cual significaria que no se cerro correctamente la ultima vez, y da opcion de recuperar el backup
	calcularDias(20,11,2017);
	if(hayBackup()){
		cout<<"Se detecto un backup de la ultima sesion, ¿cargar backup?"<<endl<<endl<<"N-No, cargar normal"<<endl<<"S-Si, cargar Backup"<<endl<<endl<<"?";	
		string opc="n";	
		cin>>opc;
		if(opc=="s"||opc=="S"){
			cargarTodo(sistemaGlobal,1);
   			menuPrincipal();
		}else{
			cargarTodo(sistemaGlobal,0);
   			menuPrincipal();
		}
	}else{
		cargarTodo(sistemaGlobal,0);
   		menuPrincipal();
	}
}

/*
string nombres[]={"Carolina_Vargas","Andres_Vanegas","Cristian_Ruiz","Cindy_Mendez","Maria_Bernal","Camila_Muñoz","Rodrigo_Castro","Diego_Salazar","Andrea_Martinez",
"Catherine_Rodriguez","Mindi_Vanegas","Rodrigo_Mendez","Rodrigo_Vanegas","Cindy_Muñoz","Cindy_Martinez","Carolina_Muñoz","Carolina_Bastidas","Camila_Pedroza",
"Maria_Peña","Andrea_Lopez","Andres_Vargas","Andrea_Vargas","Carolina_Bustos","Cindy_Castro","Maria_Cardenas","Maria_Cardona","Ximena_Ruiz","Andrea_Amaya","Marcela_Ruiz",
"Sergio_Vargas","Hernan_Vargas","John_Mendez","Heidy_Mendez","Johanna_Vanegas","Carolina_Mendez","Martin_Mendez","Maria_Cabral","Lizeth_Mendez","Patricia_Mendez",
"Judi_Castañeda","Martin_Ruiz","Andrea_Ruiz","Maria_Rojas","Marcela_Mendez","Katherin_Castillo","David_Toledo","Katherin_Rodriguez","Katherin_Bernal","Juan_Sanchez",
"Andres_Ariza","Heidy_Vanegas","Cristina_Vargas","Yeimy_Ruiz","Camila_Parra","Cristian_Vargas","Camila_Cabral","Cristian_Cabral","Andres_Mendoza","Maria_Bustos",
"Juan_Mendez","John_Mendoza","Juan_Mendez","Maria_Mendez","Andrea_Reyes","Cristian_Cota","Cindy_Muñoz","Carolina_Betancour","Judi_Vanegas","Rodrigo_Vanegas","David_Mendez",
"Maria_Reyes","Paola_Vanegas","Alexander_Mendez","Cristian_Toledo","Cindy_Cardona","Carolina_Betancour","Camilo_Vanegas","Cristian_Forero","Andrea_Mendoza","Martin_Bustos",
"Jessica_Cancelado","Jessica_Parra","Cristina_Muñoz","Camila_Martinez","Jessica_Ruiz","Juan_Mendez","Andres_Ruiz","Katherin_Lopez","Pablo_Ruiz","Cristian_Escobar",
"Andrea_Bustamante","Mario_Mendez","Alex_Mendez","Carolina_Martinez","Johanna_Ariza","Heidy_Vanegas","Felipe_castro","Nicol_Cardona","Ximena_Muñoz","Pablo_Castro"};

string sexos[]={"F","M","M","F","F","F","M","M","F",
"F","F","M","M","F","F","F","F","F",
"F","F","M","F","F","F","F","F","F","F","F",
"M","M","M","F","F","F","M","F","F","F",
"F","M","F","F","F","F","M","F","F","M",
"M","F","F","F","F","M","F","M","M","F",
"M","M","M","F","F","M","F","F","F","M","M",
"F","F","M","M","F","F","M","M","F","M",
"F","F","F","F","F","M","M","F","M","M",
"F","M","M","F","F","F","M","F","F","M"};

long int generarAleatorio(int min,int max,int semilla){
	long int aleatorio=0;	
	int rango=max-min;	
	aleatorio = rand()%rango;	
	aleatorio=aleatorio+min;
	cout<<aleatorio<<endl;		
	return aleatorio;
	
  }

void guardarTodasLosUsuarios(){
	
	string archivo="asd.txt";
	ofstream fs(archivo.c_str()); 
	fs<<"100"<<endl;
	int contador=0;
	int id=1023587985;
	srand (time(NULL));
		for(int j=0;j<100;j++){
			Usuario user;
			user.edad=generarAleatorio(18,60,j);
			user.nombre=nombres[j];
			user.idUnico=j+1;
			user.sexo=sexos[j];
			ostringstream os;
			os<<(id+j);
			user.identificacion=(os.str());
			sistemaGlobal->usuarios.insertarFinal(user);
			guardarTodo(sistemaGlobal,0);
		}		
		system("pause");	
	fs.close();
}

/*
string idSillas[]={"1A","2A","1B","2B","3B"};

void guardarTodasLasSillas(){	
	string archivo="asd.txt";
	ofstream fs(archivo.c_str()); 
	fs<<"750"<<endl;
	int contador=0;
	
		for(int j=0;j<sistemaGlobal->aerolineas.getTam();j++){
			Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(j+1);
			for(int k=0;k<aero.aviones.getTam();k++){
				Avion avion=aero.aviones.buscarElemento(k+1);
				for(int l=0;l<5;l++){
					fs<<aero.idAerolinea<<endl;
					fs<<avion.idAvion<<endl;
					fs<<"5"<<endl;
					fs<<idSillas[l]<<endl;					
					fs<<"0"<<endl;
					contador++;
					cout<<contador<<"-";
				}
			}
		}		
		system("pause");
	
	fs.close();
}*/
/*
   	Prioridad arreglo[5]={{1,5},{2,4},{3,5},{4,1},{5,2}};
   	Cola<Prioridad> cola;
   	
   	for(int i=0;i<5;i++){
   		cola.anadir(arreglo[i])	;
	   }
	   cout<<cola.getTam()<<endl<<endl;
	   Cola<Prioridad> copia=cola;
	for(int i=0;i<5;i++){
		Prioridad prio=cola.leer();
		cout<<prio.prioridad<<endl;
		cola.anadir(prio);
	}
	cout<<endl<<endl<<endl;
	for(int i=0;i<cola.getTam();i++){
		Prioridad prio=cola.leer();
		cout<<prio.prioridad<<endl;
		cola.anadir(prio);
	}*/

int main(int argc, char** argv) {	
	detectarBackup();
	//guardarTodasLasSillas();
	//guardarTodasLosUsuarios();

	
   	
	return 0;
}

