#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "controller.h"

int main()
{
    LinkedList* listaPosts = ll_newLinkedList();
    LinkedList* listaLikes = ll_newLinkedList();
    LinkedList* listaHaters = ll_newLinkedList();
    char salir = 'n';
    char nombreArchivo[30];
    int flag = 0;
    if(listaPosts == NULL && listaLikes != NULL)
    {
        printf("no se pudo crear el linkedList");
    	exit(1);
    }

    do{
        switch(menu())
        {
        case 1:
             pedirArchivo(nombreArchivo);
            if(!strcmp(nombreArchivo, "posts.csv") || !strcmp(nombreArchivo, "posts"))
            {
                if(cargarDatosPostText("posts.csv", listaPosts))
                {
                    printf("archivos leidos con exito\n");
                    flag = 1;
                }
                else
                {
                    printf("no se pudo abrir el archivo\n");
                }
            }
            else
            {
                printf("nombre incorrecto\n");
            }
            break;
        case 2:
            if(flag)
            {
               if(!listarPosts(listaPosts))
                {
                    printf("hubo un error al mostrar\n");
                }
            }
            else
            {
                printf("primero tenes que cargar los archivos\n");
            }
            break;
        case 3:
            if(flag)
            {
                listMap(listaPosts);
            }
            else
            {
                printf("primero tenes que cargar los archivos\n");
            }
            break;
        case 4:
            if(flag)
            {
                if(!fitrarMejoresPosteos(listaPosts, listaLikes))
                {
                    printf("hubo un error al mostrar\n");
                }
            }
            else
            {
                printf("primero tenes que cargar los archivos\n");
            }
            break;
        case 5:
            if(flag)
            {
                if(!filtrarHaters(listaPosts, listaHaters))
                {
                    printf("hubo un error al mostrar\n");
                }
            }
            else
            {
                printf("primero tenes que cargar los archivos\n");
            }
            break;
        case 6:
            if(flag)
            {
                ll_sort(listaPosts, filterFollowers, 0);
                listarPosts(listaPosts);
            }
            else
            {
                printf("primero tenes que cargar los archivos\n");
            }
            break;
        case 7:
            if(flag)
            {
                userMasLikeado(listaPosts);
            }
            else
            {
                printf("primero tenes que cargar los archivos\n");
            }
            break;
        case 8:
            confirmarSalida(&salir, 's', 'n');
            break;
        default:
            printf("no existe esa opcion\n");
        }
        fflush(stdin);
    }while(salir != 's');
    return 0;
}
