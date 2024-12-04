#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    vector<int> dx = {-1, -1, -1, 0, 0, 1, 1, 1};
    vector<int> dy = {-1, 0, 1, -1, 1, -1, 0, 1};

    bool isValid(int x, int y, int rows, int cols)
    {
        return (x >= 0 && x < rows && y >= 0 && y < cols);
    }

    bool searchDirection(vector<string> &board, int row, int col, int dir)
    {
        string word = "XMAS";
        int rows = board.size();
        int cols = board[0].size();

        for (int i = 0; i < 4; i++)
        {
            int newRow = row + i * dx[dir];
            int newCol = col + i * dy[dir];

            if (!isValid(newRow, newCol, rows, cols) ||
                board[newRow][newCol] != word[i])
            {
                return false;
            }
        }
        return true;
    }

    bool isValidPattern(const vector<string> &board, int row, int col)
    {
        if (board[row][col] != 'A')
            return false;

        char topLeft = board[row - 1][col - 1];
        char topRight = board[row - 1][col + 1];
        char bottomLeft = board[row + 1][col - 1];
        char bottomRight = board[row + 1][col + 1];

        bool case1 = (topLeft == 'M' && topRight == 'M' &&
                      bottomLeft == 'S' && bottomRight == 'S');
        bool case2 = (topLeft == 'S' && topRight == 'S' &&
                      bottomLeft == 'M' && bottomRight == 'M');
        bool case3 = (topLeft == 'M' && topRight == 'S' &&
                      bottomLeft == 'M' && bottomRight == 'S');
        bool case4 = (topLeft == 'S' && topRight == 'M' &&
                      bottomLeft == 'S' && bottomRight == 'M');

        return case1 || case2 || case3 || case4;
    }

public:
    pair<int, int> solve(vector<string> &board)
    {
        int xmasCount = 0;
        int patternCount = 0;
        int rows = board.size();
        int cols = board[0].size();

        // Count XMAS occurrences
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (board[i][j] == 'X')
                {
                    for (int dir = 0; dir < 8; dir++)
                    {
                        if (searchDirection(board, i, j, dir))
                        {
                            xmasCount++;
                        }
                    }
                }
            }
        }

        // Count pattern occurrences
        for (int i = 1; i < rows - 1; i++)
        {
            for (int j = 1; j < cols - 1; j++)
            {
                if (isValidPattern(board, i, j))
                {
                    patternCount++;
                }
            }
        }

        return {xmasCount, patternCount};
    }
};

int main()
{
    Solution solution;
    ifstream file("input/day4.txt");
    string line;
    vector<string> board;

    while (getline(file, line))
    {
        board.push_back(line);
    }

    pair<int, int> result = solution.solve(board);
    std::cout << "XMAS count: " << result.first << endl;
    std::cout << "Pattern count: " << result.second << endl;

    return 0;
}