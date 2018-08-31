// ----------------------------------------------------------
// boggles.cpp
// Jeremy Campbell
// This program will determine if a word can be found within
// random 4x4 letter grid, only using letters once and never 
// jumping further than one letter.
// ----------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;
using std::setw;

struct LetterGrid
{
	public:
		LetterGrid() : sizeRowCol(4) {}
		void initializeGrid(ifstream& in);
		bool findWord(string word);

	private:
		vector<vector<char>> grid;
		bool visited;
		int sizeRowCol;
};

void LetterGrid::initializeGrid(ifstream& in)
{
	for (int i = 0; i < sizeRowCol; i++)
	{
		string line; 
		vector<char> chars(4);
		getline(in, line);
		for (int j = 0; j < sizeRowCol; j++)
		{
			chars[j] = line[j];
		}
		grid.push_back(chars);
	}
}

bool LetterGrid::findWord(string word)
{
	bool result = false;


	return result;
}

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
	lg.initializeGrid(fin);

	string word;
	getline(fin, word);
	while (word != "*")
	{
		bool result = lg.findWord(word);
		fout << setw(17) << word;
		(result) ? fout << "VALID" : fout << "NOT VALID";
		fout << endl;
		getline(fin, word);
	}
}