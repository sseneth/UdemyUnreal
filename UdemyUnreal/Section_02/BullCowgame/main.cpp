/* This is the console executable, that makes use of the BullCow cass
This acts as the view in a MCV pattern, and is responsoble for all user interaction.
For game logic, see the FBullCowGame class
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool PlayAgain();

FBullCowGame BCGame;

// the entry point for our application
int main(){

	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();

		bPlayAgain = PlayAgain();
	} 
	while (bPlayAgain);
	
	return 0;
} 

void PrintIntro(){

	// introduce the game
	std::cout << "Welcome to Bulls and Cows\n";
	std::cout << "Can you guess the " << BCGame.GetWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}

void PlayGame() {

	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries << std::endl;

	//loop for the number of turns asking for guesses
	//TODO change from for to while loops
	for (int32 i = 1; i <= MaxTries; i++) {
		FText Guess = GetGuess();

		// submit valid guess to the game, and receive data
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}

	//TODO summarize game

	return;
}

// loop continually until user gives a valid guess
FText GetGuess() {

	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		FText Guess = "";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetWordLength() << " letter word \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n";
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
}

bool PlayAgain() {

	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	
	return (Response[0] == 'y') || (Response[0] == 'Y');
	// TODO Accept only (y/n) type inputs
}