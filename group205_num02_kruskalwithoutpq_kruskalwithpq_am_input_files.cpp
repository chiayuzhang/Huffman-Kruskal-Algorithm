// ******
// Program: group205_num02_kruskalwithoutpq_kruskalwithpq_am_input_files.cpp
// Course: TCP2101 ALGORITHM DESIGN & ANALYSIS
// Class: TC1L
// Trimester: 2220
// Member 1: 1201101003 | CHIA YU ZHANG | 12011011003@student.mmu.edu.my | 0183521866
// Member 2: 1201100514 | YAP ZHI TOUNG | 1201100514@student.mmu.edu.my | 0165243967
// Member 3: 1201100924 | TEO HAZEL | 1201100924@student.mmu.edu.my | 0122604688
// Member 4: 1201100324 | GERALD GODWIN LEE YONG LIN | 1201100324@student.mmu.edu.my | 0106633340
// ********************************************************
// Task Distribution
// Member 1:
// Member 2:
// Member 3: Q2
// Member 4: Q2

#include <iostream>
#include <fstream>
#include <string>
#include <random>

using namespace std;

// Function to generate a random integer between min and max (inclusive)
int generateRandomInt(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// Function to generate the input file for Kruskal algorithm with adjacency matrix representation
void generateInputFile(int numVertices, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        file << numVertices << "\n";

        for (int i = 0; i < numVertices; i++) {
            file << i << " " << "A" << i << "\n";
        }

        vector<vector<int>> adjacencyMatrix(numVertices, vector<int>(numVertices, 0));

        for (int i = 0; i < numVertices; i++) {
            for (int j = i + 1; j < numVertices; j++) {
                int weight = generateRandomInt(1,1201101003);
                adjacencyMatrix[i][j] = weight;
                adjacencyMatrix[j][i] = weight;
            }
        }


        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (i == j) {
                    file << "i";
                } else {
                    file << adjacencyMatrix[i][j];
                    adjacencyMatrix[j][i] = adjacencyMatrix[i][j]; // Assign the same weight to adjacencyMatrix[j][i]
                }

                if (j != numVertices - 1) {
                    file << " ";
                }
            }
            file << "\n";
        }

        file.close();
        cout << "Input file " << filename << " generated successfully.\n";
    } else {
        cerr << "Unable to create the file: " << filename << "\n";
    }
}

int main() {
    string filePrefix = "kruskalwithoutpq_kruskalwithpq_am_";
    string fileSuffix = "_input.txt";
    int inputSizes[] = {10, 100, 1000, 5000, 10000, 100000};
    int numInputSizes = sizeof(inputSizes) / sizeof(inputSizes[0]);

    for (int i = 0; i < numInputSizes; i++) {
        string paddedInputSizeStr = string(8 - to_string(inputSizes[i]).length(), '0') + to_string(inputSizes[i]);
        string filename = filePrefix + paddedInputSizeStr + fileSuffix;
        generateInputFile(inputSizes[i], filename);
    }

    return 0;
}
