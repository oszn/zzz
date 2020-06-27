#pragma once
#ifndef lreee
#define lreee


#include"input.h"
struct resultLayers
{
	int len;
	netinput *vecf;
	resultLayers(int l, netinput x) {  
		len = l;
		vecf=&x;
	}
	resultLayers() {

	}
};
class lre
{
private:
	vector<resultLayers> veclist;
	vector<VectorXf> listreult;
public:
	lre() ;
	int size() {
		return listreult.size();
	}
	void push(netinput x) {
		resultLayers cli(x.getCol(), x);
		veclist.push_back(cli);
		listreult.push_back(x.get());
	};
	VectorXf getrow(int n) {
		return listreult.at(n);
	}
	void update(netinput x) {
		resultLayers c(x.getCol(), x);
		if (listreult.size() == 0) {
			listreult.push_back(x.get());
			veclist.push_back(c);
		}
		else {
			listreult[0] = x.get();
			veclist[0] = c;
		}
	}
	//int size() {
	//	return listreult.size();
	//}
	int getsize(int n) {
		return listreult[n].size();
	}
	int getlastsize() {
		return listreult[listreult.size() - 1].size();
	}
	void set(RowVectorXf k,int n) {
		
		listreult[n] =k.transpose();
	}
	/*void push(VectorXf x) {
		listreult.push_back(x);
	}*/
	~lre();
};

#endif // !lreee