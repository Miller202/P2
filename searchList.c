node* search(node *head, int item) //procurar algum elemento em uma lista
{
    while (head != NULL)
    {
        if (head -> item == item)
        {
            return head;
        }
        head = head -> next;
    }
    return NULL;
}
