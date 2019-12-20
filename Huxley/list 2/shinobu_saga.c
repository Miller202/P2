#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Armazena o primeiro item da fila
typedef struct _stack STACK;

//Armazena o conteudo do no e um ponteiro para o proximo no da fila
typedef struct _node NODE;

struct _stack
{
    NODE* head;
};
struct _node
{
    int element;
    NODE* next;
};

//Cria uma stack com o a head NULL
STACK* Create_stack();

//Recebe um elemento e cria e retorna um novo node
// com o elemento passado
NODE* create_node(int element);

//Verifica se a pilha esta vazia
int IS_EMPTY(STACK* stack);

//Recebe uma pilha e Retorna o elemento que esta no topo da fila
int POP(STACK* stack);

//Recebe uma pilha e um inteiro e retorna a nova pilha
//Adiciona um novo node no topo da pilha
void PUSH(STACK* stack, int element);

//Recebe a pilha e a operacao a ser feita
//faz a operacao da calculadora
void result(STACK* stack, char operation);

//Recebe uma pilha vazia e quantas strings serao lidas
//Le as n strings que vao seguir e resolve as expressoes
void Calculadora(STACK* calculadora, int size);

int main()
{
    STACK* calculadora = Create_stack();
    int k;
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 1: %d\n", POP(calculadora));
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 2: %d\n", POP(calculadora));

}
//Insira o código aqui

STACK* Create_stack()
{
    STACK *stack = (STACK*) malloc(sizeof(STACK));
    stack->head = NULL;
    return stack;
}

NODE* create_node(int element)
{
    NODE *node = (NODE*) malloc(sizeof(NODE));
    node->element = element;
    node->next = NULL;
    return node;
}

int IS_EMPTY(STACK* stack)
{
    return (stack->head == NULL);
}

int POP(STACK* stack)
{
    if (!IS_EMPTY(stack))
    {
        int item;
        NODE *node = stack->head;

        stack->head = stack->head->next;
        node->next = NULL;
        item = node->element;

        free(node);
        return item;
    }
}

void PUSH(STACK* stack, int element)
{
    NODE *top = create_node(element);
    top->next = stack->head;
    stack->head = top;
}

void result(STACK* stack, char operation)
{
    int value_1, value_2, calc;

    if (operation == '+')
    {
        value_1 = POP(stack);
        value_2 = POP(stack);
        calc = value_2 + value_1;
        PUSH(stack, calc);
    }
    else if (operation == '-')
    {
        value_1 = POP(stack);
        value_2 = POP(stack);
        calc = value_2 - value_1;
        PUSH(stack, calc);
    }
    else if (operation == '*')
    {
        value_1 = POP(stack);
        value_2 = POP(stack);
        calc = value_2 * value_1;
        PUSH(stack, calc);
    }
    else if (operation == '/')
    {
        value_1 = POP(stack);
        value_2 = POP(stack);
        calc = value_2 / value_1;
        PUSH(stack, calc);
    }
}

void Calculadora(STACK* calculadora, int size)
{
    char string[5];

    while(size > 0)
    {
        fflush(stdin);
        scanf("%s", string);

        if ((string[0] == '+') || (string[0] == '-') || (string[0] == '*') || (string[0] == '/'))
        {
            result(calculadora, string[0]);
        }
        else{
            int string_number = 0;
            string_number = atoi(string);
            PUSH(calculadora, string_number);
        }
        size--;
    }
}
