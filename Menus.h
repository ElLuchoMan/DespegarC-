#ifndef MENUS_h
#define MENUS_h
#include <iostream>
#include <sstream>
#include "Lista.h"
#include "Estructuras.h"
#include <stdlib.h>
#include "BaseDeDatos.h"
#include "GestorEstructuras.h"
#include "Menus.h"
#include "Ordenamiento.h"
#include "time.h"

using namespace std;

string obtenerFechaActual(){
	time_t tiempo = time(NULL);//variable tiempo
    struct tm *tlocal = localtime(&tiempo); //estructura donde guardara el tiempo 
    char output[11]; //array donde guardo la fecha
    strftime(output,11,"%d/%m/%Y",tlocal); //formato para guardar la fecha obtenido en *tlocal como dd/mm/yyyy    
    string retorno=output;
    return retorno;
}

bool verificarFechaMenor(int diaMenor,int mesMenor,int annoMenor,int diaMayor,int mesMayor,int annoMayor){
	if(annoMayor>annoMenor){//si el año es diferente
		return true;
	}else if(annoMenor>annoMayor){
		return false;
	}else if(annoMenor==annoMayor){//si el año es igual
		if(mesMayor>mesMenor){//si el mes es diferente
			return true;
		}else if(mesMenor>mesMayor){
			return false;
		}else if(mesMenor==mesMayor){//si el mes es igual
			if(diaMayor>diaMenor){//si el dia es diferente
				return true;
			}else if(mesMenor>mesMayor){
				return false;
			}else if(mesMenor==mesMayor){//si el dia es igual
				return true;
			}
		}	
	}
}

int calcularDias(int dia,int mes, int anno){//calcula la cantidad de dias entre la fecha actual y la del viaje.	
    string fechaAct=obtenerFechaActual();    
    string diaAct,mesAct,annoAct;//separar la fecha en partes dia mes año
    ostringstream os;
   	os <<fechaAct[0]<<fechaAct[1];   	
	diaAct=os.str();
	os.str(std::string());
	os <<fechaAct[3]<<fechaAct[4];
	mesAct=os.str();
	os.str(std::string());
	os <<fechaAct[6]<<fechaAct[7]<<fechaAct[8]<<fechaAct[9];
	annoAct=os.str();
	os.str(std::string());
	int diaH=atoi(diaAct.c_str()),mesH=atoi(mesAct.c_str()),annoH=atoi(annoAct.c_str());
	bool Hmenor=verificarFechaMenor(diaH,mesH,annoH,dia,mes,anno);
	int total=-1;
	int annosDif=0,mesesDif=0,diasDif=0;
	if(Hmenor){		
		if(anno>annoH){
			annosDif=anno-annoH;
		}
		if(mes>mesH){
			mesesDif=mes-mesH;
		}
		if(dia>diaH){//si el dia es diferente
			diasDif=dia-diaH;
		}else if(diaH==dia){//si el dia es igual					
			diasDif=0;
		}				
		total=diasDif+(mesesDif*30)+(annosDif*364);
	}    
    return total;
	
}

int calcularPrecioConDescuento(int precio,int descuento){//descuento %
	int descuentoT=(precio/100)*descuento;
	int precioFinal=precio-descuentoT;
	return precioFinal;
}

string nombreDiaSemana(int i){//devuelve el nombre del dia segun el numero que ingrese
	if(i==1){
		return "lunes";
	}else if(i==2){
		return "martes";
	}else if(i==3){
		return "miercoles";
	}else if(i==4){
		return "jueves";
	}else if(i==5){
		return "viernes";
	}else if(i==6){
		return "sabado";
	}else if(i==7){
		return "domingo";
	}
}

void ubicarPosicionUsuario(int tipo, Sistema *sistema, int *guardar){	//se mueve entre las listas, ubicando un dato u objeto en especifico
	system("cls");														//tipo es el caso, y cada caso es un diferente nivel de las listas.
	Usuario user;														//guardar es un puntero, donde se guardara un arreglo con las posiciones encontradas
	Viaje viaje;
	Reserva reserva;

	bool x;
	switch(tipo){		

		case 1://ubicar una usuario;
			int arreglo1[1];//crea un arreglo para guardar la posicion
			arreglo1[0]=-1;			
			x=true;
			while(x){//mientras no haya encontrado la aerolinea continue
				system("cls");	
				cout<<"Lista de usuarios:"<<endl<<endl;//imprimir todos los usuarios
				for(int i=0;i<sistema->usuarios.getTam();i++){
					user=sistema->usuarios.buscarElemento(i+1);
					cout<<i+1<<" - "<<user.identificacion<<" ("<<user.nombre<<") "<<endl;
				}
				cout<<endl<<"Escriba el numero del usuario"<<endl<<endl<<"?";//pedir que elijan el numero
				cin>>arreglo1[0];
				cout<<endl<<endl;		
				if(arreglo1[0]>0&&arreglo1[0]<=sistema->usuarios.getTam()){//asegurarse que ingresaron un numero correcto. y acabar while
					x=false;
				}else{
					cout<<"Ingrese una opcion valida"<<endl;
					system("PAUSE");
				}
			}

			*guardar=*arreglo1;//guardar lo encontrado en la variable para ello
			break;
		case 2://ubicar un viaje			
			int arreglo2[2];			
			ubicarPosicionUsuario(1,sistema,guardar);
			arreglo2[0]=guardar[0];			
			x=true;
			while(x){
				system("cls");	
				user=sistema->usuarios.buscarElemento(arreglo2[0]);
				cout<<"Lista de viajes del usuario "<<user.identificacion<<" : "<<endl<<endl;
				
				for(int i=0;i<user.viajes.getTam();i++){
					viaje=user.viajes.buscarElemento(i+1);
					cout<<i+1<<" - "<<viaje.tipoDeViaje<<"-"<<viaje.reservas.getTam()<<" reservas."<<endl;
				}
				cout<<"Escriba el numero del viaje"<<endl<<endl<<"?";
				cin>>arreglo2[1];
				cout<<endl<<endl;		
				if(arreglo2[1]>0&&arreglo2[1]<=user.viajes.getTam()){//acaba el while
					x=false;
				}else{
					cout<<"Ingrese una opcion valida"<<endl;
					system("PAUSE");
				}
			}
						
			*guardar=*arreglo2;
			guardar[1]=arreglo2[1];			
			break;
		case 3://ubicar una reserva
			int arreglo3[3];
			ubicarPosicionUsuario(2,sistema,guardar);
			arreglo3[0]=guardar[0];
			arreglo3[1]=guardar[1];
			x=true;
			while(x){
				system("cls");	
				user=sistema->usuarios.buscarElemento(arreglo3[0]);
				viaje=user.viajes.buscarElemento(arreglo3[1]);
				cout<<"Lista de reservas del viaje elegido "<<viaje.tipoDeViaje<<"-"<<viaje.reservas.getTam()<<" reservas."<<endl<<endl;				
				for(int i=0;i<viaje.reservas.getTam();i++){
					reserva=viaje.reservas.buscarElemento(i+1);
					cout<<i+1<<" - "<<reserva.fechaReserva<<" - "<<reserva.idVuelo<<" - "<<reserva.precioPagado<<endl;
				}
				cout<<"Escriba el numero de la reserva"<<endl<<endl<<"?";
				cin>>arreglo3[2];
				cout<<endl<<endl;		
				if(arreglo3[2]>0&&arreglo3[2]<=viaje.reservas.getTam()){
					x=false;
				}else{
					cout<<"Ingrese una opcion valida"<<endl;//acaba el while
					system("PAUSE");
				}
			}
			*guardar=*arreglo3;
			guardar[1]=arreglo3[1];
			guardar[2]=arreglo3[2];	
			break;
	
	}
}

void ubicarPosicionAerolinea(int tipo, Sistema *sistema, int *guardar){	//se mueve entre las listas, ubicando un dato u objeto en especifico
	system("cls");														//tipo es el caso, y cada caso es un diferente nivel de las listas.
	Aerolinea aero;														//guardar es un puntero, donde se guardara un arreglo con las posiciones encontradas
	VueloPlaneado vueloP;
	VueloEspecifico vueloE;
	Silla silla;
	Avion avion;

	bool x;
	switch(tipo){		

		case 1://ubicar una aerolinea;
			int arreglo1[1];//crea un arreglo para guardar la posicion
			arreglo1[0]=-1;			
			x=true;
			while(x){//mientras no haya encontrado la aerolinea continue
				system("cls");	
				cout<<"Lista de aerolineas:"<<endl<<endl;//imprimir todas las erolineas
				for(int i=0;i<sistema->aerolineas.getTam();i++){
					Aerolinea aero=sistema->aerolineas.buscarElemento(i+1);
					cout<<i+1<<" - "<<aero.nombre<<endl;
				}
				cout<<endl<<"Escriba el numero de la aerolinea"<<endl<<endl<<"?";//pedir que elijan el numero
				cin>>arreglo1[0];
				cout<<endl<<endl;		
				if(arreglo1[0]>0&&arreglo1[0]<=sistema->aerolineas.getTam()){//asegurarse que ingresaron un numero correcto.
					x=false;
				}else{
					cout<<"Ingrese una opcion valida"<<endl;
					system("PAUSE");
				}
			}

			*guardar=*arreglo1;//guardar lo encontrado en la variable para ello
			break;
		case 2://ubicar una vuelo planeado			
			int arreglo2[2];			
			ubicarPosicionAerolinea(1,sistema,guardar);
			arreglo2[0]=guardar[0];			
			x=true;
			while(x){
				system("cls");	
				aero=sistema->aerolineas.buscarElemento(arreglo2[0]);
				cout<<"Lista de vuelos planeados en la aerolinea "<<aero.nombre<<" : "<<endl<<endl;
				
				for(int i=0;i<aero.itinerarios.vuelosPlaneados.getTam();i++){
					vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(i+1);
					cout<<i+1<<" - "<<vueloP.idOrigen<<"-"<<vueloP.idDestino<<endl;
				}
				cout<<"Escriba el numero del vuelo"<<endl<<endl<<"?";
				cin>>arreglo2[1];
				cout<<endl<<endl;		
				if(arreglo2[1]>0&&arreglo2[1]<=aero.itinerarios.vuelosPlaneados.getTam()){
					x=false;
				}else{
					cout<<"Ingrese una opcion valida"<<endl;
					system("PAUSE");
				}
			}
						
			*guardar=*arreglo2;
			guardar[1]=arreglo2[1];			
			break;
		case 3://ubicar un vuelo especifico
			int arreglo3[3];
			ubicarPosicionAerolinea(2,sistema,guardar);
			arreglo3[0]=guardar[0];
			arreglo3[1]=guardar[1];
			x=true;
			while(x){
				system("cls");	
				aero=sistema->aerolineas.buscarElemento(arreglo3[0]);
				vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(arreglo3[1]);
				cout<<"Lista de vuelos especificos del planeado elegido "<<vueloP.idOrigen<<"-"<<vueloP.idDestino<<endl<<endl;				
				for(int i=0;i<vueloP.vuelosEspecificos.getTam();i++){
					vueloE=vueloP.vuelosEspecificos.buscarElemento(i+1);
					cout<<i+1<<" - "<<vueloE.dia<<"/"<<vueloE.mes<<"/"<<vueloE.anio<<endl;
				}
				cout<<"Escriba el numero del vuelo especifico"<<endl<<endl<<"?";
				cin>>arreglo3[2];
				cout<<endl<<endl;		
				if(arreglo3[2]>0&&arreglo3[2]<=vueloP.vuelosEspecificos.getTam()){
					x=false;
				}else{
					cout<<"Ingrese una opcion valida"<<endl;
					system("PAUSE");
				}
			}
			*guardar=*arreglo3;
			guardar[1]=arreglo3[1];
			guardar[2]=arreglo3[2];	
			break;
		case 4:{//ubicar un avion
			int arreglo4[2];
			ubicarPosicionAerolinea(1,sistema,guardar);
			arreglo4[0]=guardar[0];			
			x=true;
			while(x){
				system("cls");	
				aero=sistema->aerolineas.buscarElemento(arreglo4[0]);
				cout<<"Lista de aviones en la aerolinea "<<aero.nombre<<" : "<<endl<<endl;
				
				for(int i=0;i<aero.aviones.getTam();i++){
					avion=aero.aviones.buscarElemento(i+1);
					cout<<i+1<<" - "<<avion.modelo<<"-"<<avion.matricula<<endl;
				}
				cout<<"Escriba el numero del avion"<<endl<<endl<<"?";
				cin>>arreglo4[1];
				cout<<endl<<endl;		
				if(arreglo4[1]>0&&arreglo4[1]<=aero.aviones.getTam()){
					x=false;
				}else{
					cout<<"Ingrese una opcion valida"<<endl;
					system("PAUSE");
				}
			}
						
			*guardar=*arreglo4;
			guardar[1]=arreglo4[1];	
			break;
		}
				
		case 5://ubicar una silla
			int arreglo5[3];
			ubicarPosicionAerolinea(4,sistema,guardar);
			arreglo5[0]=guardar[0];
			arreglo5[1]=guardar[1];			
			x=true;
			while(x){
				system("cls");	
				aero=sistema->aerolineas.buscarElemento(arreglo5[0]);
				avion=aero.aviones.buscarElemento(arreglo5[1]);				
				cout<<"Lista de sillas del avion escogido "<<" - "<<avion.modelo<<" - "<<avion.matricula<<endl<<endl;				
				for(int i=0;i<avion.sillas.getTam();i++){
					silla=avion.sillas.buscarElemento(i+1);
					cout<<i+1<<" - "<<silla.idSilla<<endl;
				}
				cout<<"Escriba el numero de la silla"<<endl<<endl<<"?";
				cin>>arreglo5[3];
				cout<<endl<<endl;		
				if(arreglo5[3]>0&&arreglo5[3]<=avion.sillas.getTam()){
					x=false;
				}else{
					cout<<"Ingrese una opcion valida"<<endl;
					system("PAUSE");
				}
			}
			*guardar=*arreglo5;
			guardar[1]=arreglo5[1];
			guardar[2]=arreglo5[2];	
			guardar[3]=arreglo5[3];	
			break;
	}
}

