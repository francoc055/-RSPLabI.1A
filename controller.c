#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "controller.h"



int menu()
{
    int opcion;
    printf("1-cargar archivo\n");
    printf("2-listar posts\n");
    printf("3-asignar estadisticas\n");
    printf("4-generar archivo mayores likes\n");
    printf("5-generar archivo haters\n");
    printf("6-ordenar por followers\n");
    printf("7-user mas likeado\n");
    printf("8-salir\n");
    scanf("%d", &opcion);

    return opcion;
}

int confirmarSalida(char* pVariable, char confirma, char rechaza)
{
    int ret = 0;
    char resp;
    if(pVariable != NULL)
    {
       printf("confirma salir?");
       fflush(stdin);
       resp = getchar();
       if(resp == 's')
       {
           *pVariable = confirma;
       }
       else
       {
           *pVariable = rechaza;
       }
        ret = 1;
    }

    return ret;
}

int pedirArchivo(char cadena[])
{
    int ret = 0;
    if(cadena != NULL)
    {
        printf("ingrese el nombre del archivo\n");
        fflush(stdin);
        gets(cadena);
        ret = 1;
    }
    return ret;
}

int cargarDatosPostText(char* path,LinkedList* listaPosts)
{
    int ret = -1;
    FILE* f = NULL;
    char buffer[5][100];
	int cant;
	ePosts* aux;
    if(path != NULL && listaPosts != NULL)
    {
        f = fopen(path, "r");
        if(f == NULL)
        {
            ret = 0;
        }
        else
        {
            fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

            do
            {
                cant = fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
                    if(cant < 5)
                    {
                        break;
                    }

                aux = posts_newParametros(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
                if(aux != NULL)
                {
                    ll_add(listaPosts, aux);
                    aux = NULL;
                    ret = 1;
                }

            }while(!feof(f));
        }
    }
    fclose(f);
    return ret;
}


int mostrarPost(ePosts* m)
{
    int ret = 0;
    int id;
    char user[50];
    int likes;
    int dislikes;
    int followers;

    if(m != NULL)
    {
        if(posts_getId(m, &id)
           && posts_GetUser(m, user)
           && posts_getLike(m, &likes)
           && posts_getDislike(m, &dislikes)
           && posts_getFollower(m, &followers))
        {
            printf("%-5d %26s %10d %15d %15d\n", m->id, m->user, m->like, m->dislike, m->followers);
            ret = 1;
        }
    }
    return ret;
}
int listarPosts(LinkedList* listaPosts)
{
    int ret = 0;
	int leng;
	ePosts* aux;
		    if(listaPosts != NULL && ll_len(listaPosts) > 0)
		    {
		        leng = ll_len(listaPosts);
		        printf("id\t\t\t user\t\tlike\t\tdislike\t\tfollowers\n"
		        		"---------------------------------------------------------------------------\n");
		        for(int i = 0; i < leng; i++)
		        {
		            aux = (ePosts*) ll_get(listaPosts, i);
		        	mostrarPost(aux);
		        }
		        printf("\n\n");
		        ret = 1;
		    }
    return ret;
}

//asignar de manera aleatoria
void* estadisticasAleatorias(void* pElement)
{
    ePosts* auxPost = NULL;
    int id;
    char user[30];
    int likes;
    int dislikes;
    int followers;
    char idStr[30];
    char likeStr[30];
    char dislikeStr[30];
    char followerStr[30];
    int minL = 600;
    int maxL = 5000;
    int minD = 300;
    int maxD = 3500;
    int minF = 10000;
    int maxF = 20000;
    if(pElement != NULL)
    {
        posts_getId(pElement, &id);
        posts_GetUser(pElement, user);

        likes = (rand() % (maxL - minL + 1)) + minL;
        dislikes = (rand() % (maxD- minD + 1)) + minD;
        followers = (rand() % (maxF - minF + 1)) + minF;

        itoa(id, idStr, 10);
        itoa(likes, likeStr, 10);
        itoa(dislikes, dislikeStr, 10);
        itoa(followers, followerStr, 10);

        auxPost = posts_newParametros(idStr, user, likeStr, dislikeStr, followerStr);
    }
    return auxPost;
}

int listMap(LinkedList* lista)
{
    system("cls");
	int ret=0;
	LinkedList* auxLinkedList;
	ePosts* aux = NULL;
	if(lista != NULL){
		auxLinkedList = ll_map(lista, estadisticasAleatorias);
		if(auxLinkedList != NULL){
            ll_clear(lista);
            for(int i = 0; i< ll_len(auxLinkedList); i++)
            {
                aux = (ePosts*) ll_get(auxLinkedList, i);
                ll_add(lista, aux);
            }
			listarPosts(auxLinkedList);
			ret=1;
		}
	}
	return ret;
}

//punto 4
int fitrarMejoresPosteos(LinkedList* listaPosts, LinkedList* listaLikes)
{
    int ret = 0;
    int leng;
    ePosts* aux;
    if(listaLikes != NULL && listaPosts != NULL)
    {
        leng = ll_len(listaPosts);
        for(int i = 0; i < leng; i++)
        {
            aux = (ePosts*) ll_get(listaPosts, i);
            if(aux->like > 4000)
            {
                ll_add(listaLikes, aux);
                ret = 1;
            }
        }
        if(ret == 1)
        {
            listarPosts(listaLikes);
            guardarLista("mejoresPost.csv", listaLikes);
        }
    }
    return ret;
}

/*int guardarMejoresPosteos(char* path, LinkedList* listaLikes)
{
    int ret = 0;
    int leng;
    int cant;
    int flag = 0;
    FILE* f = NULL;
    ePosts* aux = NULL;
    if(path != NULL && listaLikes != NULL)
    {
        f = fopen(path, "w");
        if(f == NULL)
        {
            printf("no se pudo abrir el archivo\n");
        }
        else
        {
            leng = ll_len(listaLikes);
            fprintf(f, "id,user,likes,dislikes,followers\n");

            for(int i = 0; i < leng; i++)
            {
                aux = (ePosts*) ll_get(listaLikes, i);
                if(aux != NULL)
                {
                    cant = fprintf(f, "%d,%s,%d,%d,%d\n", aux->id, aux->user, aux->like, aux->dislike, aux->followers);
                    if(cant < 5)
                    {
                        flag =1;
                        break;
                    }
                    ret = 1;
                }
            }
            if(flag)
            {
                printf("hubo un problema al guardar los post\n");
            }
            else
            {
                printf("posts guardados con exito\n");
            }
        }
    }
    fclose(f);
    return ret;
}*/

//punto 5
int filtrarHaters(LinkedList* listaPosts, LinkedList* listaHaters)
{
    int ret = 0;
    int leng;
    ePosts* aux;
    if(listaHaters != NULL && listaPosts != NULL)
    {
        leng = ll_len(listaPosts);
        for(int i = 0; i < leng; i++)
        {
            aux = (ePosts*) ll_get(listaPosts, i);
            if(aux->like < aux->dislike)
            {
                ll_add(listaHaters, aux);
                ret = 1;
            }
        }
        if(ret == 1)
        {
            listarPosts(listaHaters);
            guardarLista("haters.csv", listaHaters);
        }
    }
    return ret;
}

int guardarLista(char* path, LinkedList* lista)
{
    int ret = 0;
    int leng;
    int cant;
    int flag = 0;
    FILE* f = NULL;
    ePosts* aux = NULL;
    if(path != NULL && lista != NULL)
    {
        f = fopen(path, "w");
        if(f == NULL)
        {
            printf("no se pudo abrir el archivo\n");
        }
        else
        {
            leng = ll_len(lista);
            fprintf(f, "id,user,likes,dislikes,followers\n");

            for(int i = 0; i < leng; i++)
            {
                aux = (ePosts*) ll_get(lista, i);
                if(aux != NULL)
                {
                    cant = fprintf(f, "%d,%s,%d,%d,%d\n", aux->id, aux->user, aux->like, aux->dislike, aux->followers);
                    if(cant < 5)
                    {
                        flag =1;
                        break;
                    }
                    ret = 1;
                }
            }
            if(flag)
            {
                printf("hubo un problema al guardar los post\n");
            }
            else
            {
                printf("posts guardados con exito\n");
            }
        }
    }
    fclose(f);
    return ret;
}
int filterFollowers(void* p, void* q)
{
	int rta = 0;
	ePosts* p1 = NULL;
	ePosts* p2 = NULL;

	if(p != NULL && q != NULL)
	{
		p1 = (ePosts*) p;
		p2 = (ePosts*) q;
		if(p1->followers > p2->followers)
		{
			rta =1;
		}
		else if(p1->followers < p2->followers)
		{
			rta = -1;
		}
	}
	return rta;
}

int userMasLikeado(LinkedList* listaPosts)
{
    int ret = 0;
    int leng;
    int mayor = 0;
    int indice;
    ePosts* aux;
    if(listaPosts != NULL)
    {
        leng = ll_len(listaPosts);
        for(int i = 0; i < leng; i++)
        {
            aux = ll_get(listaPosts, i);
            if(i == 0 || mayor < aux->like)
            {
                mayor = aux->like;
                indice = i;
                ret = 1;
            }
        }
        if(ret == 1)
        {
            aux = (ePosts*) ll_get(listaPosts, indice);
            printf("nombre: %s, likes: %d\n", aux->user, aux->like);
        }
    }
    return ret;
}
