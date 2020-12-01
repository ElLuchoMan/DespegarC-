#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <iostream>
#include "Lista.h"
#include "Cola.h"

using namespace std;

struct Prioridad{
	int cliente;
	int prioridad;
};

struct Hora{
	int hora;
	int minuto;
};

struct Pasajero{
	string identificacion;
	string nombre;
	string apellido;
	string tipo;//niño, señor o señora
	int numeroReserva;
	string fechaNacimiento;
};

struct Silla{
	string idSilla;
	bool estado;//true- vendida, false - no vendida
	Pasajero pasajero;
};

struct VueloEspecifico{
	int idCodigoVueloEspecifico;
	int anio;
	int mes;
	int dia;
	int idAvion;
	int cuposLibres;
	int tarifaAdulto;
	int tarifaNinio;
	Cola<Prioridad> prioridades;		
};

struct VueloPlaneado{
	int codigoVuelo;
	int idOrigen;
	int idDestino;
	int diaDeLaSemana[8];	
	Hora salida;
	Hora llegada;
	int duracion;//en horas
	Lista<VueloEspecifico> vuelosEspecificos;
	bool vueloMultiple;
	Lista<int> vuelosDirectos;//guardara el id de los vuelos planeados que haran parte del vuelo multiple
};

struct PlanTrayecto{
	int idPlan;
	Lista<VueloPlaneado> vuelosPlaneados;
};

struct Avion{
	int idAvion;
	string modelo;
	string matricula;
	int capacidad;
	Lista<Silla> sillas;
};

struct Aerolinea{
	int idAerolinea;
	string nombre;
	int avionesDisponibles;	
	PlanTrayecto itinerarios;
	Lista<Avion> aviones;
	string numero_cuenta_bancaria;
};

struct Reserva{
	int idReserva;
	string fechaReserva;//fecha en que se reservo
	int idVuelo;//id del vuelo especifico
	string tipo;//niño o adulto
	int precioPagado;
};

struct Viaje{
	int idViaje;
	string nombre;
	string tipoDeViaje;//normal, ida y vuelta, multiple
	Lista<Reserva> reservas;
};

struct Usuario{
	int idUnico;
	string identificacion;
	string nombre;
	string sexo;
	int edad;
	Lista<Viaje> viajes;
};

struct Ciudad{
	int idCiudad;
	string nombreCiudad;
};

struct Sistema{
	Lista<Aerolinea> aerolineas;
	Lista<Usuario> usuarios;
	Lista<Ciudad> ciudades;
};

//estructuras planas

struct PlanTotal{
	int idAerolinea;
	PlanTrayecto itinerarios;
};

struct VueloPlaneadosTotal{
	int idAerolinea;
	int idPlanTrayecto;
	int ctdadVuelosPlaneados;	
	Lista<VueloPlaneado> vuelosP;	
};

struct VueloEspecificoTotal{
	int idAerolinea;
	int idPlanTrayecto;
	int idVueloPlaneado;
	int ctdadVuelosEspecificos;
	Lista<VueloEspecifico> vuelosE;	
};

struct SillaTotal{
	int idAerolinea;
	int idAvion;
	int ctdadSillas;
	Lista<Silla> sillas;
};

struct AvionTotal{
	int idAerolinea;
	int ctdadAviones;
	Lista<Avion> aviones;
};

struct PasajeroTotal{
	int idAerolinea;
	int idPlanTrayecto;
	int idVueloPlaneado;
	int idVueloEspecifico;
	string idSilla;
	Pasajero pasajero;
};

struct ViajeTotal{
	int idUsuario;
	int ctdadViajes;
	Lista<Viaje> viajes;
};

struct ReservaTotal{
	int idUsuario;
	int idViaje;
	int ctdadReservas;
	Lista<Reserva> reservas;
};

//---------------------------------------


#endif    