void imprimirAerolinea(Aerolinea aerolinea){
	cout<<"Aerolinea N° "<<aerolinea.idAerolinea<<endl<<"Nombre: "<<aerolinea.nombre<<endl<<"Aviones disponibles: "<<aerolinea.avionesDisponibles<<endl	
	<<"Cuenta Bancaria: "<<aerolinea.numero_cuenta_bancaria<<endl<<"Plan de trayecto: "<<aerolinea.itinerarios.idPlan<<" - "<<aerolinea.itinerarios.vuelosPlaneados.getTam()<<" vuelos planeados."<<endl<<endl;
}

void imprimirUsuario(Usuario usuario){
	cout<<"Usuario N° "<<usuario.idUnico<<endl<<"Nombre: "<<usuario.nombre<<endl<<"Identificacion: "<<usuario.identificacion<<endl	
	<<"Edad: "<<usuario.edad<<endl<<"Sexo: "<<usuario.sexo<<endl<<"Cantidad viajes: "<<usuario.viajes.getTam()<<endl<<endl;
}

void imprimirVueloPlaneado(VueloPlaneado vuelop){
	Ciudad ciudad;
	string origen,destino;
	ciudad=sistemaGlobal->ciudades.buscarElemento(vuelop.idOrigen);
	origen=ciudad.nombreCiudad;
	ciudad=sistemaGlobal->ciudades.buscarElemento(vuelop.idDestino);
	destino=ciudad.nombreCiudad;
	cout<<"Codigo N° "<<vuelop.codigoVuelo<<endl<<"Origen-Destino: "<<vuelop.idOrigen<<"("<<origen<<") "<<" - "<<vuelop.idDestino<<"("<<destino<<")."<<endl;
	cout<<"Vuelo multiple: ";
	if(vuelop.vueloMultiple){	
		cout<<"Si"<<endl<<"Vuelos Asociados: ";
		for(int i=0;i<vuelop.vuelosDirectos.getTam();i++){
			cout<<vuelop.vuelosDirectos.buscarElemento(i+1);
			if(i!=vuelop.vuelosDirectos.getTam()-1){
				cout<<" - ";
			}
		}
		cout<<endl<<endl;
	}else{
		cout<<"No"<<endl<<"Dia: ";	
		int contador=0;
		for(int i=1;i<8;i++){		
			if(vuelop.diaDeLaSemana[i]==1){
				cout<<nombreDiaSemana(i);
				contador++;
				if(contador<vuelop.diaDeLaSemana[0]){
					cout<<" - ";
				}	
			}
		}
		cout<<endl;		
		cout<<"Horario: "<<vuelop.salida.hora<<":"<<vuelop.salida.minuto<<" - "<<vuelop.llegada.hora<<":"<<vuelop.llegada.minuto<<" ("<<vuelop.duracion<<" horas)"<<endl<<
		"Cantidad viajes especificos: "<<vuelop.vuelosEspecificos.getTam()<<endl;
	}
	cout<<endl<<endl;
	
	
	
}

void imprimirViaje(Viaje viaje){
	cout<<"id N° "<<viaje.idViaje<<endl<<"tipo de viaje: "<<viaje.tipoDeViaje<<endl<<"Cantidad de reservas: "<<viaje.reservas.getTam()<<endl<<endl;
}

void imprimirReserva(Reserva reserva){
	cout<<"id N° "<<reserva.idReserva<<endl<<"tipo de reserva: "<<reserva.tipo<<endl<<"id vuelo: "<<reserva.idVuelo<<endl<<"Precio pagado: "<<reserva.precioPagado
	<<endl<<"Fecha en que se reservo: "<<reserva.fechaReserva<<endl<<endl;
}

void imprimirVueloEspecifico(VueloEspecifico vueloe){
	int cantDias=calcularDias(vueloe.dia,vueloe.mes,vueloe.anio);
	cout<<"Codigo N° "<<vueloe.idCodigoVueloEspecifico<<endl<<"Fecha: "<<vueloe.dia<<"/"<<vueloe.mes<<"/"<<vueloe.anio<<endl<<"Id Avion: "<<vueloe.idAvion<<endl<<
	"Cupos Libres: "<<vueloe.cuposLibres<<endl<<"Tarifa ";
	if(cantDias>30 && cantDias<=60){	
		cout<<"(10% dcto):"<<endl<<vueloe.tarifaAdulto<<"-10%:"<<calcularPrecioConDescuento(vueloe.tarifaAdulto,10) <<" (adulto)"<<endl
		<<vueloe.tarifaNinio<<"-10%:"<<calcularPrecioConDescuento(vueloe.tarifaNinio,10)<<" (nino)"<<endl<<endl;
	}if(cantDias>60){
		cout<<"(20% dcto):"<<endl<<vueloe.tarifaAdulto<<"-20%:"<<calcularPrecioConDescuento(vueloe.tarifaAdulto,20) <<" (adulto)"<<endl
		<<vueloe.tarifaNinio<<"-20%:"<<calcularPrecioConDescuento(vueloe.tarifaNinio,20)<<" (nino)"<<endl<<endl;
	}else if(cantDias<=30){
		cout<<": "<<vueloe.tarifaAdulto<<" (adulto)               -     "<<vueloe.tarifaNinio<<" (nino)"<<endl<<endl;
	}
}

void imprimirAvion(Avion avion){
	cout<<"id N° "<<avion.idAvion<<endl<<"Modelo: "<<avion.modelo<<endl<<"Matricula: "<<avion.matricula<<endl<<"capacidad: "<<avion.capacidad<<endl<<endl;
}

void imprimirPasajero(Pasajero pasajero){
	cout<<"identificacion: "<<pasajero.identificacion<<endl<<"Nombre: "<<pasajero.nombre<<" "<<pasajero.apellido<<endl<<": "<<pasajero.fechaNacimiento<<endl
	<<"tipo: "<<pasajero.tipo<<endl<<"reserva N°: "<<pasajero.numeroReserva<<endl<<endl;
}

void imprimirSilla(Silla silla){
	cout<<"Codigo N° "<<silla.idSilla<<endl<<"estado: ";
	if(silla.estado){
		cout<<"vendida"<<endl;
		imprimirPasajero(silla.pasajero);
	}else{
		cout<<"disponible";
	}
	cout<<endl<<endl;
}

void menuPrincipalImprimir(){
	int opcion=-1;
	while (opcion!=0){
		system("cls");
		cout<<"-------------Menu de impresion---------------"<<endl<<endl;
	   	//cout<<"Si desea imprimir toda la informacion ingrese 1"<<endl;
	   	cout<<"Si desea imprimir AEROLINEAS ingrese 2"<<endl;
	   	cout<<"Si desea imprimir USUARIOS ingrese 3"<<endl;
	   	cout<<"Si desea imprimir VUELOS PLANEADOS ingrese 4"<<endl;
	   	cout<<"Si desea imprimir VIAJES ingrese 5"<<endl;
	   	cout<<"Si desea imprimir RESERVAS ingrese 6"<<endl;
	   	cout<<"Si desea imprimir VUELOS ESPECIFICOS ingrese 7"<<endl;
	   	cout<<"Si desea imprimir AVIONES ingrese 8"<<endl;
	   	cout<<"Si desea imprimir SILLAS ingrese 9"<<endl;
	   	cout<<"Si desea regresar al menu anterior ingrese 0"<<endl<<endl<<"?";
	   	cin>>opcion;
	   	
	   	switch(opcion){
	   		case 1:
	   			//imprimirTodo(sistemaGlobal);
	   			break;
	   		case 2://imprimir aerolineas
	   			system("cls");
	   			cout<<"Mostrando "<<sistemaGlobal->aerolineas.getTam()<<" aerolineas"<<endl<<endl;
	   			for(int i=0;i<sistemaGlobal->aerolineas.getTam();i++){
				   	imprimirAerolinea(sistemaGlobal->aerolineas.buscarElemento(i+1));
	   			}
	   			system("PAUSE");
				break;
	   		case 3://imprimir usuarios
	   			system("cls");
	   			cout<<"Mostrando "<<sistemaGlobal->usuarios.getTam()<<" usuarios"<<endl<<endl;
	   			system("pause");
	   			for(int i=0;i<sistemaGlobal->usuarios.getTam();i++){
				   	imprimirUsuario(sistemaGlobal->usuarios.buscarElemento(i+1));
	   			}
	   			system("PAUSE");
	   			break;
	   		case 4:{	//imprimir vuelos planeados			
	   			system("cls");
	   			Lista<VueloPlaneadosTotal> vuelosPla=crearListaVuelosPlaneadosTotales(sistemaGlobal);
	   			cout<<"Mostrando "<<vuelosPla.getTam()<<" vuelos planeados"<<endl<<endl;
	   			for(int i=0;i<vuelosPla.getTam();i++){
	   				VueloPlaneadosTotal aux=vuelosPla.buscarElemento(i+1);
	   				cout<<"Aerolinea: "<<aux.idAerolinea<<"   - Plan de trayecto: "<<aux.idPlanTrayecto<<endl;
				   	imprimirVueloPlaneado(aux.vuelosP.buscarElemento(1));
	   			}
	   			system("PAUSE");
	   			break;
	   		}
	   		case 5:{//imprimir viajes 
	   			system("cls");
	   			Lista<ViajeTotal> viajes=crearListaViajesTotales(sistemaGlobal);
	   			cout<<"Mostrando "<<viajes.getTam()<<" viajes"<<endl<<endl;
	   			for(int i=0;i<viajes.getTam();i++){
	   				ViajeTotal aux=viajes.buscarElemento(i+1);
	   				cout<<"Usuario: "<<aux.idUsuario<<endl;
				   	imprimirViaje(aux.viajes.buscarElemento(1));
	   			}
	   			system("PAUSE");
				break;
			   }
			case 6:{//imprimir reservas
				system("cls");
	   			Lista<ReservaTotal> reservas=crearListaReservasTotales(sistemaGlobal);
	   			cout<<"Mostrando "<<reservas.getTam()<<" reservas"<<endl<<endl;
	   			for(int i=0;i<reservas.getTam();i++){
	   				ReservaTotal aux=reservas.buscarElemento(i+1);
	   				cout<<"Usuario: "<<aux.idUsuario<<" - "<<"Viaje: "<<aux.idViaje<<endl;
				   	imprimirReserva(aux.reservas.buscarElemento(1));
	   			}
	   			system("PAUSE");
				break;
			}
			case 7:{//imprimir vuelos especificos
				system("cls");
	   			Lista<VueloEspecificoTotal> vuelosEsp=crearListaVuelosEspecificosTotales(sistemaGlobal);
	   			cout<<"Mostrando "<<vuelosEsp.getTam()<<" vuelos especificos"<<endl<<endl;
	   			for(int i=0;i<vuelosEsp.getTam();i++){
	   				VueloEspecificoTotal aux=vuelosEsp.buscarElemento(i+1);
	   				cout<<"Aerolinea: "<<aux.idAerolinea<<"   - P. trayecto: "<<aux.idPlanTrayecto<<" - V. planeado: "<<aux.idVueloPlaneado<<endl;
				   	imprimirVueloEspecifico(aux.vuelosE.buscarElemento(1));
	   			}
	   			system("PAUSE");
				break;
			}
			case 8:{//imprimir aviones
				system("cls");
	   			Lista<AvionTotal> aviones=crearListaAvionesTotales(sistemaGlobal);
	   			cout<<"Mostrando "<<aviones.getTam()<<" aviones"<<endl<<endl;
	   			system("pause");
	   			for(int i=0;i<aviones.getTam();i++){
	   				AvionTotal aux=aviones.buscarElemento(i+1);
	   				cout<<"Aerolinea: "<<aux.idAerolinea<<endl;
				   	imprimirAvion(aux.aviones.buscarElemento(1));
	   			}
	   			system("PAUSE");
				break;
			}
			case 9:{//imprimir sillas
				system("cls");
	   			Lista<SillaTotal> sillas=crearListaSillasTotales(sistemaGlobal);
	   			cout<<"Mostrando "<<sillas.getTam()<<" sillas"<<endl<<endl;
	   			system("pause");
	   			for(int i=0;i<sillas.getTam();i++){
	   				SillaTotal aux=sillas.buscarElemento(i+1);
	   				cout<<"Aerolinea: "<<aux.idAerolinea<<" - Avion: "<<aux.idAvion<<endl;
				   	imprimirSilla(aux.sillas.buscarElemento(1));
	   			}
	   			system("PAUSE");
				break;
			}
	   		case 0:
	   				
	   			break;

	   		default:
	   			cout<<"---Ingrese una opcion valida---"<<endl<<endl<<endl;
	   			system("PAUSE");
	   			break;
	  	}
	  	guardarTodo(sistemaGlobal,1);//guardar backup
	}
}

