#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class kupac
{
public:
	vector<int> t;

	kupac()
	{
		t.push_back(0);
	}

	int size()
	{
		return t.size() - 1;
	}

	~kupac()
	{
	}

	int peek()
	{
		return t[1];
	}

	void push(int e)
	{
		t.push_back(e);
		fellebegtet(size());
	}

	void repair(int e)
	{
		int i = keres(1, e);
		megigazit(i);
	}

	void diagnosztika()
	{
		for (int i = t.size() - 1; 0 <= i; i--)
		{
			int j = i;
			while (j != 0)
			{
				cout << "t[" << j << "] : " << t[j] << endl;
				j = szulo(j);
			}
			cout << "lanc vege\n";
		}
	}

	int pop()
	{
		int result = peek();
		csere(1, size());
		t.erase(t.end() - 1);

		sullyeszt(1);

		return result;
	}
	int search(int elem) {
		return keres(1, elem);
	}

private:
	int szulo(int n)
	{
		return n / 2;
	}
	int kisebbik_gyerek(int n)
	{
		int egyik = n * 2;
		int masik = egyik + 1;
		if (size() < egyik)
			return -1;
		if (size() < masik)
			return egyik;
		return t[egyik] < t[masik] ? egyik : masik;
	}
	int nagyobbik_gyerek(int n)
	{
		int egyik = n * 2;
		int masik = egyik + 1;
		if (size() < egyik)
			return -1;
		if (size() < masik)
			return egyik;
		return t[egyik] > t[masik] ? egyik : masik;
	}
	void fellebegtet(int n)
	{
		while (t[szulo(n)] > t[n])
		{
			csere(n, szulo(n));
			n = szulo(n);
		}
	}
	void sullyeszt(int n)
	{
		int kgy = kisebbik_gyerek(n);
		if (kgy == -1)
		{
			return;
		}
		if (t[kgy] < t[n])
		{
			csere(kgy, n);
			sullyeszt(kgy);
		}
	}
	void csere(int i, int j)
	{
		int i_elem = t[i];
		int j_elem = t[j];
		t[i] = j_elem;
		t[j] = i_elem;
	}
	void megigazit(int n)
	{
		sullyeszt(n);
		fellebegtet(n);
	}
	int keres(int hol, int elem)
	{
		if (t[hol] == elem)
			return hol;
		int egyik = 2 * hol;
		if (size() < egyik)
			return -1;
		int az_eredmeny = keres(egyik, elem);
		if (az_eredmeny != -1)
			return az_eredmeny;
		int masik = 2 * hol + 1;
		if (size() < masik)
			return -1;
		az_eredmeny = keres(masik, elem);
		if (az_eredmeny != -1)
			return az_eredmeny;
		return -1;
	}
};

int random_int_kozott(int tol, int ig)
{
	return tol + (rand() % (ig - tol));
}

kupac general(int n, int min, int max) {
	kupac k;
	for (int i = 0; i < n; i++)
	{
		int randomelem = random_int_kozott(min, max);
		k.push(randomelem);
	}
	return k;
}

bool Jo_e(kupac k, int n, int min, int max) {
	int randomelem = random_int_kozott(min, max);
	int a = k.search(randomelem);
	int b;

	if (a != -1 && k.t[a] != randomelem)
	{
		cout << "hiba:" << n << endl;
		cout << "randomelem:" << randomelem << endl;
		cout << "a:" << a << endl;
	}
	else if (a == -1) {
		/**/
		int i = 0;
		while (i < k.t.size() && k.t[i] != randomelem)
		{
			i++;
		}
		i == k.t.size() ? b = -1 : b = i;
		/**/
		return a == b;
	}

	return k.t[a] == randomelem;
}

int teszt(int n, int m, int min, int max) {
	int db = 0;
	for (int i = 0; i < n; i++)
	{
		kupac t = general(m, min, max);
		if (Jo_e(t, m, min, max))
		{
			db++;
		}
		else {
			cout << n;
		}
	}
	return db;
}


int main()
{
	srand((unsigned)time(NULL));
	int db = teszt(10000, 1000, 0, 1000000);
	cout << db;
}
