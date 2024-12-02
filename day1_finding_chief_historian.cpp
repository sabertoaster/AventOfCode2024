#include <bits/stdc++.h>

#define abs(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))

using namespace std;

// Create a quick sort function that sort a vector
void qsort(vector<int> &vec) {
    if (vec.size() <= 1) return;
    int pivot = vec[vec.size() / 2];
    vector<int> left, right;
    for (int i = 0; i < vec.size(); i++) {
        if (i == vec.size() / 2) continue;
        if (vec[i] < pivot) left.push_back(vec[i]);
        else right.push_back(vec[i]);
    }
    qsort(left);
    qsort(right);
    vec.clear();
    vec.insert(vec.end(), left.begin(), left.end());
    vec.push_back(pivot);
    vec.insert(vec.end(), right.begin(), right.end());
}

// Create a read file function that get filename and read it into 2 vectors of in
void read_file(string filename, vector<int> &a, vector<int> &b)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "File not found" << endl;
        return;
    }
    int n = 1000;
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; i++)
    {
        file >> a[i] >> b[i];
    }
    file.close();
}

/*
    Create a function that calculate the total distance between 2 vectors of int
    The total distance is the sum of the absolute difference between each element of the 2 vectors
*/
int total_distance(vector<int> &a, vector<int> &b)
{
    int sum = 0;
    for (int i = 0; i < a.size(); i++)
    {
        sum += abs(a[i], b[i]);
    }
    return sum;
}

/*
    Create a function that calculate the similarity score between 2 vectors of int
    The similarity score is the sum of the product of the frequency of each element in the 2 vectors
*/
int similarity_score(vector<int> &a, vector<int> &b)
{
    map<int, int> m{};
    for (int i = 0; i < a.size(); i++)
    {
        m[b[i]]++;
    }
    int score = 0;
    for (int i = 0; i < a.size(); i++)
    {
        score += m[a[i]] * a[i];
    }
    return score;
}


int main()
{
    vector<int> a, b;
    read_file("input_day1.txt", a, b); // My input for reference
    qsort(a);
    qsort(b);
    
    cout << "Total distance: " << total_distance(a, b) << endl;
    cout << "Similarity score: " << similarity_score(a, b) << endl;

    return 0;
}