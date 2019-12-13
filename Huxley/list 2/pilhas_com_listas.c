#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;
typedef struct stack stack;
typedef struct stack_node stack_node;

struct node
{
    int item;
    node *next;
};

struct stack
{
    stack_node *top;
};

struct stack_node
{
    node *head;
    stack_node *next;
};

node* create_linked_list();
node* node_add(int item);
node* end_add(node *head, int item);

stack* create_stack();
stack_node *create_stack_node();
int is_empty(stack *stack);
void push(stack *stack, node *head);
int pop(stack *stack);
void print_stack_list(node *head, int i);

int main()
{
    stack *new_stack = create_stack();

    char command[30];

    while (scanf("%s", command) != EOF)
    {
        if (strcmp(command, "PUSH") == 0)
        {
            node *head = create_linked_list();
            while (1)
            {
                int n;
                char aux;
                scanf("%d%c", &n, &aux);

                head = end_add(head, n);

                if (aux == '\n')
                {
                    break;
                }
            }
            push(new_stack, head);
        }
        else if(strcmp(command, "POP") == 0)
        {
            pop(new_stack);
        }
    }
}

node* create_linked_list()
{
    return NULL;
}

node* node_add(int item)
{
	node *head = (node*) malloc(sizeof(node));
	head->item = item;
	head->next = NULL;
	return head;
}

node* end_add(node *head, int item)
{
	node *new_node = node_add(item);
	node *aux = head;

	if (head == NULL)
	{
		return new_node;
	}

	while (aux->next != NULL)
	{
		aux = aux->next;
	}

	aux->next = new_node;
	return head;
}

stack* create_stack()
{
    stack *new_stack = (stack*) malloc(sizeof(stack));
    new_stack->top = NULL;
    return new_stack;
}

stack_node *create_stack_node()
{
    stack_node *new_stack_node = (stack_node*) malloc(sizeof(stack_node));
    new_stack_node->head = NULL;
    new_stack_node->next = NULL;
    return new_stack_node;
}

int is_empty(stack *stack)
{
    return (stack->top == NULL);
}

void push(stack *stack, node *head)
{
    stack_node *new_top = create_stack_node();
    new_top->head = head;

    if (!is_empty(stack))
    {
        new_top->next = stack->top;
        stack->top = new_top;
    }
    else{
        stack->top = new_top;
        return;
    }
}

int pop(stack *stack)
{
    if (!is_empty(stack))
    {
        node *new_node = stack->top->head;
        print_stack_list(new_node, 0);
        stack->top = stack->top->next;
        free(new_node);
        return ;
    }
    printf("EMPTY STACK\n");
    return;
}

void print_stack_list(node *head, int n)
{
    if (head == NULL)
    {
        printf("\n");
        return;
    }
    if (n != 0)
    {
        printf(" %d", head->item);
    }
    else{
        printf("%d", head->item);
    }
    print_stack_list(head->next, 1);
}
