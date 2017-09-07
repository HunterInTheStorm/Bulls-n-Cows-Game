#pragma once
#include <string>
#include <map>

#define TMap std::map

using FString = std::string;
using int32 = int;
using uint32 = unsigned int;

constexpr int32 MAX_GUESS_TRIES = 8;
constexpr int32 InitialTryNumber = 1;
const FString MyHiddenWord[] = { "sam", "doge", "nymph", "string", "zephyrs" };

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Word_OK,
	Word_Not_Isogram,
	Word_Wrong_Lenght,
	Word_Invalid_Symbols,
	Undefined
};

class FBullCowGame
{
public:
	FBullCowGame(int32 Difficulty);
	FBullCowGame(const FBullCowGame& game);
	~FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTries() const;
	uint32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus checkQuessValidity(FString guess) const;

	void SetMaxTries(int32 Tries);
	void SetCurretnTries(int32 Tries);

	void Reset(int32 Difficulty);
	void PlayGame();
	FBullCowCount SubmitValidGuess(FString guess);

private:
	bool IsWordLengthCorrect(FString Guess) const;
	bool IsWordAnIsogram(FString Guess) const;
	bool IsWordMadeOfNonLetterSymbols(FString Guess) const;

	int MyCurrentTurn;
	int MyMaxTurn;
	FString HiddenWord;
	bool bIsGameWon;
};