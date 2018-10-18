#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

void PrintIntro();
string GetGuessAndPrintBack();

constexpr int WORD_LENGTH = 5;

// the entry point for our application
int main(){

	PrintIntro();

	constexpr int NUMBER_OF_TURNS = 5;
	for (int i = 1; i <= NUMBER_OF_TURNS; i++) {
		GetGuessAndPrintBack();
		cout << endl;
	}

	return 0;
} 

void PrintIntro(){

	// introduce the game
	cout << "Welcome to Bulls and Cows\n";
	cout << "Can you guess the " << WORD_LENGTH;
	cout << " letter isogram I'm thinking of?\n";
	cout << endl;
	return;
}

string GetGuessAndPrintBack() {

	// get guess from the player
	cout << "Enter your guess: ";
	string Guess = "";
	getline(cin, Guess);

	// print the guess back
	cout << "Your guess was " << Guess << endl;
	return Guess;
}