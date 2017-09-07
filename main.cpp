#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FString = std::string;
using int32 = int;


int32 GameDifficulty = 3;
FBullCowGame Game = FBullCowGame(GameDifficulty);

//set the game difficulty, to be used after a difficulty is selected
void SetGameDifficulty();

//read player input to determine game difficulty
int32 ChooseDifficulty();

//Itroduction to the game
void PrintIntroduction();

//loops continuesly until a valid guess is entered
FString GetValidGuess();

void BullsCowsResult(FBullCowCount* Guess);

bool AskToPlayAgain();
//the entry point of the application

void PlayGame();

//prints a message depending on whether the player won or lost the game
void PrintGameSummary();

void PrintErrorCodes(EGuessStatus Status);

int main()
{
	bool bPlayAgain = true;

	do
	{
		PrintIntroduction();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);
	return 0;
}

void PrintIntroduction()
{
	std::cout << "Welcome to Bulls and Cows" << std::endl;
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Choose the difficulty you want to play on!\nBaby | Normal | Hard | Expert | Masochist\n";
	GameDifficulty = ChooseDifficulty();
	SetGameDifficulty();
	std::cin.ignore();
	std::cout << "Can you guess the " << Game.GetHiddenWordLength() << " letter isogram I am thinking of?";
	std::cout << std::endl;
}

FString GetValidGuess()
{
	int32 TryNum = Game.GetCurrentTries();
	FString Guess = "";
	EGuessStatus Status = EGuessStatus::Undefined;

	//loop untill user imput is valid
	while (Status != EGuessStatus::Word_OK)
	{

		std::cout << "\nTRY " << TryNum << "/" << Game.GetMaxTries() << " .Wath is your guess: ";
		std::getline(std::cin, Guess);

		//validating the guess
		Status = Game.checkQuessValidity(Guess);

		//check guess status
		if (Status != EGuessStatus::Word_OK)
		{
			PrintErrorCodes(Status);
		}
		else
			break;
	}

	return Guess;
}

void BullsCowsResult(FBullCowCount* BullCowCount)
{
	std::cout << BullCowCount->Bulls << " bulls, ";
	std::cout << BullCowCount->Cows << " cows";
	std::cout << std::endl;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to paly again?(Y/N)" << std::endl;
	FString Response;
	std::cin >> Response;
	std::cin.ignore();
	std::cout << std::endl;
	return (Response[0] == 'Y') || (Response[0] == 'y');
}

void PlayGame()
{
	int32 MaxTries = Game.GetMaxTries();
	FString Guess = "";

	while (Game.GetCurrentTries() != Game.GetMaxTries() && !Game.IsGameWon())
	{
		Guess = GetValidGuess();

		//submit valid guess to the game
		FBullCowCount BullCowCount = Game.SubmitValidGuess(Guess);

		//print number of bulls and cows
		BullsCowsResult(&BullCowCount);
	}

	PrintGameSummary();
}

//print error messeges for word not being an isogram, word containing characters different from lowercase letters, word with incorrect lenght
void PrintErrorCodes(EGuessStatus Status)
{
	switch (Status)
	{
	case EGuessStatus::Word_Wrong_Lenght:
		std::cout << "Please enter a word with lenght " << Game.GetHiddenWordLength() << " .\n";
		break;
	case EGuessStatus::Word_Not_Isogram:
		std::cout << "Please entered a word that is an ISOGRAM.\n";
		break;
	case EGuessStatus::Word_Invalid_Symbols:
		std::cout << "You must enter a word consisting of only letters.\n";
		break;
	default:
		std::cout << "error\n";
		break;
	}
}

void PrintGameSummary()
{
	if (Game.IsGameWon())
	{
		std::cout << "\nYOU WIN! CONGRADULATIONS!!!\n";
	}
	else
	{
		std::cout << "\nYOU LOSE FOOL\n";
	}
}

int32 ChooseDifficulty()
{
	FString Difficulty = "";
	std::cin >> Difficulty;
	char FirstCharacterOfDifficulty = Difficulty[0];
	if (FirstCharacterOfDifficulty == 'B' || FirstCharacterOfDifficulty == 'b')
		return MyHiddenWord[0].length();
	if (FirstCharacterOfDifficulty == 'N' || FirstCharacterOfDifficulty == 'n')
		return MyHiddenWord[1].length();
	if (FirstCharacterOfDifficulty == 'H' || FirstCharacterOfDifficulty == 'h')
		return MyHiddenWord[2].length();
	if (FirstCharacterOfDifficulty == 'E' || FirstCharacterOfDifficulty == 'e')
		return MyHiddenWord[3].length();
	if (FirstCharacterOfDifficulty == 'M' || FirstCharacterOfDifficulty == 'm')
		return MyHiddenWord[4].length();
	return 0;
}

void SetGameDifficulty()
{
	Game.Reset(GameDifficulty);
}