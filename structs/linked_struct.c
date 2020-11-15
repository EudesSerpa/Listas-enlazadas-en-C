#include <stdio.h>
#include <stdlib.h>

struct Student{
	char *ptrNombre;
	struct Student *ptrNextAlumn;
};

struct Nodo{
	char *ptrNombre;
	char *ptrApellido;
	char *ptrEdad;
	char *ptrPeso;
	struct Student *ptrStudent;
	struct Nodo *ptrNext;
}; 

typedef struct Nodo Nodo;
typedef struct Student Student;

Nodo *header = NULL;
Nodo *footer = NULL;
//Student *first = NULL;
//Student *last = NULL;

Nodo *create_nodo();
void insert_nodo(Nodo *nodo);
void show_list();
void free_memory();

int main(void){

 	unsigned	char teachers = 0, i = 0;
	Nodo *ptrDocentes = NULL;

	printf("Write the numbers of teachers to assign: ");
	scanf("%1u",&teachers);

//	system("Pause");

	ptrDocentes = (Nodo *) malloc(sizeof(Nodo) * teachers); //Array of pointers for nodos

	for(i=0; i<teachers; i++){
		printf("Docente %d\r\n", i+1);
		Nodo *nodo1 = create_nodo();
		*(ptrDocentes + i) = *nodo1; //Location stored in array
	}

	for(i=0; i<teachers; i++)
		insert_nodo(ptrDocentes + i);
	
	show_list();

	free_memory();

	return (0);
}

Nodo *create_nodo(){
	/* Crea los nuevos nodos e inicializa sus miembros.
		Return:
			Puntero al nuevo nodo.*/	
	char *data(); //Prototipo
	static char i=0;

	Nodo *new_nodo = (Nodo *) malloc(sizeof(Nodo)); //Crea nodo
	Student *new_alumn = (Student *) malloc(sizeof(Student));
	
	if(i==0){ //ARREGLAR. SI NO SE LEE ALGO ANTES, LA PRIMERA VEZ QUE SE LLAME PARA CREAR EL 1ra NODO, ES COMO QUE SI SE LEYESE UN SALTO DE LINEA YA QUE NO DA LA OPCION PARA INGRESAR EL NOMBRE DEL PROFESOR EN DICHA 1ra PASADA. 
		new_nodo->ptrNombre = data();
		i++;
	}
	printf("Write the teacher's name: ");
	new_nodo->ptrNombre = data();
	printf("Write the teacher's last name: ");
	new_nodo->ptrApellido = data();
	printf("Write the teacher's age: ");
	new_nodo->ptrEdad = data();  
	printf("Write the teacher's weight: ");
	new_nodo->ptrPeso = data();

	printf("Write the Alumn's name: ");
	new_nodo->ptrStudent = new_alumn; 
	new_nodo->ptrStudent->ptrNombre= data();
	
	new_nodo->ptrNext = NULL;
	new_nodo->ptrStudent->ptrNextAlumn = NULL;

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
		printf("\r\nThe list is...\r\n");
		while(scroll != NULL){
			printf("\r\nNombre: %s\r\nApellido: %s\r\n", scroll->ptrNombre, scroll->ptrApellido);			
			printf("Edad: %s\r\nPeso: %s\r\n", scroll->ptrEdad, scroll->ptrPeso);			
			printf("Alumnos: [%s]\r\n", scroll->ptrStudent->ptrNombre);
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
			//free(scroll->ptrStudent);
			scroll = header;
		}
		header = NULL;
		footer = NULL;
		puts("Memory freed");
	}
}
