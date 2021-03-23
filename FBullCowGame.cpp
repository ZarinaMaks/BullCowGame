//  FBullCowGame.cpp
//  BullCowGame
//  Created by zarina on 09.07.18.
//  Copyright (c) 2018 study. All rights reserved.

#include "FBullCowGame.h"
#include <iostream>
#include <iterator>
#include <map>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// To make syntax UnrealEngine friendly
using FString = std::string;
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset();}

int32 FBullCowGame::GetMaxTries() const
{
    //diverse word length -> diverse number of tries {word length, number of tries}
    TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {7,16}, {8,20}, {9,25}, {10,27}};
    return WordLengthToMaxTries[MyHiddenWord.length()];
}
int32 FBullCowGame::GetCurrentTry() const { return FBullCowGame::MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool IsGuessUpper (FString Guess)
{
    int32 i=0;
    while (Guess[i] && i < Guess.length())
    {
        if (isupper(Guess[i]))
        {
            return true;
        }
        i++;
    }
    return false;
}

void FBullCowGame::Reset()
{
    //constexpr int32 MAX_TRIES = 5;
    //const FString HIDDEN_WORD = "shirt";
    //MyMaxTries = MAX_TRIES;
    //MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    return;
}

bool FBullCowGame::IsGameWon(FString Guess) const
{
    if (Guess == MyHiddenWord)
    {
        std::cout << "Congratulations! You won!\n";
        return true;
    }
    return false;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess)) //if the guess isn't an isogram, return the error Not_Isogram:
    {
        return EWordStatus::Not_Isogram;
    }
    else if (IsGuessUpper(Guess)) //if the guess isn't all lowercase, return the error Not_Lowercase:
    {
        return EWordStatus::Not_Lowercase;
        
    }
    else if (Guess.length() != GetHiddenWordLength()) //if the guess length is wrong, return the error Wrong_Length:
    {
        return EWordStatus::Wrong_Length;
    }
    else  //otherwise, return OK:
    {
        return EWordStatus::OK;
    }
    return EWordStatus::OK; 
}


//reseives a VALID guess, incriments turns, returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;  //setup a return variable
    int32 WordLength = MyHiddenWord.length(); //assuming same length as guess
    
    //loop through all letters in the hidden word:
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
    {
      //compare letters againts the guess:
        for (int32 GChar=0; GChar < WordLength; GChar++)
        {
        //if they match then:
            if (Guess[GChar]== MyHiddenWord[MHWChar])
            {
          //if they're in the same place:
                if (MHWChar == GChar)
                {
                    BullCowCount.Bulls++;  //<-incriment bulls
                }
                else
                {  BullCowCount.Cows++; //<-incriment cows
                    
                }
            }
        }
    }
    return BullCowCount;
}

void FBullCowGame::ResetTryNumber() { MyCurrentTry = 1; }

bool FBullCowGame::IsIsogram(FString Word) const
{
    // treat 0 and 1 letter words as isograms
    if (Word.length() <= 1) { return true; }
    
    /* for (int i = 0; i < Word.length(); i++) {
        Letter = Word[i];
    }*/
    
    TMap<char, bool> LetterSeen; // setup our map(unstructured data base)
    for (auto Letter : Word) 	// for all letters of the word
    {
        Letter = tolower(Letter); // handle mixed case
        if (LetterSeen[Letter]) {// if the letter is in the map
            return false; // we do NOT have an isogram
        } else {
            LetterSeen[Letter] = true;// add the letter to the map
        }
    }
    
    return true; // for example in cases where /0 is entered
}

void FBullCowGame::PickNextHiddenWord(  )
{
    auto MassiveLength = std::end(HiddenWords)-std::begin(HiddenWords);
    srand(time(NULL));
    int32 RandomWordNumber = rand() % MassiveLength;
    MyHiddenWord = HiddenWords[RandomWordNumber];
    
}
