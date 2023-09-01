#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char nombre[30];
    char genero;
    int edad;
} persona;

typedef struct
{
    int valores[100];
    int posTope; //posici�n de nuevo tope, lugar en donde se almacenar� el nuevo valor
} Pila;

persona cargarPersona();
persona* crearArreglo(int validos);
int cargarArreglo(persona arreglo[], int dim);
void cargarArregloGenero (persona arr[], persona arr2[], int validos, char genero);
int cantidadGenero(persona arreglo[], int validos, char genero);
void mostrarArreglo (persona arreglo[], int validos);
void ordenarArreglo(persona arreglo[], int validos);
int posicionMenor (persona arreglo[], int posIni, int validos);
void eliminaNumero(int arreglo[], int numAEliminar);

void inicPila(Pila* p);
void apilar(Pila * p, int valor);
void mostrar(Pila * p);
void cargarPila (Pila * p);
int desapilar(Pila* p);
int tope(Pila * p);
int pilavacia(Pila * p);
void leer(Pila* p);

int main()
{

    persona arreglo[30];
    int arregloINT[30];
    char genero;
    int validos = cargarArreglo(arreglo, 30);
    int choice;
    int cantGenero;
    Pila pilita;
    Pila pilita2;
    Pila pilita3;

    printf("\nMENU:\n");
    printf("1. Filtrar por genero\n");
    printf("2. Ordenar el arreglo\n");
    printf("3. Cargar Pilas y realizar intercambio\n");
    printf("4. Realizar insercion\n");
    printf("5. Salir\n");

    printf("Seleccione una opcion: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: // Filtrar por genero
            printf("\nIngresa el genero a filtrar: ");
            fflush(stdin);
            scanf(" %c", &genero);
            cantGenero = cantidadGenero(arreglo, validos, genero);
            printf("La cantidad de ese genero es: %d\n", cantGenero);
            persona* arregloGenero = crearArreglo(validos);
            printf("\n----------ARREGLO FILTRADO----------\n");
            cargarArregloGenero(arreglo, arregloGenero, validos, genero);
            mostrarArreglo(arregloGenero, cantGenero);
            break;

        case 2: // Ordenar el arreglo
            printf("\n----------ARREGLO ORDENADO----------\n");
            ordenarArreglo(arreglo, validos);
            mostrarArreglo(arreglo, validos);
            break;

        case 3: // Cargar Pilas y realizar intercambio

            inicPila(&pilita);
            inicPila(&pilita2);
            inicPila(&pilita3);

            printf("CARGAR PILA 1: \n");
            cargarPila(&pilita);

            printf("CARGAR PILA 2: \n");
            cargarPila(&pilita2);

            // Realizar intercambio
            printf("\nRealizando intercambio de pilas...\n");
            intercaPila(&pilita, &pilita2, &pilita3);
            break;

        case 4: // Realizar insercion
            validos = cargarArr(arregloINT, 30);
            printf("ARREGLO SIN ORDENAR....\n");
            mostrarArregloINT(arregloINT, validos);
            printf("\nARREGLO ORDENADO....\n");
            insercion(arregloINT, validos);
            mostrarArregloINT(arregloINT, validos);

            break;

        case 5: //Funci�n eliminar un elemento de un arreglo.

            break;

        default:
            printf("Opcion no valida. Por favor, seleccione una opcion valida.\n");
            break;
    }

    return 0;
}

persona cargarPersona()
{

    persona aux;

    printf("\nIngresa el nombre: ");
    fflush(stdin);
    gets(aux.nombre);
    printf("\n");
    printf("Ingresa la edad: ");
    fflush(stdin);
    scanf("%d", &aux.edad);
    printf("\n");
    printf("Ingresa el genero (M o F): ");
    fflush(stdin);
    scanf("%c", &aux.genero);

    return aux;
}

int cargarArreglo(persona arreglo[], int dim)
{

    int i = 0;
    char letra = 's';

    while(i < dim && letra == 's')
    {
        arreglo[i] = cargarPersona();
        printf("\nIngresa 's' para continuar: ");
        fflush(stdin);
        scanf("%c", &letra);
        i++;
    }

    return i;
}

int cantidadGenero(persona arreglo[], int validos, char genero)
{

    int i = 0;
    int cant = 0;

    while(i < validos)
    {

        if(genero == arreglo[i].genero)
        {
            cant++;
            i++;
        }
        else
        {
            i++;
        }
    }

    return cant;
}

persona* crearArreglo(int validos)
{

    persona* arreglo = malloc(sizeof(persona) * validos);

    return arreglo;
}