//consultas

Lista<Pasajero> pasajerosEnVueloDeUsuario(Viaje viaje){
	Lista<Pasajero> retorno;
	for(int i=0;i<viaje.reservas.getTam();i++){
		Reserva reserva=viaje.reservas.buscarElemento(i+1);
		VueloEspecificoTotal vueloT=encontrarVueloEspecifico(reserva.idVuelo,sistemaGlobal);
		VueloEspecifico vueloE=vueloT.vuelosE.buscarElemento(1);
		Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(vueloT.idAerolinea);
		VueloPlaneado vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(buscarPosVueloPlaneado(vueloT.idVueloPlaneado,aero.itinerarios.vuelosPlaneados));
		Avion avion=aero.aviones.buscarElemento(buscarPosAvion(vueloE.idAvion,aero.aviones));
		for(int j=0;j<avion.sillas.getTam();j++){
			Silla silla=avion.sillas.buscarElemento(j+1);
			if(silla.pasajero.numeroReserva==reserva.idReserva){
				retorno.insertarFinal(silla.pasajero);
			}
		}
	}
	return retorno;
}

void pasajerosEnVueloEspecifico(VueloEspecifico vuelo){
	Lista<Pasajero> retorno;
	VueloEspecificoTotal vueloT=encontrarVueloEspecifico(vuelo.idCodigoVueloEspecifico,sistemaGlobal);
	Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(vueloT.idAerolinea);
	Avion avion=aero.aviones.buscarElemento(buscarPosAvion(vuelo.idAvion,aero.aviones));
	Silla silla;
	for(int i=0;i<avion.sillas.getTam();i++){
		silla=avion.sillas.buscarElemento(i+1);				
		if(silla.estado){
			cout<<"Silla "<<silla.idSilla<<endl;
			imprimirPasajero(silla.pasajero);
		}
		cout<<endl<<endl;
	}
	system("pause");
}

void SillasVaciasEnVueloEspecifico(VueloEspecifico vuelo){
	Lista<Pasajero> retorno;
	VueloEspecificoTotal vueloT=encontrarVueloEspecifico(vuelo.idCodigoVueloEspecifico,sistemaGlobal);
	Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(vueloT.idAerolinea);
	Avion avion=aero.aviones.buscarElemento(buscarPosAvion(vuelo.idAvion,aero.aviones));
	Silla silla;
	for(int i=0;i<avion.sillas.getTam();i++){
		silla=avion.sillas.buscarElemento(i+1);		
		
		if(!silla.estado){				
			cout<<"Silla "<<silla.idSilla<<endl;
			cout<<"-----No vendida-----"<<endl;
		}
		cout<<endl<<endl;
	}
	system("pause");
}

void ColasDeEspera(VueloEspecifico vuelo){	
	Usuario user;
	if(vuelo.prioridades.getTam()>0){
		cout<<"Mostrando "<<vuelo.prioridades.getTam()<<" personas en cola:"<<endl<<endl;
		for(int i=0;i<vuelo.prioridades.getTam();i++){
			Prioridad prioridad=vuelo.prioridades.leer();
			user=sistemaGlobal->usuarios.buscarElemento(prioridad.cliente);
			cout<<user.identificacion<<" - prioridad: "<<prioridad.prioridad<<endl;
			vuelo.prioridades.anadir(prioridad);
		}
	}else{
		cout<<"No hay personas en cola."<<endl<<endl;
	}
	system("pause");

}

void vuelosEnViajesMultiples(){
	Aerolinea aero;
	VueloPlaneado vueloP,vueloPAux;	
	Ciudad ciudad;
	int idVueloP,pos;
	string origen,destino;
	VueloPlaneadosTotal vueloPT;
	for(int i=0;i<sistemaGlobal->aerolineas.getTam();i++){
		aero=sistemaGlobal->aerolineas.buscarElemento(i+1);
		for(int j=0;j<aero.itinerarios.vuelosPlaneados.getTam();j++){
			vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(j+1);
			if(vueloP.vueloMultiple){
				ciudad=sistemaGlobal->ciudades.buscarElemento(vueloP.idOrigen);
				origen=ciudad.nombreCiudad;
				ciudad=sistemaGlobal->ciudades.buscarElemento(vueloP.idDestino);
				destino=ciudad.nombreCiudad;
				cout<<"Id vuelo: "<<vueloP.codigoVuelo<<"   "<<origen<<" - "<<destino<<"("<<vueloP.vuelosDirectos.getTam()<<" escalas)."<<endl<<endl;
				for(int k=0;k<vueloP.vuelosDirectos.getTam();k++){	
					idVueloP=vueloP.vuelosDirectos.buscarElemento(k+1);
					Lista<VueloPlaneadosTotal> vuelosPT=crearListaVuelosPlaneadosTotales(sistemaGlobal);
					pos=buscarPosVueloPlaneado(idVueloP,vuelosPT);
					vueloPT=vuelosPT.buscarElemento(pos);
					vueloPAux=vueloPT.vuelosP.buscarElemento(1);
					ciudad=sistemaGlobal->ciudades.buscarElemento(vueloPAux.idOrigen);
					origen=ciudad.nombreCiudad;
					ciudad=sistemaGlobal->ciudades.buscarElemento(vueloPAux.idDestino);
					destino=ciudad.nombreCiudad;			
					cout<<k+1<<" - "<<origen<<" - "<<destino<<endl;
				}
				cout<<endl<<endl;
			}
			
		}
		
	}
	cout<<endl;
	system("pause");
}

//fin cosultas
//rankings
//dd/mm/AAAA

Lista<Reserva> buscarPasajesVendidosEnMes(){
	Lista<Reserva> retorno;
	string fechaActual=obtenerFechaActual();
	ostringstream os;	
	string mesReserva;
	ReservaTotal reservaT;
	Reserva reserva;
	os<<fechaActual[4]<<fechaActual[5];
	string mesS=os.str();
	
	Lista<ReservaTotal> reservas=crearListaReservasTotales(sistemaGlobal);	
	for(int i=0;i<reservas.getTam();i++){		
		reservaT=reservas.buscarElemento(i+1);	
		reserva=reservaT.reservas.buscarElemento(1);		
		os.str("");			
		os<<reserva.fechaReserva[4]<<reserva.fechaReserva[5];				
		mesReserva=os.str();
		if(mesReserva==mesS){
			retorno.insertarFinal(reserva);			
		}
	}
	return retorno;
	system("pause");	
} 

void imprimirRankingUsuarios(){
	Usuario user;
	Viaje viaje;	
	Reserva reserva;
	int contadorTotal=0;
	int usarios_totalPagado[sistemaGlobal->usuarios.getTam()][2];	
	for(int i=0;i<sistemaGlobal->usuarios.getTam();i++){
		user=sistemaGlobal->usuarios.buscarElemento(i+1);		
		contadorTotal=0;
		
		for(int j=0;j<user.viajes.getTam();j++){			
			viaje=user.viajes.buscarElemento(j+1);			
			for(int k=0;k<viaje.reservas.getTam();k++){
				reserva=viaje.reservas.buscarElemento(k+1);
				contadorTotal=contadorTotal+reserva.precioPagado;
				
			}
		}		
		usarios_totalPagado[i][0]=user.idUnico;
		usarios_totalPagado[i][1]=contadorTotal;
	}
	//usarios_totalPagado[20][1]=4254658;
	//usarios_totalPagado[53][1]=3954642;
	seleccion(usarios_totalPagado,sistemaGlobal->usuarios.getTam());
	cout<<endl<<endl;
	for(int i=sistemaGlobal->usuarios.getTam()-1;i>=0;i--){
		user=sistemaGlobal->usuarios.buscarElemento(usarios_totalPagado[i][0]);
		cout<<usarios_totalPagado[i][0]<<" - "<<user.identificacion<<" "<<user.nombre<<" ($"<<usarios_totalPagado[i][1]<<")"<<endl;
	}
	system("pause");
}

void imprimirRankingAerolineas(){
	Usuario user;
	Viaje viaje;	
	Reserva reserva;	
	Aerolinea aero;
	int usoDeAerolineas[sistemaGlobal->aerolineas.getTam()][2];	
	for(int i=0;i<sistemaGlobal->aerolineas.getTam();i++){		
		usoDeAerolineas[i][0]=i;
		usoDeAerolineas[i][1]=0;
	}
	Lista<VueloEspecificoTotal> vuelosET=crearListaVuelosEspecificosTotales(sistemaGlobal);
	VueloEspecificoTotal vueloET;
	VueloEspecifico vueloE;	
	for(int i=0;i<sistemaGlobal->usuarios.getTam();i++){
		user=sistemaGlobal->usuarios.buscarElemento(i+1);		
		for(int j=0;j<user.viajes.getTam();j++){			
			viaje=user.viajes.buscarElemento(j+1);			
			for(int k=0;k<viaje.reservas.getTam();k++){
				reserva=viaje.reservas.buscarElemento(k+1);
				vueloET=vuelosET.buscarElemento(buscarPosVueloEspecifico(reserva.idVuelo,vuelosET));
				usoDeAerolineas[vueloET.idAerolinea-1][1]=usoDeAerolineas[vueloET.idAerolinea-1][1]+1;
				
			}
		}	
		
	}	
	
	seleccion(usoDeAerolineas,sistemaGlobal->aerolineas.getTam());
	cout<<endl<<endl;
	for(int i=sistemaGlobal->aerolineas.getTam()-1;i>=0;i--){
		aero=sistemaGlobal->aerolineas.buscarElemento(usoDeAerolineas[i][0]+1);
		cout<<usoDeAerolineas[i][0]+1<<" - "<<aero.nombre<<" ("<<usoDeAerolineas[i][1]<<" boletos vendidos)"<<endl;
	}
	system("pause");
}

void imprimirRankingDestinos(){
	Usuario user;
	Viaje viaje;	
	Reserva reserva;	
	Aerolinea aero;
	Ciudad ciudad;
	int usoDeCiudades[sistemaGlobal->ciudades.getTam()][2];	
	for(int i=0;i<sistemaGlobal->ciudades.getTam();i++){		
		usoDeCiudades[i][0]=i;
		usoDeCiudades[i][1]=0;
	}
	Lista<VueloEspecificoTotal> vuelosET=crearListaVuelosEspecificosTotales(sistemaGlobal);
	Lista<VueloPlaneadosTotal> vuelosPT=crearListaVuelosPlaneadosTotales(sistemaGlobal);
	VueloEspecificoTotal vueloET;
	VueloEspecifico vueloE;	
	VueloPlaneadosTotal vueloPT;
	VueloPlaneado vueloP;
	for(int i=0;i<sistemaGlobal->usuarios.getTam();i++){
		user=sistemaGlobal->usuarios.buscarElemento(i+1);		
		for(int j=0;j<user.viajes.getTam();j++){			
			viaje=user.viajes.buscarElemento(j+1);			
			for(int k=0;k<viaje.reservas.getTam();k++){
				reserva=viaje.reservas.buscarElemento(k+1);
				vueloET=vuelosET.buscarElemento(buscarPosVueloEspecifico(reserva.idVuelo,vuelosET));
				vueloPT=vuelosPT.buscarElemento(buscarPosVueloPlaneado(vueloET.idVueloPlaneado,vuelosPT));
				vueloP=vueloPT.vuelosP.buscarElemento(1);
				usoDeCiudades[vueloP.idDestino-1][1]=usoDeCiudades[vueloP.idDestino-1][1]+1;				
			}
		}	
		
	}		
	seleccion(usoDeCiudades,sistemaGlobal->ciudades.getTam());
	cout<<endl<<endl;
	for(int i=sistemaGlobal->ciudades.getTam()-1;i>=0;i--){
		ciudad=sistemaGlobal->ciudades.buscarElemento(usoDeCiudades[i][0]+1);		
		cout<<usoDeCiudades[i][0]+1<<" - "<<ciudad.nombreCiudad<<" ("<<usoDeCiudades[i][1]<<" veces reservado como destino)"<<endl;
	}
	system("pause");
}

//fin rankings

