#ifndef dictionary_H
#define dictionary_H

class dictionary {
	private:
		String types;
		int dots[];
		int dotnumber;
	
	public:
		dictionary(String s);
		~dictionary();
		int getDotNumber();
		int *getDots();
};

#endif
