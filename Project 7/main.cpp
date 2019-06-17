#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include "Edge.h"
using namespace std;
const int vertex = 8;
int graphMile[8][8] = {
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
};
int graphCost[8][8] = {
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},
};

//Function	:printHead()
//Purpose	:
//Parameters:
//Returns	:
void printHead() {
	cout << "Brendon King" << endl;
	cout << "Project 7" << endl;
	cout << "6/16/2019" << endl << endl;
}

int getAirportIndex(string airport) {
	if (airport == "SFA")
	{
		return 0;
	}
	if (airport == "SFO")
	{
		return 1;
	}
	if (airport == "LAX")
	{
		return 2;
	}
	if (airport == "LV")
	{
		return 3;
	}
	if (airport == "PHX")
	{
		return 4;
	}
	if (airport == "DEN")
	{
		return 5;
	}
	if (airport == "SLC")
	{
		return 6;
	}
	if (airport == "SJC")
	{
		return 7;
	}
}

string getAirportName(int n) {
	switch (n)
	{
	case 0:
		return "SFA";
	case 1:
		return "SFO";
	case 2:
		return "LAX";
	case 3:
		return "LV";
	case 4:
		return "PHX";
	case 5:
		return "DEN";
	case 6:
		return "SLC";
	case 7:
		return "SJC";
	default:
		break;
	}
}

void printDirectFlights(Edge edges) {
	Edge temp = edges;
	cout << getAirportName(temp.src) << "\t" << getAirportName(temp.dest) << "\t" << temp.mile << "\t" << temp.cost << endl;
}

int minimumDist(int dist[], bool Dset[])   
{
	int min = INT_MAX, index;                 
	for (int v = 0; v < 8; v++)
	{
		if (Dset[v] == false && dist[v] <= min)
		{
			min = dist[v];
			index = v;
		}
	}
	return index;
}

void findShortestPath(int graph[vertex][vertex], int graph2[vertex][vertex], string airport) {
	int src = getAirportIndex(airport);
	int distMile[vertex];
	bool dsetMile[vertex];
	int distCost[vertex];
	bool dsetCost[vertex];
	for (int i = 0; i < vertex; i++)                    
	{
		distMile[i] = INT_MAX;
		dsetMile[i] = false;
	}
	for (int i = 0; i < vertex; i++)                   
	{
		distCost[i] = INT_MAX;
		dsetCost[i] = false;
	}
	distMile[src] = 0;
	distCost[src] = 0;
	for (int c = 0; c < 8; c++)
	{
		int u = minimumDist(distMile, dsetMile);              
		dsetMile[u] = true;                              
		for (int v = 0; v < vertex; v++)	
		{
			if (!dsetMile[v] && graph[u][v] && distMile[u] != INT_MAX && distMile[u] + graph[u][v] < distMile[v]) {
				distMile[v] = distMile[u] + graph[u][v];
				distCost[v] = distCost[u] + graph2[u][v];
			}
		}
	}
	cout << "\nDestination\tCost\t\Miles\t" << endl;
	for (int i = 0; i < vertex; i++)                       
	{

		cout << getAirportName(i) << "\t\t" << distMile[i] << "\t" << distCost[i] << endl;
		
	}
}

int main() 
{
	int V = 8;
	Edge edges[15];

	string nextInput;
	string c1, c2;
	int c3, c4;
	int count = 0;
	char userInput = '?';
	string fileName;
	fstream textFile;
	string userInputString;
	printHead();
	while (userInput != 'n')
	{
		cout << "Enter text file name: ";
		cin >> fileName;
		textFile.open(fileName);
		while (textFile.fail())
		{
			cout << "File Read Error. Please try again: ";
			cin >> fileName;
			textFile.open(fileName);
		}
		while (textFile >> nextInput)
		{
			c1 = nextInput;
			textFile >> nextInput;
			c2 = nextInput;
			textFile >> nextInput;
			c3 = stoi(nextInput);
			textFile >> nextInput;
			c4 = stoi(nextInput);
			int temp1 = getAirportIndex(c1);
			int temp2 = getAirportIndex(c2);
			edges[count] = { temp1, temp2, c3, c4 };
			count++;
			graphMile[temp1][temp2] = c3;
			graphMile[temp2][temp1] = c3;

			graphCost[temp1][temp2] = c4;
			graphCost[temp2][temp1] = c4;
		}
		textFile.close();
		cout << "\nDIRECT FLIGHTS" << endl;
		cout << "SRC\tDEST\tMILES\tCOST" << endl;
		for (int i = 0; i < 15; i++)
		{
			printDirectFlights(edges[i]);
		}
		
		//displayMatrix(8);

		cout << "\nEnter Airport: ";
		cin >> userInputString;
		findShortestPath(graphCost, graphMile, userInputString);
	}
	return 0;
}