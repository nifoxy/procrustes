#include<iostream>
#include<vector>
#include<map>

using namespace std;

typedef pair<int,int> point;

class PObject {
  public:
	PObject();
	~PObject();
	static const int POINT = 1;
	static const int SPACE = 2;
	static const int BOUNDARY = 3;
	void addPoint(point* p);
	void addBoundary(point* p);
	vector<point*>* getBoundary();
	vector<point*>* getPoints();
	point* getCenter();
	bool isEmpty();
  private:
	point* center;
	vector<point*>* bound;
	vector<point*>* points;
	double* dist;
	void getCenter(int acc);
	double getDistance(point* p1, point* p2);
	void getDistance(int acc);
	double getDistance(point* p, int acc);
	double getLeft(point* p);
	double getRight(point* p);
	double getTop(point* p);
	double getBottom(point* p);
};
