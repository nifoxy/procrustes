#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class GridReader {
  public:
	GridReader(string* file);
	~GridReader();
	float** getGrid(int &row, int &col);
  private:
	ifstream* in;
	static const char delim = ' ';
	float* split(string l, int &col);
	vector<pair<int,int>*>* coords;
};