void cargarArregloGenero (persona arr[], persona arr2[], int validos, char genero)
{

    int i = 0;
    int cant = 0;

    for(i = 0; i < validos; i++)
    {
        if(arr[i].genero == genero)
        {
            arr2[cant] = arr[i];
            cant++;
        }
    }
}

void mostrarArreglo (persona arreglo[], int validos)
{

    for(int i = 0; i < validos; i++)
    {

        printf("\n\n=================\n");
        printf("Nombre: %s\n", arreglo[i].nombre);
        printf("Genero: %c\n", arreglo[i].genero);
        printf("Edad: %d\n", arreglo[i].edad);
        printf("=================\n");

    }
}

void ordenarArreglo(persona arreglo[], int validos)
{
    int posmenor;
    persona aux;
    int i = 0;
    while(i < validos-1)
    {
        posmenor = posicionMenor(arreglo, i, validos);
        aux = arreglo[posmenor];
        arreglo[posmenor] = arreglo[i];
        arreglo[i] = aux;
        i++;
    }
}

int posicionMenor (persona arreglo[], int posIni, int validos)
{

    persona menor = arreglo[posIni];
    int posMenor = posIni;
    int i = posIni+1;

    while(i < validos)
    {
        if(menor.edad > arreglo[i].edad)
        {
            menor.edad = arreglo[i].edad;
            posMenor = i;

        }
        i++;
    }
    return posMenor;
}

///FUNCIONES PILAS
void inicPila(Pila* p)
{
    p->posTope = 0;
}

void apilar(Pila * p, int valor)
{
    if(p->posTope <=100)
    {
        p->valores[p->posTope] = valor;
        p->posTope++;
    }
    else
    {
        printf("\nLA PILA ESTA LLENA\n");
    }
}

void mostrar(Pila* p)
{
    int i = 0;
    printf ("\nBASE...                                                            ...TOPE\n");
    printf ("==========================================================================\n");
    while (i<p->posTope)
    {
        printf("|  %i  |", p->valores[i]);
        i++;
    }
    printf ("\n==========================================================================\n");
}

void leer(Pila* p)
{
    int valor;
    printf ("\nIngrese el valor de un numero entero \n");
    fflush(stdin);
    scanf("%i", &valor);

    apilar(p, valor);

}

void cargarPila (Pila * p)
{
    char opcion ='s';
    while (opcion =='s')
    {
        leer(p);
        printf("\nSI DESEA CONTINUAR, INGRESE ' s ' \n");
        fflush(stdin);
        scanf("%c", &opcion);
    }
}

int tope(Pila * p)
{
    return p->valores[p->posTope-1];
}

int pilavacia(Pila * p)
{
    if(p->posTope == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int desapilar(Pila* p)
{
    int pos = p->posTope - 1;
    int valor = p->valores[pos];
    if(p->posTope > 0)
    {
        p->posTope = p->posTope-1;
    }
    else
    {
        printf("\nLA PILA ESTA VACIA\n");
    }
    return valor;
}

void insercion (int arreglo[], int validos)
{

    int indiceActual = 0;
    while(indiceActual < validos-1)
    {

        insertarDato(arreglo, indiceActual, arreglo[indiceActual+1]);
        indiceActual++;

    }
}

void insertarDato(int arreglo[], int inicioBusqueda, int dato)
{
    int i = inicioBusqueda;
    while(i >= 0 && dato < arreglo[i])
    {

        arreglo[i+1] = arreglo[i];
        i--;

    }
    arreglo[i+1] = dato;
}

void pilaApila (Pila* p1, Pila* p2)
{
    while(!pilavacia(p1))
    {
        apilar(p2, desapilar(p1));
    }
    printf("\nPILITA \n");
    mostrar(p1);
    printf("\nPILITA2 \n");
    mostrar(p2);
}

void intercaPila (Pila *p1, Pila *p2, Pila *p3)
{

    while (!pilavacia(p1)||!pilavacia(p2))
    {
        if(!pilavacia(p1))
        {
            apilar(p3,desapilar (p1));
        }
        if(!pilavacia(p2))
        {
            apilar(p3,desapilar (p2));
        }
    }
    printf("PILA NUMERO 3: \n");
    mostrar(p3);
}

int cargarArr(int arreglo[],int dim)
{
    int i=0;
    char op = 's';
    while (op=='s')
    {
        printf("Ingrese el valor que quiera en el arreglo\n");
        fflush(stdin);
        scanf("%i",&arreglo[i]);

        i++;

        printf("Si desea continuar ingrese s\n");
        fflush(stdin);
        scanf("%c",&op);
    }


    return i;
}

void mostrarArregloINT (int arreglo[], int validos)
{

    for(int i = 0; i < validos; i++)
    {

        printf("|%d |", arreglo[i]);

    }
}