void entrarEnCola(int posUsuario,VueloPlaneado vueloP, int idAerolinea, int cantBoletos){
	bool elegir=false;
	cout<<"Elija la prioridad con la que desea entrar en cola"<<endl<<endl;
	cout<<"1 - Pasajero empleado de aerolinea o familiar"<<endl;
	cout<<"2 - Pago inmediato con descuentos"<<endl;
	cout<<"3 - Pago inmediato tarifa plena"<<endl;
	int elegido,prioridad;
	while(!elegir){
		cout<<"?";
		cin>>elegido;
		if(elegido>0 && elegido<4){
			elegir=true;
		}
	}
	if(elegido==1){
		prioridad=1;
	}else if(elegido==2){
		prioridad=3;
	}else if(elegido==3){
		prioridad=5;
	}
	Usuario user=sistemaGlobal->usuarios.buscarElemento(posUsuario);
	for( int i=0;i<vueloP.vuelosEspecificos.getTam();i++){
		VueloEspecifico vueloE=vueloP.vuelosEspecificos.buscarElemento(i+1);
		Prioridad prio;
		prio.cliente=user.idUnico;
		prio.prioridad=prioridad;
		vueloE.prioridades.anadir(prio);
	}
	
}




bool preguntarSiONO(){
	char c;
	bool x=true;
	while(x){	
		cout<<"Y -si, N -no."<<endl<<endl<<"?";
		cin>>c;
		if(c=='Y'||c=='y'){
			return true;
		}else if(c=='N'||c=='n'){
			return false;
		}else{
			cout<<"Ingrese una opcion valida"<<endl;
		}
	}
}

int separarFecha(string fecha,int tipoRetorno){//tipo retorno 0 retorna el dia, 1 retorna el mes y 2 retorna el año
	int retorno=-1;
	switch(tipoRetorno){
		case 0:{//retornar el dia
			if(fecha[1]=='/'){
				retorno=atoi(""+fecha[0]);
			}else if(fecha[2]=='/'){
				retorno=atoi(fecha[0]+""+fecha[1]);
			}
			break;
		}
		case 1:{//retornar el mes
			if(fecha[1]=='/'){
				if(fecha[3]=='/'){
					retorno=atoi(""+fecha[2]);
				}else if(fecha[4]='/'){
					retorno=atoi(fecha[2]+""+fecha[3]);
				}				
			}else if(fecha[2]=='/'){
				if(fecha[4]=='/'){
					retorno=atoi(""+fecha[3]);
				}else if(fecha[5]='/'){
					retorno=atoi(fecha[3]+""+fecha[4]);
				}
			}
			break;
		}
		case 2:{//retornar el año
			
			break;
		}
		default:
			break;
			
	}
	return retorno;
}

int elegirAvionEnAerolinea(Aerolinea aero){
	int eleccion;
	cout<<"Elija el avion"<<endl;
	for(int i=0;i<aero.aviones.getTam();i++){
		Avion avion=aero.aviones.buscarElemento(i+1);
		cout<<i+1<<avion.matricula<<endl;		
	}
	cout<<endl<<"?";
	cin>>eleccion;
	return eleccion;
	
}
	
int pedirDiaDeLaSemana(){//retornara el dia segun el orden de 1-7 de los dias.
	int opcion=-1;
	while(opcion<=0){	
		cout<<"Elija el dia de la semana"<<endl<<endl;
		cout<<"1 - Lunes"<<endl;
		cout<<"2 - Martes"<<endl;
		cout<<"3 - Miercoles"<<endl;
		cout<<"4 - Jueves"<<endl;
		cout<<"5 - Viernes"<<endl;
		cout<<"6 - Sabado"<<endl;
		cout<<"7 - Domingo"<<endl<<endl<<"?";
		cin>>opcion;
		if(opcion>7||opcion<=0){
			cout<<"ingrese una opcion valida"<<endl<<endl;
		}
	}
	
	
}

Hora obtenerHora(string horaS){//separa una cadena en formato HH:MM
	string aux=horaS,hora,minuto;
	Hora horaR;
	if(aux[2]==':'){					
		hora=aux[0];
		hora=hora+ aux[1];					
		if(aux.length()==4){
			minuto=aux[3];
		}else if(aux.length()==5){
			minuto=aux[3];
			minuto=minuto+aux[4];						
		}
	}else if(aux[1]==':'){
		hora=aux[0];
		if(aux.length()==3){
			minuto=aux[2];
		}else if(aux.length()==4){
			minuto=aux[2];
			minuto=minuto+aux[3];
		}
	}
	
	horaR.hora=atoi(hora.c_str());
	horaR.minuto=atoi(minuto.c_str());
	return horaR;
}

int calcularDuracionVuelo(Hora salida,Hora llegada){//asumiendo que ambas son del mismo dia, la de llegada siempre sera mayor que la de salida
	int minutos,horas;
	if(salida.hora<llegada.hora){	
		if(salida.minuto>=llegada.minuto){
			minutos=salida.minuto-llegada.minuto;
		}else{
			minutos=llegada.minuto-salida.minuto;
		}horas=llegada.hora-salida.hora;
		if(minutos>45){
			horas++;
		}
		if(horas==0){
			horas=1;
		}
	return horas;
	}else{
		return -1;
	}
}

Silla pedirSilla(string mensaje){
	system("cls");
	int anio,mes,dia,idAvion,cuposLibres,tarifaAdulto,tarifaNinio;
	string idSilla, fecha;	
	cout<<"------------Registrando silla-----------"<<endl<<endl;
	cout<<mensaje<<endl;
	cout<<"Ingrese el id de la silla: "<<endl;
	cin>>idSilla;	
	
	Silla silla;
	silla.idSilla=idSilla;
	silla.estado=false;
	
	
	return silla;
}

Avion pedirAvion(){
	system("cls");
	int idAvion=obtenerIdAviones(sistemaGlobal),capacidad;
	string matricula,modelo;
	cout<<"------------Registrando Avion-----------"<<endl<<endl;
	//cout<<mensaje<<endl;
	cout<<"Avion id: "<<idAvion<<endl;
	cout<<"Ingrese el modelo del avion"<<endl;
	cin>>modelo;
	cout<<"Ingrese la matricula del avion"<<endl;
	cin>>matricula;
	cout<<"Ingrese la capacidad del avion"<<endl;
	cin>>capacidad;
	
	Avion avion;
	avion.idAvion=idAvion;
	avion.matricula=matricula;
	avion.modelo=modelo;
	avion.capacidad=capacidad;
	cout<<"¿Desea registrar sillas para este avion?"<<endl;
	if(preguntarSiONO()){
		int cantidad;
		cout<<"¿Cuantas sillas va a registrar?"<<endl<<endl<<"?";
		cin>>cantidad;
		if(cantidad>0){
			string mensaje;
			for (int i=0;i<cantidad;i++){
				ostringstream os;
   				os <<i+1<<" de "<<cantidad;
				mensaje=os.str();
				Silla silla=pedirSilla(mensaje);
				avion.sillas.insertarFinal(silla);				
			}	
		}		
	}	
	return avion;
}

VueloEspecifico pedirVueloEspecificoNuevo(string mensaje,Aerolinea aero){
	system("cls");
	int id=obtenerIdEspecificos(sistemaGlobal),anio,mes,dia,idAvion,cuposLibres,tarifaAdulto,tarifaNinio;
	string fecha;	
	cout<<"------------Registrando Vuelo especifico-----------"<<endl<<endl;
	cout<<mensaje<<endl;
	cout<<"Vuelo especifico id: "<<id<<endl;
	cout<<"Ingrese la fecha del viaje (formato DD/MM/AAAA)"<<endl;
	cin>>fecha;	
	cout<<"Ingrese la tarifa del vuelo para adulto (sin comas ni puntos)"<<endl;
	cin>>tarifaAdulto;
	cout<<"Ingrese la tarifa del vuelo para niño (sin comas ni puntos)"<<endl;
	cin>>tarifaNinio;
	idAvion=elegirAvionEnAerolinea(aero);	
	VueloEspecifico vueloE;
	vueloE.idCodigoVueloEspecifico=id;
	vueloE.dia=separarFecha(fecha,0);
	vueloE.mes=separarFecha(fecha,1);
	vueloE.anio=separarFecha(fecha,2);
	vueloE.idAvion=idAvion;
	vueloE.tarifaAdulto=tarifaAdulto;	
	vueloE.tarifaNinio=tarifaNinio;	
	vueloE.cuposLibres=aero.aviones.buscarElemento(idAvion).sillas.getTam();	
	return vueloE;
}

int elegirCiudad(){
	bool x=true;
	cout<<endl<<endl;
	for(int i=0;i<sistemaGlobal->ciudades.getTam();i++){
		Ciudad ciudad=sistemaGlobal->ciudades.buscarElemento(i+1);
		cout<<ciudad.idCiudad<<" - "<<ciudad.nombreCiudad<<endl;
	}
	int eleccion=0;
	while (x){	
		cout<<"?";
		cin>>eleccion;
		if(eleccion>0 && eleccion<=sistemaGlobal->ciudades.getTam()){
			return eleccion;
		}
	}
}

VueloPlaneado pedirVueloPlaneadoNuevo(int id,string mensaje){
	system("cls");
	int diaDeLaSemana,ciudadOrigen,ciudadDestino;
	string horaSalida,horaLlegada;
	cout<<"------------Registrando Vuelo planeado-----------"<<endl<<endl;
	cout<<mensaje<<endl;
	cout<<"Vuelo planeado id: "<<id<<endl;
	cout<<"¿Es un vuelo multiple?"<<endl;
	bool multiple=preguntarSiONO();
	cout<<"Ingrese la ciudad de origen del viaje"<<endl;
	ciudadOrigen=elegirCiudad();
	cout<<"Ingresde la ciudad de destino del viaje"<<endl;
	ciudadDestino=elegirCiudad();
	int dias[8];
	for(int i=0;i<8;i++){
			dias[i]=0;
		}
	Lista<int> vuelosPlaneadosDelMultiple;
	if(multiple){
		bool acabado=true;
		string textoMultiples;
		int cantidadEscalas;
		cout<<"Ingrese la cantidad de escalas que tiene el vuelo"<<endl<<"?";
		cin>>cantidadEscalas;
		int idVueloE;
		for(int i=0;i<cantidadEscalas;i++){			
			cout<<"Ingrese el id de del vuelo de la escala "<<i+1<<endl<<"?";
			cin>>idVueloE;
			cout<<endl<<endl;
			vuelosPlaneadosDelMultiple.insertarFinal(idVueloE);
		}
		horaSalida="0:0";
		horaLlegada="0:0";		
	}else{
		cout<<"¿cuantos dias sera este vuelo? maximo una vez por dia"<<endl;
		int cantDias;
		cin>>cantDias;		
		for(int i=0;i<cantDias;i++){
			int diaElegido=pedirDiaDeLaSemana();
			dias[diaElegido]=1;;
		}	
		cout<<"Ingrese la hora de salida del viaje (formato HH:MM 24 horas)"<<endl;
		cin>>horaSalida;
		cout<<"Ingrese la hora de llegada del viaje (formato HH:MM 24 horas)"<<endl;
		cin>>horaLlegada;

				
	
		
	}
		VueloPlaneado vueloP;
		vueloP.codigoVuelo=id;
		vueloP.idOrigen=ciudadOrigen;
		vueloP.idDestino=ciudadDestino;
		*(vueloP.diaDeLaSemana)=*dias;		
		Hora horaS=obtenerHora(horaSalida);
		vueloP.salida=horaS;
		Hora horaE=obtenerHora(horaLlegada);
		vueloP.llegada=horaE;
		vueloP.duracion=calcularDuracionVuelo(vueloP.salida,vueloP.llegada);
		vueloP.vueloMultiple=multiple;
		vueloP.vuelosDirectos=vuelosPlaneadosDelMultiple;	
		return vueloP;
	
}

Aerolinea pedirAerolineaNueva(){//pedir los datos de una arelinea nueva que se va a registrar
	system("cls");
	int id=obtenerIdAerolinea(sistemaGlobal),cantidadAviones;
	string nombreAerolinea,numeroCuenta;
	cout<<"----------------Registrando Aerolinea------------------"<<endl<<endl;
	cout<<"Aerolinea id: "<<id<<endl;
	cout<<"Ingrese el nombre de la aerolinea"<<endl;
	cin>>nombreAerolinea;
	cout<<"Ingrese el numero de la cuenta bancaria"<<endl;
	cin>>numeroCuenta;
	Aerolinea aero;//guardar los datos en un objeto aerolinea
	aero.avionesDisponibles=0;
	aero.idAerolinea=id;
	aero.nombre=nombreAerolinea;
	aero.numero_cuenta_bancaria=numeroCuenta;
	aero.itinerarios.idPlan=id;
	cout<<"¿Desea registrar vuelos planeados para esta aerolinea?"<<endl;
	if(preguntarSiONO()){
		int cantidad;
		cout<<"Cuantos vuelos planeados va a ingresar"<<endl<<endl<<"?";
		cin>>cantidad;
		if(cantidad>0){
			string mensaje;
			int id=obtenerIdPlaneados(sistemaGlobal);
			for (int i=0;i<cantidad;i++){
				ostringstream os;
   				os <<i+1<<" de "<<cantidad;
				mensaje=os.str();				
				VueloPlaneado vueloP=pedirVueloPlaneadoNuevo(id+i,mensaje);
				aero.itinerarios.vuelosPlaneados.insertarFinal(vueloP);				
			}	
		}		
	}
	return aero;	//retornar el objeto completo
}

