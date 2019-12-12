#include <stdio.h>
#include <stdlib.h>

typedef struct binary_search_tree bs_tree;

struct binary_search_tree{
    int item;
    bs_tree *left;
    bs_tree *right;
};

bs_tree* create_bs_tree();
bs_tree* create_node_bs_tree(int item, bs_tree *left, bs_tree *right);
int is_empty(bs_tree *root);

bs_tree* min(bs_tree *node);
bs_tree* add(bs_tree *root, int item);
bs_tree* remove_node(bs_tree *root, int item);
bs_tree* search(bs_tree *root, int item);

void print_pre_order(bs_tree *root);
void print_in_order(bs_tree *root);
void print_post_order(bs_tree *root);

int main()
{
    bs_tree *bst = create_bs_tree();

    bst = add(bst, 5);
    bst = add(bst, 3);
    bst = add(bst, 7);
    bst = add(bst, 1);
    bst = add(bst, 4);

    bst = remove_node(bst, 1);

    printf("\nPRE ORDER \n");
    print_pre_order(bst);

    printf("\n\nIN ORDER \n");
    print_in_order(bst);

    printf("\n\nPOST ORDER \n");
    print_post_order(bst);
    printf("\n");
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

bs_tree* min(bs_tree *root)
{
	bs_tree *current = root;

	while (current->left != NULL)
    {
		current = current->left;
	}

	return current;
}

bs_tree* add(bs_tree *root, int item)
{
    if(is_empty(root))
    {
		return create_node_bs_tree(item, NULL, NULL);
	}
	if(root->item > item)
    {
		root->left = add(root->left, item);
	}
	else if(root->item < item)
    {
		root->right = add(root->right, item);
	}
	else{
		return root;
	}

	return root;
}

bs_tree* remove_node(bs_tree *root, int item)
{
    if(is_empty(root))
    {
		return root;
	}
	if(root->item > item)
    {
		root->left = remove_node(root->left, item);
	}
	else if(root->item < item)
    {
		root->right = remove_node(root->right, item);
	}
	else{
		if(root->left == NULL)
        {
			bs_tree *aux = root->right;
			free(root);
			return aux;
		}
		else if(root->right == NULL)
        {
			bs_tree *aux = root->left;
			free(root);
			return aux;
		}

		bs_tree *aux = min(root->right);
		root->item = aux->item;
		root->right = remove_node(root->right, aux->item);
	}

	return root;
}

bs_tree* search(bs_tree *root, int item)
{
    if((is_empty(root)) || (root->item == item))
    {
		return root;
	}
	else if(root->item > item)
	{
		search(root->left, item);
	}
    else{
		search(root->right, item);
	}
}

void print_pre_order(bs_tree *root)
{
    if(!is_empty(root))
    {
        printf("%d ", root->item);
        print_pre_order(root->left);
        print_pre_order(root->right);
    }
}

void print_in_order(bs_tree *root)
{
    if(!is_empty(root))
    {
        print_in_order(root->left);
        printf("%d ", root->item);
        print_in_order(root->right);
    }
}

void print_post_order(bs_tree *root)
{
    if(!is_empty(root))
    {
        print_post_order(root->left);
        print_post_order(root->right);
        printf("%d ", root->item);
    }
}
