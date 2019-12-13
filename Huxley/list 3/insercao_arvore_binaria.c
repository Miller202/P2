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
bs_tree* add(bs_tree *root, int item);
void print_pre_order(bs_tree *root);

int main()
{
    bs_tree *bst = create_bs_tree();

    int item;
    while(scanf("%d", &item) != EOF)
    {
        printf("----\nAdicionando %d\n  ", item);
        bst = add(bst, item);
        print_pre_order(bst);
        printf("\n");
    }
    printf("----");
}

bs_tree* create_bs_tree()
{
    return NULL;
}

bs_tree* create_node_bs_tree(int item, bs_tree *left, bs_tree *right)
{
    bs_tree *new_bt = (bs_tree*) malloc(sizeof(bs_tree));
	new_bt->item = item;
	new_bt->left = left;
	new_bt->right = right;
	return new_bt;
}

int is_empty(bs_tree *root)
{
    return (root == NULL);
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
	else if(root->item <= item)
    {
		root->right = add(root->right, item);
	}

	return root;
}

void print_pre_order(bs_tree *root)
{
    if(!is_empty(root))
    {
        printf(" ( ");
        printf("%d ", root->item);

        if(root->left != NULL)
        {
            print_pre_order(root->left);
        }
        else{
            printf(" () ");
        }

        if(root->right != NULL)
        {
            print_pre_order(root->right);
        }
        else{
            printf(" () ");
        }

        printf(") ");
    }
}
