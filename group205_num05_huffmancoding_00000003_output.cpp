// ******
// Program: group205_num05_huffmancoding_00000003_output.cpp
// Course: TCP2101 ALGORITHM DESIGN & ANALYSIS
// Class: TC1L
// Trimester: 2220
// Member 1: 1201101003 | CHIA YU ZHANG | 12011011003@student.mmu.edu.my | 0183521866
// Member 2: 1201100514 | YAP ZHI TOUNG | 1201100514@student.mmu.edu.my | 0165243967
// Member 3: 1201100924 | TEO HAZEL | 1201100924@student.mmu.edu.my | 0122604688
// Member 4: 1201100324 | GERALD GODWIN LEE YONG LIN | 1201100324@student.mmu.edu.my | 0106633340
// ********************************************************
// Task Distribution
// Member 1:Q5
// Member 2:Q5
// Member 3: 
// Member 4:

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <chrono>
#include <queue>
#include <unordered_map>

using namespace std;

struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;

    Node(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

void encode(Node* root, string code, unordered_map<char, string>& encoding) {
    if (root == nullptr)
        return;

    // Leaf node
    if (!root->left && !root->right) {
        encoding[root->character] = code;
        return;
    }

    // Recursive calls for left and right subtrees
    encode(root->left, code + "0", encoding);
    encode(root->right, code + "1", encoding);
}

unordered_map<char, string> buildHuffmanTree(string text) {
    unordered_map<char, int> frequency;
    for (char ch : text)
        frequency[ch]++;

    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create a leaf node for each character and add it to the priority queue
    for (auto& pair : frequency) {
        Node* newNode = new Node(pair.first, pair.second);
        pq.push(newNode);
    }

    // Build the Huffman tree
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* combined = new Node('$', left->frequency + right->frequency);
        combined->left = left;
        combined->right = right;

        pq.push(combined);
    }

    Node* root = pq.top();
    unordered_map<char, string> encoding;
    encode(root, "", encoding);

    delete root;
    return encoding;
}

map<char, int> calculateCharacterFrequencies(const string& str) {
    map<char, int> frequencies;
    for (char c : str) {
        if (isalpha(c)) {  // Count only alphabetical characters
            frequencies[c]++;
        }
    }
    return frequencies;
}

int main() {
    // Declare the startTime variable
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    string inputFileName = "group205_num05_huffmancoding_00000003_input.txt";
    string outputFileName = "group205_num05_huffmancoding_00000003_output.txt";

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (inputFile.is_open()) {
        string line;
        string lastLine;
        while (getline(inputFile, line)) {
            lastLine = line;
        }
        inputFile.close();

        // Remove spaces from the last line
        lastLine.erase(remove_if(lastLine.begin(), lastLine.end(), [](char c) { return isspace(c); }), lastLine.end());

        // Calculate character frequencies and build Huffman tree
        map<char, int> frequencies = calculateCharacterFrequencies(lastLine);
        unordered_map<char, string> encoding = buildHuffmanTree(lastLine);

        // Print character frequencies and encodings
        int totalBits = 0;
        int bit = 7;
        int totalFrequency = 0;

        for (const auto& pair : frequencies) {
            totalFrequency += pair.second;
        }

        // Write the number of unique characters to the output file
        int numUniqueChars = frequencies.size();
        outputFile<< numUniqueChars << endl;

        for (const auto& pair : frequencies) {
            char character = pair.first;
            int frequency = pair.second;
            string code = encoding[character];
            int codeLength = code.length();
            int frequencyWithCode = frequency * codeLength;
            outputFile << character << " " << frequency << " " << code << " " << frequencyWithCode << endl;
            totalBits += frequencyWithCode;
        }


        // Calculate the percentage of words with spaces
        double percentageWithSpaces = (static_cast<double>(totalBits));

        // Calculate and print the program execution time
        std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);
        std::string executionTime = std::to_string(duration.count()) + "s";
        outputFile << totalBits << "-bits out of " << totalFrequency * bit << "-bit" << endl;
        outputFile <<"Total space "<< percentageWithSpaces << "%" << endl;
        outputFile << executionTime << endl;


        outputFile.close();

        cout << "Output has been written to '" << outputFileName << "'." << endl;
    } else {
        cout << "Failed to open the file." << endl;
    }

    return 0;
}

