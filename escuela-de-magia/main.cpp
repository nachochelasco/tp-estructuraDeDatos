#include <iostream>
#include <cstdlib>
#include <vector>
#include "../hechizo/hechizo.h"
#include "../mago/mago.h"
#include "../set/set.h"
#include "../map/map.h"
#include "../maxheap/maxheap.h"
#include "escuela_magia.h"
#include "../common/Common.h"

using namespace std;

/// Proposito: Retorna todos los hechizos aprendidos por los magos.
/// Eficiencia: ?
Set hechizosAprendidos(EscuelaDeMagia m) {
   Set newSet = emptyS() ;
   for ( string nombre: magos(m)) {
        newSet = unionS(hechizosDe(nombre,m),newSet) ;
    }
    return newSet ;
}


/// Proposito: Indica si existe un mago que sabe todos los hechizos enseñados por la escuela.
/// Eficiencia: ?
bool hayUnExperto(EscuelaDeMagia m) {
   return leFaltanAprender(nombreMago(unEgresado(m)),m) == 0 ;
}

/// Proposito: Devuelve una maxheap con los magos que saben todos los hechizos dados por la escuela, quitándolos de la escuela.
/// Eficiencia: ?
MaxHeap egresarExpertos(EscuelaDeMagia m) {
    MaxHeap newHeap = emptyH() ;
    while( hayUnExperto(m) ) {
        insertH(unEgresado(m),newHeap) ;
        quitarEgresado(m) ;
        }
    return newHeap ;
}

void nombreMagos(EscuelaDeMagia m) {
    vector<string> ms = magos(m);
    for ( string s : ms) {
        cout << s << endl ;
    }
}

/// Probando las funciones de interfaz y usuario

void testFundarEscuela() {
    EscuelaDeMagia escuela = fundarEscuela() ;
    if ( estaVacia(escuela) ) {
        cout << "testFundarEscuela = test OK" << endl ;
    } else {
        cout << "testFundarEscuela = test FALLA" << endl ;
    }
}

void testRegistrarMago() {
    EscuelaDeMagia escuela = fundarEscuela() ;
    registrar("Harry",escuela) ;
    if ( estaVacia(escuela) ) {
        cout << "testRegistrarMago = test FALLA" << endl ;
    } else {
        cout << "testRegistrarMago = test OK" << endl ;
    }
}

void testCantidadHechizosDeMago() {
    EscuelaDeMagia escuela = fundarEscuela() ;
    registrar("Ron",escuela) ;
    Hechizo h1 = crearHechizo("h1",5) ;
    Hechizo h2 = crearHechizo("h2",4) ;
    enseniar(h1,"Ron",escuela) ;
    enseniar(h2,"Ron",escuela) ;
    cout << "testCantidadHechizosDeMago = " << sizeS(hechizosDe("Ron",escuela)) << endl ;
}

void testLeFaltanAprender() {
    EscuelaDeMagia escuela = fundarEscuela() ;
    registrar("Harry",escuela) ;
    registrar("Ron",escuela) ;
    Hechizo h1 = crearHechizo("h1",5) ;
    Hechizo h2 = crearHechizo("h2",4) ;
    Hechizo h3 = crearHechizo("h3",2) ;
    enseniar(h1,"Harry",escuela) ;
    enseniar(h3,"Ron",escuela) ;
    enseniar(h2,"Harry",escuela) ;
    cout << "testLeFaltanAprender = " << leFaltanAprender("Harry", escuela) << endl ;
}

void testUnEgresado() {
    EscuelaDeMagia escuela = fundarEscuela() ;
    registrar("Harry",escuela) ;
    registrar("Ron",escuela) ;
    Hechizo h1 = crearHechizo("h1",5) ;
    Hechizo h2 = crearHechizo("h2",4) ;
    Hechizo h3 = crearHechizo("h3",1) ;
    enseniar(h1,"Harry",escuela) ;
    enseniar(h2,"Harry",escuela) ;
    enseniar(h3,"Ron",escuela) ;
    cout << "testUnEgresado = " << nombreMago(unEgresado(escuela)) << endl ;
}

void testQuitarEgresado() {
    EscuelaDeMagia escuela = fundarEscuela() ;
    registrar("Harry",escuela) ;
    registrar("Ron",escuela) ;
    quitarEgresado(escuela) ;
    cout << "testQuitarEgresado = Cantidad de magos en la escuela =" << magos(escuela).size() << endl ;
}

void testHechizosAprendidos() {
    EscuelaDeMagia escuela = fundarEscuela() ;
    registrar("Harry",escuela) ;
    registrar("Ron",escuela) ;
    Hechizo h1 = crearHechizo("h1",5) ;
    Hechizo h2 = crearHechizo("h2",4) ;
    Hechizo h3 = crearHechizo("h3",1) ;
    enseniar(h1,"Harry",escuela) ;
    enseniar(h2,"Harry",escuela) ;
    enseniar(h3,"Ron",escuela) ;
    enseniar(h2,"Ron",escuela) ;
    cout << "testHechizosAprendidos = Cantidad de hechizos aprendidos = " << sizeS(hechizosAprendidos(escuela)) << endl ;
}

void testHayUnExperto() {
    EscuelaDeMagia escuela = fundarEscuela() ;
    registrar("Harry",escuela) ;
    registrar("Ron",escuela) ;
    Hechizo h1 = crearHechizo("h1",5) ;
    Hechizo h2 = crearHechizo("h2",4) ;
    Hechizo h3 = crearHechizo("h3",1) ;
    enseniar(h1,"Ron",escuela) ;
    enseniar(h2,"Harry",escuela) ;
    enseniar(h3,"Ron",escuela) ;
    enseniar(h2,"Ron",escuela) ;
    enseniar(h3,"Harry",escuela) ;
    if ( hayUnExperto(escuela) ) {
        cout << "testHayUnExperto = TRUE" << endl ;
    } else {
         cout << "testHayUnExperto = FALSE" << endl ;
    }
}

void testEgresarExpertos() {
    EscuelaDeMagia escuela = fundarEscuela() ;
    registrar("Harry",escuela) ;
    registrar("Ron",escuela) ;
    registrar("Hermione",escuela) ;
    Hechizo h1 = crearHechizo("h1",5) ;
    Hechizo h2 = crearHechizo("h2",4) ;
    Hechizo h3 = crearHechizo("h3",1) ;
    enseniar(h1,"Ron",escuela) ;
    enseniar(h2,"Harry",escuela) ;
    enseniar(h3,"Ron",escuela) ;
    enseniar(h2,"Ron",escuela) ;
    enseniar(h3,"Harry",escuela) ;
    enseniar(h1,"Harry",escuela) ;
    enseniar(h2,"Hermione",escuela) ;
    cout << "testEgresarExpertos = Cantidad magos egresados = " << sizeH(egresarExpertos(escuela)) << endl ;
    }

int main()
{
    /// Escribir algunas pruebas para las funciones de la interfaz
    /// de escuela de magia, y también las de usuario.

    testFundarEscuela() ;
    testRegistrarMago() ;
    testCantidadHechizosDeMago() ;
    testLeFaltanAprender() ;
    testUnEgresado() ;
    testQuitarEgresado() ;
    testHechizosAprendidos() ;
    testHayUnExperto() ;
    testEgresarExpertos() ;

    return 0;
}
