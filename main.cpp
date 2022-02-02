#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <regex>

#define NOT_PRESENT 0
#define WRONG_LOCATION 1
#define CORRECT_LOCATION 2

using namespace std;


struct Guess {
    string word;
    int results[5];
};

void print_guess(Guess* guess) {
    cout << guess->word;
    for(int i=0; i<5; i++) {
        cout << " " << guess->results[i];
    }
    cout << endl;
}

string strategy(Guess* guesses[], int round) {
    if (round == 0) {
        return "heats";
    } else if(round == 1) {
        return "groin";
    } else if(round == 2) {
        return "clump";
    }
    return "xxxxx";
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
        } else if(ans_location != string::npos) {
            guess->results[i] = WRONG_LOCATION;
        } else {
            guess->results[i] = NOT_PRESENT;
        }
    }
    return guess;
}


void filter_by_guess(string all_words[], Guess* guess) {
    int total = 0;
    for(int i=0; i<12972; i++) {
        bool valid = true;
        for(int t=0; t<5; t++) {
            if(guess->results[t] == WRONG_LOCATION) {
                if(all_words[i].find(guess->word.at(t)) == string::npos) {
                    valid = false;
                    break;
                }
            } else if(guess->results[t] == CORRECT_LOCATION) {
                if(all_words[i].at(t) != guess->word.at(t)) {
                    valid = false;
                    break;
                }
            }
        }

        if(valid) total++;
    }

    cout << "TOTAL: " << total << endl;
}

void filter_by_posession(string all_words[], char tem[]) {
    int total = 0;
    for(int i=0; i<12972; i++) {
        bool valid = true;
        for(int t=0; t<5; t++) {
            if(tem[t] != '\0') {
                if(all_words[i].find(tem[t]) != string::npos) {
                    valid = false;
                    break;
                }
            }
        }

        if(valid) total++;
    }

    cout << "TOTAL: " << total << endl;
}

void filter_by_pos(string all_words[], char tem[]) {
    int total = 0;
    for(int i=0; i<12972; i++) {
        bool valid = true;
        for(int t=0; t<5; t++) {
            if(tem[t] != '\0') {
                if(all_words[i].at(t) != tem[t]) {
                    valid = false;
                    break;
                }
            }
        }

        if(valid) total++;
    }
    cout << "TOTAL: " << total << endl;
}

Guess* merge_guesses(Guess* guesses[]) {
    Guess* guess;
    guess = new Guess();
    guess->word = "xxxxx";
    memset(guess->results, 0, 5*sizeof(int));

    for(int i=0; i<6; i++) {
        if(guesses[i] == NULL) continue;
        for(int t=0; t<5; t++) {
            if(guesses[i]->results[t] > guess->results[t]) {
                guess->word[t] = guesses[i]->word[t];
                guess->results[t] = guesses[i]->results[t];
            }
        }

    }

    return guess;
}


void word_filter_eval(string test_word, int stop, string all_words[]) {
    Guess* guesses[6];
    for(int i=0; i<6; i++) {
        string word = strategy(guesses, i);
        Guess* guess = evaulate_guess(word, test_word);
        guesses[i] = guess;
    }

    for(int i=0; i<stop; i++) {
        cout << "guess#" << i << " ";
        if(guesses[i] == NULL) continue;
        print_guess(guesses[i]);
    }

    cout << endl;
    Guess* g = merge_guesses(guesses);
    print_guess(g);

    filter_by_guess(all_words, g);
}


string* load_words(string filename, int length) {
    string *words = new string[length]; int word_index=0;
    string line;
    ifstream all_words_file(filename);
    while(getline(all_words_file, line)) {
        words[word_index] = line;
        word_index++;
    }
    return words;
}

string random_word(string words[], int length) {
    int r = rand()%length;
    return words[r];
}

int main() {

    srand(time(0));
    cout << "Hello there!" << endl;

    string* all_words = load_words("all-words.txt", 12972);
    string* ans_words = load_words("wordle-answers-alphabetical.txt", 2315);

    string rand_word = random_word(ans_words, 2315);
    cout << "Testing: " << rand_word << endl;

    word_filter_eval(rand_word, 3, all_words);
    return 0; 

    // char test_word[] = {'t', 'h', 'o', '\0', '\0'};
    // filter_by_posession(all_words, test_word);

    string ANSWER_WORD = "laugh";
    Guess* guesses[6];

    int i=0;
    for(; i<6; i++) {
        string word = strategy(guesses, i);
        Guess* guess = evaulate_guess(word, ANSWER_WORD);
        guesses[i] = guess;

        bool gameover = true;
        for(int r=0; r<5; r++) {
            gameover = gameover && (guess->results[i]==2);
        }
        if(gameover) break;
    }

    cout << "Finished in " << i+1 << " turns" << endl;

    for(int i=0; i<6; i++) {
        cout << "guess#" << i << " ";
        if(guesses[i] == NULL) continue;
        print_guess(guesses[i]);
    }

    cout << endl;
    Guess* g = merge_guesses(guesses);
    print_guess(g);

    filter_by_guess(all_words, g);

    return 0;
}