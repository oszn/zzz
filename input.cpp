#include"input.h"

netinput::netinput(int c) {
	colunm = c;
	
	input.setZero(c);
}
netinput::netinput(vector<float> c, int i)
{
	//srand((unsigned)time(NULL));
	colunm = c.size();
	input.setZero(colunm);
	for (int i = 0; i < c.size(); i++) {
		input(i) = c[i];
	}
	//cout << rand();
	//input(colunm - 1) = float(rand() % 100) / 100;
	int cl;
}
netinput::netinput(vector<float> c)
{
	srand((unsigned)time(NULL));
	colunm = c.size()+1;
	input.setZero(colunm);
	for (int i = 0; i < c.size(); i++) {
		input(i) = c[i];
	}
	cout << rand();
	input(colunm - 1) = float(rand() % 100)/100;
	int cl;
}
void netinput::init(ll c) {
	for (int i = 0; i < colunm; i++) {
		input(i) = pow(c, i);
	}
}


