#include "outlayer.h"



outlayer::outlayer()
{
}

void outlayer::push_layers(mid m)
{
	pair<int, int> cr = m.getRowsCows();
	all_layes.push_back(layers(cr.first, cr.second,m));
}
outlayer::~outlayer()
{

}
