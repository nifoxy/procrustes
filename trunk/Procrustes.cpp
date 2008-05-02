#include "Procrustes.h"

Procrustes::Procrustes(pngwriter* png, int col, int row)
{
	objs = new vector<PObject*>();
	this -> png = png;
	this -> col = col;
	this -> row = row;
}

Procrustes::~Procrustes()
{
	for (int i = 0; i < objs -> size(); i++)
	{
		delete objs -> at(i);
	}
	delete objs;

}

vector<PObject*>* Procrustes::findObjects() {
	findObjects(0,0);
//	cout << objs -> size() << endl;
	return objs;
}

void Procrustes::findObjects(int x, int y) {
	double pix = 0;
	for (int i = 0; i < col; i++)
		for (int j = 0; j < row; j++)
		{
			pix = png -> dread(i,j,3);
			if (pix > 0)
			{
				PObject* obj = new PObject();
				getObject(i,j,obj);
				if (!(obj -> isEmpty()))
					objs -> push_back(obj);
			}
		}
}

int Procrustes::getObject(int x, int y, PObject* obj) {
	if (x >= col || x < 0 || y >= row || y < 0)
                return PObject::SPACE;
	double pix = png -> dread(x,y,3);
	point* p;
	if (pix > 0)
	{
		p = new point(x,y);
		png -> plot(x,y,0.0,1.0,0.0);
		obj -> addPoint(p);
	}
	else if (png -> dread(x,y,2) > 0)
	{
		return PObject::POINT;
	}
	else if (png -> dread(x,y,1) > 0)
	{
		return PObject::BOUNDARY;
	}
	else
	{
		return PObject::SPACE;
	}
	/**
	*  using integers and checking for 3 spaces reduces redundant boundaries,
	*  using bools is acurate but makes extra boundaries.
	**/
	int* ans = new int[8];
	ans[0] = getObject(x+1,y,obj);
	ans[1] = getObject(x-1,y,obj);
	ans[2] = getObject(x,y+1,obj);
	ans[3] = getObject(x,y-1,obj);
	ans[4] = getObject(x+1,y+1,obj);
	ans[5] = getObject(x-1,y+1,obj);
	ans[6] = getObject(x+1,y-1,obj);
	ans[7] = getObject(x-1,y-1,obj);
	int space = 0;
	int point = 0;
	int bound = 0;
	for (int i = 0; i < 8; i++)
	{
		if (ans[i] == PObject::SPACE)
			space ++;
		else if (ans[i] == PObject::POINT)
			point ++;
		else if (ans[i] == PObject::BOUNDARY)
			bound ++;
	}
	delete [] ans;
	if (space >= 3)
	{
//		cout << "boundary at " << x << "," << y << endl;
		obj -> addBoundary(p);
		png -> plot(x,y,1.0,0.0,0.0);
		return PObject::BOUNDARY;
	}
	return PObject::POINT;
}
