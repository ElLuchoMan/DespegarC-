#ifndef BASEDEDATOS_h
#define BASEDEDATOS_h
#include "Lista.h"
#include "Estructuras.h"


Sistema *sistemaGlobal=new Sistema();

int buscarPosVueloPlaneado(int id, Lista<VueloPlaneadosTotal> vuelos){
	for(int i=1;i<=vuelos.getTam();i++){
		VueloPlaneadosTotal vueloPT=vuelos.buscarElemento(i);
		VueloPlaneado vuelo=vueloPT.vuelosP.buscarElemento(1);		
		if(vuelo.codigoVuelo==id){
			return i;
		}
	}
	return -1;
}

int buscarPosVueloPlaneado(int id, Lista<VueloPlaneado> vuelos){
	for(int i=1;i<=vuelos.getTam();i++){
		VueloPlaneado vuelo=vuelos.buscarElemento(i);
		if(vuelo.codigoVuelo==id){
			return i;
		}
	}
	return -1;
}

int buscarPosVueloEspecifico(int id, Lista<VueloEspecifico> vuelos){
	for(int i=1;i<=vuelos.getTam();i++){
		VueloEspecifico vuelo=vuelos.buscarElemento(i);
		if(vuelo.idCodigoVueloEspecifico==id){
			return i;
		}
	}
	return -1;
}

int buscarPosVueloEspecifico(int id, Lista<VueloEspecificoTotal> vuelos){
	for(int i=1;i<=vuelos.getTam();i++){
		VueloEspecificoTotal vueloET=vuelos.buscarElemento(i);
		VueloEspecifico vuelo=vueloET.vuelosE.buscarElemento(1);
		if(vuelo.idCodigoVueloEspecifico==id){
			return i;
		}
	}
	return -1;
}

int buscarPosAvion(int id, Lista<Avion> aviones){
	for(int i=1;i<=aviones.getTam();i++){
		Avion avion=aviones.buscarElemento(i);
		if(avion.idAvion==id){
			return i;
		}
	}
	return -1;
}

int buscarPosSilla(string id, Lista<Silla> sillas){
	for(int i=1;i<=sillas.getTam();i++){
		Silla silla=sillas.buscarElemento(i);
		if(silla.idSilla==id){
			return i;
		}
	}
	return -1;
}

int buscarPosSillaPorReserva(int idReserva, Lista<Silla> sillas){//buscar silla por reservacion
	for(int i=1;i<=sillas.getTam();i++){
		Silla silla=sillas.buscarElemento(i);
		if(silla.pasajero.numeroReserva==idReserva){
			return i;
		}
	}
	return -1;
}

int buscarPosViaje(int id, Lista<Viaje> viajes){
	for(int i=1;i<=viajes.getTam();i++){
		Viaje viaje=viajes.buscarElemento(i);
		if(viaje.idViaje==id){
			return i;
		}
	}
	return -1;
}

int buscarPosReserva(int id, Lista<Reserva> reservas){
	for(int i=1;i<=reservas.getTam();i++){
		Reserva reserva=reservas.buscarElemento(i);
		if(reserva.idReserva==id){
			return i;
		}
	}
	return -1;
}

int buscarPosUsuario(string identificacion, Lista<Usuario> usuarios){
	for(int i=1;i<=usuarios.getTam();i++){
		Usuario usuario=usuarios.buscarElemento(i);
		if(usuario.identificacion==identificacion){
			return i;
		}
	}
	return -1;
}




//consultas:

Lista<string> destinosPorAerolinea(Aerolinea aero){
	Lista<string> retorno;
	for(int j=0;j<aero.itinerarios.vuelosPlaneados.getTam();j++){
		VueloPlaneado vuelo=aero.itinerarios.vuelosPlaneados.buscarElemento(j+1);
		Ciudad origen=sistemaGlobal->ciudades.buscarElemento(vuelo.idOrigen);
		Ciudad destino=sistemaGlobal->ciudades.buscarElemento(vuelo.idDestino);
		ostringstream os;
		os<<origen.nombreCiudad<<" - "<<destino.nombreCiudad;
		string orgdes=os.str();
		retorno.insertarFinal(orgdes);
	}
	return retorno;	
}

Lista<Silla> sillasVaciasEnVuelo(VueloEspecifico vuelo,int idAerolinea){
	Lista<Silla> retorno;
	Aerolinea aero=sistemaGlobal->aerolineas.buscarElemento(idAerolinea);
	Avion avion=aero.aviones.buscarElemento(buscarPosAvion(vuelo.idAvion,aero.aviones));
	for(int i=0;i<avion.sillas.getTam();i++){
		Silla silla=avion.sillas.buscarElemento(i+1);
		if(!silla.estado){
			retorno.insertarFinal(silla);
		}
	}
	return retorno;
}




/*
void actualizarIDS(){	
	Localidad local;
	Sucursal suc;
	Cliente cli;
	Paseador paseador;
	Perro perr;
	Horario hora;
	Paseo pase;
	for(int i=0;i<global->getTam();i++){//for localidades
		local=global->buscarElemento(i+1);
		for(int j=0;j<local.sucursales.getTam();j++){//for sucursales
			suc=local.sucursales.buscarElemento(j+1);
			int k;
			for(k=0;k<suc.clientes.getTam() ;k++){//for clientes
				cli=suc.clientes.buscarElemento(k+1);
				for(int l=0;l<cli.perros.getTam();l++){//for perros
					perr= cli.perros.buscarElemento(l+1);
					//for paseos si es necesario
					perr.idPerro=l+1;
					cli.perros.modificarElemento(l+1,perr);
				}
				cli.idCliente=k+1;
				suc.clientes.modificarElemento(k+1,cli);
			}
			for(k=0;k<suc.paseadores.getTam();k++){//for paseadores
				paseador=suc.paseadores.buscarElemento(k+1);
				for(int l=0;l<paseador.horarioDisponible.getTam();l++){//for horarios
					hora=paseador.horarioDisponible.buscarElemento(l+1);
					hora.idHorario=l+1;
					paseador.horarioDisponible.modificarElemento(l+1,hora);
				}
				paseador.idPaseador=k+1;
				suc.paseadores.modificarElemento(k+1,paseador);
			}
			suc.idSucrusal=j+1;
			local.sucursales.modificarElemento(j+1,suc);
		}
		local.id=i+1;
		global->modificarElemento(i+1,local);
	}
}*/

#endif
