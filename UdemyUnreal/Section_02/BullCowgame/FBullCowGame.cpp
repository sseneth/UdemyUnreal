#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FText = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
	constexpr int MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetWordLength()) 
	{
		return EGuessStatus::Wrong_Length;
	}
	else 
	{
		return EGuessStatus::OK;
	};

}

// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WorldLength = MyHiddenWord.length(); // assuming same length as guess

	for (int32 MHWChar = 0; MHWChar < WorldLength; MHWChar++) {
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < WorldLength; GChar++) {
			// if they match then 
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WorldLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// Treat 0 and 1 letter words as isogram
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // set up char map
	for (auto Letter : Word) //for all letters of the word ("Range based for-loop")
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false; // we have seen the letter and therefore do NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		
		if (!islower(Letter)) {
			
			return false;
		}
	}

	return true;
}
