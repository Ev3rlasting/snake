#pragma once
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;
#define HEIGHT 25
#define WIDTH 50
char * MapReader(char Items[][WIDTH]) {
	int temp = 0;
	int H=0,W=0;
	ifstream Map;
	Map.open("map.txt",std::ios::in);
	for(int i=0;i<HEIGHT;i++)
	{	
		for(int j=0;j<WIDTH;j++)
	{
		Map.get(Items[i][j]);
	}
		Map.get();
	}
	Map.close();
	return *Items;
}

char * GameOverReader(char Items[][WIDTH]) {
	int temp = 0;
	int H=0,W=0;
	ifstream Map;
	Map.open("GameOver.txt",std::ios::in);
	for(int i=0;i<HEIGHT;i++)
	{	
		for(int j=0;j<WIDTH;j++)
	{
		Map.get(Items[i][j]);
	}
		Map.get();
	}
	Map.close();
	return *Items;
}

char * ScoreReader(char Items[][3],char Name[]) {
	int temp = 0;
	int H=0,W=0;
	ifstream Map;
	Map.open(Name,std::ios::in);
	for(int i=0;i<5;i++)
	{	
		for(int j=0;j<3;j++)
	{
		Map.get(Items[i][j]);
	}
		Map.get();
	}
	Map.close();
	return *Items;
}

