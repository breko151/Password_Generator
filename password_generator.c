#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SIZE_CHAR 100
#define PASSWORD_SIZE 20
#define MAX_CAR 95

typedef struct t_node {
    struct t_node *ptrNext;
    char page[SIZE_CHAR];
    char user[SIZE_CHAR];
    char password[SIZE_CHAR];
} User;

typedef struct {
    int size;
    User *ptr;
} Stack;

Stack *create();
void push(Stack *myStack, char *page, char *user, char *password);
void top(Stack *myStack);
void fileCreate(char *fileName, Stack *myStack);
char *passwordGen();
User *pop(Stack *myStack);

int main(int argc, char **argv) {
    char ans = 's';
    int opt = 0;
    char page[SIZE_CHAR] = " ";
    char user[SIZE_CHAR] = " ";
    char password[SIZE_CHAR] = " ";
    char fileName[SIZE_CHAR] = " ";
    Stack *usersStack = create();
    printf("Bienvenido...");
    while(ans == 's' || ans == 'S') {
        printf("\nQue desea?");
        printf("\n1. Escribir un usuario...");
        printf("\n2. Eliminar el ultimo usuario ingresado...");
        printf("\n3. Ver cual es el ultimo usuario ingresado...");
        printf("\nTu opcion: ");
        scanf("%d", &opt);
        if(opt > 0 && opt < 4) {
            fflush(stdin);
            if(opt == 1) {
                printf("\nEscribe pagina: ");
                gets(page);
                printf("\nEscribe usuario: ");
                gets(user);
                strcpy(password, passwordGen());
                push(usersStack, page, user, password);
            } else if(opt == 2) {
                User *aux = pop(usersStack);
                printf("\nLa pagina eliminada: %s", aux->page);
                printf("\nEl usuario eliminado: %s", aux->user);
                printf("\nEl password eliminado: %s", aux->password);
                free(aux);
            } else {
                top(usersStack);
            }
        } else {
            printf("\nNo una opcion viable...");
        }
        fflush(stdin);
        fflush(stdout);
        printf("\nDesea seguir escribiendo mas Usuarios [s/n]: ");
        scanf("%c", &ans);
    }
    printf("Quieres crear un archivo con los usuarios? [s/n]: ");
    fflush(stdin);
    fflush(stdout);
    scanf("%c", &ans);
    if(ans == 'S' || ans == 's') {
        printf("Nombre del archivo sin la terminacion .txt: ");
        fflush(stdin);
        gets(fileName);
        fileCreate(fileName, usersStack);
    }
    free(usersStack);
    return 0;
} 

Stack *create() {
    Stack *newStack = (Stack *) malloc(sizeof(Stack));
    if(newStack == NULL) {
        printf("\nHubo un error en la funcion create()");
        printf("\nSaldra del programa");
        exit(1);
    }
    newStack->ptr = NULL;
    newStack->size = 0;
    return newStack;
}

void push(Stack *myStack, char *page, char *user, char *password) {
    if(myStack) {
        User *newUser = (User *) malloc(sizeof(User));
        if(newUser == NULL) {
            printf("\nHubo un error en la funcion push()");
            printf("\nSaldra del programa");
            exit(1);     
        }
        newUser->ptrNext = myStack->ptr;
        strcpy(newUser->page, page);
        strcpy(newUser->user, user);
        strcpy(newUser->password, password);
        myStack->ptr = newUser;
        myStack->size++;
    }
    else {
        printf("\nHubo un error en la funcion push()");
        printf("\nSaldra del programa");
        exit(1);
    }
}

User *pop(Stack *myStack) {
    if(myStack) {
        if(myStack->size != 0) {
            User *aux = myStack->ptr;
            myStack->ptr = myStack->ptr->ptrNext;
            myStack->size--;
            return aux;
        }
    }
}

void top(Stack *myStack) {
    if(myStack) {
        printf("\nLa pagina: %s", myStack->ptr->page);
        printf("\nEl usuario: %s", myStack->ptr->user);
        printf("\nEl password: %s", myStack->ptr->password);
    }
}

char *passwordGen() {
    srand(time(NULL));
    char *car;
    char *pass;
    int i = 0;
    int aux = 0;
    car = (char *) malloc(sizeof(char) * MAX_CAR);
    pass = (char *) malloc(sizeof(char) * PASSWORD_SIZE + 1);
    if(pass == NULL) {
        printf("\nError en passwordGen()");
        printf("\nSaldra del programa");
        exit(1);      
    } 
    if(car == NULL) {
        printf("\nError en passwordGen()");
        printf("\nSaldra del programa");
        exit(1);
    }
    pass[20] = '\0';
    for(int j = 48; j < 58; i++, j++)
        car[i] = j;
    for(int j = 97; j < 123; i++, j++)
        car[i] = j;
    for(int j = 65; j < 91; i++, j++)
        car[i] = j;
    car[63] = '!';
    car[64] = 34;
    car[65] = '#';
    car[66] = '$';
    car[67] = '%';
    car[68] = '&';
    car[69] = 39;
    car[70] = '(';
    car[71] = ')';
    car[72] = '*';
    car[73] = '+';
    car[74] = ',';
    car[75] = '-';
    car[76] = '.';
    car[77] = '/';
    car[78] = ':';
    car[79] = ';';
    car[80] = '<';
    car[81] = '=';
    car[82] = '>';
    car[83] = '?';
    car[84] = '@';
    car[85] = '[';
    car[86] = 92;
    car[87] = ']';
    car[88] = '^';
    car[89] = '_';
    car[90] = '{';
    car[91] = '|';
    car[92] = '}';
    car[93] = '~';
    car[94] = 96;
    for(int k = 0; k < PASSWORD_SIZE; k++) {
        aux = rand() % MAX_CAR;
        pass[k] = car[aux];
    }
    return pass; 
}

void fileCreate(char *fileName, Stack *myStack) {
    strcat(fileName, ".txt");
    FILE *newFile = fopen(fileName, "a");
    if(newFile == NULL) {
        printf("\nError en fileCreate()");
        printf("\nSaldra del programa");
        exit(1);       
    } 
    while(myStack->size != 0) {
        User *newUser = pop(myStack);
        fprintf(newFile, "Pagina: %s\nNombre: %s\nPassword: %s\n\n", newUser->page, newUser->user, newUser->password);
        free(newUser);
    }
    printf("\nArchivo creado con exito...");
    fclose(newFile);
}