#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int main() {
	int N, a, b, c, d, e, f;
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> d;
		cin >> e;
		cin >> f;
		printf("\t%d, %d, %d\n", d, e, f);
	}
	return 0;
}
