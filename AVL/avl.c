#include <stdio.h>
#include <stdlib.h>

typedef struct binary_tree b_tree;

struct binary_tree{
    int item;
    int height;
    b_tree* left;
    b_tree* right;
};

b_tree* create_b_tree();
b_tree* create_node_b_tree(int item, b_tree *left, b_tree *right);

int is_empty(b_tree *root);
int max(int a, int b);
int height(b_tree *bt);
int balance_factor(b_tree *bt);

b_tree *rotate_left(b_tree *ubt);
b_tree *rotate_right(b_tree *ubt);

b_tree* add(b_tree *root, int item);
b_tree* min(b_tree *root);
b_tree* remove_node(b_tree *root, int item);
b_tree* search(b_tree *bt, int item);

void print_pre_order(b_tree *bt);
void print_in_order(b_tree *bt);
void print_post_order(b_tree *bt);

int main()
{
    b_tree *bt = create_b_tree();

    bt = add(bt, 4);
    bt = add(bt, 5);
    bt = add(bt, 7);
    bt = add(bt, 2);
    bt = add(bt, 9);
    bt = remove_node(bt, 2);
    bt = add(bt, 12);

    printf("AVL\n");
    printf("\nPRE ORDER \n");
    print_pre_order(bt);

    printf("\n\nIN ORDER \n");
    print_in_order(bt);

    printf("\n\nPOST ORDER \n");
    print_post_order(bt);
    printf("\n");
}

b_tree* create_b_tree()
{
    return NULL;
}

b_tree* create_node_b_tree(int item, b_tree *left, b_tree *right)
{
    b_tree *new_bt = (b_tree*) malloc(sizeof(b_tree));
	new_bt->item = item;
	new_bt->left = NULL;
	new_bt->right = NULL;
	new_bt->height = 1;
	return new_bt;
}

int is_empty(b_tree *root)
{
    return (root == NULL);
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int height(b_tree *bt)
{
	if(bt == NULL)
    {
		return -1;
	}
    return 1 + max(height(bt->left), height(bt->right));
}

int balance_factor(b_tree *bt)
{
	if(bt == NULL)
    {
		return 0;
	}
	return height(bt->left) - height(bt->right);
}

b_tree *rotate_left(b_tree *ubt)
{
	b_tree *subtree = ubt->right;
	b_tree *left_subtree = subtree->left;

	subtree->left = ubt;
	ubt->right = left_subtree;

	ubt->height = max(height(ubt->left), height(ubt->right)) + 1;
	subtree->height = max(height(subtree->left), height(subtree->right)) + 1;

	return subtree;
}

b_tree *rotate_right(b_tree *ubt)
{
	b_tree *subtree = ubt->left;
	b_tree *right_subtree = subtree->right;

	subtree->right = ubt;
	ubt->left = right_subtree;

	ubt->height = max(height(ubt->left), height(ubt->right)) + 1;
	subtree->height = max(height(subtree->left), height(subtree->right)) + 1;

	return subtree;
}

b_tree* add(b_tree *root, int item)
{
    if(is_empty(root))
    {
		return create_node_b_tree(item, NULL, NULL);
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

	root->height = height(root);
	int balance = balance_factor(root);

	 // Left Left
    if(balance > 1 && item < root->left->item)
    {
    	return rotate_right(root);
    }
    // Right Right
    if(balance < -1 && item > root->right->item)
    {
    	return rotate_left(root);
    }
    // Left Right
    if(balance > 1 && item > root->left->item)
    {
    	root->left = rotate_left(root->left);
    	return rotate_right(root);
    }
    // Right Left
    if(balance < -1 && item < root->right->item)
    {
    	root->right = rotate_right(root->right);
    	return rotate_left(root);
    }
    return root;
}

b_tree* min(b_tree *root)
{
	b_tree *current = root;

	while(current->left != NULL)
    {
		current = current->left;
	}

	return current;
}

b_tree* remove_node(b_tree *root, int item)
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
			b_tree *aux = root->right;
			free(root);
			return aux;
		}
		else if(root->right == NULL)
        {
			b_tree *aux = root->left;
			free(root);
			return aux;
		}

		b_tree *aux = min(root->right);
		root->item = aux->item;
		root->right = remove_node(root->right, aux->item);
	}

	if(is_empty(root))
    {
		return root;
	}

	root->height = height(root);
    int balance = balance_factor(root);

    // Left Left
	if(balance > 1 && balance_factor(root->left) >= 0)
    {
		return rotate_right(root);
	}
	// Right Right
	if(balance < -1 && balance_factor(root->right) <= 0)
    {
		return rotate_left(root);
	}
	// Left Right
	if(balance > 1 && balance_factor(root->left) < 0)
	{
		root->left =  rotate_left(root->left);
		return rotate_right(root);
	}
	// Right Left
	if (balance < -1 && balance_factor(root->right) > 0)
    {
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}

	return root;
}

b_tree* search(b_tree *root, int item)
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

void print_pre_order(b_tree *root)
{
    if(!is_empty(root))
    {
        printf("%d ", root->item);
        print_pre_order(root->left);
        print_pre_order(root->right);
    }
}

void print_in_order(b_tree *root)
{
    if(!is_empty(root))
    {
        print_in_order(root->left);
        printf("%d ", root->item);
        print_in_order(root->right);
    }
}

void print_post_order(b_tree *root)
{
    if(!is_empty(root))
    {
        print_post_order(root->left);
        print_post_order(root->right);
        printf("%d ", root->item);
    }
}
