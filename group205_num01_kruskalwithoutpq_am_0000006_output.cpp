// ******
// Program: group205_num01_kruskalwithoutpq_am_0000006_output.cpp
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
// Member 3: Q1
// Member 4: Q1

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    vector<Edge> edges;
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

int findParent(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return findParent(parent, parent[i]);
}

void unionSet(int parent[], int x, int y) {
    int xset = findParent(parent, x);
    int yset = findParent(parent, y);
    parent[xset] = yset;
}

void kruskalMST(Graph& graph, ofstream& output) {
    int V = graph.V;
    vector<Edge> result;
    int* parent = new int[V];

    // Record the start time
    auto start = chrono::system_clock::now ();

    for (int i = 0; i < V; i++)
        parent[i] = i;

    sort(graph.edges.begin(), graph.edges.end(), compareEdges);

    int i = 0, e = 0;
    while (e < V - 1 && i < graph.E) {
        Edge nextEdge = graph.edges[i++];

        int x = findParent(parent, nextEdge.src);
        int y = findParent(parent, nextEdge.dest);

        if (x != y) {
            result.push_back(nextEdge);
            unionSet(parent, x, y);
            e++;
        }
    }

    // Record the end time
    auto end = chrono::system_clock::now ();

    // Calculate the duration
    chrono::duration < double >duration = end - start;

    int totalWeight = 0;
    output << V << endl;
    for (int i = 0; i < V; i++)
        output << i << " " << (char)('A' + i) << endl;

    for (Edge edge : result) {
        output << (char)('A' + edge.src) << " " << (char)('A' + edge.dest) << " " << edge.weight << endl;
        totalWeight += edge.weight;
    }

    output << totalWeight << endl;

    // Print the total time taken in second
    // cout << duration.count () << "s" << endl;
    output << duration.count () << "s" << endl;

    delete[] parent;
}

int main() {
    string inputFileName = "kruskalwithoutpq_am_0000006_input.txt";
    string outputFileName = "kruskalwithoutpq_am_0000006_output.txt";

    ifstream inputFile (inputFileName);

    if (!inputFile)
    {
        cout << "Failed to open the input file." << endl;
        return 0;
    }

    Graph graph;
    inputFile >> graph.V;

    for (int i = 0; i < graph.V; i++) {
        int index;
        char name;
        inputFile >> index >> name;
    }

    for (int i = 0; i < graph.V; i++) {
        for (int j = 0; j < graph.V; j++) {
            int weight;
            char c;
            inputFile >> c;
            if (c == 'i')
                continue;
            else
                weight = c - '0';
            if (i < j) {
                Edge edge;
                edge.src = i;
                edge.dest = j;
                edge.weight = weight;
                graph.edges.push_back(edge);
            }
        }
    }

    graph.E = graph.edges.size();

    inputFile.close();

    ofstream outputFile(outputFileName);

    if (!outputFile)
    {
        cout << "Failed to open the output file." << endl;
        return 0;
    }

    kruskalMST(graph, outputFile);

    outputFile.close();

    cout << "Output generated and saved to kruskalwithoutpq_am_0000006_output.txt." << endl;

    return 0;
}
