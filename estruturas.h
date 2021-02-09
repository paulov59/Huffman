#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define SLASH 92


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista node;
typedef struct queue queue;
typedef struct element element;
typedef struct hash_table ht;

struct lista
{
	int frequency;
	void *item;
	node *right;
	node *left;
	node *next;
};

struct queue
{
	node *head;
};

struct element
{
	char string[50];
	int n;
};

struct hash_table
{
	element *table[256];
};


/*
 * Recebe 2 caracteres com ponteiro pra void;
 * Compara os caracteres recebidos;
 * Retorna o resultado da comparacao.
 */
int comparing(void *item_a, unsigned char item_b);

/*
 * Recebe um caractere sem sinal e um inteiro;
 * Checa se o bit esta "setado";
 * Retorna o resultado da comparacao.
 */
int is_bit_i_set(unsigned char c, int i);

/*
 * Recebe um caractere sem sinal e um inteiro;
 * "Seta" se o bit na posicao desejada;
 * Retorna o bit setado.
 */
unsigned char set_bit(unsigned char c, int i);

/*
 * Recebe um caractere sem sinal;
 * "Printa" os bits do caractere;
 * Sem retorno.
 */
void print_un_char(unsigned char c);

/*
 * Recebe um array de inteiros com as frequencias com caracteres;
 * "Printa" o valor na tabela ASCII, o caractere e sua frequencia;
 * Sem retorno.
 */
void print_freq_list(int freq[]);

/*
 * Sem parâmetros iniciais;
 * Cria uma fila vazia;
 * Retorna a fila criada.
 */
queue *create_queue();

/*
 * Sem parâmetros iniciais;
 * Cria uma hash vazia;
 * Retorna a hash criada;
 */
ht *create_hash();

/*
 * Sem parâmetros iniciais;
 * Cria uma hash de element vazia;
 * Retorna a hash criada;
 */
element *create_element();

/*
 * Recebe uma fila;
 * Remove o primeiro nó;
 * Retorna o nó removido;
 */
node *dequeue(queue *queue);

/*
 * Recebe uma fila;
 * Cria uma árvore Huffman a partir da fila;
 * Retorna a árvore Huffman criada;
 */
node *merge_nodes(queue *queue);

/*
 * Recebe uma fila;
 * Verifica se a fila está vazia;
 * Retorna um valor lógico.
 */
int is_empty(queue *queue);

/*
 * Recebe o nó raiz de uma árvore; 
 * Verifica o tamanho da árvore;
 * Retorna o tamanho da árvore;
 */
int tree_size(node *root);

/*
 * Recebe uma fila, um ponteiro void e a frequência do elemento;
 * Coloca e ordena o elemento void na fila;
 * Sem retorno;
 */
void enqueue(queue *queue, void *item, int frequency);

/*
 * Recebe um nó de árvore e uma fila;
 * Coloca e ordena o nó na fila;
 * Sem retorno;
 */
void enqueue_node(node *node, queue *queue);

/*
 * Recebe as frequências dos elementos e uma fila;
 * Cria uma fila de prioridade baseada nas frequências;
 * Sem retorno.
 */
void frequency_enqueue(int *frequency, queue *queue);

/*
 * Recebe uma tabela hahs, um ponteiro void, sequência de bits de um item na árvoree a quantidade de bits da sequência;
 * Adiciona um novo elemento a tabela;
 * Sem retorno;
 */
void add_hash(ht *ht, void *item, char bit[], int n);

/*
 * Recebe uma árvore Huffman e um ponteiro pra arquivo;
 * Imprime a árvore Huffman no arquivo;
 * Sem retorno;
 */
void fprint_tree(node *root, FILE *compact_file);

/*
 * Recebe o nó raiz de uma arvore;
 * Imprime em pré-ordem a partir dele;
 * Sem retorno;
 */
void print_tree(node *raiz);

/*
 * Recebe uma fila;
 * Imprime os itens presentes na fila;
 * Sem retorno;
 */
void print_queue(queue *queue);

/*
 * Recebe uma tabela hash;
 * Imprime os elementos presentes na hash e suas frequências;
 * Sem retorno;
 */
void print_hash(ht *ht); 

#endif