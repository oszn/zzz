#include"input.h"
#include"mid.h"
//#include <iostream>
//#include <Eigen/Dense>
//using namespace Eigen;
//using namespace std;
#include"fix.h"


typedef Matrix<double, Dynamic, Dynamic> matrixw;

int main() {
	/*netinput np(5);
	np.init(2);*/
	int n = 4;
	//netinput x(n);
	
	fix f;
	vector<float> c=getxn(2,n);
	vector<float> c1 = getxn(3, n);
	f.setInput(c);
	vector<int> layers{3,6};
	f.set_layers(layers);
	vector<int>cq{1,1,3,2,2,3,3,4,4,5};
	f.setoutput(cq);
	for (int i = 0; i < 200; i++) {
		VectorXf tx=f.forward();
		cout << tx.transpose() << endl;
		f.backpro(c,3.9);
	}
	f.print_map();
	system("pause");
	return 0;
}