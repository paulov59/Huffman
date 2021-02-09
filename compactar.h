#ifndef COMPACTAR_H
#define COMPACTAR_H


#include "estruturas.h"

/*
 * Recebe um ponteiro de arquivo e uma string com o nome do arquivo original;
 * Compacta o arquivo;
 * Retorna o arquivo compactado.
 */
FILE *compact(FILE *original_file, char filename[]);

/*
 * Recebe um ponteiro de arquivo;
 * Cria um array com a frequencia de cada caracter da tabela ascii;
 * Retorna o array criado.
 */
int *save_freq(FILE *file);

/*
 * Recebe uma arvore binaria, um inteiro para contagem (0), uma hash table e a string 
 * que representa o caminho percorrido na arvore huffman;
 * Adiciona os valores dos bytes comprimidos a hash, junto de seus respectivos caminhos na arvore huffman;
 * Sem retorno.
 */
int generate_huffman_tree(node *root, int count, ht *ht, char string[]);

/*
 * Recebe a hash com as frequencias e os valores dos bytes;
 * Calcula a quantidade de bits em um arquivo, e quantos bits sobram no último byte;
 * Retorna um inteiro, representando quantos bits sobram no ultimo byte(lixo).
 */
int trash_size(ht *hash, int *frequency);

#endif