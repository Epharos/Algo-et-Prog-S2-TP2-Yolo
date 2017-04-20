#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

int * question(int, int, int);
void printTable(int*, int);
int balance(int*, int, int, int);
int weight(int, int, int);
int resoudre(int*, int, int, int, int, int&);
bool verifier(int*, int, int, int);
int randExcept(int, int);
bool valider(int);

int main()
{
	srand(time(NULL));

	int * T = question(3, 0, 1);
	int pm = 0;
	int index = resoudre(T, 1, 0, 1, 2, pm);
	cout << index << " et " << pm << endl;
}

int * question(int n, int x, int d)
{
	int * tab = new int[n];
	int weight = 10; //Modifiez cette ligne pour modifier le poids des balles

	for(int i = 0 ; i < n ; i++)
	{
		if(i == x)
		{
			tab[i] = weight + d;
			continue;
		}

		tab[i] = weight;
	}

	return tab;
}

void printTable(int * T, int n)
{
	for(int i = 0 ; i < n - 1 ; i++)
	{
		cout << T[i] << " | ";
	}

	cout << T[n - 1] << endl;
}

int balance(int * T, int n, int d1, int d2)
{
	if(d1 > d2)
	{
		return balance(T, n, d2, d1); //Pour éviter un problème de signe
	}

	int sum1 = 0, sum2 = 0;

	for(int i = 0 ; i < n ; i++)
	{
		sum1 += T[d1 + i];
		sum2 += T[d2 + i];
	}

	return sum1 - sum2;
}

int weight(int * T, int n, int d)
{
	int sum = 0;

	for(int i = 0 ; i < n ; i++)
	{
		sum += T[d + i];
	}

	return sum;
}

int resoudre(int * T, int n, int d1, int d2, int d3, int & pm)
{
	if(n > 1 && pm == 0)
	{
		int cur = balance(T, n, d1, d2);
		int cur2 = balance(T, n, d1, d3);

		pm = cur > 0 || cur2 < 0 ? 1 : -1;

		if(cur == 0)
		{
			return resoudre(T, n / 3, d3, d3 + (n / 3), d3 + (n / 3 * 2), pm);
		}

		if(cur2 == 0)
		{
			return resoudre(T, n / 3, d2, d2 + (n / 3), d2 + (n / 3 * 2), pm);
		}

		return resoudre(T, n / 3, d1, d1 + (n / 3), d1 + (n / 3 * 2), pm);
	}
	
	if(pm != 0)
	{
		int cur = balance(T, n, d1, d2);

		if(cur == 0)
		{
			return resoudre(T, n / 3, d3, d3 + (n / 3), d3 + (n / 3 * 2), pm);
		}

		if(weight(T, n, d1))
	}
}

bool verifier(int * T, int n, int s, int pm)
{
	int r1 = randExcept(n, s), r2 = randExcept(n, s);

	while(r1 == r2)
	{
		r2 = randExcept(n, s);
	}

	if(T[s] != T[r1] && T[s] != T[r2])
	{
		if((T[s] - T[r1] > 0 && pm == 1) || (T[s] - T[r1] < 0 && pm == -1))
		{
			return true;
		}
	}

	return false;
}

int randExcept(int n, int s)
{
	int r = 0;

	do
	{
		r = (int)(rand() % n);
	} while(r == s);

	return r;
}

bool valider(int n)
{
	for(int i = 0 ; i < n ; i++)
	{
		int pm = 0;
		int * T = question(n, i, 1);

		if(!verifier(T, n, resoudre(T, n, 0, n / 3, 2 * n / 3, pm), pm))
		{
			return false;
		}

		T = question(n, i, -1);

		if(!verifier(T, n, resoudre(T, n, 0, n / 3, 2 * n / 3, pm), pm))
		{
			return false;
		}
	}

	return true;
}