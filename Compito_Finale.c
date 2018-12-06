#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <dirent.h>
#include <string.h>
#include <sys/sysinfo.h>

typedef struct nodo_t{
char info[256];
struct nodo_t *next;
} nodo_lista;

typedef nodo_lista* lista;

void ini_lista(lista *lis);
void agg_coda_lista(lista *lis, char *elemento);
void stampa_lista(lista lis);


	char buffer[256];
	lista l1;


int main(void){

	int cores = get_nprocs();
	
	ini_lista(&l1);


	struct dirent *de;

	printf("Inserire pathname Assoluto della directory: \n");
	scanf("%s", buffer);
	
	DIR *dr = opendir(buffer);
	
	strcat(buffer, "/");
	
	if(dr == NULL){
	printf("Il pathname e' errato o non e' una directory\n"); 
	exit(EXIT_FAILURE);
	}
	
	while((de = readdir(dr)) != NULL){
	//printf("%d\n", de->d_type);
	agg_coda_lista(&l1, de->d_name);	
	}
	closedir(dr);
	stampa_lista(l1);
	exit(EXIT_SUCCESS);	
}


void ini_lista(lista *lis){
	*lis = NULL;
}
void agg_coda_lista(lista *lis, char *elemento){
	lista appoggio;
	char appoggio_stringa[256];
	strcpy(appoggio_stringa, buffer);
	
	if(*lis == NULL){
	*lis = malloc(sizeof(nodo_lista));
	strcpy((*lis)->info, strcat(appoggio_stringa,elemento));
	(*lis)->next = NULL;
	return;
	}
	
	appoggio = *lis;

	while(appoggio->next != NULL)
	appoggio = appoggio->next;

	appoggio->next = malloc(sizeof(nodo_lista));
	appoggio = appoggio->next;

	strcpy(appoggio->info, strcat(appoggio_stringa,elemento));
	appoggio->next = NULL;
}
void stampa_lista(lista lis){
	while(lis != NULL){
	printf("%s  \n", lis->info);
	lis = lis->next;
	}
}
