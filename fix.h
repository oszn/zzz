#pragma once
#ifndef fiix
#define fixx
#include"lre.h"
#include"outlayer.h"
#include"sta.h"
#include<map>
class fix
{
private:
	float rate;
	map<int, int> lbp;
	lre result;//store hidden and input
	outlayer weight;//store weight maybe baits next;
public:
	fix();
	void setInput(vector<float> x) {
		rate = 0.5;
		netinput input(x);
		//resultlayer.push(x);
		result.update(input);
	}
	void set_weight(int start) {
		VectorXf v1=result.getrow(start);
		VectorXf v2 = result.getrow(start+1);
		mid m(v2.size(), v1.size());
		weight.push_layers(m);
	}
	//前项传播

	VectorXf forward() {
		/********
		*firstr check date:2020/6/27 17:11 author liuyi or u can call me oszn
		*in this section,i calculate by myself,at least forward process is ok.(include function int sta.h simoid f_vec),i have to say ptr void is really amazing.
		*if u hava any question u can email this mailbox(1091756452@qq.com)
		*/
		cout << result.getrow(0).transpose()<<endl;
		for (int i = 1; i < result.size(); i++) {
			VectorXf x = getmultiply(result.getrow(i-1), weight.getmaxtrix(i - 1));
			//cout << x << "before-"<<endl;
			x = f_vec(x, simoid);
			//cout << "forward_step____________________________________________________" << i << endl;
			//cout << x.transpose() << endl;
			//cout << weight.getmaxtrix(i - 1) << endl<<"---------------------------"<<endl;
			//cout << weight.getmaxtrix(i) << endl<<"------------------------------"<<endl;
			result.set(x, i);
		}
		return result.getrow(result.size() - 1);
	}
	void setoutput(vector<int> lables) {
		map<int, int> temp;
		for (auto c : lables) {
			if (temp.count(c) == 0)
				temp[c] = temp.size() + 1;
		}
		vector<float> rpx;
		int num = 0;
		for (auto xx : temp) {
			lbp[xx.first] = num;
			rpx.push_back(num);
			num++;
		}
		netinput end(rpx.size());
		result.push(end);
		set_weight(result.size()-2);
	}
	//得到结果矩阵
	vector<float> getouput_label(int lb) {
		vector<float> x(result.getrow(result.size()-1).size());
		x[lbp[lb]] = 1;
		return x;
	}
	float getDerivative(int level,int c,int l) {
		VectorXf tmp = result.getrow(level-1);
		return tmp(l);
	}
	vector<float> setonline(vector<float> target) {
		//int n=result.getlastsize();
		vector<float> err(target.size());
		int n = weight.size();
		VectorXf temp = result.getrow(n);
		//cout << weight.getmaxtrix(n - 1) << endl << "-----------------------" << endl;
		for (int i = 0; i < target.size(); i++) {
			float err1 = getErrorValue(target[i], temp[i]);
			float err2 = getfxshame(temp[i]);
			err[i]=(err1*err2);
			for (int j = 0; j < result.getsize(n - 1); j++) {
				float err3 = getDerivative(n, i,j);
				float w = weight.get(n - 1,i, j);
				float neww = w - err1 * err2*err3*rate;
				weight.set(n-1, i, j,neww);
				//cout << weight.getmaxtrix(n - 1)<<endl<<"--------------"<<endl;
			}
		}
		return err;
	}
	vector<float> getmse(vector<float> x,int c,matrix m) {
		float r = 0;
		//matrix m = weight.getmaxtrix(c);
		//cout << m<<endl<<"mse---------------"<<endl;
		vector<float> rs;
		for (int i = 0; i < m.cols(); i++) {
			for (int j = 0; j < m.rows(); j++) {
				r += m(j, i)*x[j];				
			}
			rs.push_back(r);
			r = 0;
		}
		return rs;
	}
	void print_map() {
		for (auto c : lbp) {
			cout << c.first << ":" << c.second << endl;

		}
	}
	//得到隐藏层误差
	vector<float> ppx(vector<float> target,int n) {
		vector<float> err(target.size());
		//int n = result.size() - 1;
		VectorXf temp = result.getrow(n);
		//cout << weight.getmaxtrix(n - 1) << endl << "-----------------------" << endl;
		for (int i = 0; i < target.size(); i++) {
			float err1 = target[i];
			float err2 = getfxshame(temp[i]);
			err[i] = (err1*err2);
			for (int j = 0; j < result.getsize(n - 1); j++) {
				float err3 = getDerivative(n, i, j);
				float w = weight.get(n - 1, i, j);
				float neww = w - err1 * err2*err3*rate;
				weight.set(n - 1, i, j, neww);
				//cout << weight.getmaxtrix(n - 1) << endl << "--------------" << endl;
			}
		}
		return err;
	}
	void backpro(vector<float> label,int cx) {
		/***first check backpro
		*check backpro date:2020/6/27 23:24 auther oszn
		*in this section,there 2 part to deal with backpro.
			1.output backpro.
			2.hidden backpro.
		in fact this process mabey very similar.it is a Derivative process.so in particular,u must get every layer's output throghted function(f(x)->sigmoid).
		an then u can get a chain to get previous weight_matrix's drop direction.
		so if u want through output changing wij
		1.output=f(in) in fact,if  u known ptr void,u can easyly use any function as f,in my it's sigmoid.
		2.labels,if type is third,and lables's num is 4 and the vector is[0,0,1,0]
			*actually,there might be all random number weight in begin,i set them between -1 and 1.so as result,output might be not perfect to our labels.
			*but it's normal,so we can adjust them.throght oceans reading,i think,we should adjust wij,so any layer output is only result,not reason. 
			*so the meaning of Derivative is obvious,we can throght fun by result and adjust weight.
			*mse=(1/2)*(output-labels)^2 ,actuall in classfier the loss function should be another void name cross entropy,it's part of Kullback-Leibler.it's previous part is static so left part is cross entropy
			*mse'=0.5*2*(output-labels)*output'
			*output'=f'(x) and if function is sigmoid.(1/(1+e^(-x)))
			*sigmoid'=-e^(-x)/(1+e^(-x))^2=sigmoid*(1-sigmoid)
			*so output'=simoid*(1-sigmoid)
			*but if we want wij,we just get x.and this x is anthor y(output),so we replace this x as y
			*y1=w11*h_n1+w12*h_n2....;
			*w11'Derivativs is h_n1,w12'Derivative is h_n2.
			*this is the all process,it's chain process.
		3.diffent between output layer and hidden layer.
			*output layer is easy.
			*hidden layer is get from last output loss*wij.this wij is not adjusted.
		*
		*
		*
		*
		***/
		vector<float> mse = getouput_label(cx);
		int n = weight.size();
		matrix temp = weight.getmaxtrix(n-1);
		//cout << temp << endl << "--------------------------outputbeefore!!!!" << endl;
		vector<float> errs=setonline(mse);
		//cout << weight.getmaxtrix(n - 1)<<endl<<"-------------------------------ouputUpdate!!!!"<<endl;
		for (int i = n - 1; i >= 1; i--) {
		//	cout << "fffff-------------------" << i << endl;
			vector<float> next = getmse(errs,i,temp);
			//cout << "_____next___erorr" << endl
			if(i>=0)
			temp = weight.getmaxtrix(i - 1);
			//cout << weight.getmaxtrix(i - 1) << endl << "----------------"<< endl;
			errs=ppx(next, i);
			//cout << weight.getmaxtrix(i - 1) << endl << "----------------" << endl;
			//cout<<endl;
		}
		int as = 0;
	}
	/***
这一步是设置layers
这是把网络，和结果矩阵放进去
需要设置w参数。
*/
	void set_layers(vector<int> level) {
		for (int i = 0; i < level.size(); i++) {
			netinput x(level[i]+1);
			result.push(x);
			//resultlayer.push(x.get());
			set_weight(i);
		}
	}
	~fix();
};

#endif // !fiix