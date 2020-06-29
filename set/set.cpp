#include "set.h"
#include "../common/Common.h"

struct Node {
   Hechizo elem; // el elemento que este nodo almacena
   Node* next; // siguiente nodo de la cadena de punteros
};

struct SetSt {
   int size; // cantidad de elementos del conjunto
   Node* first; // puntero al primer elemento
};

/**
  Invariantes de representacion:
    - size es la cantidad de nodos
    - no hay nodos con hechizos repetidos
**/

/// Proposito: retorna un conjunto de hechizos vacio
/// Costo: O(1)
Set emptyS() {
   Set s = new SetSt ;
   s->size = 0;
   s->first = NULL ;
   return s ;
}

/// Proposito: retorna la cantidad de hechizos
/// Costo: O(1)
int sizeS(Set s) {
   return s->size ;
}

/// Proposito: indica si el hechizo pertenece al conjunto
/// Costo: O(h), h = cantidad de hechizos
bool belongsS(Hechizo h, Set s) {
    Node* n = s->first ;
    while( n != NULL && not mismoHechizo(n->elem,h)) {
        n= n->next ;
    }
    return n != NULL ;
}

/// Proposito: agrega un hechizo al conjunto
/// Costo: O(h), h = cantidad de hechizos
void addS(Hechizo h, Set s) {
   Node* nodo = new Node ;
   nodo->elem = h ;
   nodo->next = NULL ;
   if ( s->first == NULL ) {
        s->size++;
        s->first = nodo;
   }
   if ( !belongsS(h,s)) {
        Node* tmp = s->first ;
        s->size++;
        s->first = nodo ;
        s->first->next = tmp ;
    }
}

/// Proposito: borra un hechizo del conjunto (si no existe no hace nada)
/// Costo: O(h), h = cantidad de hechizos
void removeS(Hechizo h, Set s) {
   if ( belongsS(h,s)) {
    Node* firstNode = s->first ;
    Node* anterior = NULL ;

    while (firstNode->elem != h) {
        anterior = firstNode ;
        firstNode= firstNode->next;
    }
    if (s->size == 1) {
        delete firstNode;
        s->first = NULL ;
    }

    if (anterior == NULL) {
        Node* temp = firstNode->next;
        firstNode = temp ;
        delete firstNode ;
        s->size--;
    }
    else {
        Node* tmp = firstNode->next;
        firstNode = tmp ;
        delete firstNode ;
        s->size--;
    }
 }

}

/// Proposito: borra toda la memoria consumida por el conjunto (pero no la de los hechizos)
/// Costo: O(n)
void destroyS(Set s) {
    Node* n = s->first ;
    while(n != NULL) {
        Node* tmp = n->next ;
        n=tmp ;
        delete n ;
    }
    delete s ;
}

/// Proposito: retorna un nuevo conjunto que es la union entre ambos (no modifica estos conjuntos)
/// Costo: O(h^2), h = cantidad de hechizos
Set unionS(Set s1, Set s2) {
    Set newSet = emptyS() ;
    Node* nodoSet1 = s1->first ;
    Node* nodoSet2 = s2->first ;
    if ((s1->size == 0) && (s2->size == 0)) {
        return s1;
    }
    else {
        while (nodoSet1 != NULL) {
            addS(nodoSet1->elem,newSet);
            nodoSet1 = nodoSet1->next;
        }
        while (nodoSet2 != NULL) {
            addS(nodoSet2->elem,newSet);
            nodoSet2 = nodoSet2->next;
        }
        return newSet ;
    }
}
