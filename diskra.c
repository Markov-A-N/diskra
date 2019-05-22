#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct 
{
	int i;//начальная вершина ребра
	int j;//конечная вершина ребра
	int color;
	int name;
	int power;	
} Edge;

typedef struct 
{
	Edge* data;
	int size;	
} oneVector;

typedef struct 
{
	int** data;
	int size;
} twoVector;

void oneCreate(oneVector* v, int sz)
{
	v->size = sz;
	v->data = (Edge*) malloc(sizeof(Edge) * v->size);
}

void twoCreate(twoVector* v, int sz)
{
	v->size = sz;
	v->data = (int **) malloc(sizeof(int*) * v->size);
	for (int counter = 0; counter < v->size; counter++)
	{
		v->data[counter] = (int *) malloc(sizeof(int) * v->size);
	}
}

void oneDestroy(oneVector* v)
{
	v->size = 0;
	free(v->data);
}

void twoDestroy(twoVector* v, int sz)
{
	for (int i = 0; i < sz; i++)
	{
		free(v->data[i]);
	}
	v->size = 0;
	free(v->data);
}

void Sort(oneVector* v, int counter)
{
	int x, k;
	Edge y;
	for (int i = 0; i < counter-1; i++)
	{
		x = v->data[i].power;
		k = i;
		for (int j = i + 1; j < counter; j++)
		{
			if (v->data[j].power < x)
			{
				k = j;
				y = v->data[j];
				x = v->data[j].power;
				v->data[k] = v->data[i];
				v->data[i] = y;
			}
		}
	}
}


int main(int argc, char * argv[])
{
	int razmer = 0, counter = 0, b = 0;
	int color[7] = {0, 1, 2, 3, 4, 5, 6};
	char *colorWords[7] = {"Blue", "Red", "Green", "Yellow", "Magenta", "Gray", "Black"};
	oneVector *s;
	twoVector *v, *k;
	FILE *fp;
	FILE *fout;
	fp = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	if ((fp = NULL)) 
	{
		printf("Error");
		return 0;
	}

	fscanf(fp, "%d", &razmer);
	twoCreate(v, razmer);

	for (int i = 0; i < razmer; i++)
	{
		for (int j = 0; j < razmer; j++)
		{
			fscanf(fp, "%d", &(v->data[i][j]));
			if (v->data[i][j] == 1)
			{
				counter++;
			}
		}
	}

	counter /= 2;
	oneCreate(s, counter);

	for (int i = 0; i < razmer; i++)
	{
		for (int j = 0; j < razmer; j++)
		{
			if (v->data[i][j] == 1)
			{
				v->data[j][i] = 0;
				s->data[b].i = i;
				s->data[b].j = j;
				s->data[b].color = 0;
				s->data[b].power = 0;
				s->data[b].name = b;
				b++;
			}
		}
	}

	twoCreate(k, counter);

	for (int i = 0; i < counter; i++)
	{
		for (int j = 0; j < counter; j++)
		{
			if (i == j)
			{
				k->data[i][j] = 0;
			}
			else 
			{
				if ((s->data[i].i == s->data[j].i) || (s->data[i].j == s->data[j].j) || (s->data[i].j == s->data[j].i) || (s->data[i].i == s->data[j].j))
				{
					k->data[i][j] = 1;
					s->data[i].power++;
				}
				else 
				{
					k->data[i][j] = 0;
				}
			}
		}
	}

	Sort(s, counter);
	for (int p = 0; p < counter; p++)
	{
		int n = 1;
		Edge* last = NULL;
		if (p == 0)
		{
			s->data[p].color = color[n];
		} else {
			s->data[p].color = color[n];
		}
		for (int u = 0; u < counter; u++)
		{
			if (k->data[p][u] == 1 && ((last == NULL) || (k->data[last->name][u] == 1) )) continue;
			else 
			{
				if (p != u) 
				{
					s->data[u].color = color[n];
					last->name = s->data[u].name;
				}
			}
		}
		n++;
	}

	for (int i = 0; i < razmer; i++)
	{
		for (int j = 0; j < razmer; j++)
		{
			if (v->data[i][j] == 1)
			{
				v->data[j][i] = 1;
			}
		}
	}

	fprintf(fout, "%d\n", razmer);
	for (int i = 0; i < razmer; i++)
	{
		for (int j = 0; j < razmer; j++)
		{
			if (j%razmer == 0) printf("\n");
			fprintf(fout, "%d ", v->data[i][j]);
		}
	}
	fprintf(fout, "\nColors_Edges:\n");
	for (int i = 0; i < counter; i++)
	{
		fprintf(fout, "%d %d %s\n", s->data[i].j, s->data[i].i, colorWords[s->data[i].color]);
	}

	fclose(fp);

	return 0;
}