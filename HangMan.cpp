#include <iostream>
#include <cctype>

#include "HangMan.h"

using namespace std;

const int IGNORE_CHARS = 256;
const char* INPUT_ERROR_STRING = "Input error! Please try again.";

int GetSecretPhrase(char secretPhrase[], int maxLength)
{
	bool failure;
	int length;
	do
	{
		failure = false;

		cout << "Please enter the secret phrase: ";
		cin.get(secretPhrase, maxLength);

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << INPUT_ERROR_STRING << endl;
			failure = true;
		}
		else
		{
			length = strlen(secretPhrase);

			if (length == 0)
			{
				cout << "You must enter a word that's longer than 0 characters! Please try again." << endl;
				failure = true;
			}
		}
	} while (failure);


	return length;
}

char* MakeHiddenPhrase(const char* secretPhrase, int secretPhraseLength)
{
	char* hiddenPhrase = new char[secretPhraseLength + 1];

	for (int i = 0; i < secretPhraseLength; i++)
	{
		if (secretPhrase[i] != ' ')
		{
			hiddenPhrase[i] = '-';
		}
		else
			hiddenPhrase[i] = ' ';
	}

	hiddenPhrase[secretPhraseLength] = '\0';

	return hiddenPhrase;
}

char GetGuess()
{
	return GetCharacter("Please input your guess: ", INPUT_ERROR_STRING);
}

void UpdateBoard(char guess, char* noptrHiddenPhrase, const char secretPhrase[], int secretPhraseLength, int& numberOfGuessesLeft)
{
	bool found = false;

	for (int i = 0; i < secretPhraseLength; i++)
	{
		if (tolower(secretPhrase[i]) == guess)
		{
			noptrHiddenPhrase[i] = secretPhrase[i];
			found = true;
		}
	}

	if (!found)
	{
		numberOfGuessesLeft--;
	}

}

bool IsGameOver(int numberOfGuessesLeft, const char* noptrHiddenPhrase, int secretPhraseLength)
{
	bool hasDash = false;

	for (int i = 0; i < secretPhraseLength; i++)
	{
		if (noptrHiddenPhrase[i] == '-')
		{
			hasDash = true;
			break;
		}
	}

	return numberOfGuessesLeft == 0 || !hasDash;
}

void DisplayResult(const char* secretPhrase, int numberOfGuessesLeft)
{
	if (numberOfGuessesLeft > 0)
	{
		cout << "You got it! The phrase was: " << secretPhrase << endl;
	}
	else
	{
		cout << "You didn't get it.... The phrase was: " << secretPhrase << endl;
	}
}

bool WantToPlayAgain()
{
	const char validInputs[] = { 'y', 'n' };

	char response = GetCharacter("Would you like to play again? (y/n) ", INPUT_ERROR_STRING, validInputs, 2);

	return response == 'y';
}

void DrawBoard(int numberOfGuessesLeft, const char* noptrHiddenPhrase)
{

	ClearScreen();

	switch (numberOfGuessesLeft)
	{
	case 0:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\" << endl;
		cout << " |  / \\" << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 1:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\" << endl;
		cout << " |  /" << endl;
		cout << "-+-" << endl << endl;
	}
	break;

	case 2:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\" << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 3:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|" << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 4:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |   |" << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 5:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  " << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 6:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |  " << endl;
		cout << " |  " << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	default:
		break;
	}

	cout << "Secret Phrase: " << noptrHiddenPhrase << endl << endl;
}

void PlayGame()
{
	const int MAX_LENGTH_OF_SECRET_PHRASE = 256;
	const int MAX_NUMBER_OF_GUESSES = 6;

	char secretPhrase[MAX_LENGTH_OF_SECRET_PHRASE];
	char* optrHiddenPhrase = nullptr;
	int numberOfGuessesLeft = MAX_NUMBER_OF_GUESSES;

	int secretPhraseLength = GetSecretPhrase(secretPhrase, MAX_LENGTH_OF_SECRET_PHRASE);

	optrHiddenPhrase = MakeHiddenPhrase(secretPhrase, secretPhraseLength);

	DrawBoard(numberOfGuessesLeft, optrHiddenPhrase);

	char guess;

	do
	{
		guess = GetGuess();

		UpdateBoard(guess, optrHiddenPhrase, secretPhrase, secretPhraseLength, numberOfGuessesLeft);

		DrawBoard(numberOfGuessesLeft, optrHiddenPhrase);


	} while (!IsGameOver(numberOfGuessesLeft, optrHiddenPhrase, secretPhraseLength));

	DisplayResult(secretPhrase, numberOfGuessesLeft);

	delete[] optrHiddenPhrase;

}

char GetCharacter(const char* prompt, const char* error)
{

	const int IGNORE_CHARS = 256;

	char input;
	bool failure;

	do
	{
		failure = false;

		cout << prompt;
		cin >> input;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << error << endl;
			failure = true;
		}
		else
		{
			cin.ignore(IGNORE_CHARS, '\n');

			if (isalpha(input))
			{
				input = tolower(input);
			}
			else
			{
				cout << error << endl;
				failure = true;
			}
		}

	} while (failure);

	return input;
}

char GetCharacter(const char* prompt, const char* error, const char validInput[], int validInputLength)
{

	const int IGNORE_CHARS = 256;

	char input;
	bool failure;

	do
	{
		failure = false;

		cout << prompt;
		cin >> input;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << error << endl;
			failure = true;
		}
		else
		{
			cin.ignore(IGNORE_CHARS, '\n');

			if (isalpha(input))
			{
				input = tolower(input);

				for (int i = 0; i < validInputLength; i++)
				{
					if (input == validInput[i])
					{
						return input;
					}
				}
			}

			cout << error << endl;
			failure = true;

		}

	} while (failure);

	return input;
}

void ClearScreen()
{
	system("clear");
}

void WaitForKeyPress()
{
	system("read -n 1 -s -p \"Press any key to continue...\";echo");
}