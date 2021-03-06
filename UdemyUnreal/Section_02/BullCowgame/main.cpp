/* This is the console executable, that makes use of the BullCow cass
This acts as the view in a MCV pattern, and is responsoble for all user interaction.
For game logic, see the FBullCowGame class
*/
#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// To make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// Function protypes as outside a class
void PrintIntro();
void PlayGame();
FText GetGuess();
bool PlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we reuse across games

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

	// Introduce the game
	std::cout << "\n\nWelcome to Bulls and Cows\n";
	std::cout << "Can you guess the " << BCGame.GetWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}

void PlayGame() {

	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop asking for guesses while game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		
		FText Guess = GetGuess();

		// submit valid guess to the game, and receive data
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}
	
	PrintGameSummary();

	return;
}

// loop continually until user gives a valid guess
FText GetGuess() {

	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		// get guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);

	return Guess;
}

bool PlayAgain() { 

	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	
	return (Response[0] == 'y') || (Response[0] == 'Y');
	// TODO Accept only (y/n) type inputs
}

void PrintGameSummary() {

	if (BCGame.IsGameWon()) {
		std::cout << "Well done! - You won!\n";
	}
	else {
		std::cout << "Better luck next time!\n";
	};
}
