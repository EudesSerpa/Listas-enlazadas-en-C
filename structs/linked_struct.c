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
void show_list(Student **ptrAxD, FILE *ptrFP);
void free_memory();

int main(void){

 	unsigned	char teachers = 0, i = 0;
	Nodo *ptrDocentes = NULL; //Array de tipo Nodo.
	Student **ptrAlumnxDoc = NULL; //Array de punteros: Student *ptrAlumnxDoc[]; 	
	FILE *ptrFile = NULL;
	
	if((ptrFile = fopen("Leidy.json", "w")) == NULL){
		printf("ERROR: File not created/loaded\r\n");
		return (1);
	}else
		printf("File created/loaded\r\n");

	printf("Write the numbers of teachers to assign: ");
	scanf("%u",&teachers);
	while(getchar() != '\n'); //Limpiar buffer

	ptrDocentes = (Nodo *) malloc(sizeof(Nodo) * teachers); //Array de tipo Nodo
	ptrAlumnxDoc = (Student **) malloc(sizeof(Student) * teachers);

	for(i=0; i<teachers; i++){ //Creacion e inicializacion de nodos
		printf("Docente %d\r\n", i+1);
		Nodo *nodo1 = create_nodo(ptrAlumnxDoc); 
		*(ptrDocentes + i) = *nodo1; //Almacena ubicacion del nodo en el array
	}

	for(i=0; i<teachers; i++) //Insercion (al final) de nodos
		append(ptrDocentes + i);

	show_list(ptrAlumnxDoc, ptrFile);

	fclose(ptrFile);
	free_memory();

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
	while(getchar() != '\n'); //Limpiar buffer 
	
	for(i=0; i<alumns; i++){
		Student *new_alumn = (Student *) malloc(sizeof(Student)); //Crear nodo para alumnos
		
		printf("Write the Alumn's name: ");
		new_alumn->ptrNombre = data(); //Inicializar nodo del alumno.
		new_alumn->ptrNextAlumn = NULL;
			
		if(i == 0){//First alumn (first nodo)
			new_nodo->ptrStudent = new_alumn; //Miembro de struct padre apunta al primer nodo de list alumns
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
	else{ 
		len = strlen(ptrName);
		if(ptrName[len - 1] == '\n') //Elimina saltos de linea.
			ptrName[len - 1] = '\0';
		return ptrName;
	}
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
	/* Recorre la lista de docentes y de sus estudiantes para mostrar los datos de sus nodos.
	 * Escribe listas en el archivo abierto/creado previamente.
		Args: 
			- Student **ptrAxD: Vector de punteros a la estructura Student. 
					(Se almacenan los punteros a los headers de las listas de alumnos para cada profesor)
			- FILE *ptrFP: Puntero al descriptor de archivo abierto/creado por fopen.
	*/
	Nodo *scroll = header;
	Student *ptrA = NULL;
	unsigned char i = 0, len=0, amount=0;

	if(scroll == NULL){
		puts("Empty list");
		return;
	}else{
		fputs("[\n", ptrFP);
		while(scroll != NULL){//Escribe en archivo los datos de los nodos doc en format JSON (parecido)
			fputs("\t{\r\n\t\t", ptrFP);
			
			fprintf(ptrFP, "'Nombre': '%s',\r\n\t\t'Apellido': '%s',\r\n", scroll->ptrNombre, scroll->ptrApellido);
			
			fprintf(ptrFP, "\t\t'Edad': '%s',\r\n\t\t'Peso': '%s',\r\n\t\t", scroll->ptrEdad, scroll->ptrPeso);
			
			fputs("'Alumnos': [", ptrFP);
			
			ptrA = *(ptrAxD+i); //Almacena pos de inicio de lista
			while(*(ptrAxD+i) != NULL){ //Conocer cantidad de alumnos para el docente
				amount++;
				*(ptrAxD+i) = (*(ptrAxD+i))->ptrNextAlumn;
			}
			
			*(ptrAxD+i) = ptrA; //Vuelve a la cabeza de la list
			while(*(ptrAxD+i) != NULL){//Recorrer nodos de Alumnos y se escriben en el archivo.
				if(len == amount-1){
					//Ultimo estudiante (Solo para quitar la , final)
					fprintf(ptrFP, "'%s'", (*(ptrAxD+i))->ptrNombre);
				}else{
					fprintf(ptrFP, "'%s', ", (*(ptrAxD+i))->ptrNombre);
				}
				
				len++;
				*(ptrAxD+i)= (*(ptrAxD+i))->ptrNextAlumn;
			}

			fputs("]\r\n", ptrFP);
			fputs("\t},\r\n", ptrFP);
			scroll = scroll->ptrNext;
			i++;
		}

		fputs("]\r\n", ptrFP);
		amount = i = 0; //Restart 
	}
}

void free_memory(){
	/* 
		Libera la memoria asignada para la lista de docentes
	*/
	void free_student(Nodo *scroll); 
	Nodo *scroll = header;
	
	if(scroll == NULL){
		puts("\r\nWARNING: No se han insertado nodos a la lista para liberar memoria");
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
		puts("\r\nWARNING: No se han insertado nodos a la lista para liberar memoria");
		return;
	}else{
		free(scroll->ptrStudent);
		header = NULL;
		footer = NULL;
		puts("Memory students structs freed\r\n");
	}
}
