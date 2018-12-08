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
void rimuovi_cartella(lista *lis, char *elemento);
void unisci_liste(lista *lis1, lista *lis2);
int letta(char *elemento);
void stampa_lista(lista lis);
void *funzione_t(void *arg);


	char buffer[256];
	lista l1;
	lista cartelle_lette;


int main(void){

	int cores = get_nprocs();
	
	ini_lista(&l1);
	ini_lista(&cartelle_lette);


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
	agg_coda_lista(&cartelle_lette, buffer);
	stampa_lista(l1);

	while(cores > 0){
	cores --;
	}

	exit(EXIT_SUCCESS);	
}


void ini_lista(lista *lis){
	*lis = NULL;
}
void agg_coda_lista(lista *lis, char *elemento){
	lista appoggio;
	char appoggio_stringa[256];
	
	if(*lis == NULL){
	*lis = malloc(sizeof(nodo_lista));
	strcpy((*lis)->info, elemento);
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
void unisci_liste(lista *lis1, lista *lis2){

	lista appoggio = *lis1;
	while(appoggio->next != NULL)
	appoggio = appoggio->next;
		
	appoggio->next = *lis2;
}
int letta(char *elemento){

	lista appoggio = cartelle_lette;
	while(appoggio != NULL){

		if(strcmp(elemento, appoggio->info) == 0){
		
		return 0;
		
		}	
	appoggio = appoggio->next;
	}
	return 1;
}
void rimuovi_cartella(lista *lis, char *elemento){

	if(*lis != NULL){
	

		if((*lis)->next != NULL){

		lista appoggio = *lis;
			while(appoggio->next != NULL){
				if(strcmp(appoggio->next->info, elemento) == 0){
				lista da_eliminare = appoggio->next;
				appoggio->next = appoggio->next->next;
				free(da_eliminare);
				return;	
				}
				else
				appoggio = appoggio->next;
			}

		}
		if(strcmp((*lis)->info, elemento) == 0){
		lista da_eliminare = *lis;
		*lis = NULL;
		free(da_eliminare);		
		}
	}

}
void *funzione_t(void *arg){
	lista appoggio = l1;
	char *cartella;
	struct dirent *de;
	DIR *dr;
	while(appoggio != NULL){
	cartella = appoggio->info;
		if(dr = opendir(cartella) != NULL){
			if(letta(cartella) == 0){
				lista l_temporanea;
				ini_lista(&l_temporanea);
				rimuovi_cartella(&l1, cartella);
				while((de = readdir(dr)) != NULL){
					agg_coda_lista(&l_temporanea, de->d_name);
		    		}
		unisci_liste(&l1, &l_temporanea);
		         }
	    closedir(dr);
	         }
	appoggio = appoggio->next;
	}
}
