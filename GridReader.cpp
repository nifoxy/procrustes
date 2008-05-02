#include<string>
#include "GridReader.h"

GridReader::GridReader(string* file) {
	in = new ifstream(file->c_str(),ifstream::in);
	coords = new vector<pair<int,int>*>();
}

float** GridReader::getGrid(int &col, int &row) {
	vector<string>* lines = new vector<string>();
	string* line = new string();
	while (getline(*in,*line))
	{
		lines->push_back(*line);
	}
	float** grid = new float*[lines->size()];
	row = lines -> size();
	for (int i = 0; i < lines->size(); i++)
	{
		grid[i] = split(lines->at(i),col);
	}
	delete line;
	delete lines;
	return grid;
}

float* GridReader::split(string l, int &col) {
	vector<string>* ls = new vector<string>();
	string* s = new string("");
	for (int i = 0; i < l.length(); i++)
	{
		char c = l[i];
		if (c == delim)
		{
			ls -> push_back(*s);
			s -> clear();
		}
		else if (c == '_')
		{
			ls -> push_back("0");
		}
		else
		{
			s -> push_back(c);
		}
	}
	if (!s -> empty())//last cell
	{
		ls -> push_back(*s);
	}
	float* ans = new float[ls->size()];
	for (int i = 0; i < ls->size(); i++)
	{
		string f = ls->at(i);
		ans[i] = atof(f.c_str());
	}
	col = ls -> size();
	delete s;
	delete ls;
	return ans;
}

GridReader::~GridReader() {
	in -> close();
	delete in;
	delete coords;
}
