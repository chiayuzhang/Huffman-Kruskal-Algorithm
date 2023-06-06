// ****** 
// Program: group205_num04_kruskalwithpq_am_all_outputs.cpp 
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
// Member 3: Q4
// Member 4: Q4

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <queue>
using namespace std;

// Create Edge Structure to store the data for each edge
struct Edge {
    int src, dest, weight;
};


// Create Graph Structure to store the data for each verticies and edges
struct Graph {
    int V, E;
    vector<Edge> edges;
};

// To sort
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

struct CompareEdges{
    bool operator()(Edge const& edge1, Edge const& edge2) {
        return edge1.weight > edge2.weight;
    };
};

// Find Parent Node? I assuming Root Node
int findParent(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return findParent(parent, parent[i]);
}

// Assuming is for adjacency matrix
void unionSet(int parent[], int x, int y) {
    int xset = findParent(parent, x);
    int yset = findParent(parent, y);
    parent[xset] = yset;
}

// Calculating Kruskal
void kruskalMST(Graph& graph, ofstream& output) {
    int V = graph.V;
    vector<Edge> result;
    int* parent = new int[V];

    // Record the start time
    auto start = chrono::system_clock::now ();

    for (int i = 0; i < V; i++)
        parent[i] = i;

    // Using Priority Queue to sort
    priority_queue<Edge, vector<Edge>, CompareEdges> pq;

    for (Edge e: graph.edges){
        pq.emplace(e);
    }
    graph.edges.clear();
    while (!pq.empty()) {
        Edge e = pq.top();
        pq.pop();
        graph.edges.push_back(e);
    }

    // sort(graph.edges.begin(), graph.edges.end(), compareEdges);

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
        output << i << " " << "A" << i << endl;

    for (Edge edge : result) {
        output << "A" << edge.src << " " << "A" << edge.dest << " " << edge.weight << endl;
        totalWeight += edge.weight;
    }

    output << totalWeight << endl;

    // Print the total time taken in second
    output << duration.count () << "s" << endl;

    delete[] parent;
}

int main() {
    string inputFiles[] = {
        "kruskalwithoutpq_kruskalwithpq_am_00000010_input.txt",
        "kruskalwithoutpq_kruskalwithpq_am_00000100_input.txt",
        "kruskalwithoutpq_kruskalwithpq_am_00001000_input.txt",
        "kruskalwithoutpq_kruskalwithpq_am_00005000_input.txt",
        "kruskalwithoutpq_kruskalwithpq_am_00010000_input.txt",
        "kruskalwithoutpq_kruskalwithpq_am_00100000_input.txt"
    };

    string outputFiles[] = {
        "kruskalwithpq_am_00000010_output.txt",
        "kruskalwithpq_am_00000100_output.txt",
        "kruskalwithpq_am_00001000_output.txt",
        "kruskalwithpq_am_00005000_output.txt",
        "kruskalwithpq_am_00010000_output.txt",
        "kruskalwithpq_am_00100000_output.txt"
    };

    for (int fileIndex = 0; fileIndex < 5; fileIndex++) {
        ifstream inputFile(inputFiles[fileIndex]);

        if (!inputFile) {
            cout << "Failed to open the input file: " << inputFiles[fileIndex] << endl;
            continue;
        }

        Graph graph;
        inputFile >> graph.V;

        for (int i = 0; i < graph.V; i++) {
            int index;
            string name;
            inputFile >> index >> name;
        }

        for (int i = 0; i < graph.V; i++) {
            for (int j = 0; j < graph.V; j++) {
                int weight;
                string c;
                inputFile >> c;
                if (c == "i")
                    continue;
                else
                    weight = stoi(c);
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

        ofstream outputFile(outputFiles[fileIndex]);

        if (!outputFile) {
            cout << "Failed to open the output file: " << outputFiles[fileIndex] << endl;
            continue;
        }

        kruskalMST(graph, outputFile);

        outputFile.close();

        cout << "Output generated and saved to " << outputFiles[fileIndex] << "." << endl;
    }

    return 0;
}
