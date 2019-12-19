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
    int size;
    node *top;
};

stack *create_stack();
node *stack_add(stack *stack, char item);
void push(stack *stack, char item);
int pop(stack *stack);
void reset(stack *stack);

int main()
{
    stack *front = create_stack();
    stack *back = create_stack();

    front->size = 0;
    back->size = -1;

    char action[20];

    while(scanf("%s", action) != EOF)
    {
        if(strcmp(action, "ENTER") == 0)
        {
            push(back, action);
            reset(front);
        }
        else if(strcmp(action, "BACK") == 0)
        {
            push(front, action);
            pop(back);
        }
        else if(strcmp(action, "FORWARD") == 0)
        {
            push(back, action);
            pop(front);
        }
    }

    printf("BACK: %d\nFORWARD: %d\n", back->size, front->size);
}

stack *create_stack()
{
    stack *new_stack = (stack*) malloc(sizeof(stack));
    new_stack->top = NULL;
    new_stack->size = 0;
    return new_stack;
}

node *stack_add(stack *stack, char item)
{
    node* new_node = (node*) malloc(sizeof(node));
    strcpy(new_node->item, item);
    new_node->next = stack;
    return new_node;
}

void push(stack *stack, char item)
{
    node *new_node = (node*)malloc(sizeof(node));

    if(stack->top != NULL)
    {
        new_node->next = stack->top;
        stack->top = new_node;
        stack->size = stack->size + 1;
    }
    else{
        stack->top = new_node;
        stack->size = stack->size + 1;
    }
}

int pop(stack *stack)
{
    if (stack->size != 0)
    {
        node *new_node = stack->top;
        stack->top = stack->top->next;
        new_node->next = NULL;
        free(new_node);
        stack->size = stack->size - 1;
    }
    return;
}

void reset(stack *stack)
{
    if (stack->top != NULL)
    {
        node *new_node = stack->top;
        stack->top = stack->top->next;
        free(new_node);
        stack->size = stack->size - 1;
        reset(stack);
    }
    return;
}
