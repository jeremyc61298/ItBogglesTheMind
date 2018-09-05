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
#include <stack>
#include <iomanip>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;
using std::setw;
using std::left;

struct Point
{
	Point() {}
	Point(int x, int y) : x(x), y(y){}
	int x; 
	int y;
};

struct Letter 
{
	char letter = '#';
	bool usedLetter = false;
};

struct LetterGrid
{
	public:
		LetterGrid() : sizeRowCol(6), letterCount(0), MAX_LOOP(8) {}
		void initializeGrid(ifstream& in);
		bool findWord(string word);
		bool testNextDirections(vector<Point> directions, string wordToFind);
		void reset();

	private:
		bool testNextDirection();
		vector<Point> determineDirections(int row, int col);
		vector<vector<Letter>> grid;
		
		//string wordToFind;
		int totalLetters;
		int letterCount;
		int sizeRowCol;
		const int MAX_LOOP;
};

void LetterGrid::initializeGrid(ifstream& in)
{
	vector <vector<Letter>> newGrid(sizeRowCol, vector<Letter>(sizeRowCol, Letter()));
	grid = newGrid;
	for (int i = 1; i < sizeRowCol - 1; i++)
	{
		string line;
		getline(in, line);
		for (int j = 1; j < sizeRowCol - 1; j++)
		{
			grid[i][j].letter = line[j - 1];
		}
	}
}

bool LetterGrid::findWord(string word)
{
	bool found = false;
	for (int i = 1; i < sizeRowCol - 1 && !found; i++)
	{
		for (int j = 1; j < sizeRowCol - 1 && !found; j++)
		{
			if (grid[i][j].letter == word[0])
			{
				++letterCount;
				grid[i][j].usedLetter = true;
				found = testNextDirections(determineDirections(i, j), word.substr(1));
			}
			reset();
		}
	}
	return found;
}

bool LetterGrid::testNextDirections(vector<Point> directions, string wordToFind)
{
	bool found = false;
	
	// Base Case
	if (directions.empty()) return false;

	Point dir = directions.back();
	directions.pop_back();
	
	if (grid[dir.x][dir.y].letter == wordToFind[0] && !grid[dir.x][dir.y].usedLetter)
	{
		if (wordToFind.size() == 1)
		{
			// Another base case, word has been found
			return true;
		}

		// Found next letter in the word
		grid[dir.x][dir.y].usedLetter = true;
		found = testNextDirections(determineDirections(dir.x, dir.y), wordToFind.substr(1));
		grid[dir.x][dir.y].usedLetter = false;
	}

	if (found != true)
	{
		found = testNextDirections(directions, wordToFind);
	}

	return found;
}

bool LetterGrid::testNextDirection()
{
	bool found = false;
	if (letterCount == totalLetters)
	{
		found = true;
	}
	for (int i = 0; i < MAX_LOOP && !found; i++)
	{
		//Point dir = directions.back();
		//directions.pop_back();
		//if (dir.x >= 0 && dir.x < sizeRowCol && dir.y >= 0 && dir.y < sizeRowCol)
		{
			// direction is valid
			//if (grid[dir.x][dir.y].letter == wordToFind[letterCount] && !grid[dir.x][dir.y].usedLetter)
			//{
			//	// Found next letter in the word
			//	updateDirections(dir.x, dir.y);
			//	++letterCount;
			//	grid[dir.x][dir.y].usedLetter = true;
			//	found = testNextDirection();
			//	grid[dir.x][dir.y].usedLetter = false;
			//}
		}
	}
	if (letterCount != totalLetters && letterCount != 0)
	{
		--letterCount;
	}

	return found;
}

vector<Point> LetterGrid::determineDirections(int row, int col)
{
	// Push new points to search for, starting with Northwest 
	// and ending with North
	vector<Point> directions;
	directions.push_back(Point(row - 1, col - 1));
	directions.push_back(Point(row, col - 1));
	directions.push_back(Point(row + 1, col - 1));
	directions.push_back(Point(row + 1, col));
	directions.push_back(Point(row + 1, col + 1));
	directions.push_back(Point(row, col + 1));
	directions.push_back(Point(row - 1, col + 1));
	directions.push_back(Point(row - 1, col));
	return directions;
}

void LetterGrid::reset()
{
	//directions.resize(0);
	//letterCount = 0;
	for (int i = 0; i < sizeRowCol; i++)
	{
		for (int j = 0; j < sizeRowCol; j++)
		{
			grid[i][j].usedLetter = false;
		}
	}
}

int main()
{
	ifstream fin("boggle.in");
	if (!fin)
	{
		cout << "Input file could not be opened." << endl;
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
		fout << left << setw(17) << word;
		(result) ? fout << "VALID" : fout << "NOT VALID";
		lg.reset();
		getline(fin, word);
		if (word != "*")
		{
			fout << endl;
		}
	}
}