#include "dictionary.hpp"

using namespace std;

dictionary::dictionary(string s) {
	types = s;
	switch (s) {
		case "fontA" :
			dots =	{ 6, 0, 10, 0,
					10, 0, 16, 20,
					16, 20, 12, 20,
					12, 20, 10, 14,
					10, 14, 6, 14,
					6, 14, 4, 20,
					4, 20, 0, 20,
					0, 20, 6, 0,
					8, 7, 9, 10,
					9, 10, 7, 10,
					7, 10, 8, 7	}
			dotnumber = 11;
	}
}

int main () {
	return 0;
}