void menuPrincipalAerolinea(){
	int opcion=-1;
	while (opcion!=0){
		system("cls");
		cout<<"-------------Menu Aerolinea--------------------"<<endl<<endl;
	   	cout<<"Si desea REGISTRAR una aerolinea ingrese 1"<<endl;
	   	cout<<"Si desea registrar un vuelo PLANEADO ingrese 2"<<endl;
	   	cout<<"Si desea registrar un vuelo ESPECIFICO ingrese 3"<<endl; 	
	   	cout<<"Si desea regostrar un AVION ingrese 4"<<endl;	
	   	cout<<"Si desea registrar una SILLA ingrese 5"<<endl;	
	   	cout<<"Si desea volver al menu anterior ingrese 0"<<endl<<endl<<"?";
	   	cin>>opcion;
	   	
	   	switch(opcion){
	   		case 0:	   			
	   			system("cls");				
	   			break;
	   		case 1:{//registrar aerolinea
			   	Aerolinea aero=pedirAerolineaNueva();			   	
			   	sistemaGlobal->aerolineas.insertarFinal(aero);
			   	cout<<"Aerolinea creada. Presione una tecla para continuar."<<endl;	  
				   system("PAUSE");
	   			break;
			}
	   		case 2:{//registrar vuelo planeado
	   				int guardar0[2];
					int *pguardar0;
					pguardar0=guardar0;
					ubicarPosicionAerolinea(1,sistemaGlobal,pguardar0);//ubicar la aerolinea
					Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(pguardar0[0]);
					cout<<"Ingrese la cantidad de vuelos planeados que va a registar para la aerolinea elegida"<<endl<<endl<<"?";
					int cantidadVuelos;
					cin>>cantidadVuelos;
					if(cantidadVuelos>0){
						string mensajeAcumulado;
						int id=obtenerIdPlaneados(sistemaGlobal);
						for(int i=0;i<cantidadVuelos;i++){
							ostringstream os;
   							os <<i+1<<" de "<<cantidadVuelos;
							mensajeAcumulado=os.str();						
							aero.itinerarios.vuelosPlaneados.insertarFinal(pedirVueloPlaneadoNuevo(id+i,mensajeAcumulado));
						}						
						sistemaGlobal->aerolineas.modificarElemento(pguardar0[0],aero);
					}
					break;
				}
	   		case 3:{//registrar vuelo especifico
		   			int guardar1[2];
					int *pguardar1;
					pguardar1=guardar1;
					ubicarPosicionAerolinea(2,sistemaGlobal,pguardar1);//ubicar el vuelo planeado
					Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(pguardar1[0]);
					VueloPlaneado vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(pguardar1[1]);
					cout<<"Ingrese la cantidad de vuelos especificos que va a registar para el vuelo planeado elegido"<<endl<<endl<<"?";
					int cantidadVuelos;
					cin>>cantidadVuelos;
					if(cantidadVuelos>0){
						string mensajeAcumulado;
						for(int i=0;i<cantidadVuelos;i++){
							ostringstream os;
   							os <<i+1<<" de "<<cantidadVuelos;
							mensajeAcumulado=os.str();						
							vueloP.vuelosEspecificos.insertarFinal(pedirVueloEspecificoNuevo(mensajeAcumulado,aero));
						}
						aero.itinerarios.vuelosPlaneados.modificarElemento(pguardar1[1],vueloP);
						sistemaGlobal->aerolineas.modificarElemento(pguardar1[0],aero);
					}
					break;
				}
	   		case 4:{//registrar avion
	   				int guardar2[2];
					int *pguardar2;
					pguardar2=guardar2;
					ubicarPosicionAerolinea(1,sistemaGlobal,pguardar2);//ubicar la aerolinea
					Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(pguardar2[0]);					
					aero.aviones.insertarFinal(pedirAvion());
					sistemaGlobal->aerolineas.modificarElemento(pguardar2[0],aero);					
	   				break;
	   			}
	   		case 5:{//registrar silla
	   				int guardar3[2];
					int *pguardar3;
					pguardar3=guardar3;
					ubicarPosicionAerolinea(4,sistemaGlobal,pguardar3);//ubicar el avion
					Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(pguardar3[0]);
					Avion avion=aero.aviones.buscarElemento(guardar3[1]);
					cout<<"id avion"<<avion.idAvion<<endl;
					cout<<"Ingrese la cantidad de sillas que va a registar para el avion elegido"<<endl<<endl<<"?";
					int cantidadSillas;
					cin>>cantidadSillas;
					if(cantidadSillas>0){
						string mensajeAcumulado;
						for(int i=0;i<cantidadSillas;i++){
							ostringstream os;
   							os <<i+1<<" de "<<cantidadSillas;
							mensajeAcumulado=os.str();				
							Silla silla=pedirSilla(mensajeAcumulado);
									
							avion.sillas.insertarFinal(silla);
							system("pause");
						}
						
						aero.aviones.modificarElemento(guardar3[1],avion);
						sistemaGlobal->aerolineas.modificarElemento(guardar3[0],aero);
					}
					break;
			   }
			case 6:{
				break;
				}
	   		
	   		default://opcion no valida, error si es caracter.
	   			cout<<"---Ingrese una opcion valida---"<<endl<<endl<<endl;
	   			system("PAUSE");
	   			break;
	  	}
	  	guardarTodo(sistemaGlobal,1);//guardar backup
	}
}

string preguntarSexo(){
	int eleccion=0;
	while(eleccion<=0 || eleccion>2){
		cout<<endl<<endl<<"Elija el sexo (Ingrese el numero correspondiente):"<<endl<<"1- Masculino"<<endl<<"2- Femenino"<<endl<<endl<<"?";
		cin>>eleccion;
	}
	if(eleccion==1){
		return "M";
	}
	if(eleccion==2){
		return "F";
	}	
}

void crearUsuario(){
	system("cls");
	int edad;
	string cedula,nombre,sexo;
	int id=obtenerIdUsuarios(sistemaGlobal);
	cout<<"El id de usuario unico sera: "<<id<<endl;
	cout<<"Ingrese la cedula del usuario"<<endl<<"?";
	cin>>cedula;
	int pos=buscarPosUsuario(cedula,sistemaGlobal->usuarios);
	if(pos>0){
		cout<<"El usuario ya esta registrado"<<endl;
		system("pause");
	}else{	
		cout<<"Ingrese el nombre del usuario"<<endl<<"?";
		cin>>nombre;
		sexo=preguntarSexo();
		cout<<"Ingrese la edad del usuario"<<endl<<"?";
		cin>>edad;
	
		Usuario user;
		user.edad=edad;
		user.identificacion=cedula;
		user.idUnico=id;
		user.nombre=nombre;
		user.sexo=sexo;
		cout<<endl<<endl;
		imprimirUsuario(user);
		cout<<"¿Desea guardar este usuario?"<<endl;
		bool guardar=preguntarSiONO();
		if(guardar){	
			sistemaGlobal->usuarios.insertarFinal(user);
			cout<<"Guardado.";
			system("pause");		
		}else{
			cout<<"Eliminado";
			system("pause");		
		}
	}
}

void menuPrincipalUsuario(){
	int opcion=-1;
	while (opcion!=0){
		system("cls");
		cout<<"-------------Menu Usuario--------------------"<<endl<<endl;
	   	cout<<"Si desea REGISTRAR un usuario ingrese 1"<<endl;
	   	cout<<"Si desea REGISTRAR un VIAJE ingrese 2"<<endl;
	   	cout<<"Si desea REGISTRAR una RESERVA ingrese 3"<<endl;
	   	cout<<"Si desea volver al menu anterior ingrese 0"<<endl<<endl<<"?";
	   	cin>>opcion;
	   	
	   	switch(opcion){
	   		case 0:	   			
	   			system("cls");				
	   			break;
	   		case 1://registrar usuario
			   	crearUsuario();
	   			break;
	   		case 2://consultar vuelo 
	   			
				break;
	   		case 3://reservar vuelo 
	   			
	   			break;
	   		case 4://cancelar vuelo
	   		
	   			break;	   		
	   		default://opcion no valida, error si es caracter.
	   			cout<<"---Ingrese una opcion valida---"<<endl<<endl<<endl;
	   			system("PAUSE");
	   			break;
	  	}
	  	guardarTodo(sistemaGlobal,1);//guardar backup
	}
}


Lista<VueloPlaneadosTotal> filtrarVuelosOrigenDestino(Lista<VueloPlaneadosTotal> vuelos,int idOrigen,int idDestino){
	Lista<VueloPlaneadosTotal> retorno;
	for (int i=0;i<vuelos.getTam();i++){
		VueloPlaneadosTotal vueloPT=vuelos.buscarElemento(i+1);
		VueloPlaneado vuelo=vueloPT.vuelosP.buscarElemento(1);
		if(idOrigen==vuelo.idOrigen && idDestino==vuelo.idDestino){
			retorno.insertarFinal(vueloPT);
		}
	}
	return retorno;
}

Lista<VueloEspecifico> filtrarVuelosConBoletos(Lista<VueloEspecifico> vuelos,int cantidadBoletos){
	Lista<VueloEspecifico> retorno;
	for(int i=0;i<vuelos.getTam();i++){
		VueloEspecifico vuelo=vuelos.buscarElemento(i+1);
		if(vuelo.cuposLibres>=cantidadBoletos){
			int ctdadDias=calcularDias(vuelo.dia,vuelo.mes,vuelo.anio);
			if(ctdadDias>0){						
				retorno.insertarFinal(vuelo);
			}
		}
	}
	return retorno;
}

Lista<VueloEspecifico> organizarVuelosPor(Lista<VueloEspecifico> vuelos,int caso){//caso 1 organizar por precio
	int todos[vuelos.getTam()][2];									//caso 2 organizar por fecha
	for(int i=0;i<vuelos.getTam();i++){							//caso 3 organizar por 
		int representante;
		VueloEspecifico vuelo=vuelos.buscarElemento(i+1);
		if(caso==1){
			representante=vuelo.tarifaAdulto;
		}else if(caso==2){			
			representante=calcularDias(vuelo.dia,vuelo.mes,vuelo.anio);
			
		}else if(caso==3){
			//representante=vuelo.
		}
		
		cout<<endl<<endl;
		todos[i][0]=i;
		todos[i][1]=representante;		
	}
	seleccion(todos,vuelos.getTam());
	Lista<VueloEspecifico> vuelosOrganizados;
	for(int i=0;i<vuelos.getTam();i++){
		VueloEspecifico vuelo=vuelos.buscarElemento(todos[i][0]+1);
		vuelosOrganizados.insertarFinal(vuelo);		
	}
	return vuelosOrganizados;
	
}



