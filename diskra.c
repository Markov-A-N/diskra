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
	int elem;
	int diag;
} dd;

typedef struct 
{
	Edge* data;
	int size;	
} oneVector;

typedef struct 
{
	dd** data;
	int size;
} twoVector;

void oneCreate(oneVector* v, int sz)
{
	v->size = sz;
	v->data = (Edge*) malloc(sizeof(Edge) * v->size);
}

void twoCreate(twoVector* v, int sz)
{
	v->data = (dd **) malloc(sizeof(dd*) * sz);
	for (int counter = 0; counter < sz; counter++)
	{
		v->data[counter] = (dd *) malloc(sizeof(dd) * sz);
	}
	v->size = sz;
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

void Sort(oneVector* v, twoVector* z, int counter)
{
	int x, k, f, m, fDiag, mDiag;
	Edge y;
	for (int i = 0; i < counter-1; i++)
	{
		x = v->data[i].power;
		k = i;
		for (int j = i + 1; j < counter; j++)
		{
			if (v->data[j].power > x)
			{
				k = j;
				y = v->data[j];
				x = v->data[j].power;
				v->data[k] = v->data[i];
				v->data[i] = y;
				for (int tj = 0; tj < counter; tj++)
				{
					f = z->data[i][tj].elem;
					fDiag = z->data[i][tj].diag;
					z->data[i][tj].elem = z->data[i+1][tj].elem;
					z->data[i][tj].diag = z->data[i+1][tj].diag;
					z->data[i+1][tj].elem = f;
					z->data[i+1][tj].diag = fDiag;
				}
				for (int ti = 0; ti < counter; ti++)
				{			
					if (ti != i && ti != i+1)
					{
						m = z->data[ti][i].elem;
						mDiag = z->data[ti][i].diag;
						z->data[ti][i].elem = z->data[ti][i+1].elem;
						z->data[ti][i].diag = z->data[ti][i+1].diag;
						z->data[ti][i+1].elem = m;
						z->data[ti][i+1].diag = mDiag;
					}
				}
			}
		}
	}
}

int main(int argc, char * argv[])
{
	int razmer = 0, counter = 0, b = 0, cc = 0;
	int color[7] = {0, 1, 2, 3, 4, 5, 6};
	char *colorWords[7] = {"Blue", "Red", "Yellow", "Green", "Magenta", "Gray", "Black"};
	oneVector *s = (oneVector *) malloc(sizeof(oneVector) * 1);
	twoVector *k = (twoVector *) malloc(sizeof(twoVector) * 1);
	twoVector *v = (twoVector *) malloc(sizeof(twoVector) * 1);
	FILE* fin;
	FILE* fout;
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	fscanf(fin, "%d", &razmer);
	twoCreate(v, razmer);

	for (int i = 0; i < razmer; i++)
	{
		for (int j = 0; j < razmer; j++)
		{
			fscanf(fin, "%d", &(v->data[i][j].elem));
			if (v->data[i][j].elem == 1)
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
			if (v->data[i][j].elem == 1)
			{
				v->data[j][i].elem = 0;
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
				k->data[i][j].elem = 0;
				k->data[i][j].diag = 1;

			}
			else 
			{
				if ((s->data[i].i == s->data[j].i) || (s->data[i].j == s->data[j].j) || (s->data[i].j == s->data[j].i) || (s->data[i].i == s->data[j].j))
				{
					k->data[i][j].elem = 1;
					s->data[i].power++;
				}
				else 
				{
					k->data[i][j].elem = 0;
				}
			}
		}
	}

	Sort(s, k, counter);
	for (int p = 0; p < counter; p++)
	{
		Edge* last = (Edge*) malloc(sizeof(Edge) * 1);
		last->name = p;

		s->data[p].color = color[p+1];
		cc++;

		
		for (int u = 0; u < counter; u++)
		{
			if (k->data[p][u].elem == 1 || (k->data[last->name][u].elem == 1) ) continue;
			else 
			{
				if (k->data[p][u].diag != 1) 
				{
					s->data[u].color = color[p+1];
					last->name = s->data[u].name;
					cc++;
				}
			}
		}
		if (cc == counter)
		{
			break;
		}
	}

	for (int i = 0; i < razmer; i++)
	{
		for (int j = 0; j < razmer; j++)
		{
			if (v->data[i][j].elem == 1)
			{
				v->data[j][i].elem = 1;
			}
		}
	}

	fprintf(fout, "%d", razmer);
	for (int i = 0; i < razmer; i++)
	{
		for (int j = 0; j < razmer; j++)
		{
			if (j%razmer == 0) fprintf(fout, "\n");
			fprintf(fout, "%d ", v->data[i][j].elem);
		}
	}
	fprintf(fout, "\nColors_Edges:\n");
	for (int i = 0; i < counter; i++)
	{
		fprintf(fout, "%d %d %s\n", s->data[i].j, s->data[i].i, colorWords[s->data[i].color]);
	}

	fclose(fin);
	fclose(fout);

	return 0;
}
