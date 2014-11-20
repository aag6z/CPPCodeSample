#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "SeparateChaining.h"

using namespace std;

void findForward(int width, int length, vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha);
void findBackward(int width, int length, vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha);
void findUpward(int width, int length, vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha);
void findDownward(int width, int length, vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha);
void findTopRightDiag(int width, int length, vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha);
void findTopLeftDiag(int width, int length, vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha);
void findBottomLeftDiag(int width, int length, vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha);
void findBottomRightDiag(int width, int length, vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha);


int main()
{
ifstream myfile;
string filename = "words.txt";
//cout << "Enter file name: ";
//cin >> filename;
myfile.open(filename.c_str());

if(myfile.is_open())
{
string line;
HashTable ht("NOT FOUND");
HashTable ha("NOT FOUND");

getline(myfile,line);
while(! myfile.eof())
	{
	
	for(int i = 3; i <= (line.length() - 1 ); i++)
	{
		string s = line.substr(0,i);
		ha.insert(s);		
	}
ht.insert(line);
getline(myfile,line);
}
myfile.close();

ifstream myfile2;
//cout << "Enter file name for puzzle: ";
//cin >> filename;
filename = "50x50.grid.txt";
myfile2.open(filename.c_str());

if(myfile2.is_open())
{
	string line;
	getline(myfile2, line);
	int width = atoi(line.c_str());
	getline(myfile2, line);
	int length = atoi(line.c_str());
	
	vector<vector<char> > puzzle(width, vector<char>(length, 0));
	
	getline(myfile2,line);
	for(int i = 0; i < width; i++){
		
		for(int j = 0; j < length; j++)
		{
			puzzle[i][j] = line[(length*i)+j];
		}
	}	

	cout << endl;
	/*for(int i = 0; i < puzzle.size(); i++){
		for(int j = 0; j < puzzle[0].size(); j++)
		{
			cout << puzzle[i][j];
		}
		cout << endl;
	}*/

//Puzzle searching
vector<string> wordList;

for(int i = 0; i < width; i++){
	for(int j = 0; j < length; j++)
	{
		if(j <= length - 3)
			findForward(i, j, wordList, puzzle, ht, ha);
		if(j >= 2)
			findBackward(i, j, wordList, puzzle, ht, ha);
		if(i >= 2)
			findUpward(i, j, wordList, puzzle, ht, ha);
		if(i <= width - 3)
			findDownward(i, j, wordList, puzzle, ht, ha );
		if(i >= 2 && j >= 2)
			findTopLeftDiag(i, j, wordList, puzzle, ht, ha );
		if(i >= 2 && j <= length - 3)
			findTopRightDiag(i, j, wordList, puzzle, ht, ha);
		if(i <= width - 3 && j >= 2)
			findBottomLeftDiag(i, j, wordList, puzzle, ht, ha );
		if(i <= width - 3 && j <= length - 3)
			findBottomRightDiag(i, j, wordList, puzzle, ht, ha);
	}
}

for(int i = 0; i < wordList.size(); i++)
	cout << endl<< wordList.at(i);

cout << endl << endl << "Total number of words:" << wordList.size();
}





else
cout << "Error opening file";
}
else
cout << "Error opening file";


cout << endl << endl;
return 0;
}





void findForward(int w, int l,  vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha ){
int width = p.size();
	int length = p[0].size();
	string a = "";
	a += p[w][l];
	a += p[w][l + 1];
	
	for(int k = 2; l+k < length && k < 22; k++){ 
		
		a += p[w][l + k];
		if(ht.find(a).compare("NOT FOUND")){
			if(ha.find(a).compare("NOT FOUND"))
				return;
	
		else
		{
			wordList.push_back(a);
			if(ha.find(a).compare("NOT FOUND"))
				return;
		}
	}
	}	

}

