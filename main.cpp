#include <iostream>
#include <string>

#define NOT_PRESENT 0
#define WRONG_LOCATION 1
#define CORRECT_LOCATION 2

using namespace std;


struct Guess {
    string word;
    int results[5];
};

string strategy(Guess** guesses) {
    return "guess";
}

// Will assume that the guess is a valid string to save checking
Guess* evaulate_guess(string word, string answer) {
    Guess* guess;
    guess = new Guess();
    guess->word = word;
    for(int i=0; i<word.size(); i++) {
        char c = word.at(i);
        int ans_location = answer.find(c);
        if(ans_location == i) {
            guess->results[i] = CORRECT_LOCATION;
        } else if(ans_location < 4) {
            guess->results[i] = WRONG_LOCATION;
        } else {
            guess->results[i] = NOT_PRESENT;
        }
    }
    return guess;
}

int main() {
    cout << "Hello there!" << endl;

    string ANSWER_WORD = "laugh";
    cout << ANSWER_WORD.find('n') << endl;
    Guess* guesses[6];


    for(int i=0; i<6; i++) {
        string word = strategy(guesses);
        Guess* guess = evaulate_guess(word, ANSWER_WORD);
        guesses[i] = guess;

        bool gameover = true;
        for(int r=0; r<5; r++) {
            gameover = gameover || (guess->results[i]==2);
        }
        if(gameover) break;
    }


    return 0;
}