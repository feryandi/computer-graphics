#ifndef dictionary_H
#define dictionary_H

#include <string.h>

using namespace std;

class dictionary {
	private:
		string types;
		int dots[];
		int dotnumber;
	
	public:
		dictionary(string s);
		~dictionary();
		int getDotNumber();
		int *getDots();
};

#endif
