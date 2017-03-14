#include "splaytree.h"
#include "node.h"
#include <cassert>
#include <sstream>
#include <iostream>
#include <ifstream>
#include <cstdio>
#include <cstdint>
using std::cout;
using std::endl;
using std::cout;
using std::cin;
#include <string>
using std::string;
#include <vector>
#include <sstream>

std::vector<int> starttime;
std::vector<int> endtime;
std::vector<int> classnum;
std::vector<string> classes1;
std::vector<int> classes2;
int numofclasses;

Intervals::Intervals()
{
	
	numofclasses = 0;
}
Intervals::Intervals(char * a1)
{
	openfile1(a1);
	bSearch();
	findMax(classes1);
}

void Intervals::openfile1(string a1)
{
	
string line;	
ifstream myfile;
myfile.open(a1);
int c = 0;
if(myfile.is_open())
{
	while(getline(myfile,line))
	{
		if (c == 0)
		{
			numofclasses = (int)line.front;
			starttime.resize(numofclases);
			endtime.resize(numofclasses);
			classnum.resize(numofclasses);
			c++;
			
		}
		else{
		cout << line << '\n';
		divide(line);
		}
	}
	myfile.close();
}
}

void Intervals::addtovectors(int a, int b, int c)
{
	classnum.push_back(a);
	starttime.push_back(b);
	endtime.push_back(c);
	
	
}

void Intervals::divide(string a)
{
	stringstream iss;
	iss << a;
	int a0;
	int a1;
	int a2;
	iss >> a0 >> a1 >> a2;
	addtovectors(a0,a1,a2);
	
	
	
}
void Intervals::bSearch()
{
	int x0;
	int x1;
	int x2;
	int x3;
	int x4;
	int x5;
	string load;
	
	for (unsigned i=0; i<classnum.size(); i++)
	{
    x0 = classnum.at(i);
	x1 = starttime.at(i);
	x2 = endtime.at(i);
	for(unsigned j=0; i < classnum.size(); i++)
	{
	 x3 = classnum.at(j);
	 x4 = starttime.at(j);
	 x5 = endtime.at(j);
		if((j/x0) != 1)
		{
		  check(x1,x2,x4,x5);
			
			
		}
		else
		{
			load = "" + x0 + " " + x1 + " " + x2 + "\n";
			classes1.push_back(load);
			
		}
	}
	}
}
void Intervals::check(int c0, int c1, int c2, int c3)
{
	bool c4 = 0;
	 if ((c2 >= c1 ) || (c3 <= c0))
	 {
		 
		 c4 = 1;
		 return;
		 
		 
		 
	 }
	
	return c4;
}
findMax(vector
