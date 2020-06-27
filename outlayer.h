#pragma once
#ifndef opl
#define opl


#include"mid.h"
#include<vector>
struct layers
{
	int row;//行数
	int cow;//列数
	mid data;
	layers(int r, int c,mid x) {
		row = r;
		cow = c;
		data = x;
	}
	layers() {

	}
};
class outlayer
{
private:
	vector<layers> all_layes;
public:
	outlayer();
	matrix getmaxtrix(int i) { return all_layes.at(i).data.getmatrix(); };
	void push_layers(mid m);
	void set(int level,int i,int j,float value) {
		all_layes[level].data.set(i, j, value);
	}
	float get(int level, int i, int j) {
		return all_layes[level].data.get(i, j);
	}
	int size() {
		return all_layes.size();
	}
	~outlayer();
};

#endif // !opl
