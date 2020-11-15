#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
Student *last = NULL;

Nodo *create_nodo(Student **ptrAlumnxDoc);
void insert_nodo(Nodo *nodo);
void show_list(Student **ptrAxD);
void free_memory();

int main(void){

 	unsigned	char teachers = 0, i = 0;
	Nodo *ptrDocentes = NULL;
	Student **ptrAlumnxDoc = NULL; //Vector de punteros Student *ptrAlumnxDoc[0]; 

	printf("Write the numbers of teachers to assign: ");
	scanf("%1u",&teachers);

//	system("Pause");

	ptrDocentes = (Nodo *) malloc(sizeof(Nodo) * teachers); //Array of pointers for nodos
	ptrAlumnxDoc = (Student **) malloc(sizeof(Student) * teachers); //Array of pointers for alumns x teachers

	for(i=0; i<teachers; i++){
		printf("Docente %d\r\n", i+1);
		Nodo *nodo1 = create_nodo(ptrAlumnxDoc); //*ptrAlumnxDoc
		*(ptrDocentes + i) = *nodo1; //Location stored in array
	}

	for(i=0; i<teachers; i++)
		insert_nodo(ptrDocentes + i);
	
	show_list(ptrAlumnxDoc);

	free_memory();

	return (0);
}

Nodo *create_nodo(Student **ptrAlumnxDoc){
	/* Crea los nuevos nodos e inicializa sus miembros.
		Args:
			- Student **ptrAxD: Vector de punteros la estructura Student. 
								  Estos almacenan los punteros al header de listas de alumnos para cada profesor.
		Return:
			- Puntero al nuevo nodo.
	*/	
	char *data(); //Prototipo
	static char x=0, y=0;
	unsigned char alumns = 0, i=0;

	Nodo *new_nodo = (Nodo *) malloc(sizeof(Nodo)); //Crea nodo
	
	if(x==0)  
		new_nodo->ptrNombre = data(); //Fail, si no se lee algo antes, para el 1er nodo al nombre del profesor lee 
												//un salto de linea o algo asi.
	printf("Write the teacher's name: ");
	new_nodo->ptrNombre = data();
	printf("Write the teacher's last name: ");
	new_nodo->ptrApellido = data();
	printf("Write the teacher's age: ");
	new_nodo->ptrEdad = data();  
	printf("Write the teacher's weight: ");
	new_nodo->ptrPeso = data();

	printf("how many students does this teacher has?: ");
	scanf("%d", &alumns);
	if(x>=0){ //Lo mismo que antes, no deja ingresar nada la primera vez. El SCANF es el problema. 
		data();
		x++;
	}
	
	for(i=0; i<alumns; i++){
		Student *new_alumn = (Student *) malloc(sizeof(Student));
		
		printf("Write the Alumn's name: ");
		new_alumn->ptrNombre = data();
		new_alumn->ptrNextAlumn = NULL;
			
		if(i == 0){
			new_nodo->ptrStudent = new_alumn; //El miembro de la struct padre apunta al primer nodo de la list alumns
			*(ptrAlumnxDoc + y) = new_alumn; //Almacena la dir del inicio de la list de alumns. 
			last = new_alumn;
			y++;
		}else{
			last->ptrNextAlumn = new_alumn;
			last = new_alumn;
		}
	}
	
	new_nodo->ptrNext = NULL;

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

void show_list(Student **ptrAxD){
	/*Recorre la lista y muestra los datos de sus nodos.
		Args: 
			- Student **ptrAxD: Vector de punteros la estructura Student. 
									  Estos almacenan los punteros al header de listas de alumnos para cada profesor.
	*/
	Nodo *scroll = header;
	unsigned char i = 0, len=0;

	if(scroll == NULL){
		puts("Empty list");
		return;
	}else{
		printf("\r\nThe list is...\r\n");
		puts("[");
		while(scroll != NULL){
			puts("\t{");
			printf("\t\tNombre: %s\r\n\t\tApellido: %s\r\n\t\t", scroll->ptrNombre, scroll->ptrApellido);			
			printf("Edad: %s\r\n\t\tPeso: %s\r\n\t\t", scroll->ptrEdad, scroll->ptrPeso);			
			printf("Alumnos: [");
			while(*(ptrAxD+i) != NULL){
				len = strlen((*(ptrAxD+i))->ptrNombre);
				if((*(ptrAxD+i))->ptrNombre[len - 1] == '\n') //Eliminar saltos de linea
					(*(ptrAxD+i))->ptrNombre[len - 1] = '\0';
				printf("%s, ", (*(ptrAxD+i))->ptrNombre); //v[0+i] = ptr = &var ---> *v[0+i] == var 
				*(ptrAxD+i)= (*(ptrAxD+i))->ptrNextAlumn;
			}
			printf("]\r\n");
			puts("\t},\r\n");
			scroll = scroll->ptrNext;
			i++;
		}
		puts("]\r\n");
	}
}

void free_memory(){
	/* Libera la memoria asignada para cada nodo insertado en la lista.*/
	Nodo *scroll = header;
	
	if(scroll == NULL){
		puts("\r\nWARNING: No se han insertado nodos a la lista para liberar memoria automaticamente.");
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
		puts("\r\nMemory freed");
	}
}
