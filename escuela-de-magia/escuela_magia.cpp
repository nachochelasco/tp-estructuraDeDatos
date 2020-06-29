#include "escuela_magia.h"
#include "../common/Common.h"

struct EscuelaDeMagiaSt {
   Set hechizos ;
   Map magosMap ;
   MaxHeap magosHeap ;
};

/// Propósito: Devuelve una escuela vacía.
/// O(1)
EscuelaDeMagia fundarEscuela() {
   EscuelaDeMagia escuela = new EscuelaDeMagiaSt ;
   escuela->hechizos = emptyS() ;
   escuela->magosMap = emptyM() ;
   escuela->magosHeap = emptyH() ;
   return escuela ;
}

/// Propósito: Indica si la escuela está vacía.
/// O(1)
bool estaVacia(EscuelaDeMagia m) {
   return isEmptyH(m->magosHeap) ;
}

/// Propósito: Incorpora un mago a la escuela (si ya existe no hace nada).
/// O(log m)
void registrar(string nombre, EscuelaDeMagia m) {
    if ( lookupM(nombre,m->magosMap) == NULL ) {
        assocM(nombre,crearMago(nombre),m->magosMap) ;
        insertH(crearMago(nombre),m->magosHeap) ;
        }
}

/// Propósito: Devuelve los nombres de los magos registrados en la escuela.
/// O(m)
vector<string> magos(EscuelaDeMagia m) {
   return domM(m->magosMap) ;
}

/// Propósito: Devuelve los hechizos que conoce un mago dado.
/// Precondición: Existe un mago con dicho nombre.
/// O(log m)
Set hechizosDe(string nombre, EscuelaDeMagia m) {
   return hechizosMago(lookupM(nombre,m->magosMap)) ;
}

/// Propósito: Dado un mago, indica la cantidad de hechizos que la escuela ha dado y él no sabe.
/// Precondición: Existe un mago con dicho nombre.
/// O(log m)
int leFaltanAprender(string nombre, EscuelaDeMagia m) {
   return sizeS(m->hechizos) - sizeS(hechizosDe(nombre,m)) ;
}

/// Propósito: Devuelve el mago que más hechizos sabe.
/// Precondición: La escuela no está vacía.
/// O(log m)
Mago unEgresado(EscuelaDeMagia m) {
   return maxH(m->magosHeap) ;
}

/// Propósito: Devuelve la escuela sin el mago que más sabe.
/// Precondición: La escuela no está vacía.
/// O(log m)
void quitarEgresado(EscuelaDeMagia m) {

    deleteM(nombreMago(unEgresado(m)),m->magosMap) ;
    deleteMax(m->magosHeap) ;
}

MaxHeap actualizarHeap(Hechizo hechizo,string nombre,MaxHeap h) {
    MaxHeap newHeap = emptyH() ;
        while ( sizeH(h) != 0 ) {
            if ( nombre != nombreMago(maxH(h))) {
                insertH(maxH(h),newHeap) ;
                deleteMax(h) ;
            }
            else {
                aprenderHechizo(hechizo,maxH(h)) ;
                insertH(maxH(h),newHeap) ;
                deleteMax(h);
                }
            }
    return newHeap ;
}

/// Propósito: Enseña un hechizo a un mago existente, y si el hechizo no existe en la escuela es incorporado a la misma.
/// O(m . log m + log h)
void enseniar(Hechizo h, string nombre, EscuelaDeMagia m) {
    addS(h,m->hechizos) ;
    aprenderHechizo(h,lookupM(nombre,m->magosMap)) ;
    m->magosHeap = actualizarHeap(h,nombre,m->magosHeap) ;
}


/// Propósito: Libera toda la memoria creada por la escuela (incluye magos, pero no hechizos).
void destruirEscuela(EscuelaDeMagia m) {
    while( sizeH(m->magosHeap) > 0) {
        deleteMax(m->magosHeap);
        }
    destroyM(m->magosMap) ;
}


