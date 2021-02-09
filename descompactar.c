#include "descompactar.h"

int descompact(FILE *compacted, char name[])
{
	int t_file = 0;
	short t_trash, t_tree = 8191; //t_tree = 8191 because it fills the byte with 1
	char output_name[50];
    unsigned char firstbyte, secondbyte;
    node *root = NULL;
    FILE *descompacted;
    getchar();
    printf("Enter the output file file:\n");
    scanf("%[^\n]s", output_name);
    compacted = fopen(name, "rb"); //reads in binary
    descompacted = fopen(output_name, "wb"); //write in binary
    fseek(compacted, 0, SEEK_END); //Go to the final position of the file
    t_file = ftell(compacted); //ftell returns the size of bytes of the final file
	rewind(compacted); //Return to the inicial position of the file
	printf("Decompressing...\n");
    firstbyte = fgetc(compacted);
	secondbyte = fgetc(compacted);
	t_trash = firstbyte >> 5; //Move 5 bits to the right, leaving only the 3 bits of trash 
	t_tree = ((firstbyte << 8) | secondbyte) & t_tree; //t_tree receives the size of tree
	root = build_tree(compacted); 
	fseek(compacted, t_tree + 2, SEEK_SET); //Write after the tree in the new file
	print_byte(compacted, descompacted, root, t_tree, t_trash, t_file);
	fclose(compacted);
	fclose(descompacted);
    printf("DONE!\n");
	return 0;
}

node *build_tree(FILE *compacted) //Rebuild the original hufftree by given a string
{
	unsigned char atual;
    node *new_node;
    atual = fgetc(compacted);
    if (atual == '*')
    {
    	new_node = create_node(atual);
        new_node->left = build_tree(compacted);
        new_node->right = build_tree(compacted);
    }
    else if (atual == (char)SLASH) //slash == '\'//
    {
        atual = fgetc(compacted);
        new_node = create_node(atual);
    }
    else
    {
        new_node = create_node(atual);
    }
    return new_node;
}

node *create_node(unsigned char caractere)
{
	unsigned char *aux = (unsigned char *)malloc(sizeof(unsigned char));
    *aux = caractere;
	node *new_node = (node *)malloc(sizeof(node));
    new_node->frequency = 0;
    new_node->item = aux;
    new_node->right = NULL;
    new_node->left = NULL;
    new_node->next = NULL;
    return new_node;
}

void print_byte(FILE* compacted, FILE* descompacted, node *root, short t_tree, short t_trash, int t_file) //Write the descompacted file
{
	long int i, j, k;
	unsigned char c;
	node *atual = root;
	for (i = 0; i < t_file; ++i)
	{
		c = fgetc(compacted);
		if (i == t_file - 1)
			k = 8 - t_trash;
		else
			k = 8;
		for (j = 0; j < k; ++j)
		{
			if(is_bit_i_set(c, 7 - j))
				atual = atual->right;
			else
				atual = atual->left;
			if (atual->left == NULL && atual->right == NULL)
            {
                fprintf(descompacted, "%c", *(unsigned char*)atual->item);
                atual = root;
            }
		}
	}
}