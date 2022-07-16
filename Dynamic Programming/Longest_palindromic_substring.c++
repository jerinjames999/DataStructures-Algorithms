
/*
Approach 5: Manacher's Algorithm(Time O(n), space O(n))
There is even an O(n) algorithm called Manacher's algorithm, explained here in detail. However, it is a non-trivial algorithm, and no one expects you to come up with this algorithm in a 45 minutes coding session. But, please go ahead and understand it, I promise it will be a lot of fun.

*/

class Solution
{
public:
    string longestPalindrome(string s)
    {
        int size = s.size();
        string str;
        for (int i = 0; i < size; i++)
        {
            str.append("$" + s.substr(i, 1));
        }
        str.append("$");
        int new_size = 2 * size + 1;
        vector<int> Palindrome(new_size, 1);
        int Pos = 0, LPlength = 1;
        int center = 0, L = 0, R = 0;
        while (1)
        {
            int Plength = Palindrome[center];
            L = center - Plength / 2;
            R = center + Plength / 2;
            Palindrome[center] = PLengthwithCenter(str, center, L, R);
            if (LPlength < Palindrome[center])
            {
                LPlength = Palindrome[center];
                Pos = center - LPlength / 2;
            }
            //now L and R are the end indexes of the palindrome[center];
            if (R == new_size - 1)
                break;
            if (R != center)
            {
                center = nextCenter(str, Palindrome, center);
            }
            else
            {
                center = center + 1;
            }
        }

        LPlength = LPlength / 2;
        Pos = Pos / 2;

        return s.substr(Pos, LPlength);
    }

    int PLengthwithCenter(string &str, int center, int &l, int &r)
    { //done for l and r;
        int length = r - l + 1;
        l--;
        r++;
        while (isinBoundary(l, 0, str.size() - 1) && isinBoundary(r, 0, str.size() - 1) && str[l] == str[r])
        {
            length = length + 2;
            l--;
            r++;
        }
        l++;
        r--;
        return length;
    }

    bool isinBoundary(int point, int L, int R)
    {
        if (point < L || point > R)
            return 0;

        return 1;
    }

    int nextCenter(string &str, vector<int> &Palindrome, int center)
    {
        int Plength = Palindrome[center];
        int L = center - Plength / 2;
        int R = center + Plength / 2;
        int i = 1;
        while (center + i <= R)
        {
            if (Palindrome[center - i] != Plength - 2 * i)
            {
                Palindrome[center + i] = min(Plength - 2 * i, Palindrome[center - i]);
            }
            else
            {
                Palindrome[center + i] = Palindrome[center - i];
                return center + i;
            }
            i++;
        }
        return R + 1;
    }
};

//Time: O(n2) space: O(n2)
class Solution
{
public:
    string longestPalindrome(string s)
    {
        int size = s.size();
        int best = 1, pos = 0;
        vector<vector<bool>> isPalindrome(size, vector<bool>(size, 0));
        for (int i = 0; i < size; i++)
        {
            isPalindrome[i][i] = 1;
        }
        for (int i = 0; i < size - 1; i++)
        {
            if (s[i] == s[i + 1])
            {
                best = 2;
                pos = i;
                isPalindrome[i][i + 1] = 1;
            }
        }
        int diff = 2;
        while (diff < size)
        {
            for (int i = 0; i + diff < size; i++)
            {
                if (s[i] == s[i + diff] && isPalindrome[i + 1][i + diff - 1])
                {
                    best = diff + 1;
                    pos = i;
                    isPalindrome[i][i + diff] = 1;
                }
            }
            diff++;
        }
        return s.substr(pos, best);
    }
};