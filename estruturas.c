#include "compactar.h"

/*
 * Auxiliary Functions
 */

int comparing(void *item_a, unsigned char item_b)
{
    return (*((unsigned char *)item_a) == item_b);
}

int is_bit_i_set(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask & c;
}

unsigned char set_bit(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask | c;
}

void print_un_char(unsigned char c)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        if (is_bit_i_set(c, 7 - i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
}

void print_freq_list(int freq[])
{
    int i;
    for (i = 0; i < 256; i++)
    {
        if (freq[i] != 0)
        {
            printf("(%d) %c -> [%d]\n", i, (char)i, freq[i]);
        }
    }
}

/*
 * Priority Queue
 */

queue *create_queue()
{
	queue *new_queue = malloc(sizeof(queue));
	new_queue->head = NULL;
	return new_queue;
}

void enqueue(queue *queue, void *item, int frequency)
{
	node *new_node = malloc(sizeof(node));
	(new_node->item) = item;
	new_node->frequency = frequency;
	new_node->left = NULL;
	new_node->right = NULL;
	if ((is_empty(queue)) || (frequency <= queue->head->frequency))
	{
		new_node->next = queue->head;
		queue->head = new_node;
	}
	else
	{
		node *current = queue->head;
		while ((current->next != NULL) && (current->next->frequency < frequency))
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

void enqueue_node(node *head, queue *queue)
{
	if ((is_empty(queue)) || (head->frequency <= queue->head->frequency))
    {
        head->next = queue->head;
        queue->head = head;
    }
    else
    {
        node *current = queue->head;
        while ((current->next != NULL) && (current->next->frequency < head->frequency))
        {
            current = current->next;
        }
        head->next = current->next;
        current->next = head;
    }
}

node *dequeue(queue *queue)
{
	if (is_empty(queue))
	{
		printf("Priority Queue Underflow\n");
	}
	else
	{
		node *node = queue->head;
		queue->head = queue->head->next;
		node->next = NULL;
		return node;
	}
}

void print_queue(queue *queue)
{
	if (!is_empty(queue))
	{
		node *current = queue->head;
		while(current != NULL)
		{
			printf("%c ", *(unsigned char *)current->item);
			current = current->next;
		}
		printf("\n");
	}
}

int is_empty(queue *queue)
{
    return (queue->head == NULL);
}

void frequency_enqueue(int frequency[], queue *queue)
{
	for (int i = 0; i < 256; i++)
	{
		if (frequency[i] != 0)
		{
			unsigned char *aux = (unsigned char *)malloc(sizeof(unsigned char));
			*aux = i;
			enqueue(queue, aux, frequency[i]);
		}
	}
}

/*
 * Binary Tree
 */

void print_tree(node *root)
{
	if (root != NULL)
	{
		printf("node: %c %d\n", *(unsigned char *)root->item, root->frequency); 
        print_tree(root->left);                                                 
        print_tree(root->right);                                                
	}
}

node *merge_nodes(queue *queue)
{
	if (queue->head->next != NULL)
	{
		unsigned char *aux = (unsigned char *)malloc(sizeof(unsigned char));
		*aux = '*';
		node *new_node = malloc(sizeof(node));
		new_node->left = dequeue(queue);
		new_node->right = dequeue(queue);
		new_node->item = aux;
		new_node->frequency = new_node->left->frequency + new_node->right->frequency;
		enqueue_node(new_node, queue);
		merge_nodes(queue);
	}
	else
	{
		return queue->head;
	}
}

int tree_size(node *root)
{
    if (root->left == NULL && root->right == NULL)
    {
        if (comparing(root->item, '*') || comparing(root->item, (char)SLASH))
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1 + tree_size(root->left) + tree_size(root->right);
    }
}

void fprint_tree(node *root, FILE *compact_file)
{
	if (root != NULL)
	{
		if (root->left == NULL && root->right == NULL && (comparing(root->item, '*') || comparing(root->item, (char)SLASH)))
        {
            fprintf(compact_file, "%c", (char)SLASH);
        }
        fprintf(compact_file, "%c", *(unsigned char *)root->item);
        fprint_tree(root->left, compact_file);
        fprint_tree(root->right, compact_file);
	}
}

/*
 * Hash Table
 */
ht *create_hash()
{
	ht *new_hash = (ht *)malloc(sizeof(ht));
	for (int i = 0; i < 256; i++)
	{
		new_hash->table[i] = NULL;
	}
	return new_hash;
}

element *create_element()
{
	element *new_element = (element *)malloc(sizeof(element));
	new_element->n = 0;
	return new_element;
}

void add_hash(ht *ht, void *item, char bit[], int n)
{
	int h = *(unsigned char *)item;
	element *new_element = create_element();
	new_element->n = n;
	for (int i = 0; i < n; i++)
	{
		new_element->string[i] = bit[i];
	}
	ht->table[h] = new_element;
}

void print_hash(ht *ht)
{
	for (int i = 0; i < 256; i++)
	{
		if (ht->table[i] != NULL)
		{
			printf("%d ->", i);
			for (int j = 0; j < ht->table[i]->n; j++)
			{
				printf("%c", ht->table[i]->string[j]);
			}
			printf(" [%d]\n", ht->table[i]->n);
		}
	}
}