void findBackward(int w, int l,  vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha ){
	int width = p.size();
	int length = p[0].size();
	string a = "";
	a += p[w][l];
	a += p[w][l - 1];

	for(int k = 2; l - k >= 0 && k < 22; k++){ 
		
		a += p[w][l - k];
		if(ht.find(a).compare("NOT FOUND")){
			if(ha.find(a).compare("NOT FOUND"))
				return;
	
		else
		{
			wordList.push_back(a);
			if(ha.find(a).compare("NOT FOUND"))
				return;
		}
	}
	}
	
}

void findUpward(int w, int l,  vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha ){
	int width = p.size();
	int length = p[0].size();
	string a = "";
	a += p[w][l];
	a += p[w - 1][l];
	
	for(int k = 2; w - k >= 0 && k < 22; k++){ 
		
		a += p[w - k][l];
		if(ht.find(a).compare("NOT FOUND")){
			if(ha.find(a).compare("NOT FOUND"))
				return;
	
		else
		{
			wordList.push_back(a);
			if(ha.find(a).compare("NOT FOUND"))
				return;
		}
		}
	}
}

void findDownward(int w, int l,  vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha ){
	int width = p.size();
	int length = p[0].size();
	string a = "";
	a += p[w][l];
	a += p[w + 1][l];
	
	for(int k = 2; w+k < width && k < 22; k++){ 
		
		a += p[w + k][l];
		if(ht.find(a).compare("NOT FOUND")){
			if(ha.find(a).compare("NOT FOUND"))
				return;
	
		else
		{
			wordList.push_back(a);
			if(ha.find(a).compare("NOT FOUND"))
				return;
		}
	}
	}
}

void findTopLeftDiag(int w, int l,  vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha ){
	int width = p.size();
	int length = p[0].size();
	string a = "";
	a += p[w][l];
	a += p[w-1][l-1];

	for(int k = 2; (w-k) >= 0 && k < 22 && (l-k) >= 0; k++){ 
		
		a += p[w-k][l-k];
		if(ht.find(a).compare("NOT FOUND")){
			if(ha.find(a).compare("NOT FOUND"))
				return;
	
		else
		{
			wordList.push_back(a);
			if(ha.find(a).compare("NOT FOUND"))
				return;
		}
	}
	}
}
void findTopRightDiag(int w, int l,  vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha ){
	int width = p.size();
	int length = p[0].size();
	string a = "";
	a += p[w][l];
	a += p[w-1][l+1];
	string temp = "NOT FOUND";
	for(int k = 2; (w-k) >= 0 && k < 22 && l+k < length; k++){ 
		
		a += p[w-k][l+k];
		if(ht.find(a).compare("NOT FOUND")){
			if(ha.find(a).compare("NOT FOUND"))
				return;
	
		else
		{
			wordList.push_back(a);
			if(ha.find(a).compare("NOT FOUND"))
				return;
		}
		}
	}
}

void findBottomLeftDiag(int w, int l,  vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha ){
	int width = p.size();
	int length = p[0].size();
	string a = "";
	a += p[w][l];
	a += p[w+1][l-1];
	string temp = "NOT FOUND";
	for(int k = 2; k+w < width && k < 22 && (l-k) >= 0; k++){ 
		
		a += p[w+k][l-k];
		if(ht.find(a).compare("NOT FOUND")){
			if(ha.find(a).compare("NOT FOUND"))
				return;
	
		else
		{
			wordList.push_back(a);
			if(ha.find(a).compare("NOT FOUND"))
				return;
		}
	}
	}
}

void findBottomRightDiag(int w, int l,  vector<string> & wordList, vector< vector<char> > & p, HashTable & ht, HashTable & ha ){
	int width = p.size();
	int length = p[0].size();
	string a = "";
	a += p[w][l];
	a += p[w+1][l+1];
	bool prev = false;

	for(int k = 2; k+w < width && k < 22 && k+l < length; k++){ 
		a += p[w+k][l+k];
		if(ht.find(a).compare("NOT FOUND")){
			if(ha.find(a).compare("NOT FOUND"))
				return;
	
		else
		{
			wordList.push_back(a);
			if(ha.find(a).compare("NOT FOUND"))
				return;
		}
		}

	}

}
