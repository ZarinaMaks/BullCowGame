//  FBullCowGame.h
//  BullCowGame
//  Created by zarina on 09.07.18.
//  Copyright (c) 2018 study. All rights reserved.

/* 
 The game logic (no view code or direct user interaction).
 The game is a simple guess the word game based on Mastermind.
*/

#pragma once
#include <string>

// To make syntax UnrealEngine friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EWordStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame
{
public:
    FBullCowGame(); //constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    void PickNextHiddenWord();
    bool IsGameWon(FString Guess) const;
    EWordStatus CheckGuessValidity(std::string) const;
    
    void Reset();
    void ResetTryNumber();
    //counting bulls & cows, increasing try #, assuming valid guess
    FBullCowCount SubmitValidGuess(FString);
    
private:
    bool IsIsogram(FString) const;
    int32 MyCurrentTry = 1;
    //int32 MyMaxTries = 5;
    FString MyHiddenWord;
    
    FString HiddenWords[10] = {"sky", "game", "shirt", "ocean", "plant", "yoghurt", "caption"
         "software", "mineralogy", "tambourine",};
};