void reservarVueloMultiple(int posUsuario,int idViaje,int cantidadVuelos,int ticketsAdulto,int ticketsNino,int *arreglo,int idAerolinea){
	Usuario user=sistemaGlobal->usuarios.buscarElemento(posUsuario);//obtener usuario
	VueloEspecificoTotal vueloET;
	Aerolinea aero;
	int posVueloP,posVueloE,posAvion,diasDif,descuento,idVueloE,posSilla,idReserva;
	VueloPlaneado vueloP;
	VueloEspecifico vueloE;
	Avion avion;
	Viaje viaje;
	Reserva reserva;
	Pasajero pasajero;
	viaje.idViaje=idViaje;//crear el nuevo viaje
	viaje.tipoDeViaje="multiple";
	viaje.nombre="";
	//definir pasajeros y reserva
	Pasajero pasajerosAdultos[ticketsAdulto];
	Pasajero pasajerosNino[ticketsAdulto];
	idReserva=obtenerIdReservas(sistemaGlobal);
	int contadorReservas=0;
	if(ticketsAdulto>0){	//crear la reserva y el pasajero para cada ticket de adulto
		for(int i=0;i<ticketsAdulto;i++){			
			cout<<endl<<endl<<"Ingresde los datos del pasajero adulto "<<i+1<<endl<<endl;			
			cout<<"Ingrese el nombre del pasajero"<<endl<<"?";
			cin>>pasajero.nombre;
			cout<<"Ingrese el apellido del pasajero"<<endl<<"?";
			cin>>pasajero.apellido;
			cout<<"Ingrese la identificacion del pasajero"<<endl<<"?";
			cin>>pasajero.identificacion;
			cout<<"Ingrese la fecha de nacimiento del pasajero"<<endl<<"?";
			cin>>pasajero.fechaNacimiento;
			pasajero.tipo="adulto";			
			pasajerosAdultos[i]=pasajero;
		}
	}
		cout<<endl<<endl;
	if(ticketsNino>0){	//crear la reserva y el pasajero para cada ticket de niño
		for(int i=0;i<ticketsNino;i++){			

			cout<<endl<<endl<<"Ingresde los datos del pasajero nino "<<i+1<<endl<<endl;			
			cout<<"Ingrese el nombre del pasajero"<<endl<<"?";
			cin>>pasajero.nombre;
			cout<<"Ingrese el apellido del pasajero"<<endl<<"?";
			cin>>pasajero.apellido;
			cout<<"Ingrese la identificacion del pasajero"<<endl<<"?";
			cin>>pasajero.identificacion;
			cout<<"Ingrese la fecha de nacimiento del pasajero"<<endl<<"?";
			cin>>pasajero.fechaNacimiento;			
			pasajero.tipo="nino";
			
			pasajerosNino[i]=pasajero;
		}
	}
	//reservar
	for(int i=0;i<cantidadVuelos;i++){
		idVueloE=arreglo[i];
		if(idVueloE>0){
				
			vueloET=encontrarVueloEspecifico(idVueloE,sistemaGlobal);//obtener las direcciones para encontrar el vuelo especifico
			aero=sistemaGlobal->aerolineas.buscarElemento(vueloET.idAerolinea);//buscar la aerolinea donde esta el vuelo
			posVueloP=buscarPosVueloPlaneado(vueloET.idVueloPlaneado,aero.itinerarios.vuelosPlaneados);//obtener la pos del vuelo en esa aerolinea
			vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(posVueloP);//obtener el vuelo planeado
			posVueloE=buscarPosVueloEspecifico(idVueloE,vueloP.vuelosEspecificos);//obtener la pos del vuelo especifico en el vuelo planeado
			vueloE=vueloP.vuelosEspecificos.buscarElemento(posVueloE);//obtener el vuelo especifico
			posAvion=buscarPosAvion(vueloE.idAvion,aero.aviones);//obtener la posicion del avion segun el id que diga el vuelo especifico
			avion=aero.aviones.buscarElemento(posAvion);	//	obtener el avion
			cout<<avion.idAvion<<endl;
			system("pause");
			diasDif=calcularDias(vueloE.dia,vueloE.mes,vueloE.anio);//calcular tiempo para ver si gana descuento
			descuento=0;
			
			if(diasDif>30 && diasDif<=60){//definir descuento 0%,10% o 20%
				descuento=10;
			}else if(diasDif>60){
				descuento=20;
			}
			
			descuento=descuento+10;//por ser multiple
			
			for(int j=0;j<ticketsAdulto;j++){//reservar adultos
				reserva.idReserva=idReserva+contadorReservas;
				contadorReservas++;
				reserva.idVuelo=idVueloE;
				reserva.precioPagado=calcularPrecioConDescuento(vueloE.tarifaAdulto,descuento);
				reserva.fechaReserva=obtenerFechaActual();
				reserva.tipo="adulto";
				pasajero=pasajerosAdultos[j];
				pasajero.numeroReserva=reserva.idReserva;
				Silla silla;
				bool sillaDisponible=false;
				int posSilla=1;			
				
				while (!sillaDisponible){//buscar cual es la siguiente silla disponible en el avion				
					silla=avion.sillas.buscarElemento(posSilla);				
					
					if(silla.estado){
						posSilla++;//pos silla queda guardando la posicion de la silla
					}else{
						sillaDisponible=true;
					}				
				}
				
				
				
				silla.estado=true;//vender la silla
				silla.pasajero=pasajero;//asignarle el pasajero
				avion.sillas.modificarElemento(posSilla,silla);//guardar la silla con las modificaciones
				aero.aviones.modificarElemento(posAvion,avion);
				vueloE.cuposLibres=vueloE.cuposLibres-1;
				vueloP.vuelosEspecificos.modificarElemento(posVueloE,vueloE);
				aero.itinerarios.vuelosPlaneados.modificarElemento(posVueloP,vueloP);
				sistemaGlobal->aerolineas.modificarElemento(aero.idAerolinea,aero);
				viaje.reservas.insertarFinal(reserva);							
			}	
			
			for(int j=0;j<ticketsNino;j++){//reservar niños
				reserva.idReserva=idReserva+contadorReservas;
				contadorReservas++;
				reserva.idVuelo=idVueloE;
				reserva.precioPagado=calcularPrecioConDescuento(vueloE.tarifaNinio,descuento);
				reserva.fechaReserva=obtenerFechaActual();
				reserva.tipo="nino";
				pasajero=pasajerosNino[j];
				pasajero.numeroReserva=reserva.idReserva;
				Silla silla;
				bool sillaDisponible=false;
				int posSilla=1;			
				while (!sillaDisponible){//buscar cual es la siguiente silla disponible en el avion				
					silla=avion.sillas.buscarElemento(posSilla);				
					if(silla.estado){
						posSilla++;//pos silla queda guardando la posicion de la silla
					}else{
						sillaDisponible=true;
					}				
				}
				silla.estado=true;//vender la silla
				silla.pasajero=pasajero;//asignarle el pasajero
				avion.sillas.modificarElemento(posSilla,silla);//guardar la silla con las modificaciones
				aero.aviones.modificarElemento(posAvion,avion);
				vueloE.cuposLibres=vueloE.cuposLibres-1;
				vueloP.vuelosEspecificos.modificarElemento(posVueloE,vueloE);
				aero.itinerarios.vuelosPlaneados.modificarElemento(posVueloP,vueloP);
				sistemaGlobal->aerolineas.modificarElemento(aero.idAerolinea,aero);
				viaje.reservas.insertarFinal(reserva);							
			}	
		}
	}
	//guardar el viaje
	user.viajes.insertarFinal(viaje);
	sistemaGlobal->usuarios.modificarElemento(user.idUnico,user);
	system("cls");
	cout<<"Se ha guardado con exito."<<endl<<endl;
	system("pause");
}

void elegirVuelosEspecificosMultiple(int posUsuario,VueloPlaneado vueloPM, int ticketsAdulto,int ticketsNino,int idAerolinea){
	int cantidadEscalas=vueloPM.vuelosDirectos.getTam();
	cout<<"A continuacion elegira los vuelos que desee tomar"<<endl<<endl;
	system("pause");
	system("cls");
	int vuelosEscogidos[cantidadEscalas] ;
	VueloPlaneado vueloP;
	Aerolinea aero;
	Ciudad ciudad;
	string origen,destino;
	for(int i=0;i<cantidadEscalas;i++){
		aero=sistemaGlobal->aerolineas.buscarElemento(idAerolinea);
		vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(buscarPosVueloPlaneado(vueloPM.vuelosDirectos.buscarElemento(i+1),aero.itinerarios.vuelosPlaneados));
		Lista<VueloEspecifico> vuelosConBoletos=filtrarVuelosConBoletos(vueloP.vuelosEspecificos,ticketsAdulto+ticketsNino);
		ciudad=sistemaGlobal->ciudades.buscarElemento(vueloP.idOrigen);
		origen=ciudad.nombreCiudad;
		ciudad=sistemaGlobal->ciudades.buscarElemento(vueloP.idDestino);
		destino=ciudad.nombreCiudad;
		if(vuelosConBoletos.getTam()>0){
			system("cls");
			cout<<"Vuelo directo "<<i+1<<" de "<<cantidadEscalas<<" ("<<origen<<" - "<<destino<<")."<<endl<<endl;
			for(int j=0;j<vuelosConBoletos.getTam();j++){
				cout<<"mostrando el "<<j+1<<" de "<<vuelosConBoletos.getTam()<<endl;
				imprimirVueloEspecifico(vuelosConBoletos.buscarElemento(j+1));
			}
			int organizar=-1;
			while(organizar!=0){
				cout<<endl<<"Si dese reorganizar los vuelos ingrese el numero del parametro para reorganizar:"<<endl<<endl;
				cout<<"1- por precio."<<endl;
				cout<<"2- por fecha"<<endl;
				cout<<"0- no reorganizar (continuar)"<<endl<<endl<<"?";
				cin>>organizar;
				Lista<VueloEspecifico> reorganizar=vuelosConBoletos;
				switch(organizar){
					
					case 0:{						
						break;
					}
					case 1:{
						reorganizar=organizarVuelosPor(vuelosConBoletos,1);
						break;
					}
					case 2:{
						reorganizar=organizarVuelosPor(vuelosConBoletos,2);
						break;
					}default:{
						cout<<"Ingrese una opcion valida"<<endl<<endl;
					}
				}
				if(organizar==1 or organizar==2){				
					system("cls");				
					for(int i=0;i<reorganizar.getTam();i++){
						cout<<"mostrando el "<<i+1<<" de "<<reorganizar.getTam()<<endl;
						imprimirVueloEspecifico(reorganizar.buscarElemento(i+1));
					}
				}
			}
			
			cout<<"Ingrese el codigo del vuelo que desee: "<<endl;
			int codigoVueloE;
			string escogido;						
			bool existe=false;
			while (!existe){
				cout<<"?";
				cin>>escogido;				
				codigoVueloE=atoi(escogido.c_str());
				int pos=buscarPosVueloEspecifico(codigoVueloE,vuelosConBoletos);
				if(pos>0){				
					vuelosEscogidos[i]=codigoVueloE;
					existe=true;
				}
			}
									
		}else{
			cout<<"No hay vuelos con suficientes boletos para su reserva."<<endl<<endl;
			vuelosEscogidos[i]=-1;
			system("pause");
		}
	}
	cout<<"¿Desea reservar los vuelos que escogio?"<<endl;
	bool reservar=preguntarSiONO();
	if(reservar){
		int *pArreglo=vuelosEscogidos;
		int idViaje=obtenerIdViajes(sistemaGlobal);
		reservarVueloMultiple(posUsuario,idViaje,cantidadEscalas,ticketsAdulto,ticketsNino,pArreglo,idAerolinea);
	}	
	system("pause");
		
	
}


void reservarVueloSimple(int posUsuario,int idVueloE,int ticketsAdulto,int ticketsNino){
	Usuario user=sistemaGlobal->usuarios.buscarElemento(posUsuario);//obtener usuario
	VueloEspecificoTotal vueloET=encontrarVueloEspecifico(idVueloE,sistemaGlobal);//obtener las direcciones para encontrar el vuelo especifico
	Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(vueloET.idAerolinea);//buscar la aerolinea donde esta el vuelo
	int posVueloP=buscarPosVueloPlaneado(vueloET.idVueloPlaneado,aero.itinerarios.vuelosPlaneados);//obtener la pos del vuelo en esa aerolinea
	VueloPlaneado vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(posVueloP);//obtener el vuelo planeado
	int posVueloE=buscarPosVueloEspecifico(idVueloE,vueloP.vuelosEspecificos);//obtener la pos del vuelo especifico en el vuelo planeado
	VueloEspecifico vueloE=vueloP.vuelosEspecificos.buscarElemento(posVueloE);//obtener el vuelo especifico
	int posAvion=buscarPosAvion(vueloE.idAvion,aero.aviones);//obtener la posicion del avion segun el id que diga el vuelo especifico
	Avion avion=aero.aviones.buscarElemento(posAvion);	//	obtener el avion
	Viaje viaje;
	viaje.idViaje=obtenerIdViajes(sistemaGlobal);//crear el nuevo viaje
	viaje.tipoDeViaje="normal";
	viaje.nombre="";
	Reserva reserva;
	Pasajero pasajero;
	int diasDif=calcularDias(vueloE.dia,vueloE.mes,vueloE.anio);//calcular tiempo para ver si gana descuento
	int descuento=0;
	if(diasDif>30 && diasDif<=60){//definir descuento 0%,10% o 20%
		descuento=10;
	}else if(diasDif>60){
		descuento=20;
	}
	if(ticketsAdulto>0){	//crear la reserva y el pasajero para cada ticket de adulto
		for(int i=0;i<ticketsAdulto;i++){			
			reserva.idReserva=obtenerIdReservas(sistemaGlobal);
			reserva.idVuelo=idVueloE;
			reserva.precioPagado=calcularPrecioConDescuento(vueloE.tarifaAdulto,descuento);
			reserva.fechaReserva=obtenerFechaActual();
			reserva.tipo="adulto";
			cout<<endl<<endl<<"Ingresde los datos del pasajero adulto "<<i+1<<endl<<endl;			
			cout<<"Ingrese el nombre del pasajero"<<endl<<"?";
			cin>>pasajero.nombre;
			cout<<"Ingrese el apellido del pasajero"<<endl<<"?";
			cin>>pasajero.apellido;
			cout<<"Ingrese la identificacion del pasajero"<<endl<<"?";
			cin>>pasajero.identificacion;
			cout<<"Ingrese la fecha de nacimiento del pasajero"<<endl<<"?";
			cin>>pasajero.fechaNacimiento;
			pasajero.tipo=reserva.tipo;
			pasajero.numeroReserva=reserva.idReserva;
			Silla silla;
			bool sillaDisponible=false;
			int posSilla=1;			
			while (!sillaDisponible){//buscar cual es la siguiente silla disponible en el avion				
				silla=avion.sillas.buscarElemento(posSilla);				
				if(silla.estado){
					posSilla++;//pos silla queda guardando la posicion de la silla
				}else{
					sillaDisponible=true;
				}				
			}					
			silla.estado=true;//vender la silla
			silla.pasajero=pasajero;//asignarle el pasajero
			avion.sillas.modificarElemento(posSilla,silla);//guardar la silla con las modificaciones
			aero.aviones.modificarElemento(posAvion,avion);
			vueloE.cuposLibres=vueloE.cuposLibres-1;
			vueloP.vuelosEspecificos.modificarElemento(posVueloE,vueloE);
			aero.itinerarios.vuelosPlaneados.modificarElemento(posVueloP,vueloP);
			sistemaGlobal->aerolineas.modificarElemento(aero.idAerolinea,aero);
			viaje.reservas.insertarFinal(reserva);
		}
	}
	cout<<endl<<endl;
	if(ticketsNino>0){	//crear la reserva y el pasajero para cada ticket de niño
		for(int i=0;i<ticketsNino;i++){			
			reserva.idReserva=obtenerIdReservas(sistemaGlobal);
			reserva.idVuelo=idVueloE;
			reserva.precioPagado=calcularPrecioConDescuento(vueloE.tarifaNinio,descuento);
			reserva.fechaReserva=obtenerFechaActual();
			reserva.tipo="nino";
			cout<<endl<<endl<<"Ingresde los datos del pasajero nino "<<i+1<<endl<<endl;			
			cout<<"Ingrese el nombre del pasajero"<<endl<<"?";
			cin>>pasajero.nombre;
			cout<<"Ingrese el apellido del pasajero"<<endl<<"?";
			cin>>pasajero.apellido;
			cout<<"Ingrese la identificacion del pasajero"<<endl<<"?";
			cin>>pasajero.identificacion;
			cout<<"Ingrese la fecha de nacimiento del pasajero"<<endl<<"?";
			cin>>pasajero.fechaNacimiento;
			pasajero.tipo=reserva.tipo;
			pasajero.numeroReserva=reserva.idReserva;
			Silla silla;
			bool sillaDisponible=false;
			int posSilla=1;
			while (!sillaDisponible){//buscar cual es la siguiente silla disponible en el avion
				silla=avion.sillas.buscarElemento(posSilla);
				if(silla.estado){
					posSilla++;//pos silla queda guardando la posicion de la silla
				}else{
					sillaDisponible=true;
				}
			}			
			silla.estado=true;//vender la silla
			silla.pasajero=pasajero;//asignarle el pasajero
			avion.sillas.modificarElemento(posSilla,silla);//guardar la silla con las modificaciones
			aero.aviones.modificarElemento(posAvion,avion);
			vueloE.cuposLibres=vueloE.cuposLibres-1;
			vueloP.vuelosEspecificos.modificarElemento(posVueloE,vueloE);
			aero.itinerarios.vuelosPlaneados.modificarElemento(posVueloP,vueloP);
			sistemaGlobal->aerolineas.modificarElemento(aero.idAerolinea,aero);
			viaje.reservas.insertarFinal(reserva);
		}
	}
	user.viajes.insertarFinal(viaje);
	sistemaGlobal->usuarios.modificarElemento(user.idUnico,user);
	system("cls");
	cout<<"Se ha guardado con exito."<<endl<<endl;
	system("pause");
}

