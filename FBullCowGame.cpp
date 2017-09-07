#include "FBullCowGame.h"

int32 FBullCowGame::GetCurrentTries() const { return this->MyCurrentTurn; }

bool FBullCowGame::IsGameWon() const { return this->bIsGameWon; };

uint32 FBullCowGame::GetHiddenWordLength() const { return this->HiddenWord.length(); }

int32 FBullCowGame::GetMaxTries() const
{
	int32 MinimumWordLength = 3;
	int32 Multiplier = 4;
	TMap<int32, int32> WordLengthToMaxTries{ { 3, 12 },{ 4, 17 },{ 5, 22 },{ 6, 27 } };
	//return WordLengthToMaxTries[this->GetHiddenWordLength()];
	return Multiplier * this->GetHiddenWordLength() + (this->GetHiddenWordLength() - MinimumWordLength);
}

//check if the user has entered a valid guess
EGuessStatus FBullCowGame::checkQuessValidity(FString Guess) const
{

	if (!this->IsWordLengthCorrect(Guess))
	{
		return EGuessStatus::Word_Wrong_Lenght;
	}
	else if (!this->IsWordMadeOfNonLetterSymbols(Guess))
	{
		return EGuessStatus::Word_Invalid_Symbols;
	}
	else if (!this->IsWordAnIsogram(Guess))
	{
		return EGuessStatus::Word_Not_Isogram;
	}

	//player's word is in correct format
	return EGuessStatus::Word_OK;;
}

void FBullCowGame::Reset(int32 Difficulty)
{
	this->MyCurrentTurn = InitialTryNumber;
	this->MyMaxTurn = MAX_GUESS_TRIES;
	int32 MinimumDifficulty = 3;
	this->HiddenWord = MyHiddenWord[Difficulty - MinimumDifficulty];
	this->bIsGameWon = false;
}

void FBullCowGame::SetMaxTries(int32 Tries)
{
}

void FBullCowGame::SetCurretnTries(int32 Tries)
{
}

FBullCowGame::FBullCowGame(int32 Difficulty)
{
	this->Reset(Difficulty);
}

FBullCowGame::FBullCowGame(const FBullCowGame & game)
{
}

FBullCowGame::~FBullCowGame()
{
}

void FBullCowGame::PlayGame()
{
}

//counts bulls and cows, and increase turn number, assuming a valid guess is passed
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	this->MyCurrentTurn++;
	FBullCowCount BullCowCount;

	//the two word should have the same lenght at this point
	uint32 WordLenght = this->GetHiddenWordLength();

	for (uint32 GuessCharIndex = 0; GuessCharIndex < WordLenght; GuessCharIndex++)
	{
		for (uint32 HiddenWordIndex = 0; HiddenWordIndex < WordLenght; HiddenWordIndex++)
		{
			//check if two letters match
			if (Guess[GuessCharIndex] == this->HiddenWord[HiddenWordIndex])
			{
				//increment bulls counter if the positions match
				if (GuessCharIndex == HiddenWordIndex) { BullCowCount.Bulls++; }
				//increment coes counter if the positions are different
				else { BullCowCount.Cows++; }
				break;
			}
		}
	}
	if (BullCowCount.Bulls == WordLenght)
	{
		this->bIsGameWon = true;
	}
	return BullCowCount;
}

//checks if the player's word is of a different length than the hidden word
bool FBullCowGame::IsWordLengthCorrect(FString Guess) const
{
	return Guess.length() == this->HiddenWord.length();
}

//cheks if the palyer's word is an isogram
bool FBullCowGame::IsWordAnIsogram(FString Guess) const
{
	TMap<char, bool> LettersSeen;
	for (char Letter : Guess)
	{
		char ActualLetter = tolower(Letter);
		if (LettersSeen[ActualLetter])
		{
			return false;
		}
		else
		{
			LettersSeen[ActualLetter] = true;
		}
	}
	return true;
}

//checks if the player's word contains symbold that are not lower case letters from the English alphabet
bool FBullCowGame::IsWordMadeOfNonLetterSymbols(FString Guess) const
{
	for (uint32 i = 0; i < Guess.length(); i++)
	{
		if(!isalpha(Guess[i]))
			return false;
	}
	return true;
}
