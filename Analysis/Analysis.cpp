// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

void printAdjacencyList(const std::vector<std::vector<unsigned long long>>& adj, std::ofstream& outfile) {
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
bool in_vector(const unsigned long long node, const std::vector<unsigned long long>& adj) {
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

void read_graph(std::ifstream& input, size_t& nodes, size_t& edges, bool& directed, std::vector<std::vector<unsigned long long>>& adj, std::vector<std::vector<unsigned long long>>& adj_dir) {

    input >> nodes;
    input >> edges;
    unsigned long long edge_counter = 0;
    input.get();
    if (static_cast<char>(input.get()) == 'd') {
        directed = true;
        adj_dir.resize(nodes);
    }
    else {
        directed = false;
    }

    adj.resize(nodes);
    std::vector<unsigned long long> renamed(nodes);

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
            if (directed) {
                adj_dir[a].push_back(b);
            }
        }
        if (!in_vector(a, adj[b])) {
            adj[b].push_back(a);
        }
    }
    edges = edge_counter;
}

void read_graph_upd(std::ifstream& input, size_t& nodes, size_t& edges, bool& directed, std::vector<std::vector<unsigned long long>>& adj, std::vector<std::vector<unsigned long long>>& adj_dir) {

    input >> nodes;
    input >> edges;
    input.get();
    if (static_cast<char>(input.get()) == 'd') {
        directed = true;
        adj_dir.resize(nodes);
    }
    else {
        directed = false;
    }

    adj.resize(nodes);

    unsigned long long counter = 0;
    unsigned long long a;
    char mychar = ' ';
    unsigned long long edge_counter = 0;
    while (input.peek()!=EOF) {
        while (mychar != ':' && input.peek() != EOF) {
            /*std::cout << mychar << "\n";*/
            mychar = input.get();
        }
        mychar = ' ';
        if(input.peek() != EOF){
            input.get();
        }
        while(input.peek() != '\n' && input.peek() != EOF) {
            input >> a;
            ++edge_counter;
            adj[a].push_back(counter);
            adj[counter].push_back(a);
            if (directed) {
                adj_dir[counter].push_back(a);
            }
        }
        ++counter;
    }
}
void find_WCC(unsigned long long& max_size, unsigned long long& num_of_sets, std::vector<unsigned long long>& sets, const size_t nodes, const std::vector<std::vector<unsigned long long>>& adj) {
    sets.resize(nodes);
    std::queue<unsigned long long> q;
    unsigned long long cur_size = 0;
    for (size_t i = 0; i < nodes; ++i) {
        sets[i] = 0;
    }
    for (size_t i = 0; i < nodes; ++i) {
        if (sets[i] == 0) {
            ++num_of_sets;
            sets[i] = num_of_sets;
            q.push(i);
            ++cur_size;
            unsigned long long current_node;
            while (!q.empty()) {
                current_node = q.front();
                for (int i = 0; i < adj[current_node].size(); ++i) {
                    if (sets[adj[current_node][i]] == 0) {
                        sets[adj[current_node][i]] = num_of_sets;
                        q.push(adj[current_node][i]);
                        ++cur_size;
                    }
                }
                q.pop();
            }
            if (max_size < cur_size) {
                max_size = cur_size;
            }
            cur_size = 0;
        }
    }
}
void DFS(unsigned long long node, const std::vector<std::vector<unsigned long long>>& adj_dir, std::vector<bool>& visited, unsigned long long& visited_counter, std::vector<unsigned long long>& ordered) {
    visited[node] = true;
    for (unsigned long long i = 0; i < adj_dir[node].size(); ++i) {
        if (!visited[adj_dir[node][i]]) {
            DFS(adj_dir[node][i], adj_dir, visited, visited_counter, ordered);
        }
    }
    ordered[visited_counter] = node;
    ++visited_counter;
}
void reverse_list(const std::vector<std::vector<unsigned long long>>& adj_dir, std::vector<std::vector<unsigned long long>>& adj_dir_reverse) {
    for (size_t i = 0; i < adj_dir.size(); ++i) {
        for (size_t j = 0; j < adj_dir[i].size(); ++j) {
            adj_dir_reverse[adj_dir[i][j]].push_back(i);
        }
    }
}
void DFS_reverse(unsigned long long node, const std::vector<std::vector<unsigned long long>>& adj_dir_reverse, std::vector<bool>& visited, unsigned long long& cur_size_dir, unsigned long long& num_of_sets_dir, std::vector<unsigned long long>& sets_dir) {
    visited[node] = true;
    sets_dir[node] = num_of_sets_dir;
    ++cur_size_dir;
    //std::cout << node << "\n";
    for (unsigned long long i = 0; i < adj_dir_reverse[node].size(); ++i) {
        if (!visited[adj_dir_reverse[node][i]]) {
            DFS_reverse(adj_dir_reverse[node][i], adj_dir_reverse, visited, cur_size_dir, num_of_sets_dir, sets_dir);
        }
    }
}
void find_SCC(unsigned long long& max_size_dir, unsigned long long& num_of_sets_dir, std::vector<unsigned long long>& sets_dir, const size_t nodes, const std::vector<std::vector<unsigned long long>>& adj_dir_reverse,const std::vector<unsigned long long>& ordered, std::vector<bool>& visited) {
    for(unsigned long long i = 0; i < ordered.size(); ++i) {
        if (!visited[ordered[i]]) {
            //std::cout << "new set\n";
            unsigned long long cur_size = 0;
            DFS_reverse(ordered[i], adj_dir_reverse, visited, cur_size, num_of_sets_dir, sets_dir);
            ++num_of_sets_dir;
            if (max_size_dir < cur_size) {
                max_size_dir = cur_size;
            }
        }
    }
}
int main(int argc, char** argv)
{
    std::ifstream input(argv[1]);
    std::ofstream outfile("C:\\Users\\dmitry\\dataset\\output.txt");

    size_t edges;
    size_t nodes;
    bool directed;
    std::vector<std::vector<unsigned long long>> adj;
    std::vector<std::vector<unsigned long long>> adj_dir;

    //read_graph(input, nodes, edges, directed, adj, adj_dir);
    read_graph_upd(input, nodes, edges, directed, adj, adj_dir);

    //unsigned long long max_size = 0;
    //unsigned long long num_of_sets = 0;
    //std::vector<unsigned long long> sets;

    //find_WCC(max_size, num_of_sets, sets, nodes, adj);

    if (directed) {
        unsigned long long max_size_dir = 0;
        unsigned long long num_of_sets_dir = 0;
        std::vector<unsigned long long> sets_dir(nodes);
        std::vector<bool> visited(nodes);
        unsigned long long visited_counter = 0;
        std::vector<unsigned long long> ordered(nodes);
        std::vector<std::vector<unsigned long long>> adj_dir_reverse(nodes);

        for (unsigned long long i = 0; i < nodes; ++i) {
            if (!visited[i]) {
                DFS(i, adj_dir, visited, visited_counter, ordered);
            }
        }
        for (unsigned long long i = 0; i < nodes; ++i) {
            visited[i] = false;
        }
        reverse_list(adj_dir, adj_dir_reverse);
        reverse(ordered.begin(), ordered.end());

        find_SCC(max_size_dir, num_of_sets_dir, sets_dir, nodes, adj_dir_reverse, ordered, visited);

        std::cout << "number of SCC: " << num_of_sets_dir << "\n";
        std::cout << "Nodes in largest SCC: " << max_size_dir << "\n";
    }


    double N = static_cast<double>(nodes);
    double E = static_cast<double>(edges);

    //std::cout << "Number of nodes: " << nodes << "\n";
    //std::cout << "Number of Edges: " << edges << "\n";

    //if (directed){
    //    std::cout << "Graph density: " << E/(N*(N-1)) << "\n";
    //}
    //else {
    //    std::cout << "Graph density: " << 2 * E / (N * (N - 1)) << "\n";
    //}


    //std::cout << "number of WCC: " << num_of_sets << "\n";
    //std::cout << "Nodes in largest WCC: " << max_size << "\n";


    //printAdjacencyList(adj_dir, outfile);
    return 0;
}
