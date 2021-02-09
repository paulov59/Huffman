#include "compactar.h"

FILE *compact(FILE *original_file, char filename[]){
    int *freq, count=0;
    short tree, trash, final;

    char huff_tree_path[256];
    unsigned char curr_byte, compact=0;

    node *root = NULL;
    queue *queue = create_queue();
    ht *hash = create_hash();

    FILE *final_file;

    original_file = fopen(filename, "rb"); //read the original file

    printf("Reading Original file...\n");
    freq = save_freq(original_file); //Save frequency on an array with the ASCII table
    printf("DONE!\n");
    rewind(original_file); //Return to the inicial position of the file
    
    printf("Generating Frequency Queue...\n");
    frequency_enqueue(freq, queue); //Create a ordenate list by frequency
    printf("DONE!\n");
    
    printf("Generating Huffman Tree...\n");
    root = merge_nodes(queue); //Create the huffman tree
    generate_huffman_tree(root, 0, hash, huff_tree_path); 
    printf("DONE!\n");

    printf("Creating Compacted file...\n");
    filename = strtok(filename,".");
    filename = strcat(filename,".huff");
    final_file = fopen(filename, "wb");
    printf("DONE!\n");

    trash = trash_size(hash,freq); 
    tree = tree_size(root);


    trash = trash << 13; //Leaves only 3 bits for trash set
    final = trash | tree;

    curr_byte = final >> 8; //Write the first byte of the new file
    fprintf(final_file, "%c", curr_byte);
    
    curr_byte = final; //Write the second byte of the new file
    fprintf(final_file, "%c", curr_byte);

    fprint_tree(root, final_file); //Write the tree in the compacted file

    fseek(final_file, 2+tree, SEEK_SET); //Write after the tree in the compacted file
    
    printf("Writing Compacted file...\n");
    while (!feof(original_file))			//Write all bytes on the compacted file
    {
        curr_byte = fgetc(original_file);
        int i;
        for (i = 0; i < hash->table[(int)curr_byte]->n; ++i)
        {
            if (hash->table[(int)curr_byte]->string[i] == '1')
                compact = set_bit(compact, 7 - count);
            count++;
            if (count == 8)
            {
                fprintf(final_file, "%c", compact);
                compact = 0;
                count = 0;
            }
        }
    }
    printf("DONE!\n");

    fclose(original_file);
    fclose(final_file);

    return final_file;
}

int *save_freq(FILE *file){
	int *freq = (int *)calloc(256,sizeof(int));
	unsigned char c;
	while(!feof(file)){
        c=fgetc(file);
        freq[(int)c]++;
    }

    return freq;
}

int generate_huffman_tree(node *root, int count, ht *ht, char string[]) //Recieves root of huff tree, count of nodes in preorder, empty hash, empty huff way
{
    if (root->left == NULL && root->right == NULL)
    {
        add_hash(ht, root->item, string, count);						//Create a hash that will have the path of wich compacted byte 
    }
    else
    {
        string[count] = '0';
        generate_huffman_tree(root->left, count + 1, ht, string);
        string[count] = '1';
        generate_huffman_tree(root->right, count + 1, ht, string);
    }
}

int trash_size(ht *hash, int *frequency)
{
    int i = 0, sum = 0;

    while (i < 256)
    {
        if (frequency[i] != 0)
            sum += (hash->table[i]->n) * frequency[i];	//Says how many bits the finalfile have
        i++;
    }
    return 8 - (sum % 8);		//Says the size of trash
}

