#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int main() {
	int N, a, b, c, d;
	cin >> N;
	cin >> a;
	cin >> b;
	printf("\t%d, %d, ", a, b);
	for (int i = 0; i < N-1; ++i)
	{
		cin >> c;
		cin >> d;
		printf("%d, %d,\n", c, d);
		printf("\t%d, %d, ", c, d);
	}
	printf("%d, %d,\n", a, b);
	return 0;
}