// ----------------------------------------------------------
// boggles.cpp
// Jeremy Campbell
// This program will determine if a word can be found within
// random letter grid, only using letters once and never 
// jumping further than one letter.
// ----------------------------------------------------------

#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;

int main()
{
	ifstream fin("boggles.in");
	if (!fin)
	{
		cout << "Input file could not be opened. " << endl;
		return -1;
	}

	ofstream fout("boggle.out");


}