int elegirVuelosEspecificosSimple(int caso,int posUsuario,VueloPlaneado vueloP, int ticketsAdulto,int ticketsNino,int idAerolinea){//caso 1 n reservar, caso 0 si reservar.
	
	Lista<VueloEspecifico> vuelosConBoletos=filtrarVuelosConBoletos(vueloP.vuelosEspecificos,ticketsAdulto+ticketsNino);
		if(vuelosConBoletos.getTam()>0){
			cout<<"El vuelo es directo y hay disponibles las siguientes fechas:"<<endl<<endl;
			for(int i=0;i<vuelosConBoletos.getTam();i++){
				cout<<"mostrando el "<<i+1<<" de "<<vuelosConBoletos.getTam()<<endl;
				imprimirVueloEspecifico(vuelosConBoletos.buscarElemento(i+1));
			}
			int organizar=-1;
			while(organizar!=0){
				cout<<endl<<"Si dese reorganizar los vuelos ingrese el numero del parametro para reorganizar:"<<endl<<endl;
				cout<<"1- por precio."<<endl;
				cout<<"2- por fecha"<<endl;
				cout<<"0- no reorganizar (continuar)"<<endl<<endl<<"?";
				cin>>organizar;
				Lista<VueloEspecifico> reorganizar=vuelosConBoletos;
				switch(organizar){
					
					case 0:{						
						break;
					}
					case 1:{
						reorganizar=organizarVuelosPor(vuelosConBoletos,1);
						break;
					}
					case 2:{
						reorganizar=organizarVuelosPor(vuelosConBoletos,2);
						break;
					}default:{
						cout<<"Ingrese una opcion valida"<<endl<<endl;
					}
				}
				if(organizar==1 or organizar==2){				
					system("cls");				
					for(int i=0;i<reorganizar.getTam();i++){
						cout<<"mostrando el "<<i+1<<" de "<<reorganizar.getTam()<<endl;
						imprimirVueloEspecifico(reorganizar.buscarElemento(i+1));
					}
				}
			}
			
			cout<<"Ingrese el codigo del vuelo que desee reservar: (n=cancelar)"<<endl<<"?";
			int codigoVueloE;
			string escogido;
			cin>>escogido;
			if(escogido!="n"){
				codigoVueloE=atoi(escogido.c_str());
				if(caso==0){				
					reservarVueloSimple(posUsuario,codigoVueloE,ticketsAdulto,ticketsNino);
				}
				return codigoVueloE;
			}						
		}else{
			cout<<"No hay vuelos con suficientes boletos para su reserva."<<endl<<endl;
			cout<<"¿Desea entrar en cola en el primer vuelo disponible con todos los tickets que necesita?"<<endl;
			bool entrar=preguntarSiONO();
			if(entrar){
				entrarEnCola(posUsuario,vueloP,idAerolinea,ticketsAdulto+ticketsNino);
			}
			
			system("pause");
		}
		return -1;
}

void consultarVuelo(){
	Aerolinea aero;
	system("cls");	
	string cedula;
	int pos=-1;
	while(pos==-1){
		cout<<"Ingrese su numero de identificacion. (n=cancelar)"<<endl<<endl<<"?";//identificar el usuario
		cin>>cedula;
		if(cedula=="n"){
			break;
		}else{
			pos=buscarPosUsuario(cedula,sistemaGlobal->usuarios);
			if(pos==-1){
				cout<<"El usuario no existe, ¿desea crearlo?"<<endl<<endl;
				bool crear=preguntarSiONO();
				if(crear){
					crearUsuario();
				}
			}
		}
	}
	if(cedula!="n"){
		Usuario user=sistemaGlobal->usuarios.buscarElemento(pos);
		cout<<endl<<endl<<"Bienvenid";
		if(user.sexo=="m"||user.sexo=="M"){
			cout<<"o ";
		}else{
			cout<<"a ";
		}cout<<user.nombre<<endl<<endl;
		cout<<"Elija la ciudad de origen:"<<endl;			//elegir origen y destino
		int origen=elegirCiudad();
		cout<<endl<<"Elija la ciudad de destino:"<<endl;
		int destino=elegirCiudad();
		//buscar vuelos en todas las aerolineas con ese origen y destino
		Lista<VueloPlaneadosTotal> vuelosDisponibles=filtrarVuelosOrigenDestino(crearListaVuelosPlaneadosTotales(sistemaGlobal),origen,destino);
		if(vuelosDisponibles.getTam()==0){//si no hay vuelos avisar
			cout<<"No hay ningun vuelo registrado con ese origen y destino"<<endl<<endl;
			system("pause");
		}else{//si hay vuelos mostrarlos
			cout<<"Se encontraron "<<vuelosDisponibles.getTam()<<" vuelos coincidentes"<<endl<<endl;
			for(int i=0;i<vuelosDisponibles.getTam();i++){
				VueloPlaneadosTotal vueloD=vuelosDisponibles.buscarElemento(i+1);
				aero=sistemaGlobal->aerolineas.buscarElemento(vueloD.idAerolinea);
				cout<<"Aerolinea: "<<vueloD.idAerolinea<<"("<<aero.nombre<<")"<<"   - Plan de trayecto: "<<vueloD.idPlanTrayecto<<endl;
				imprimirVueloPlaneado(vueloD.vuelosP.buscarElemento(1));
			}
			int idEscogido;
			string escogido;
			cout<<endl<<"Ingrese el codigo del vuelo del que desea ver fechas (n=cancelar)"<<endl; //escoger si quiere ver fechas de un vuelo especifico			
			bool existe=false;
			while (!existe){
				cout<<"?";
				cin>>escogido;
				if(escogido!="n"){
					int pos=buscarPosVueloPlaneado(atoi(escogido.c_str()),vuelosDisponibles);
					if(pos>0){
						existe=true;
					}
				}else{
					existe=true;
				}
			}			
			if(escogido!="n"){
				idEscogido=atoi(escogido.c_str());
				int ticketsAdulto,ticketsNino;			
				cout<<"Ingrese la cantidad de ticketes para ADULTO que va a reservar"<<endl<<"?";//cantidad de boletos que necesita
				cin>>ticketsAdulto;
				cout<<"Ingrese la cantidad de ticketes para NINO que va a reservar"<<endl<<"?";
				cin>>ticketsNino;
				//buscar vuelos especificos que cumplan las condiciones
				int posicion=buscarPosVueloPlaneado(idEscogido,vuelosDisponibles);//obtener el vuelo que escogio en la lista de disponibles
				VueloPlaneadosTotal vueloPT=vuelosDisponibles.buscarElemento(posicion);
				VueloPlaneado aux=vueloPT.vuelosP.buscarElemento(1);
				Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(vueloPT.idAerolinea);//buscar ese vuelo en el sistema global
				VueloPlaneado vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(buscarPosVueloPlaneado(aux.codigoVuelo,aero.itinerarios.vuelosPlaneados));
				if(vueloP.vueloMultiple){//si es un vuelo multiple, imprimira varias veces cada vuelo disponible
					system("cls");
					cout<<"El vuelo consisten en "<<vueloP.vuelosDirectos.getTam()<<" escalas"<<endl;								
					elegirVuelosEspecificosMultiple(pos,vueloP,ticketsAdulto,ticketsNino,aero.idAerolinea);
						//encontrar vuelos
					
				}else{//si no es multiple, es directo
					if(vueloP.vuelosEspecificos.getTam()>0){//buscar los vuelos disponibles					
						elegirVuelosEspecificosSimple(0,pos,vueloP,ticketsAdulto,ticketsNino,aero.idAerolinea);//metodo que muestra los especificos con boletos suficientes y llama a reservar					
						
					}else{
						cout<<"No hay fechas disponibles para ese vuelo."<<endl<<endl;
						system("pause");
					}
				}
				
				
			}		
		}
	}else{
	}	
	
	
}

void cancelarReservacion(){
	int guardar[3];
	int *pguardar=guardar;
	ubicarPosicionUsuario(3,sistemaGlobal,pguardar);
	
}

void menuPrincipalSimulacion(){
	int opcion=-1;
	while (opcion!=0){
		system("cls");
		cout<<"-------------SIMULACION--------------------"<<endl<<endl;	   	
	   	cout<<"Si desea CONSULTAR un vuelo ingrese 1"<<endl;	   	
	   	cout<<"Si desea CANCELAR un vuelo ingrese 2"<<endl;	   	
	   	cout<<"Si desea ingresar como AEROLINEA ingrese 3"<<endl;
	   	cout<<"Si desea volver al menu anterior ingrese 0"<<endl<<endl<<"?";
	   	cin>>opcion;
	   	
	   	switch(opcion){
	   		case 0:	   			
	   			system("cls");				
	   			break;
	   		case 1://consultar vuelo 
			    consultarVuelo();		
	   			break;	   		
	   		case 2://cancelar vuelo
	   			cancelarReservacion();
	   			break;
	   		case 3://aerolinea	   			   	
	   			menuPrincipalAerolinea();
	   			break;	   		
	   		default://opcion no valida, error si es caracter.
	   			cout<<"---Ingrese una opcion valida---"<<endl<<endl<<endl;
	   			system("PAUSE");
	   			break;
	  	}
	  	guardarTodo(sistemaGlobal,1);//guardar backup
	}
}

