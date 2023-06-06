// ******
// Program: group205_num06_huffmancoding_input_files.cpp
// Course: TCP2101 ALGORITHM DESIGN & ANALYSIS
// Class: TC1L
// Trimester: 2220
// Member 1: 1201101003 | CHIA YU ZHANG | 12011011003@student.mmu.edu.my | 0183521866
// Member 2: 1201100514 | YAP ZHI TOUNG | 1201100514@student.mmu.edu.my | 0165243967
// Member 3: 1201100924 | TEO HAZEL | 1201100924@student.mmu.edu.my | 0122604688
// Member 4: 1201100324 | GERALD GODWIN LEE YONG LIN | 1201100324@student.mmu.edu.my | 0106633340
// ********************************************************
// Task Distribution
// Member 1: Q6
// Member 2: Q6
// Member 3: 
// Member 4:

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

// Function to generate random words
string generateRandomWord(int wordLength) {
    string word;
    static const char alphabet[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < wordLength; ++i) {
        word += alphabet[rand() % (sizeof(alphabet) - 1)];
    }

    return word;
}

// Function to generate an input file with random words
void generateInputFile(const string& filename, int numCharacters, int charBitLength) {
    ofstream outputFile(filename);

    if (!outputFile) {
        cerr << "Failed to create file: " << filename << endl;
        return;
    }

    // Calculate the number of words required to achieve the desired number of characters
    int wordLength = charBitLength;
    int numWords = numCharacters / wordLength;
    int remainingCharacters = numCharacters % wordLength;

    // Generate the random words
    vector<string> words;
    for (int i = 0; i < numWords; ++i) {
        string word = generateRandomWord(wordLength);
        words.push_back(word);
    }

    if (remainingCharacters > 0) {
        string word = generateRandomWord(remainingCharacters);
        words.push_back(word);
    }

    // Find unique characters
    string allWords = "";
    for (const string& word : words) {
        allWords += word;
    }
    sort(allWords.begin(), allWords.end());
    auto last = unique(allWords.begin(), allWords.end());
    allWords.erase(last, allWords.end());

    // Write the number of unique characters
    int numUniqueChars = allWords.length();
    outputFile << numUniqueChars << endl;

    // Write the unique characters and their bit lengths
    for (char ch : allWords) {
        outputFile << ch << endl;
    }

    // Write the generated words with spaces every 5 characters
    int count = 0;
    for (const string& word : words) {
        for (char ch : word) {
            outputFile << ch;
            ++count;
            if (count % 5 == 0) {
                outputFile << " ";
            }
        }
    }

    outputFile.close();
    cout << "Generated file: " << filename << endl;
}


int main() {
    // Set the seed for random number generation
    srand(1201101003);

    // Number of characters for each input file
    vector<int> characterCounts = {10, 100, 1000, 10000, 100000};

    int charBitLength = 7;

    for (int count : characterCounts) {
        ostringstream oss;
        oss << "huffmancoding_" << setfill('0') << setw(8) << count << "_input.txt";
        string filename = oss.str();
        generateInputFile(filename, count, charBitLength);
    }

    return 0;
}
