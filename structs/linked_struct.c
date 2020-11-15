#include <stdio.h>
#include <stdlib.h>

struct Nodo{
	char *ptrDocente;
	char *ptrAlumno;
	struct Nodo *ptrNext;
}; 

typedef struct Nodo Nodo;

Nodo *header = NULL;
Nodo *footer = NULL;

Nodo *create_nodo();
void insert_nodo(Nodo *nodo);
void show_list();
void free_memory();

int main(void){

	Nodo *nodo1 = create_nodo();
	Nodo *nodo2 = create_nodo();

	insert_nodo(nodo1);
	insert_nodo(nodo2);
	
	show_list();
	free_memory();

	return (0);
}

Nodo *create_nodo(){
	/* Crea los nuevos nodos e inicializa sus miembros.
		Return:
			Puntero al nuevo nodo.*/	
	char *data(); //Prototipo

	char *ptrTeacher = NULL;
	char *ptrAlumn = NULL;

	printf("Write the teacher's name: ");
	ptrTeacher = data();
	printf("Write the alumns's name: ");
	ptrAlumn = data();
	
	Nodo *new_nodo = (Nodo *) malloc(sizeof(Nodo)); //Crea nodo

	new_nodo->ptrDocente = ptrTeacher;
	new_nodo->ptrAlumno = ptrAlumn;
	new_nodo->ptrNext = NULL;

	//free(ptrTeacher); //Free Memory 
	//free(ptrAlumn);
	ptrTeacher = NULL;
	ptrAlumn = NULL;

	return new_nodo;
}

char *data(){
	/* Lectura dinamica de data. 
		Return:
	   		Puntero que apunta al texto leido.*/
	size_t n_bytes = 0;
	size_t size_line = 0;
	char *ptrName = NULL;

	if ((size_line = getline(&ptrName, &n_bytes, stdin)) == -1)
		puts("ERROR: EOF found wihtout reading any byte / Others errors");
	else
		return ptrName;
}

void insert_nodo(Nodo *nodo){
	/* Inserta el nodo especificado en el parametro de esta funcion al final de la list.
		Args:
   			- Nodo *nodo: Puntero al tipo de dato Nodo.		
	*/
	if(header == NULL){ //First nodo. Es la cabeza y fin de la lista
		header = nodo;
		footer = nodo;
	}else{				//Others nodos.
		footer->ptrNext = nodo; //Insercion siempre al final
		footer = nodo;
	}
}

void show_list(){
	/*Recorre la lista y muestra los datos de sus nodos.*/
	Nodo *scroll = header;
	
	if(scroll == NULL){
		puts("Empty list");
		return;
	}else{
		puts("List is...");
		while(scroll != NULL){
			printf("Docente: %s\rAlumno: %s\r\n", scroll->ptrDocente, scroll->ptrAlumno);			
			scroll = scroll->ptrNext;
		}
	}
}

void free_memory(){
	/* Libera la memoria asignada para cada nodo insertado en la lista.*/
	Nodo *scroll = header;
	
	if(scroll == NULL){
		puts("WARNING: No se han insertado nodos a la lista para liberar memoria automaticamente.");
		return;
	}else{
		while(scroll != NULL){
			header = scroll->ptrNext; //Update header of list
			free(scroll);
			scroll = header;
		}
		header = NULL;
		footer = NULL;
		puts("Memory freed");
	}
}
