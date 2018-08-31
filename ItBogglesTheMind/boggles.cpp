// ----------------------------------------------------------
// boggles.cpp
// Jeremy Campbell
// This program will determine if a word can be found within
// random letter grid, only using letters once and never 
// jumping further than one letter.
// ----------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;

struct LetterGrid
{
	public: 
		void initialzeGrid(ifstream& in);
		bool findWord(string word);

	private:
		vector<vector<char>> grid;
		bool visited;
};

int main()
{
	ifstream fin("boggles.in");
	if (!fin)
	{
		cout << "Input file could not be opened. " << endl;
		return -1;
	}

	ofstream fout("boggle.out");
	LetterGrid lg;



}