void menuConsultasEspecificas(){
	int opcion=-1;
	while (opcion!=0){
		system("cls");
		cout<<"-------------Menu Consultas--------------------"<<endl<<endl;
	   	cout<<"Si desea ver la lista de aerolineas ingrese 1"<<endl;
	   	cout<<"Si desea ver la lista de destinos por aerolineas ingrese 2"<<endl;
	   	cout<<"Si desea ver la lista de usuarios registrados ingrese 3"<<endl;
	   	cout<<"Si desea ver la lista de pasajeros de un vuelo ingrese 4"<<endl;	   	
	   	cout<<"Si desea ver las listas de pasajeros para la reserva de un usuario ingrese 5"<<endl;	   	
	   	cout<<"Si desea ver la lista de vuelos en viajes multiples ingrese 6"<<endl;
	   	cout<<"Si desea ver la lista de sillas vacias en un vuelo ingrese 7"<<endl;
	   	cout<<"Si desea ver las listas de vuelos (planeados y especificos) ingrese 8"<<endl;
	   	cout<<"Si desea ver las colas de espera ingrese 9"<<endl;	   	
	   	cout<<"Si desea ver arbol para implementar una cola de prioridad ingrese 10"<<endl;	   	
	   	cout<<"Si desea ver la lista de vuelos progr. desde un origen a un destino ingrese 11"<<endl;
	   	cout<<"Si desea volver al menu anterior ingrese 0"<<endl<<endl<<"?";
	   	cin>>opcion;
	   	
	   	switch(opcion){
	   		case 0:	   			
	   			system("cls");				
	   			break;
	   		case 1://lista de aerolineas
	   			cout<<endl<<endl;
			    for(int i=0;i<sistemaGlobal->aerolineas.getTam();i++){
			   		Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(i+1);
			   		cout<<aero.idAerolinea<<" - "<<aero.nombre<<endl;			   		
   			    }	
   			    cout<<endl;
   			    system("pause");
	   			break;
	   		case 2://lista de destinos por aerolineas
	   			cout<<endl<<endl;
			    for(int i=0;i<sistemaGlobal->aerolineas.getTam();i++){
			   		Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(i+1);
			   		
			   		Lista<string> destinos=destinosPorAerolinea(aero);
			   		cout<<aero.nombre<<" ("<<destinos.getTam()<<" destinos):"<<endl; 
			   		for(int j=0;j<destinos.getTam();j++){
			   			cout<<j+1<<" - "<<destinos.buscarElemento(j+1)<<endl;
					}		
					cout<<endl<<endl;	   		
   			    }	
   			    cout<<endl;
   			    system("pause");
				break;
	   		case 3://lista de usuarios registrados
	   			cout<<endl<<endl;
			    for(int i=0;i<sistemaGlobal->usuarios.getTam();i++){
			   		Usuario usuario=sistemaGlobal->usuarios.buscarElemento(i+1);
			   		cout<<i+1<<" - "<<usuario.identificacion<<"  "<<usuario.nombre<<endl;			   		
   			    }	
   			    cout<<endl;
   			    system("pause");
	   			break;
	   		case 4:{//lista de pasajeros de un vuelo
	   			int guardar1[3];
	   			int *pguardar1=guardar1;
	   			ubicarPosicionAerolinea(3,sistemaGlobal,pguardar1);
	   			Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(guardar1[0]);
	   			VueloPlaneado vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(guardar1[1]);
	   			VueloEspecifico vueloE=vueloP.vuelosEspecificos.buscarElemento(guardar1[2]);
	   			pasajerosEnVueloEspecifico(vueloE);
	   			break;
			}
			
			case 5:{//listas de pasajeros para la reserva de un usuario
	   				int guardar[2];
	   				int *pguardar=guardar;
	   				ubicarPosicionUsuario(2,sistemaGlobal,pguardar);
	   				Usuario user=sistemaGlobal->usuarios.buscarElemento(guardar[0]);
	   				Viaje viaje=user.viajes.buscarElemento(guardar[1]);
	   				Lista<Pasajero> pasajeros=pasajerosEnVueloDeUsuario(viaje);
	   				cout<<endl<<endl;
	   				for(int i=0;i<pasajeros.getTam();i++){
	   					Pasajero pasajero=pasajeros.buscarElemento(i+1);
	   					cout<<pasajero.identificacion<<" - "<<pasajero.nombre<<" "<<pasajero.apellido<<endl;
					   }
					cout<<endl<<endl;		   			
		   			system("pause");
	   				break;
				}
	   		case 6:{//lista de vuelos en viajes multiples
	   			system("cls");
	   			vuelosEnViajesMultiples();		   			
	   			break;
			}
	   		case 7:{//lista de sillas vacias en un vuelo
	   			int guardar2[3];
	   			int *pguardar2=guardar2;
	   			ubicarPosicionAerolinea(3,sistemaGlobal,pguardar2);
	   			Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(guardar2[0]);
	   			VueloPlaneado vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(guardar2[1]);
	   			VueloEspecifico vueloE=vueloP.vuelosEspecificos.buscarElemento(guardar2[2]);
	   			SillasVaciasEnVueloEspecifico(vueloE);
	   			break;
			}
	   		case 8:{//listas de vuelos (planeados y especificos)
	   			system("cls");
	   			Lista<VueloPlaneadosTotal> vuelosP=crearListaVuelosPlaneadosTotales(sistemaGlobal);
	   			Lista<VueloEspecificoTotal> vuelosE=crearListaVuelosEspecificosTotales(sistemaGlobal);
	   			cout<<"Mostrando: "<<vuelosP.getTam()<<" vuelos planeados."<<endl<<endl;
	   			for(int i=0;i<vuelosP.getTam();i++){
	   				VueloPlaneadosTotal vueloPT=vuelosP.buscarElemento(i+1);
	   				cout<<"Id aerolinea: "<<vueloPT.idAerolinea<<endl;
	   				imprimirVueloPlaneado(vueloPT.vuelosP.buscarElemento(1));	   				
				   }
				system("pause");
				cout<<endl<<endl<<"Mostrando: "<<vuelosE.getTam()<<" vuelos especificos."<<endl<<endl;
	   			for(int i=0;i<vuelosE.getTam();i++){
	   				VueloEspecificoTotal vuelosET=vuelosE.buscarElemento(i+1);
	   				cout<<"Id aerolinea: "<<vuelosET.idAerolinea<<" - id vuelo planeado: "<<vuelosET.idVueloPlaneado<<endl;
	   				imprimirVueloEspecifico(vuelosET.vuelosE.buscarElemento(1));	   				
				   }
				   system("pause");
	   			break;
	   		}
	   		case 9:{//colas de espera
	   			int guardar3[3];
	   			int *pguardar3=guardar3;
	   			ubicarPosicionAerolinea(3,sistemaGlobal,pguardar3);	
	   			Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(guardar3[0]);
	   			VueloPlaneado vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(guardar3[1]);
	   			VueloEspecifico vueloE=vueloP.vuelosEspecificos.buscarElemento(guardar3[2]);
	   			ColasDeEspera(vueloE);
	   			break;
			}
			case 10://arbol para implementar una cola de prioridad 
	   		
	   			break;	   		
	   		case 11:{//lista de vuelos programados desde un origen a un destino
   				cout<<"Elija la ciudad de origen:"<<endl;			//elegir origen y destino
				int origen=elegirCiudad();
				cout<<endl<<"Elija la ciudad de destino:"<<endl;
				int destino=elegirCiudad();
				//buscar vuelos en todas las aerolineas con ese origen y destino
				Lista<VueloPlaneadosTotal> vuelosDisponibles=filtrarVuelosOrigenDestino(crearListaVuelosPlaneadosTotales(sistemaGlobal),origen,destino);
				if(vuelosDisponibles.getTam()==0){//si no hay vuelos avisar
					cout<<"No hay ningun vuelo registrado con ese origen y destino"<<endl<<endl;
					system("pause");
				}else{//si hay vuelos mostrarlos
					cout<<"Se encontraron "<<vuelosDisponibles.getTam()<<" vuelos coincidentes"<<endl<<endl;
					for(int i=0;i<vuelosDisponibles.getTam();i++){
						VueloPlaneadosTotal vueloD=vuelosDisponibles.buscarElemento(i+1);
						cout<<"Aerolinea: "<<vueloD.idAerolinea<<"   - Plan de trayecto: "<<vueloD.idPlanTrayecto<<endl;
						imprimirVueloPlaneado(vueloD.vuelosP.buscarElemento(1));
					}
					system("pause");
				}
	   			break;
			}
	   		default://opcion no valida, error si es caracter.
	   			cout<<"---Ingrese una opcion valida---"<<endl<<endl<<endl;
	   			system("PAUSE");
	   			break;
	  	}
	  	guardarTodo(sistemaGlobal,1);//guardar backup
	}
}

void menuPrincipalAdministrador(){
	int opcion=-1;
	while (opcion!=0){
		system("cls");
		cout<<"-------------Menu Administrador--------------------"<<endl<<endl;
	   	cout<<"Si desea ver reporte de PASAJES VENDIDOS ingrese 1"<<endl;
	   	cout<<"Si desea ver reporte de DESTINOS FRECUENTES ingrese 2"<<endl;
	   	cout<<"Si desea ver lista PASAJEROS de un vuelo ingrese 3"<<endl;
	   	cout<<"Si desea ver el RANKING de AEROLINEAS ingrese 4"<<endl;	   	
	   	cout<<"Si desea ver el RANKING de USUARIOS ingrese 5"<<endl;	   	
	   	cout<<"Si desea ver las consultas especificas ingrese 6"<<endl;
	   	cout<<"Si desea volver al menu anterior ingrese 0"<<endl<<endl<<"?";
	   	cin>>opcion;
	   	
	   	switch(opcion){
	   		case 0:	   			
	   			system("cls");				
	   			break;
	   		case 1:{//reporte pasajes vendidos
			   	Lista<Reserva> reservas=buscarPasajesVendidosEnMes();
			   	cout<<"Se encontraron "<<reservas.getTam()<<" reservas."<<endl;
				cout<<"Se encontraron "<<reservas.getTam()<<" pasajeros."<<endl<<endl;
				int contadorPrecios=0;
				for(int i=0;i<reservas.getTam();i++){
					Reserva reserva=reservas.buscarElemento(i+1);
					cout<<i+1<<" - "<<reserva.fechaReserva<<" $"<<reserva.precioPagado<<"  ( 5% - "<<(reserva.precioPagado*(0.05))<<")."<<endl;
					contadorPrecios=contadorPrecios+reserva.precioPagado;
				}
				cout<<"Valor final: "<<contadorPrecios;
				cout<<endl<<"La ganacia total con el 5% de cada reserva es de :  $"<<(contadorPrecios*(0.05))<<endl;
				system("pause");
	   			break;
	   		}
	   		case  2://reporte destinos frecuentes
	   			imprimirRankingDestinos();
				break;
	   		case 3:{//ver lista pasajeros de un vuelo 
	   			int guardar1[3];
	   			int *pguardar1=guardar1;
	   			ubicarPosicionAerolinea(3,sistemaGlobal,pguardar1);
	   			Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(guardar1[0]);
	   			VueloPlaneado vueloP=aero.itinerarios.vuelosPlaneados.buscarElemento(guardar1[1]);
	   			VueloEspecifico vueloE=vueloP.vuelosEspecificos.buscarElemento(guardar1[2]);
	   			pasajerosEnVueloEspecifico(vueloE);	   			
	   			break;
	   		}
	   		case 4://ranking aerolineas
	   			imprimirRankingAerolineas();
	   			break;	  
			case 5://ranking usuarios
	   			imprimirRankingUsuarios();
	   			break;	   		
	   		case 6://consultas especificas
	   			menuConsultasEspecificas();
	   			break;	
	   		default://opcion no valida, error si es caracter.
	   			cout<<"---Ingrese una opcion valida---"<<endl<<endl<<endl;
	   			system("PAUSE");
	   			break;
	  	}
	  	guardarTodo(sistemaGlobal,1);//guardar backup
	}
}

void menuPrincipal(){
	int opcion=-1;
	while (opcion!=0){
		system("cls");
		cout<<"-------------Menu Principal--------------------"<<endl<<endl;	   	
	   	cout<<"Si desea ingrear como USUARIO ingrese 1"<<endl;
	   	cout<<"Si desea ingresar como ADMINISTRATIVO ingrese 2"<<endl;
	   	cout<<"Si desea iniciar la SIMULACION ingrese 3"<<endl;
	   	cout<<"Si desea IMPRIMIR informacion en MEMORIA ingrese 4"<<endl;
	   	cout<<"Si desea salir SIN GUARDAR ingrese 5"<<endl;
	   	cout<<"Si desea guardar y salir ingrese 0"<<endl<<endl<<"?";
	   	cin>>opcion;
	   	
	   	switch(opcion){
	   		case 0:
	   			guardarTodo(sistemaGlobal,0);
	   			eliminarBackup();//ya se va a cerrar no es necesario el backup
	   			system("cls");
				cout<<"------------Hasta pronto--------"<<endl;//Despedida
	   			break;
	   		case 1://usuario
	   			menuPrincipalUsuario();
				break;
	   		case 2://admin
	   			menuPrincipalAdministrador();
	   			break;
	   		case 3://simulacion	
			   menuPrincipalSimulacion();
	   			break;
	   		case 4://ver informacion en memoria principal
	   			menuPrincipalImprimir();	   			
	   			break;
	   		case 5:
	   			eliminarBackup();
	   			opcion=0;//salta el caso 0 para evitar guardar, y el while acaba, retornando al main
				break;
	   		default://opcion no valida, error si es caracter.
	   			cout<<"---Ingrese una opcion valida---"<<endl<<endl<<endl;
	   			system("PAUSE");
	   			break;
	  	}
	  	if(opcion!=0){		  
	  		guardarTodo(sistemaGlobal,1);//guardar backup
	  	}
	}
}

#endif
