#include <bits/stdc++.h>
#include <regex>

using namespace std;

ll process_line(const string &line)
{
    ll sum = 0;
    regex const pattern{R"~(mul\(-?\d+,-?\d+\))~"};
    regex const numbers{R"~(\d+)~"};

    sregex_iterator matches{line.begin(), line.end(), pattern};
    sregex_iterator end;

    for (; matches != end; ++matches)
    {
        string match = (*matches)[0].str();
        cout << match << endl;
        sregex_iterator nums{match.begin(), match.end(), numbers};
        sum += std::stoll((*nums)[0]) * std::stoll((*++nums)[0]);
    }
    return sum;
}

ll process_line_p2(const string &line)
{
    ll sum_ = 0;
    regex const pattern{R"~(mul\(-?\d+,-?\d+\)|do\(\)|don\'t\(\))~"};
    regex const numbers{R"~(\d+)~"};

    sregex_iterator matches{line.begin(), line.end(), pattern};
    sregex_iterator end;
    bool flag = true;
    for (; matches != end; ++matches)
    {
        string match = (*matches)[0].str();
        // cout << match << endl;
        if (match == "do()")
        {
            flag = true;
        }
        else if (match == "don't()")
        {
            flag = false;
        }
        else if (flag) // if flag is true
        {
            sregex_iterator nums{match.begin(), match.end(), numbers};
            // cout << std::stoll((*nums)[0]) << " " << std::stoll((*++nums)[0]) << endl;
            sum_ += std::stoll((*nums)[0]) * std::stoll((*++nums)[0]);
            // cout << match << endl;
        }
    }
    return sum_;
}

int main()
{
    // process_line_p2(R"~(xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5)mul(8,5)))~");
    ll total_sum = 0;
    ifstream file("input/day3.txt");
    string line;

    while (getline(file, line))
    {
        total_sum += process_line_p2(line);
    }
    cout << "Total sum: " << total_sum << endl;

    file.close();
    return 0;
}