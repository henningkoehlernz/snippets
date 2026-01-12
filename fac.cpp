#include <bits/stdc++.h>

/**
 * dynamic programming approach to fractional factorial computation;
 * no divisions so that unnecessary range overflow is avoided
 */
class Factorial
{
    // store values to avoid recomputation
    static std::vector<std::vector<double>> known;
public:
    // returns x! / (x-delta)!
    static double fraction(int x, int delta);
    // returns x!
    static double of(int x);
};

using namespace std;

vector<vector<double>> Factorial::known;

double Factorial::fraction(int x, int delta)
{
    if (known.size() <= x)
        known.resize(x + 1, { 1 });
    if (known[x].size() <= delta)
    {
        int y = x, y_delta = delta;
        while (known[y-1].size() <= y_delta - 1)
        {
            y--; y_delta--;
        }
        while (y <= x)
        {
            for (int d = known[y].size(); d <= y_delta; d++)
                known[y].push_back(known[y-1][d-1] * y);
            y++; y_delta++;
        }
    }
    return known[x][delta];
}

double Factorial::of(int x)
{
    return fraction(x, x);
}

int main(int argc, char**argv)
{
    if (argc < 3)
    {
        cout << "Usage: " << argv[0] << " [x] [delta]" << endl;
        return 0;
    }
    int x = atoi(argv[1]), delta = atoi(argv[2]);
    cout << x << "! / (" << x << "-" << delta << ")! = " << Factorial::fraction(x, delta) << endl;
    return 0;
}
