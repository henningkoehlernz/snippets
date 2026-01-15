#include <bits/stdc++.h>

/**
 * dynamic programming approach to fractional factorial computation;
 * no divisions so that unnecessary range overflow is avoided
 */
template<typename T>
class Factorial
{
    // store values to avoid recomputation
    static std::vector<std::vector<T>> known;
public:
    // returns x! / (x-delta)!
    static T fraction(int x, int delta)
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
    // returns x!
    static T of(int x)
    {
        return fraction(x, x);
    }
};

template<typename T>
std::vector<std::vector<T>> Factorial<T>::known;

using namespace std;

int main(int argc, char**argv)
{
    if (argc < 3)
    {
        cout << "Usage: " << argv[0] << " [x] [delta]" << endl;
        return 0;
    }
    int x = atoi(argv[1]), delta = atoi(argv[2]);
    cout << x << "! / (" << x << "-" << delta << ")! =" << endl;
    cout << "\t= " << setprecision(16) << Factorial<double>::fraction(x, delta) << " (using double)" << endl;
    cout << "\t= " << setprecision(16) << Factorial<uint64_t>::fraction(x, delta) << " (using uint64_t)" << endl;
    return 0;
}
