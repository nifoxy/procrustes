#include<iostream>
#include<pngwriter.h>
#include<vector>
#include "PObject.h"

using namespace std;

class Procrustes {
  public:
	Procrustes(pngwriter*, int col, int row);
	~Procrustes();
	vector<PObject*>* findObjects();
	int getCol() {
		return col;
	};
	int getRow() {
		return row;
	};
  private:
	vector<PObject*>* objs;
	pngwriter* png;
	int col;
	int row;
	void findObjects(int x, int y);
	int getObject(int x, int y, PObject* obj);
};
