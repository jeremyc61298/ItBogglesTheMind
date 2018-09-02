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
	Point(int x, int y) : x(x), y(y) {}
	int x; 
	int y;
};

struct Letter
{
	char letter;
	bool usedLetter = false;
};

struct LetterGrid
{
	public:
		LetterGrid() : sizeRowCol(4), letterCount(0), totalLetters(0) {}
		void initializeGrid(ifstream& in);
		bool findWord(string word);
		void reset();

	private:
		bool testNextDirection(Point p);
		void updateDirections(int row, int col);
		vector<vector<Letter>> grid;
		vector<Point> directions;
		string wordToFind;
		int totalLetters;
		int letterCount;
		int sizeRowCol;
};

void LetterGrid::initializeGrid(ifstream& in)
{
	for (int i = 0; i < sizeRowCol; i++)
	{
		string line;
		vector<Letter> chars(4);
		getline(in, line);
		for (int j = 0; j < sizeRowCol; j++)
		{
			chars[j].letter = line[j];
		}
		grid.push_back(chars);
	}
}

bool LetterGrid::findWord(string word)
{
	wordToFind = word;
	totalLetters = word.size();
	bool found = false;
	for (int i = 0; i < sizeRowCol && !found; i++)
	{
		for (int j = 0; j < sizeRowCol && !found; j++)
		{
			if (grid[i][j].letter == wordToFind[letterCount])
			{
				++letterCount;
				grid[i][j].usedLetter = true;
				updateDirections(i, j);
				found = testNextDirection(directions.back());
			}
			reset();
		}
	}
	return found;
}

bool LetterGrid::testNextDirection(Point p)
{
	bool result;
	directions.pop_back();
	if (letterCount == totalLetters)
	{
		return true;
	}
	else if (directions.empty())
	{
		 return false;
	}
	else if (p.x < 0 || p.x >= sizeRowCol || p.y < 0 || p.y >= sizeRowCol)
	{
		// Invalid direction
		result = false;
	}
	else if (grid[p.x][p.y].letter == wordToFind[letterCount] && !grid[p.x][p.y].usedLetter)
	{
		updateDirections(p.x, p.y);
		++letterCount;
		grid[p.x][p.y].usedLetter = true;
	}

	result = testNextDirection(directions.back());
	if (p.x >= 0 && p.x < sizeRowCol && p.y >= 0 && p.y < sizeRowCol)
	{
		grid[p.x][p.y].usedLetter = false;
	}
	// letterCount only decrements if the word has not been found
	if (letterCount != totalLetters && letterCount != 0)
	{
		--letterCount;
	}
	return result;
}

void LetterGrid::updateDirections(int row, int col)
{
	// Push new points to search for, starting with Northwest 
	// and ending with North
	directions.push_back(Point(row - 1, col - 1));
	directions.push_back(Point(row, col - 1));
	directions.push_back(Point(row + 1, col - 1));
	directions.push_back(Point(row + 1, col));
	directions.push_back(Point(row + 1, col + 1));
	directions.push_back(Point(row, col + 1));
	directions.push_back(Point(row - 1, col + 1));
	directions.push_back(Point(row - 1, col));
}

void LetterGrid::reset()
{
	directions.resize(0);
	letterCount = 0;
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