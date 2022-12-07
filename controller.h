#include "posts.h"
#include "LinkedList.h"

#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED



#endif // CONTROLLER_H_INCLUDED

int menu();
int confirmarSalida(char* pVariable, char confirma, char rechaza);
int pedirArchivo(char cadena[]);
int cargarDatosPostText(char* path,LinkedList* listaPosts);

int mostrarPost(ePosts* m);
int listarPosts(LinkedList* listaPosts);

void* estadisticasAleatorias(void* pElement);
int listMap(LinkedList* lista);

int fitrarMejoresPosteos(LinkedList* listaPosts, LinkedList* listaLikes);

int filtrarHaters(LinkedList* listaPosts, LinkedList* listaHaters);
int guardarLista(char* path, LinkedList* lista);

int filterFollowers(void* p, void* q);

int userMasLikeado(LinkedList* listaPosts);
