#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct binary_search_tree bs_tree;

struct binary_search_tree
{
    int item;
    bs_tree *left;
    bs_tree *right;
};

bs_tree* create_bs_tree();
bs_tree* create_node_bs_tree(int item, bs_tree *left, bs_tree *right);
int is_empty(bs_tree *root);
bs_tree* generate_bs_tree(char *string, int *cont);
bs_tree* search(bs_tree *root, int *value);

int main()
{
    bs_tree *bst = create_bs_tree();

    char string[100];
    int value = 0, cont = 0;

    scanf("%[^\n]s", string);

    bst = generate_bs_tree(string, &cont);
    search(bst, &value);

    return (value != 1) ? printf("VERDADEIRO") : printf("FALSO");
}

bs_tree* create_bs_tree()
{
    return NULL;
}

bs_tree* create_node_bs_tree(int item, bs_tree *left, bs_tree *right)
{
    bs_tree *new_bt = (bs_tree*) malloc(sizeof(bs_tree));
	new_bt->item = item;
	new_bt->left = NULL;
	new_bt->right = NULL;
	return new_bt;
}

int is_empty(bs_tree *root)
{
    return (root == NULL);
}

bs_tree* generate_bs_tree(char *string, int *cont)
{
    bs_tree *bst = create_bs_tree();

    char StringValue[100];
    int StringToNumber;

    while(string[*cont] == '(')
    {
        *cont += 1;
    }

    if(string[*cont] != ')')
    {
        int i = 0;
        while(string[*cont] != '(')
        {
            StringValue[i++] = string[*cont];
            *cont += 1;
        }
        StringValue[i] = '\0';
        StringToNumber = atoi(StringValue);

        bst = create_node_bs_tree(StringToNumber, NULL, NULL);
        bst->left = generate_bs_tree(string, cont);
        bst->right = generate_bs_tree(string, cont);
    }
    *cont += 1;
    return bst;
}

bs_tree* search(bs_tree *root, int *value)
{
    if(is_empty(root))
    {
        return root;
    }

    if(root->left != NULL)
    {
        if((root->left->item) > root->item)
        {
            *value = 1;
        }
    }
    search(root->left, value);

    if(root->right != NULL)
    {
        if((root->right->item) < root->item)
        {
            *value = 1;
        }
    }
    search(root->right, value);
}
