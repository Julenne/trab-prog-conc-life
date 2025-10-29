/*
 * The Game of Life
 *
 * a cell is born, if it has exactly three neighbours
 * a cell dies of loneliness, if it has less than two neighbours
 * a cell dies of overcrowding, if it has more than three neighbours
 * a cell survives to the next generation, if it does not die of loneliness
 * or overcrowding
 *
 * In this version, a 2D array of ints is used.  A 1 cell is on, a 0 cell is off.
 * The game plays a number of steps (given by the input), printing to the screen each time.  'x' printed
 * means on, space means off.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

//#define DEBUG

typedef unsigned char cell_t;
cell_t **prev, **next, **tmp;
double start, finish, elapsed;

typedef struct
{
	short int id;		// identificador da thread na aplicaco
	short int nthreads; // quantidade de threads
	long int dim;		// numero de linhas do tabuleiro
} t_args;

cell_t **allocate_board(int size)
{
	cell_t **board = (cell_t **)malloc(sizeof(cell_t *) * size);
	int i;
	for (i = 0; i < size; i++)
	board[i] = (cell_t *)malloc(sizeof(cell_t) * size);
	return board;
}

void free_board(cell_t **board, int size)
{
	int i;
	for (i = 0; i < size; i++)
	free(board[i]);
	free(board);
}

/* return the number of on cells adjacent to the i,j cell */
int adjacent_to(cell_t **board, int size, int i, int j)
{
	int k, l, count = 0;
	
	int sk = (i > 0) ? i - 1 : i;
	int ek = (i + 1 < size) ? i + 1 : i;
	int sl = (j > 0) ? j - 1 : j;
	int el = (j + 1 < size) ? j + 1 : j;
	
	for (k = sk; k <= ek; k++)
	for (l = sl; l <= el; l++)
	count += board[k][l];
	count -= board[i][j];
	
	return count;
}
void play(cell_t **board, cell_t **newboard,long int i, int size)
{ // funcao para utilizar na thread
	int a;
	long int j;
	/* for each cell, apply the rules of Life */
		for (j = 0; j < size; j++)
		{
			a = adjacent_to(board, size, i, j);
			if (a == 2)
				newboard[i][j] = board[i][j];
			if (a == 3)
				newboard[i][j] = 1;
			if (a < 2)
				newboard[i][j] = 0;
			if (a > 3)
				newboard[i][j] = 0;
		}
}

void *funcao(void *args)
{
	t_args *arg = (t_args *)args;
	long int fatia, ini, fim;
	fatia = arg->dim / arg->nthreads; // quantidade de elementos que a thread vai processar
	ini = arg->id * fatia;
	fim = ini + fatia;

	if (arg->id == arg->nthreads - 1)
		fim = arg->dim;

	for (long int i = ini; i < fim; i++)
	{
		play(prev, next,i, arg->dim);
	}

	free(args); // libera a memoria alocada na main
	pthread_exit(NULL);
}

/* print the life board */
void print(cell_t **board, int size)
{
	int i, j;
	/* for each row */
	for (j = 0; j < size; j++)
	{
		/* print each column position... */
		for (i = 0; i < size; i++)
			printf("%c", board[i][j] ? 'x' : ' ');
		/* followed by a carriage return */
		printf("\n");
	}
}

/* read a file into the life board */
void read_file(FILE *f, cell_t **board, int size)
{
	int i, j;
	char *s = (char *)malloc(size + 10);
	char c;
	for (j = 0; j < size; j++)
	{
		/* get a string */
		fgets(s, size + 10, f);
		/* copy the string to the life board */
		for (i = 0; i < size; i++)
		{
			// c=fgetc(f);
			// putchar(c);
			board[i][j] = s[i] == 'x';
		}
		// fscanf(f,"\n");
	}
}

int main()
{
	short int nthreads;
	int size, steps;
	FILE *f;
	f = stdin;

	GET_TIME(start);
	fscanf(f, "%d %d %hi", &size, &steps, &nthreads);
	prev = allocate_board(size);
	read_file(f, prev, size);
	fclose(f);
	next = allocate_board(size);
	pthread_t tid[nthreads];
	int i, j;
#ifdef DEBUG
	printf("Initial \n");
	print(prev, size);
	printf("----------\n");
#endif

	for (i = 0; i < steps; i++)
	{
		for (short int k = 0; k < nthreads; k++)
		{
			t_args *args = (t_args *)malloc(sizeof(t_args));
			if (args == NULL)
        	{
				fprintf(stderr, "ERRO de criacao da estrutura de argumentos\n");
            	return 1;
        	}
			args->id = k;
			args->nthreads = nthreads;
			args->dim = size;
			//printf("Criando a thread %d\n", args->id);
			pthread_create(&tid[k], NULL, funcao, (void *)args);
		}
		for (short int k = 0; k < nthreads; k++)
		{
			if (pthread_join(tid[k], NULL))
			{
				fprintf(stderr, "ERRO na espera de threads");
				return 2;
			}
		}
		#ifdef DEBUG
			printf("%d ----------\n", i);
			print(next, size);
		#endif
		tmp = prev;
		prev = next;
		next = tmp;
	}

	print(prev, size);
	
	GET_TIME(finish);
	elapsed = finish - start;
	printf("Tempo de execucao: %.24f\n", elapsed);

	free_board(prev, size);
	free_board(next, size);
}
