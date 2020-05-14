#include <iostream>
#include <cstring>
#include <cctype>

#include "HangMan.h"

using namespace std;

int main()
{
	do
	{

		PlayGame();

	} while (WantToPlayAgain());

	return 0;
}