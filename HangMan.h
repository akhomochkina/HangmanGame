#ifndef __UTILS_H__
#define __UTILS_H__

int GetSecretPhrase(char secretPhrase[], int maxLength);
char* MakeHiddenPhrase(const char* secretPhrase, int secretPhraseLength);
char GetGuess();
void UpdateBoard(char guess, char* noptrHiddenPhrase, const char secretPhrase[], int secretPhraseLength, int& numberOfGuessesLeft);
bool IsGameOver(int numberOfGuessesLeft, const char* noptrHiddenPhrase, int secretPhraseLength);
void DisplayResult(const char* secretPhrase, int numberOfGuessesLeft);
bool WantToPlayAgain();
void DrawBoard(int numberOfGuessesLeft, const char* noptrHiddenPhrase);
void PlayGame();
char GetCharacter(const char* prompt, const char* error);
char GetCharacter(const char* prompt, const char* error, const char validInput[], int validInputLength);
void ClearScreen();
void WaitForKeyPress();

#endif