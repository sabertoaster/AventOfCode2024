#include <bits/stdc++.h>
using namespace std;

#define ll long long

void readFile(string filename, vector<pair<ll, vector<ll>>> &input)
{
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        ll key;
        char colon;
        ss >> key >> colon;

        vector<ll> values;
        ll value;
        while (ss >> value)
        {
            values.push_back(value);
        }

        input.push_back({key, values});
    }

    file.close();
}

ll process_p1(vector<pair<ll, vector<ll>>> &input)
{
    ll sum = 0;
    for (auto &pair : input)
    {
        ll key = pair.first;
        vector<ll> nums = pair.second;

        vector<char> ops(nums.size() - 1);
        for (size_t i = 0; i < ops.size(); i++)
        {
            ops[i] = '+';
        }

        bool found = false;
        while (!found)
        {
            ll result = nums[0];
            for (size_t i = 0; i < ops.size(); i++)
            {
                if (ops[i] == '+')
                {
                    result += nums[i + 1];
                }
                else
                {
                    result *= nums[i + 1];
                }
            }

            if (result == key)
            {
                sum += key;
                found = true;
            }

            // Generate next combination of operators
            size_t j = 0;
            while (j < ops.size())
            {
                if (ops[j] == '+')
                {
                    ops[j] = '*';
                    break;
                }
                ops[j] = '+';
                j++;
            }
            if (j >= ops.size())
                break;
        }
    }
    cout << "Sum: " << sum << endl;
    return sum;
}

ll process_p2(vector<pair<ll, vector<ll>>> &input)
{
    ll sum = 0;
    for (auto &pair : input)
    {
        ll key = pair.first;
        vector<ll> nums = pair.second;

        vector<char> ops(nums.size() - 1);
        for (size_t i = 0; i < ops.size(); i++)
        {
            ops[i] = '+';
        }

        bool found = false;
        while (!found)
        {
            ll result = nums[0];
            for (size_t i = 0; i < ops.size(); i++)
            {
                if (ops[i] == '+')
                {
                    result += nums[i + 1];
                }
                else if (ops[i] == '*')
                {
                    result *= nums[i + 1];
                }
                else if (ops[i] == '|')
                {
                    string concat = to_string(result) + to_string(nums[i + 1]);
                    result = stoll(concat);
                }
            }

            if (result == key)
            {
                sum += key;
                found = true;
            }

            // Generate next combination of operators
            size_t j = 0;
            while (j < ops.size())
            {
                if (ops[j] == '+')
                {
                    ops[j] = '*';
                    break;
                }
                else if (ops[j] == '*')
                {
                    ops[j] = '|';
                    break;
                }
                ops[j] = '+';
                j++;
            }
            if (j >= ops.size())
                break;
        }
    }
    cout << "Sum: " << sum << endl;
    return sum;
}

int main()
{

    vector<pair<ll, vector<ll>>> input;
    readFile("input/day7.txt", input);

    // for (auto &p : input)
    // {
    //     cout << p.first << ": ";
    //     for (int i : p.second)
    //     {
    //         cout << i << " ";
    //     }
    //     cout << endl;
    // }

    process_p1(input);
    process_p2(input);

    return 0;
}