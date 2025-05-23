#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

void printAdjacencyList(const std::vector<std::vector<unsigned long long>>& adj, size_t nodes, size_t edges, bool directed, std::ofstream& outfile) {
    outfile << nodes << " " << edges << " ";
    if (directed) {
        outfile << "d\n";
    }
    else {
        outfile << "u\n";
    }

    for (size_t i = 0; i < adj.size(); ++i) {
        outfile << i << ": ";
        for (size_t j = 0; j < adj[i].size(); ++j) {
            outfile << adj[i][j];
            if (j != adj[i].size() - 1) {
                outfile << " ";
            }
        }
        outfile << "\n";
    }
}
void printKey(const std::vector<unsigned long long>& renamed, std::ofstream& outfile) {
    for (size_t i = 0; i < renamed.size(); ++i) {
        outfile << i << ": " << renamed[i] << "\n";
    }
}
bool in_vector(unsigned long long node, std::vector<unsigned long long>& adj) {
    for (size_t i = 0; i < adj.size(); ++i) {
        if (adj[i] == node) {
            return true;
        }
    }
    return false;
}
unsigned long long find_in_renamed(unsigned long long node, std::vector<unsigned long long>& renamed, unsigned long long& counter) {
    for (size_t i = 0; i < counter; ++i) {
        if (renamed[i] == node) {
            return i;
        }
    }
    unsigned long long ans = counter;
    renamed[counter] = node;
    ++counter;
    return ans;
}

void read_graph(std::ifstream& input, size_t& nodes, size_t& edges, size_t& edges_dir, bool& directed, std::vector<std::vector<unsigned long long>>& adj, std::vector<std::vector<unsigned long long>>& adj_dir, std::vector<unsigned long long>& renamed) {

    input >> nodes;
    input >> edges;
    unsigned long long edge_counter = 0;
    unsigned long long edge_counter_dir = 0;
    input.get();
    if (static_cast<char>(input.get()) == 'd') {
        directed = true;
        adj_dir.resize(nodes);
    }
    else {
        directed = false;
    }

    adj.resize(nodes);
    renamed.resize(nodes);

    unsigned long long counter = 0;
    unsigned long long a;
    unsigned long long b;

    for (size_t i = 0; i < edges; ++i) {
        input >> a;
        input >> b;

        a = find_in_renamed(a, renamed, counter);
        b = find_in_renamed(b, renamed, counter);

        if (!in_vector(b, adj[a])) {
            adj[a].push_back(b);
            ++edge_counter;
        }
        if (!in_vector(a, adj[b])) {
            adj[b].push_back(a);
        }
        if (directed && !in_vector(b, adj_dir[a])) {
            adj_dir[a].push_back(b);
            ++edge_counter_dir;
        }
    }
    edges = edge_counter;
    edges_dir = edge_counter_dir;
}
int main(int argc, char** argv)
{
    std::ifstream input(argv[1]);
    std::string path1 = argv[1];
    std::string path3 = argv[1];
    path1.erase(path1.size() - 4);
    path3.erase(path3.size() - 4);
    path1 += "_adj_undirected.txt";   
    path3 += "_key.txt";
    
    std::ofstream outfile1(path1);
    
    std::ofstream outfile3(path3);

    size_t edges;
    size_t edges_dir;
    size_t nodes;
    bool directed;
    std::vector<std::vector<unsigned long long>> adj;
    std::vector<std::vector<unsigned long long>> adj_dir;
    std::vector<unsigned long long> renamed;

    read_graph(input, nodes, edges, edges_dir, directed, adj, adj_dir, renamed);

    printAdjacencyList(adj, nodes, edges, false, outfile1);
    if (directed) {
        std::string path2 = argv[1];
        path2.erase(path2.size() - 4);
        path2 += "_adj_directed.txt";
        std::ofstream outfile2(path2);
        printAdjacencyList(adj_dir, nodes, edges, directed, outfile2);
    }
    printKey(renamed, outfile3);
    return 0;
}
