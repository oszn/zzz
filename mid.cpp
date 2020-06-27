#include "mid.h"



void mid::init(int r, int c)
{
	rows = r;
	cows = c;
	x.setRandom(r, c);

	for (int i = 0; i < x.rows(); i++) {
		for (int j = 0; j < x.cols(); j++) {
			x(i, j) = (long long(x(i, j))%su*3.14159269)-long long(long long(x(i, j)) % su*3.14159269);
		}
	}
	cout << x << endl << endl;
	cout << "init__end"<<endl;
}

mid::mid()
{
}

mid::mid(int r, int c)
{
	rows = r;
	cows = c;
	x.setRandom(r, c);

	for (int i = 0; i < x.rows(); i++) {
		for (int j = 0; j < x.cols(); j++) {
			cout << x(i, j)<<endl;
				if(x(i,j)>1)
				x(i, j) = (long long(x(i, j)) % su*3.14159269) - long long(long long(x(i, j)) % su*3.14159269);
		}
	}
	cout << x << endl << endl;
	cout << "init__end"<<endl;
}


mid::~mid()
{
}
