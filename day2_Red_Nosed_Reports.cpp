#include <bits/stdc++.h>

#define abs(a) ((a) > 0 ? (a) : -(a))

using namespace std;

int process(vector<int> &a)
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
        dir = 0;
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
    else {
        return 0;
    }

    return 1;
}

// Create a read file function that get filename and read it into 2 vectors of in
int read_file_and_process(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "File not found" << endl;
        return 0;
    }
    int n = 1000, res = 0;
    vector<int> a(n);
    stringstream ss;
    string line, token;
    for (int i = 0; i < n; i++)
    {
        getline(file, line);
        ss.str(line);
        while (getline(ss, token, ' '))
        {
            a.push_back(stoi(token));
            cout << token << " ";
        }

        // Process
        res += process(a);
        cout << endl << res << endl;

        // Clean
        a.clear();
        ss.clear();
    }
    file.close();
    return res;
}

int main()
{
    // vector<int> a = {8, 6, 4, 4, 1};
    // cout << process(a) << endl;
    cout << read_file_and_process("input_day2.txt") << endl;
    return 0;
}