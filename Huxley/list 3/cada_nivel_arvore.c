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
int is_empty(b_tree *bt);
b_tree* construct_b_tree(b_tree *bt, int *value, int *left_child, int *right_child, int k);
void tree_level(int aux, b_tree *bt);
void compare_tree_values(b_tree *bt, int *small_child, int *big_child, int *level);

int main()
{
    int i, n;
    scanf("%d", &n);

    int value[n], left_child[n], right_child[n];
    for(i = 0; i < n; i++)
    {
        scanf("%d %d %d", &value[i], &left_child[i], &right_child[i]);
    }

    b_tree *bt = create_b_tree();
    bt = construct_b_tree(bt, value, left_child, right_child, 0);

    int level = 0, small_child[n], big_child[n];
    for(i = 0; i < n; i++)
    {
        small_child[i] = (1 << 20);
        big_child[i] = -(1 << 20);
    }

    tree_level(-1, bt);
    compare_tree_values(bt, small_child, big_child, &level);

    if(!is_empty(bt))
    {
        level++;
    }
    for(i = 0; i < level; i++)
    {
        printf("Nivel %d: Maior = %d, Menor = %d\n", i+1, big_child[i], small_child[i]);
    }
}

b_tree* create_b_tree()
{
    return NULL;
}

b_tree* create_node_b_tree(int item, b_tree *left, b_tree *right)
{
    b_tree *new_bt = (b_tree*) malloc(sizeof(b_tree));
	new_bt->item = item;
	new_bt->height = 0;
	new_bt->left = left;
	new_bt->right = right;
	return new_bt;
}

int is_empty(b_tree *bt)
{
    return (bt == NULL);
}

b_tree* construct_b_tree(b_tree *bt, int *value, int *left_child, int *right_child, int k)
{
    if(k != -1)
    {
        int l = construct_b_tree(bt, value, left_child, right_child, left_child[k]);
        int r = construct_b_tree(bt, value, left_child, right_child, right_child[k]);
        return create_node_b_tree(value[k], l, r);
    }
    return NULL;
}

void tree_level(int aux, b_tree *bt)
{
    if(!is_empty(bt))
    {
        bt->height = aux + 1;
        tree_level(bt->height, bt->left);
        tree_level(bt->height, bt->right);
    }
}

void compare_tree_values(b_tree *bt, int *small_child, int *big_child, int *level)
{
    if(!is_empty(bt))
    {
        if(small_child[bt->height] > bt->item)
        {
            small_child[bt->height] = bt->item;
        }
        if(big_child[bt->height] < bt->item)
        {
            big_child[bt->height] = bt->item;
        }
        if(*level < bt->height)
        {
            *level = bt->height;
        }
        compare_tree_values(bt->left, small_child, big_child, level);
        compare_tree_values(bt->right, small_child, big_child, level);
    }
}
