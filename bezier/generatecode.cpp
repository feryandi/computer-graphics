#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int main() {
	int N, a, b, c, d, e, f;
	cin >> N;
	cin >> a;
	cin >> b;
	cin >> c;
	printf("\t%d, %d, %d, ", a, b, c);
	for (int i = 0; i < N-1; ++i)
	{
		cin >> d;
		cin >> e;
		cin >> f;
		printf("%d, %d, %d\n", d, e, f);
		printf("\t%d, %d, %d, ", d, e, f);
	}
	printf("%d, %d, %d\n", a, b, c);
	return 0;
}
