#include "shell.h"
/**
 * oadd_nod - inserts a new node at the beginning of a list
 * @head: Address of the pointer to the first (head) node
 * @str: String data to be stored in the new node
 * @Numbre: Index of the node, utilized for history tracking
 * Return: The total number of nodes in the list after insertion
 */
list_t *oadd_nod(list_t **head, const char *str, int Numbre)
{
	list_t *Nouveau_Tete;

	if (!head)
	{
		return (NULL);
	}
	Nouveau_Tete = malloc(sizeof(list_t));
	if (!Nouveau_Tete)
	{
		return (NULL);
	}
	o_memse((void *)Nouveau_Tete, 0, sizeof(list_t));
	Nouveau_Tete->num = Numbre;
	if (str)
	{
		Nouveau_Tete->str = _strdup(str);
		if (!Nouveau_Tete->str)
		{
			free(Nouveau_Tete);
			return (NULL);
		}
	}
	Nouveau_Tete->next = *head;
	*head = Nouveau_Tete;
	return (Nouveau_Tete);
}
/**
 * ofree_lis - get free to all
 * @tete_ptr: add to head node
 * Return: none
 */
void ofree_lis(list_t **tete_ptr)
{
	list_t *node, *n_node, *head;

	if (!tete_ptr || !*tete_ptr)
	{
		return;
	}
	head = *tete_ptr;
	node = head;
	while (node)
	{
		n_node = node->next;
		free(node->str);
		free(node);
		node = n_node;
	}
	*tete_ptr = NULL;
}
/**
 * oadd_node_en - appends a node to the tail of the list
 * @head: Address of the pointer to the head node
 * @str: Content of the 'str' field in the node
 * @Numbre: Index of the node, utilized for historical purposes
 * Return: The total count of nodes in the list after the addition
 */
list_t *oadd_node_en(list_t **head, const char *str, int Numbre)
{
	list_t *nouvelle_node, *node;

	if (!head)
	{
		return (NULL);
	}
	node = *head;
	nouvelle_node = malloc(sizeof(list_t));
	if (!nouvelle_node)
		return (NULL); /*retuen this*/
	o_memse((void *)nouvelle_node, 0, sizeof(list_t));
	nouvelle_node->num = Numbre;
	if (str)
	{
		nouvelle_node->str = _strdup(str);
		if (!nouvelle_node->str)
		{
			free(nouvelle_node);
			return (NULL);
		}
	}
	if (node) /*valid node*/
	{
		while (node->next)
			node = node->next;
		node->next = nouvelle_node;
	}
	else
		*head = nouvelle_node;
	return (nouvelle_node);
}
/**
 * oprint_list_st - outputs the 'str' elements from
 * each node of a list_t linked list
 * @head: Pointer to the initial node of the list
 * Return: The number of nodes in the list
 */
size_t oprint_list_st(const list_t *head)
{
	size_t i;

	for (i = 0; head; i++)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
	}
	return (i);
}
/**
 * odelete_node_at_inde - removes the node at
 * a specified index from the list
 * @tete: Address of the pointer
 * @index: Position of the node to be deleted
 * Return: 1 if deletion is successful, 0 if it fails
 */
int odelete_node_at_inde(list_t **tete, unsigned int index)
{
	unsigned int i = 0;
	list_t *node, *nodeprecedent;

	if (!tete || !*tete)
	{
		return (0);
	}
	if (!index)
	{
		node = *tete;
		*tete = (*tete)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *tete;
	while (node)
	{
		if (i == index)
		{
			nodeprecedent->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		nodeprecedent = node;
		node = node->next;
	}
	return (0);
}
