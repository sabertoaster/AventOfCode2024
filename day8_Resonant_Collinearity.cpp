#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> isInRange_p1(const pair<int, int> &nodeA, const pair<int, int> &nodeB, int ROW, int COL)
{
    // Create a vector AB, with node A' = A - AB and node B' = B + AB
    // If A' and B' are in the range of the matrix, then A, B and AB are collinear

    pair<int, int> nodeA_prime = {nodeA.first - (nodeB.first - nodeA.first), nodeA.second - (nodeB.second - nodeA.second)};
    pair<int, int> nodeB_prime = {nodeB.first + (nodeB.first - nodeA.first), nodeB.second + (nodeB.second - nodeA.second)};

    // return the node within the range of the matrix
    vector<pair<int, int>> nodes;
    if (nodeA_prime.first >= 0 && nodeA_prime.first < ROW && nodeA_prime.second >= 0 && nodeA_prime.second < COL)
    {
        nodes.push_back(nodeA_prime);
    }
    if (nodeB_prime.first >= 0 && nodeB_prime.first < ROW && nodeB_prime.second >= 0 && nodeB_prime.second < COL)
    {
        nodes.push_back(nodeB_prime);
    }
    return nodes;
}

vector<pair<int, int>> isInRange_p2(const pair<int, int> &nodeA, const pair<int, int> &nodeB, int ROW, int COL)
{
    vector<pair<int, int>> nodes;

    int dx = nodeB.first - nodeA.first;
    int dy = nodeB.second - nodeA.second;

    int gcd = __gcd(abs(dx), abs(dy));
    dx /= gcd;
    dy /= gcd;

    pair<int, int> currentNode = nodeA;
    while (currentNode.first >= 0 && currentNode.first < ROW && currentNode.second >= 0 && currentNode.second < COL)
    {
        nodes.push_back(currentNode);
        currentNode.first += dx;
        currentNode.second += dy;
    }

    currentNode = nodeA;
    while (currentNode.first >= 0 && currentNode.first < ROW && currentNode.second >= 0 && currentNode.second < COL)
    {
        nodes.push_back(currentNode);
        currentNode.first -= dx;
        currentNode.second -= dy;
    }

    return nodes;
}

int antinodes_process(map<char, vector<pair<int, int>>> &char_positions, vector<string> &radarMap, vector<pair<int, int>> isInRange(const pair<int, int> &, const pair<int, int> &, int, int))
{
    int count = 0;
    vector<string> antinodeMap(radarMap.size(), string(radarMap[0].size(), '.'));

    for (auto &entry : char_positions)
    {
        for (int i = 0; i < entry.second.size() - 1; ++i)
        {
            for (int j = i + 1; j < entry.second.size(); ++j)
            {
                vector<pair<int, int>> nodes = isInRange(entry.second[i], entry.second[j], radarMap.size(), radarMap[0].size());
                for (const auto &node : nodes)
                {
                    if (antinodeMap[node.first][node.second] == '.')
                    {
                        antinodeMap[node.first][node.second] = '#';
                        ++count;
                    }
                }
            }
        }
    }

    return count;
}

void read_file(const string &filename, map<char, vector<pair<int, int>>> &char_positions, vector<string> &lines)
{
    ifstream file(filename);
    string line;
    int row = 0;

    while (getline(file, line))
    {
        lines.push_back(line);
        for (int col = 0; col < line.size(); ++col)
        {
            char ch = line[col];
            if (ch != '.')
            {
                char_positions[ch].emplace_back(row, col);
            }
        }
        ++row;
    }
}

int main()
{
    string filename = "input/day8.txt";
    map<char, vector<pair<int, int>>> char_positions;
    vector<string> lines;
    read_file(filename, char_positions, lines);

    // Print lines 
    for (const auto &line : lines)
    {
        cout << line << endl;
    }


    int count = antinodes_process(char_positions, lines, isInRange_p2);
    cout << count << endl;

    return 0;
}
