#ifndef DESCOMPACTAR_H
#define DESCOMPACTAR_H

#include "estruturas.h"

/*
 * Recebe um ponteiro de arquivo e o nome do arquivo compactado;
 * Prepara o arquivo e chama as funções necessárias para descompactar;
 * Retorna um inteiro indicando que a operação foi bem sucedida;
 */
int descompact(FILE *compactado, char nome[]);

/*
 * Recebe um ponteiro com o arquivo a ser descompactado;
 * Lê e remonta a árvore Huffman do arquivo compactado;
 * Retorna a raiz da árvore Huffman gerada;
 */
node *build_tree(FILE *compactado);

/*
 * Recebe um caractere sem sinal;
 * Cria um nó de árvore Huffman com o caractere recebido;
 * Retorna o nó criado;
 */
node *create_node(unsigned char caractere);

/*
 * Recebe dois ponteiros de arquivo, uma árvore Huffman e os tamanhos da árvore, do lixo e do arquivo;
 * Imprime os bytes da árvore Huffman no arquivo descompactado;
 * Sem retorno;
 */
void print_byte(FILE* compactado, FILE* descompactado, node* root, short t_arvore, short t_lixo, int t_arquivo);

#endif
