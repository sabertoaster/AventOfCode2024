#include <bits/stdc++.h>
using namespace std;

void read_file(string filename, int &rows, int &cols, pair<int, int> &startPos, vector<vector<int>> &maze)
{
    ifstream file(filename);
    string line;
    vector<string> lines;

    while (getline(file, line))
    {
        lines.push_back(line);
    }

    rows = lines.size();
    cols = lines[0].size();
    maze.resize(rows, vector<int>(cols));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (lines[i][j] == '^')
            {
                startPos = {i, j};
                maze[i][j] = 0;
            }
            else if (lines[i][j] == '#')
            {
                maze[i][j] = 1;
            }
            else
            {
                maze[i][j] = 0;
            }
        }
    }
    file.close();
}

int calculate_guard_route(vector<vector<int>> &maze, pair<int, int> startPos)
{
    int rows = maze.size();
    int cols = maze[0].size();
    int count = 0;
    pair<int, int> curDir = {0, -1}; // Initial direction: Up

    // Continue until guard walks out of bounds
    while (startPos.first >= 0 || startPos.first < rows || startPos.second >= 0 || startPos.second < cols)
    {
        int nextX = startPos.first + curDir.second;
        int nextY = startPos.second + curDir.first;

        // Check if out of bounds
        if (nextX < 0 || nextX >= rows || nextY < 0 || nextY >= cols)
        {
            break;
        }

        // Check if next position would be a wall
        if (maze[nextX][nextY] == 1)
        {
            pair<int, int> temp = curDir;
            temp.first = -curDir.second;
            temp.second = curDir.first;
            curDir = temp;
        }

        // Move the guard
        startPos.first += curDir.second;
        startPos.second += curDir.first;
        if (maze[startPos.first][startPos.second] == 0)
        {
            count++;
            maze[startPos.first][startPos.second] = 2;
        }
    }

    return count + 1; // Including starting position
}

int find_loop_point(vector<vector<int>> &maze, pair<int, int> startPos)
{
    // Loop on all maze's cells marked with "2" to find the loop point except for start position
    // If the loop point is found, increase the loop point counter

    vector<pair<int, int>> visited;
    int rows = maze.size();
    int cols = maze[0].size();

    // scan all visited cells
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (maze[i][j] == 2)
            {
                if (i != startPos.first && j != startPos.second)
                    visited.push_back({i, j});
            }
        }
    }
    int count = 0;
    for (auto cell : visited)
    {
        int x = startPos.first;
        int y = startPos.second;
        int nextX = x;
        int nextY = y;
        maze[cell.first][cell.second] = 1;                // Mark as wall
        pair<int, int> curDir = {0, -1}, upDir = {0, -1}; // Initial direction: Up

        // Continue until guard walks out of bounds
        while (nextX >= 0 || nextX < rows || nextY >= 0 || nextY < cols)
        {
            nextX = x + curDir.second;
            nextY = y + curDir.first;

            // Check if out of bounds
            if (nextX < 0 || nextX >= rows || nextY < 0 || nextY >= cols)
            {
                break;
            }

            // Check if next position would be a wall
            if (maze[nextX][nextY] == 1)
            {
                pair<int, int> temp = curDir;
                temp.first = -curDir.second;
                temp.second = curDir.first;
                curDir = temp;
            }

            // Move the guard
            x += curDir.second;
            y += curDir.first;

            if (x == startPos.first && y == startPos.second && curDir == upDir)
            {
                count++;
                break;
            }
        }
        maze[cell.first][cell.second] = 2; // Mark as visited
    }

    return count;
}

int main()
{
    int rows, cols;
    pair<int, int> startPos;
    vector<vector<int>> maze;

    read_file("input/day6.txt", rows, cols, startPos, maze);
    cout << startPos.first << " " << startPos.second << endl;

    int total_count = calculate_guard_route(maze, startPos);
    cout << total_count << endl;
    cout << find_loop_point(maze, startPos) << endl;
    // save the maze to a file
    ofstream file("output/day6.txt");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            file << maze[i][j];
        }
        file << endl;
    }

    return 0;
}
