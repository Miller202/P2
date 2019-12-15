#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;
typedef struct stack stack;

struct node{
    char item;
    node *next;
};

struct stack{
    node *top;
};

node *create_stack_node(char item);
stack *create_stack();
int is_empty(stack *stack);
void push(stack *stack, char item);
int pop(stack *stack);
char peek(stack *stack);
void balance(stack *stack, int size, char string[size], int i);

int main()
{
    stack *stack = create_stack();

    int i=0, quant, size;
    scanf("%d", &quant);

    char string[100];
    getchar();

    while (quant != 0)
    {
        gets(string);
        size = strlen(string);
        balance(stack, size, string, i);

        while(stack->top != NULL)
        {
            pop(stack);
        }
        quant--;
    }
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

int is_empty(stack *stack)
{
    return (stack->top == NULL);
}

void push(stack *stack, char item)
{
    node *new_top = create_stack_node(item);

    if (is_empty(stack))
    {
        stack->top = new_top;
    }
    else{
        new_top->next = stack->top;
        stack->top = new_top;
    }
}

int pop(stack *stack)
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

char peek(stack *stack)
{
    if (!is_empty(stack))
    {
        return stack->top->item;
    }
}

void balance(stack *stack, int size, char string[size], int i)
{
    if (i == size)
    {
        if (is_empty(stack))
        {
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
        return;
    }

    if ((is_empty(stack) && string[i] == ')') || (is_empty(stack) && string[i] == ']'))
    {
        printf("No\n");
        return;
    }
    else if ((string[i] == '(') || (string[i] == '['))
    {
        push(stack, string[i]);
    }
    else if ((peek(stack) == '(' && string[i] == ')') || (peek(stack) == '[' && string[i] == ']'))
    {
        pop(stack);
    }
    balance(stack, size, string, i+1);
}
