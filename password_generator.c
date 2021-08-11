#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SIZE_CHAR 100

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
User *pop(Stack *myStack);

int main(int argc, char **argv) {
    char ans = 's';
    int opt = 0;
    char page[SIZE_CHAR] = " ";
    char user[SIZE_CHAR] = " ";
    char password[SIZE_CHAR] = " ";
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
                printf("\nEscribe password: ");
                gets(password);
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