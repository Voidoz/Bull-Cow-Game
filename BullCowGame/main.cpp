/* This is the console executable, that makes use of the BullCow class
This acts as the view in an MVC pattern, and is responsible for all 
user interaction. For the game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// funtion prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game which we reuse across plays

//the entry point for the application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0; // exit the application
}


void PrintIntro()
{
	std::cout << ":==================================================:\n";
	std::cout << "|   Welcome to the isogram game; Bulls and Cows!   |\n";
	std::cout << "|--------------------------------------------------|\n";
	std::cout << "|               __n__n__    _(___)_                |\n";
	std::cout << "|       .------`-\\ 00/-'     (O O)-`--------.      |\n";
	std::cout << "|      / ##  ##  (oo)         @ @`   ##  ##  \\     |\n";
	std::cout << "|     / \\## __   ./            \\. # __##___ /.\\    |\n";
	std::cout << "|        |//YY \\||              |//      |||       |\n";
	std::cout << "|        |||   /||              //\\      ||\\       |\n";
	std::cout << "|--------------------------------------------------|\n";
	std::cout << "|       Don't mind the realistic art though!       |\n";
	std::cout << "|--------------------------------------------------|\n";
	std::cout << "|   Isograms are words without repeated letters!   |\n";
	std::cout << "|  A bull will mean a letter in the right place!!  |\n";
	std::cout << "|  A cow means a right letter in the wrong place!  |\n";
	std::cout << "|         So... What are you waiting for?!         |\n";
	std::cout << "|                  Good luck!^_^'                  |\n";
	std::cout << "|--------------------------------------------------|\n";
	std::cout << "| Can you guess' " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of? |\n";
	std::cout << ":==================================================:\n\n";
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to game, and reviece counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 MaxTries = BCGame.GetMaxTries();
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << "/" << MaxTries << ". Enter your guess: ";
		
		std::getline(std::cin, Guess);

		// check guess status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogrammic word.\n\n";
			break;
		default:
			// assuming the guyess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
