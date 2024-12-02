#include <bits/stdc++.h>

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
    int size_ = a.size();
    if (size_ < 2)
    {
        return 0;
    }
    int dir = sign(a[1] - a[0]), dis = abs(a[1] - a[0]);
    int fl = 1, init = 1;
    // std::cout << "\ncc " << a[1] << " " << a[0] << dir << " cc\n";
    if (dir == 0)
    {
        fl--;
    }
    if (dis > 3 || sign(a[2] - a[1]) != dir)
    {
        fl--;
        init = 2;
        dir = sign(a[2] - a[1]);
    }
    if (fl < 0)
    {
        return 0;
    }

    if (dir < 0)
    {
        for (int i = init; i < size_ - 2; i++)
        {
    // cout << "CHECK " << fl << endl;
            if (fl < 0)
            {
                return 0;
            }
            if (a[i + 1] - a[i] < -3 || a[i + 1] - a[i] >= 0)
            {

                int max_ = max(i + 1, size_ - 1);

                if (a[max_] - a[i] < -3 || a[max_] - a[i] >= 0)
                {
                    return 0;
                }
                else
                {
                    fl--;
                    i++;
                }
            }
        }
    }
    else if (dir > 0)
    {
        for (int i = init; i < size_ - 2; i++)
        {
            if (fl < 0)
            {
                return 0;
            }
            if (a[i + 1] - a[i] > 3 || a[i + 1] - a[i] <= 0)
            {
                int max_ = max(i + 1, size_ - 1);

                if (a[max_] - a[i] > 3 || a[max_] - a[i] <= 0)
                {
                    return 0;
                }
                else
                {
                    fl--;
                    i++;
                }
            }
        }
    }
    else
    {
        return 0;
    }

    return 1;
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
}