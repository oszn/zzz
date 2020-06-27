#pragma once
#ifndef inpuc
#define inpuc
#include <iostream>
#include <Eigen/Dense>
#include<math.h>
#include<vector>
#include <stdlib.h>
#include <time.h> 
using namespace Eigen;
using namespace std;
typedef long long ll;
typedef Matrix<ll, Dynamic, Dynamic> matrixF;
class netinput {
private:
		int colunm;
		RowVectorXf input;
		vector<float> qqq;
public:netinput();
	   netinput(int c);
	   netinput(vector<float>c, int i);
	   netinput(vector<float> c);
	   int getCol() {
		   return colunm;
	   }
	   RowVectorXf get() {
		   return input;
	   }
	 void set(RowVectorXf x,ll c) {
		   input = x;
		   colunm = c;
	   }
	   void init(ll c);
};

#endif // !input
