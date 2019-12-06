#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;
typedef struct stack stack;

struct node
{
    char item;
    node *next;
};
struct stack
{
    char item;
    node *next;
    stack *top;
};

node *create_node(char item);
stack *create_stack();
void push(stack *stack, char item);
int pop(stack *stack);
char peek(stack *stack);
int is_empty(stack *stack);

int main()
{
	stack *new_stack = create_stack(); // declarar uma pilha
  	//chamada de funcoes
	return 0;
}

node *create_stack_node(char item)
{
    node* new_node = (node*) malloc(sizeof(node));
    new_node -> item = item;
    new_node -> next = NULL;
    return new_node;
}

stack *create_stack()
{
    stack *new_stack = (stack*) malloc(sizeof(stack));
    new_stack->top = NULL;
    return new_stack;
}

void push(stack *stack, char item)   //empilhar
{
    node *new_top = create_stack_node(item);

    if (!is_empty(stack))
    {
        new_top->next = stack->top;
        stack->top = new_top;
    }
    else{
        stack->top = new_top;
    }
}

int pop(stack *stack) //desempilhar
{
    if (!is_empty(stack))
    {
        node *new_node = stack->top;
        stack->top = stack->top->next;
        new_node->next = NULL;
        free(new_node);
        return 1;
    }
    return 0;
}

char peek(stack *stack) //imprimir elemento da pilha
{
    if (!is_empty(stack))
    {
        return stack->top->item;
    }
}

int is_empty(stack *stack)
{
    if(stack->top == NULL)
    {
        return;
    }
}
