#include<iostream>
#include "GridReader.h"
#include "Procrustes.h"
#include<pngwriter.h>
#include<algorithm>

using namespace std;

int main(int argc, char** arg)
{
	string *of;
	string *ff;
	int opt;
	while ((opt = getopt(argc,arg,"o:f:")) != -1)
	{
		switch(opt) {
			case 'o': of = new string(optarg); break;
			case 'f': ff = new string(optarg); break;
		};
	}
	GridReader *ordr = new GridReader(of);
	GridReader *frdr = new GridReader(ff);
	int orow, ocol, frow, fcol, row, col;
	float** ogrid = ordr->getGrid(ocol,orow);
	float** fgrid = frdr->getGrid(fcol,frow);
	pngwriter* obs = new pngwriter(ocol,orow,0,"/tmp/obs.png");
	pngwriter* fcst = new pngwriter(fcol,frow,0,"/tmp/fcst.png");
	for (int i = 0; i < orow; i++)
		for (int j = 0; j < ocol; j++)
		{
			if (ogrid[i][j] > 0)
			{
				obs -> plot (j,i,0.0,0.0,1.0);
			}
		}
	for (int i = 0; i < frow; i++)
		for (int j = 0; j < fcol; j++)
		{
			if (fgrid[i][j] > 0)
				fcst -> plot (j,i,0.0,0.0,1.0);
		}
	row = max(frow,orow);
	col = max(fcol,ocol);
//	obs -> scale_wh(col,row);
//	fcst -> scale_wh(col,row);
	Procrustes* p = new Procrustes(obs,col,row);
	p -> findObjects();
	obs -> close();
	fcst -> close();
	delete obs;
	delete fcst;
	delete ordr;
	delete frdr;
	delete ff;
	delete of;
}
