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

Nodo *header = NULL; //Punteros lista doc
Nodo *footer = NULL;
Student *last = NULL; //Punteros lista alumn

Nodo *create_nodo(Student **ptrAlumnxDoc);
void append(Nodo *nodo);
void show_list(Student **ptrAxD, FILE *ptrFP){
void write_file(FILE *ptrFP);
void free_memory();

int main(void){

 	unsigned	char teachers = 0, i = 0;
	Nodo *ptrDocentes = NULL; //Array de tipo Nodo.
	Student **ptrAlumnxDoc = NULL; //Array de punteros: Student *ptrAlumnxDoc[0]; 	
	FILE *ptrFile = NULL;
	
	if((ptrFile = fopen("Leidy.txt", "a")) == NULL){
		printf("ERROR: File not created/loaded\r\n");
		return (1);
	}else
		printf("File created/loaded\r\n");
		//write_file(ptrFile);

	printf("Write the numbers of teachers to assign: ");
	scanf("%u",&teachers);
	while(getchar() != '\n'); //Limpiar buffer (Sino, se toma un \n para el 1er nombre del 1er profesor)
	ptrDocentes = (Nodo *) malloc(sizeof(Nodo) * teachers); //Array de tipo Nodo
	ptrAlumnxDoc = (Student **) malloc(sizeof(Student) * teachers);

	for(i=0; i<teachers; i++){
		printf("Docente %d\r\n", i+1);
		Nodo *nodo1 = create_nodo(ptrAlumnxDoc); 
		*(ptrDocentes + i) = *nodo1; //Location stored in array
	}

	for(i=0; i<teachers; i++)
		append(ptrDocentes + i);

	show_list(ptrAlumnxDoc, ptrFile);

	free_memory();
	fclose(ptrFile);

	return (0);
}

Nodo *create_nodo(Student **ptrAlumnxDoc){
	/* Crea los nuevos nodos e inicializa sus miembros.
		Args:
			- Student **ptrAxD: Vector de punteros la estructura Student. 
								     Almacena los punteros al header de cada list de alumnos por profesor.
		Return:
			- Puntero al nodo creado.
	*/	
	char *data(); //Prototipo
	static char y=0;
	unsigned char alumns = 0, i=0;

	Nodo *new_nodo = (Nodo *) malloc(sizeof(Nodo)); //Crea nodo
	
	printf("Write the teacher's name: ");
	new_nodo->ptrNombre = data();
	printf("Write the teacher's last name: ");
	new_nodo->ptrApellido = data();
	printf("Write the teacher's age: ");
	new_nodo->ptrEdad = data();  
	printf("Write the teacher's weight: ");
	new_nodo->ptrPeso = data();

	printf("how many students does this teacher has?: ");
	scanf("%u", &alumns);
	while(getchar() != '\n'); //Limpiar buffer (Sino, se toma un \n para el 1er nombre del 1er Alumn.)
	
	for(i=0; i<alumns; i++){
		Student *new_alumn = (Student *) malloc(sizeof(Student));
		
		printf("Write the Alumn's name: ");
		new_alumn->ptrNombre = data(); //Inicializar nodo del alumno.
		new_alumn->ptrNextAlumn = NULL;
			
		if(i == 0){//First alumn (first nodo)
			new_nodo->ptrStudent = new_alumn; //El miembro de la struct padre apunta al primer nodo de la list alumns
			*(ptrAlumnxDoc + y) = new_alumn; //Almacena la dir del inicio de la list de alumns. 
			last = new_alumn;
			y++;
		}else{//Others alumns. insert to end.
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
	   		Puntero al texto leido
	*/
	unsigned char len = 0;
	size_t n_bytes = 0;
	size_t size_line = 0;
	char *ptrName = NULL;

	if ((size_line = getline(&ptrName, &n_bytes, stdin)) == -1)
		puts("ERROR: EOF found wihtout reading any byte / Others errors");
	else 
		len = strlen(ptrName);
		if(ptrName[len - 1] == '\n') //Elimina saltos de linea.
			ptrName[len - 1] = '\0';
		
		//printf("%s", ptrName);
		return ptrName;
}

void append(Nodo *nodo){ 
	/* Inserta un nodo al final de la lista de docentes.
		Args:
   			- Nodo *nodo: Puntero al tipo de dato Nodo. Nodo a insertar.		
	*/
	if(header == NULL){ //First nodo. Es la cabeza y fin de la lista
		header = nodo;
		footer = nodo;
	}else{				//Others nodos.
		footer->ptrNext = nodo; //Insercion siempre al final
		footer = nodo;
	}
}

void show_list(Student **ptrAxD, FILE *ptrFP){
	/* Recorre la lista de docentes y de sus estudiantes para muestrar los datos de sus nodos.
		Args: 
			- Student **ptrAxD: Vector de punteros la estructura Student. 
									  Almacenan los punteros al header de listas de alumnos para cada profesor.
	*/
	Nodo *scroll = header;
	unsigned char i = 0, len=0;

	if(scroll == NULL){
		puts("Empty list");
		return;
	}else{
		printf("\r\nThe list is...\r\n");
		//fwrite
		puts("[");
		while(scroll != NULL){
			printf("\t{\r\n\t\t");
			printf("'Nombre': '%s',\r\n\t\t'Apellido': '%s',\r\n", scroll->ptrNombre, scroll->ptrApellido);
			printf("\t\t'Edad': %s,\r\n\t\t'Peso': %s,\r\n\t\t", scroll->ptrEdad, scroll->ptrPeso);			
			printf("'Alumnos': [");
			while(*(ptrAxD+i) != NULL){
				printf("'%s', ", (*(ptrAxD+i))->ptrNombre); //v[0+i] = ptr = &var ---> *v[0+i] == var 
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

void write_file(FILE *ptrFP){
	
	puts("File created/loaded");

}

void free_memory(){
	/* 
		Libera la memoria asignada para la lista de docentes
	*/
	void free_student(Nodo *scroll); 
	Nodo *scroll = header;
	
	if(scroll == NULL){
		puts("\r\nWARNING: No se han insertado nodos a la lista para liberar memoria automaticamente.");
		return;
	}else{
		while(scroll != NULL){
			header = scroll->ptrNext; //Update header of list
			free_student(scroll);
			free(scroll);
			scroll = header;
		}
		header = NULL;
		footer = NULL;
		puts("\r\nMemory teachers structs freed");
	}
}

void free_student(Nodo *scroll){
	/* 
		Libera la memoria asignada para la lista de estudiantes
	*/
	if(scroll == NULL){
		puts("\r\nWARNING: No se han insertado nodos a la lista para liberar memoria automaticamente.");
		return;
	}else{
		free(scroll->ptrStudent);
		header = NULL;
		footer = NULL;
		puts("Memory students structs freed\r\n");
	}
}
