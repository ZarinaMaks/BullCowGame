/*
 My first C++ code made via to Udemy.com course!
 This version of Bulls&Cows Game includes some of my own design solutions.
 */
//  main.cpp
//  BullCowGame
//  Created by zarina on 09.07.18.
//  Copyright (c) 2018 study. All rights reserved.

/*
 main.cpp is the concole executable, that makes use of the BullCow class.
 This acts as the view in a MVC pattern, and is responsible for all
 user interaction. For game logic see the FBullCowGame class.
*/
#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// To make syntax UnrealEngine friendly
#include "FBullCowGame.h"
using Fstring = string;
using FText = string;
using int32 = int;

// Function prototypes as outside a class, which we re-use across plays
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game


//---------/
int32 main()
{
    do {
        PlayGame();
        BCGame.ResetTryNumber();
    }
    while (AskToPlayAgain());
    return 0;
}
//---------/


void PrintIntro()
{
    cout << "Welcome to Bulls and Cows, a fun word game!\n";
    cout << endl;
    cout << "                        ..---.                         " << endl;
    cout << "                       // |\\||\\                      " << endl;
    cout << " \\   //               ///;||\\|;\\           \\   //  " << endl;
    cout << "   o               .__// \\____//\\_,.         o       " << endl;
    cout << " //   \\             {_\\_/  \'' = __/        //   \\  " << endl;
    cout << "                   \\___   (o) (o)  }                  " << endl;
    cout << "                       /         :--'  SACRE MOO~      " << endl;
    cout << "                  .---/\\_    `__\\-.                  " << endl;
    cout << "                 /     `-\\___(o'o) \\       IT'S A BULLS & COWS GAME!  " << endl;
    cout << "          \\   //|    \\      `====' | \\   //         " << endl;
    cout << "            o   `.    `.    .'    .'  o                " << endl;
    cout << "          //   \\ (`.    `. '    .') //   \\           " << endl;
    cout << "                  (  `.    `...'   )                   " << endl;
    cout << "                  (   .+.    `-.   )                   " << endl;
    cout << "                  (.-'  .>-._   `-.)                   " << endl;
    cout << " \\   //          (___.-'      `-.___)          \\   //" << endl;
    cout << "   o              (                )             o     " << endl;
    cout << " //   \\           (                )           //   \\" << endl;
    return;
}


void PlayGame()
{
    BCGame.PickNextHiddenWord();
    PrintIntro();
    
    cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    cout << " letter isogram I'm thinking of?\n";
    cout << endl;
    
    int32 MaxTries = BCGame.GetMaxTries();
    FText Guess = "";
    bool GameWon = BCGame.IsGameWon(Guess);
    // loop asking for guesses while the game is NOT won
    // and there are still tries remaining
    
    while (!GameWon && BCGame.GetCurrentTry() <= MaxTries)
    {
        Guess = GetValidGuess();

        GameWon = BCGame.IsGameWon(Guess);
        
        //submit VALID guess of the game, receive counts
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        cout << "Bulls: " << BullCowCount.Bulls;
        cout << ". Cows: " << BullCowCount.Cows << "\n\n";
        cout << endl;
    }
    if ( BCGame.GetCurrentTry() > MaxTries && !GameWon)
    {
        std::cout << "Sorry, you lost. Better luck next time!\n";
    };
    
}

//loop continually until the user gives a valid guess
FText GetValidGuess()
{
    FText Guess = "";
    EWordStatus Status = EWordStatus::Invalid_Status;
    
    do {
      int32 CurrentTry = BCGame.GetCurrentTry();
        
    
      // get a guess from the player
      cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". ( ͡° ͜ʖ ͡°)Enter your guess: ";
      getline(cin, Guess);
    
      //check status, give feedback
      Status = BCGame.CheckGuessValidity(Guess);
      switch (Status)
      {
        case EWordStatus::Wrong_Length:
            cout << "Please enter a " << BCGame.GetHiddenWordLength() << " LETTER word.\n";
            break;
    
        case EWordStatus::Not_Isogram:
            cout << "Please enter a word WITHOUT REPEATING letters.\n";
            break;
    
        case EWordStatus::Not_Lowercase:
            cout << "Please enter your word in LOWERCASE.\n";
            break;
            
        default:
              return Guess;
              break;
      }
   } while (Status != EWordStatus::OK); //keep looping until we get no errors
    return Guess;
}

bool AskToPlayAgain()
{
    cout << "Do you want to play again with the next isogram(y/n)? ";
    FText Response = "";
    getline(cin, Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}