#pragma once
#ifndef midd
#define midd



#include <iostream>
#include <Eigen/Dense>
#include<math.h>
using namespace Eigen;
using namespace std;

typedef float kk;
typedef Matrix<kk, Dynamic, Dynamic> matrix;

class mid
{
private:
	matrix x;
	int cows;//ÁÐ
	int rows;//ÐÐ
	int su=10;
public:
	void  init(int r, int c);
	mid();
	pair<int, int> getRowsCows() {
		return pair<int, int>(rows, cows);
	}
	void set(int i,int j,float value) {
		x(i, j) = value;
	}
	float get(int i, int j) {
		return x(i, j);
	}
	matrix getmatrix() { return x; };
	void setsu(int x) { su = x; };
	mid(int r, int c);
	~mid();
};

#endif // !midd