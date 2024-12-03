/* #include <bits/stdc++.h>

#define abs(a) ((a) > 0 ? (a) : -(a))
#define sign(a) (a > 0 ? 1 : -1)
using namespace std;

int process_normal(vector<int> &a)
{
    int size_ = a.size();
    if (size_ < 2)
    {
        return 0;
    }
    int dir = (a[1] - a[0]), dis = abs(dir);
    if (dis != 0)
    {

        dir = dir / dis;
    }
    else
    {
        return 0;
    }
    if (dis > 3)
    {
        return 0;
    }
    // cout << dir;

    if (dir < 0)
    {
        for (int i = 1; i < size_ - 1; i++)
        {
            if (a[i + 1] - a[i] < -3 || a[i + 1] - a[i] >= 0)
            {
                return 0;
            }
        }
    }
    else if (dir > 0)
    {
        for (int i = 1; i < size_ - 1; i++)
        {
            if (a[i + 1] - a[i] > 3 || a[i + 1] - a[i] <= 0)
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }

    return 1;
}

int process_tolerate(vector<int> &a)
{
    
}

// Create a read file function that get filename and read it into 2 vectors of in
int read_file_and_process(string filename, int process(vector<int> &a))
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "File not found" << endl;
        return 0;
    }
    int n = 1000, res = 0;
    vector<int> a;
    stringstream ss;
    string line, token;
    for (int i = 0; i < n; i++)
    {
        getline(file, line);
        ss.str(line);
        while (getline(ss, token, ' '))
        {
            a.push_back(stoi(token));
            cout << a.back() << " ";
        }

        // Process
        res += process(a);
        cout << endl
             << res << endl;

        // Clean
        a.clear();
        ss.clear();
    }
    file.close();
    return res;
}

int main()
{
    // vector<int> a = { 5, 6, 4, 5, 7};
    // cout << process_tolerate(a) << endl;
    cout << read_file_and_process("input_day2.txt", process_tolerate) << endl;
    return 0;
} */

// Disclaimer: My code is cooked while I'm trying to do O(n) and I'm too lazy to implement a new one so here's an alternative solution of @p1neapplechoco: https://github.com/p1neapplechoco/. Kudos to him.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

int part1();
int part2();

bool isSafePart1(vector<int> &);
bool isSafePart2(vector<int> &);

int main()
{
    // cout << part1();
    cout << part2();
}

int part1()
{
    int res = 0;
    ifstream input("input.txt");
    string line;

    while (getline(input, line))
    {
        vector<int> nums;

        for (int i = 0; i < line.size(); i++)
        {
            string tmp{};
            while (line[i] != ' ')
                tmp += line[i++];
            nums.push_back(stoi(tmp));
        }

        if (isSafePart1(nums))
            res++;
    }

    return res;
}

int part2()
{
    int res = 0;
    ifstream input("input.txt");
    string line;

    while (getline(input, line))
    {
        vector<int> nums;

        for (int i = 0; i < line.size(); i++)
        {
            string tmp{};
            while (line[i] != ' ')
                tmp += line[i++];
            nums.push_back(stoi(tmp));
        }

        if (isSafePart2(nums))
            res++;
    }

    return res;
}

bool isSafePart1(vector<int> &nums)
{
    if (nums[1] == nums[0])
        return false;

    bool isDescending = (nums[1] - nums[0] > 0);

    for (int i = 0; i < nums.size() - 1; i++)
    {
        int d = nums[i + 1] - nums[i];
        bool check = d > 0;
        if (abs(d) < 1 || abs(d) > 3 || check != isDescending)
            return false;
    }

    return true;
}

bool isSafePart2(vector<int> &nums)
{

    if (isSafePart1(nums))
        return true;
    else
        for (int i = 0; i < nums.size(); i++)
        {
            vector<int> tmp = nums;
            tmp.erase(tmp.begin() + i);
            if (isSafePart1(tmp))
                return true;
        }
    return false;
}
