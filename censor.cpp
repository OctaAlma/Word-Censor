#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

void format(string& input){
    for (size_t i = 0; i < input.size(); i++){
        if (input.at(i) > 64 && input.at(i)< 91){
            input.at(i) = input.at(i) + 32;
        }
    }
}

void returnFormating(string original, string& formatted){
    for (size_t i = 0; i < original.size(); i++){
        if (original.at(i) == formatted.at(i)){continue;}
        if (formatted.at(i) == '*'){continue;}
        
        // formatted is going to be lowercase, so we have to capitalize
        if (original.at(i) == formatted.at(i) - 32){
            formatted.at(i) = formatted.at(i) - 32;
        }
    }
}

string censorWord(string wordToCensor, string word, size_t& c){
    if (word.size() < wordToCensor.size()){
        return word;
    }

    if (word.size() == wordToCensor.size()){
        if (word == wordToCensor){
            c++;
            for (int i = 0; i < word.size(); i++){
                word.at(i) = '*';
            }
            return word;
        }else{return word;}
    }

    // If the word's size is bigger than wordToCensor's size,
    // wordToCensor might be inside of word
    // 
    if (word.size() > wordToCensor.size()){
        size_t counter = 0;
        size_t wtcIndex = 0; // wtcIndex = word to censor index
        for (size_t i = 0; i < word.size(); i++){

            if (word.at(i) == wordToCensor.at(wtcIndex)){
                counter++;
                wtcIndex++;
            }else if (word.at(i) != wordToCensor.at(wtcIndex)){
                counter = 0;
                wtcIndex = 0;
            }

            if (counter == wordToCensor.size()){
                c++;
                // The only possible way for the counter to be
                // equal to word to Censor.size is i is equal to wordToCensor's size

                for (int j = i; j >= i - wordToCensor.size()+1; j--){
                    // We are comparing j (an integer) to a size_t.
                    // The loop will try to convert j to an size_t to compare, but that causes problems
                    // we have to manually check if j is less than 0
                    if (j < 0){
                        break;
                    }
                    word.at(j) = '*';
                }
                wtcIndex = 0;
                counter = 0;
            }
        }
    }
    return word;
}

void Censor(string fileName, string wordToCensor){
    format(wordToCensor);

    ifstream file;
    ofstream output;
    file.open(fileName);
    output.open("censored.txt");

    if (!file.is_open()){
        cout << "ay bruh the file aint opening!\n";
    }

    size_t count = 0;

    while (!file.eof()){
        string currWord;
        stringstream line;
        string str;

        // Get a line from a file and put it in a string
        // then we insert this string into a stringstream
        getline(file,str);
        line << str;
    
        while (!line.eof()){
            string word, wordCopy;
            line >> word;
            wordCopy = word;
            format(word);
            // We check if the word to censor is found in the word we're checking
            word = censorWord(wordToCensor, word, count);
            returnFormating(wordCopy, word);
            output << word << ' ';
        }
        output << '\n';
    }

    file.close();
    output.close();

    cout << "Censorship finished. " << count << " instances of \"" << wordToCensor << "\" found.\n";
}

int main(){
    cout << "Welcome to censor.cpp. What word would you like to censor?\n";
    string censor;
    cin >> censor;
    string fileName = "censorMe.txt";
    cout << "Enter the name of the file you would like to censor: ";
    cin >> fileName; cout << "\n";
    Censor(fileName, censor);
}