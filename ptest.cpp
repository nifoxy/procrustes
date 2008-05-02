#include<iostream>
#include "GridReader.h"
#include "Procrustes.h"
#include<pngwriter.h>
#include<algorithm>
#include<vector>
#include<sstream>

using namespace std;

void writeBoundaries(pngwriter* png, Procrustes* p);
void writeObjects(pngwriter* png, Procrustes* p);
void writePairs(pngwriter* png, vector<pair<int,int>*>* ls, int red, int green , int blue);
void writeIndividualObjects(Procrustes *p);

int main(int argc, char** arg)
{
	string *of;
	int opt;
	bool bound = false;
	bool obj = false;;
	while ((opt = getopt(argc,arg,"o:bd")) != -1)
	{
		switch(opt) {
			case 'o': of = new string(optarg); break;
			case 'b': bound = true; break;
			case 'd': obj = true; break;
		};
	}
	GridReader *ordr = new GridReader(of);
	int orow, ocol, frow, fcol, row, col;
	float** ogrid = ordr->getGrid(ocol,orow);
	pngwriter* obs = new pngwriter(ocol,orow,0,"/tmp/obs.png");
	for (int i = 0; i < orow; i++)
		for (int j = 0; j < ocol; j++)
		{
			if (ogrid[i][j] > 0)
			{
				obs -> plot (j,i,0.0,0.0,1.0);
			}
		}
	Procrustes* p = new Procrustes(obs,ocol,orow);
	pngwriter* t = new pngwriter(ocol,orow,0,"/tmp/ptest.png");
//	writeIndividualObjects(p);
	if (obj)
		writeObjects(t,p);
	if (bound)
		writeBoundaries(t,p);
	obs -> close();
	t -> close();
	delete t;
	delete obs;
	delete ordr;
	delete of;
}

void writeIndividualObjects(Procrustes *p) 
{
	vector<PObject*>* objs = p -> findObjects();
	for (int i = 0; i < objs -> size(); i++)
	{
		PObject* r = objs -> at(i);
		stringstream ss;
		ss << i;
		string f = "/tmp/ptest/" + ss.str();
		f += ".png";
		pngwriter* w = new pngwriter(p->getCol(),p->getRow(),0.0,f.c_str());
//		writePairs(w,r -> getPoints(),0.0,0.0,1.0);
		w->close();
		delete w;
	}
}

void writeBoundaries(pngwriter* png, Procrustes* p)
{
	vector<PObject*>* objs = p -> findObjects();
	for (int i = 0; i < objs -> size(); i++)
	{
		PObject* o = objs -> at(i);
		int b = rand()%65535;
		int g = rand()%65535;
		int r = rand()%65535;
		writePairs(png,o->getBoundary(),r,g,b);
		point* c = o -> getCenter();
		png -> plot(c->first,c->second,0.0,0.0,1.0);
//		cout << c -> first << " " << c -> second << endl;
	}
}

void writeObjects(pngwriter* png, Procrustes* p)
{
	vector<PObject*>* objs = p -> findObjects();
	srand(time(NULL));
	for (int i = 0; i < objs -> size(); i++)
	{
		PObject* o = objs -> at(i);
		int b = rand()%65535;
		int g = rand()%65535;
		int r = rand()%65535;
		writePairs(png,o->getPoints(),r,g,b);
//		cout << r << " " << g << " " << b << endl;
	}
}

void writePairs(pngwriter* png, vector<pair<int,int>*>* ls, int red, int green , int blue)
{
	for (int j = 0; j < ls -> size(); j++)
	{
		pair<int,int>* point = ls -> at(j);
		png -> plot(point -> first, point -> second, red,green,blue);
	}
}
