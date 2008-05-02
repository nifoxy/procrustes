#include "PObject.h"
#include <math.h>

PObject::PObject() {
	bound = new vector<point*>();
	points = new vector<point*>();
}

PObject::~PObject() {
	for (int i = 0; i < bound -> size(); i++)
		delete bound -> at(i);
	for (int i = 0; i < points -> size(); i++)
		delete points -> at(i);
	delete points;
	delete bound;
	delete [] dist;
}

void PObject::addPoint(point* p) {
	points -> push_back(p);
}

void PObject::addBoundary(point* p) {
	bound -> push_back(p);
	for (vector<point*>::iterator i = points->begin(); i < points->end(); i++)
	{
		if (p == *i)
		{
			points -> erase(i,i+1);
		}
	}
}

vector<point*>* PObject::getBoundary() {
	return bound;
}

vector<point*>* PObject::getPoints() {
	return points;
}

point* PObject::getCenter() {
/*	if (center != NULL)
	{
		cout << "not null" << endl;
		return center;
	}*/
	if (isEmpty())
		return NULL;
	dist = new double[points->size()];
	getDistance(0);
	double max = 10000.0;
	int q = 0;
	for (int i = 0; i < points -> size(); i++)
	{
		if (dist[i] < max)
		{
			q = i;
			max = dist[i];
		}
	}
	center = points -> at(q);
	return center;
}

double PObject::getDistance(point* p1, point* p2) {
	return sqrt((double)(pow(p2->first-p1->first,2)+pow(p2->second-p1->second,2)));
}

void PObject::getDistance(int acc)
{
	point* p,*b;
	for (int i = 0; i < points -> size(); i++)
	{
		dist[i] = 0.0;
		for (int j = 0; j < bound -> size(); j++)
		{
			p = points->at(i);
			b = bound->at(j);
			if (p->first==b->first && p->second==b->second)
				continue;
			dist[i] += getDistance(p,b);
		}
	}
}

/*
void PObject::getDistance(int acc)
{
	if (acc >= points -> size())
		return;
	point* p = points -> at(acc);
	dist[acc] = getDistance(p,0);
//	dist[acc] = getLeft(p) + getRight(p) + getTop(p) + getBottom(p);
	getDistance(acc+1);
}
*/

double PObject::getDistance(pair<int,int>* p, int acc)
{
	if (acc >= bound -> size())
		return 0;
	point* b = bound -> at(acc);
	if (p->first == b->first && p->second == b->second)
		return 0.0;
	return getDistance(p,b) + getDistance(p,acc+1);
}

double PObject::getTop(point* p)
{
	for (int i = 0; i < bound -> size(); i++)
	{
		point* b = bound -> at(i);
		if (b->first == p->first && b->second < p->second)
			return p->second - b->second;
	}
	return 0;
}

double PObject::getBottom(point* p)
{
	for (int i = 0; i < bound -> size(); i++)
	{
		point* b = bound -> at(i);
		if (b->first == p->first && b->second > p->second)
			return p->second - b->second;
	}
	return 0;
}

double PObject::getLeft(point* p)
{
	for (int i = 0; i < bound -> size(); i++)
	{
		point* b = bound -> at(i);
		if (b->first < p->first && b->second == p->second)
			return p->second - b->second;
	}
	return 0;
}

double PObject::getRight(point* p)
{
	for (int i = 0; i < bound -> size(); i++)
	{
		point* b = bound -> at(i);
		if (b->first > p->first && b->second == p->second)
			return p->second - b->second;
	}
	return 0;
}

bool PObject::isEmpty()
{
	return (points -> size() == 0);
}
