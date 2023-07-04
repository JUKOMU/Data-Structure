#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class BigInt {
public:
    vector<int> num;
    int sign;

    BigInt() : sign(1) {}

    BigInt(int size) : num(size), sign(1) {}

    BigInt(int sign, int size) : num(size), sign(sign) {}

    BigInt(string s) {
        if (s[0] == '-') {
            sign = -1;
            s.erase(0, 1);
        }
        else {
            sign = 1;
        }
        num.resize(s.size());
        for (int i = 0; i < s.size(); ++i) {
            num[i] = s[s.size() - i - 1] - '0';
        }
        trim();
    }

    int size() const {
        return num.size();
    }

    bool empty() const {
        return num.empty();
    }

    void resize(int size) {
        num.resize(size);
        trim();
    }

    void trim() {
        while (!num.empty() && num.back() == 0) {
            num.pop_back();
        }
        if (num.empty()) {
            sign = 1;
        }
    }

    void flip() {
        sign = -sign;
    }

    int back() const {
        return num.empty() ? 0 : num.back();
    }

    int operator[](int i) const {
        return i < num.size() ? num[i] : 0;
    }

    int& operator[](int i) {
        return num[i];
    }
};

typedef vector<int> BigInt;

void output(const BigInt& num) {
    int len = num.size();
    for (int i = len - 1; i >= 0; --i) {
        cout << num[i];
    }
    cout << endl;
}

void trim(BigInt& num) {
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back();
    }
}

BigInt from_string(const string& s) {
    int len = s.size();
    BigInt num;
    for (int i = len - 1; i >= 0; --i) {
        num.push_back(s[i] - '0');
    }
    trim(num);
    return num;
}

string to_string(const BigInt& num) {
    int len = num.size();
    string s;
    for (int i = len - 1; i >= 0; --i) {
        s += (char)(num[i] + '0');
    }
    return s;
}

BigInt add(const BigInt& a, const BigInt& b) {
    int len1 = a.size(), len2 = b.size();
    int len = max(len1, len2);
    BigInt c(len);
    int carry = 0;
    for (int i = 0; i < len; ++i) {
        int tmp = (i < len1 ? a[i] : 0) + (i < len2 ? b[i] : 0) + carry;
        c[i] = tmp % 100;
        carry = tmp / 100;
    }
    if (carry > 0) {
        c.push_back(carry);
    }
    trim(c);
    return c;
}

BigInt sub(const BigInt& a, const BigInt& b) {
    int len1 = a.size(), len2 = b.size();
    int len = max(len1, len2);
    BigInt c(len);
    int borrow = 0;
    for (int i = 0; i < len; ++i) {
        int tmp = (i < len1 ? a[i] : 0) - (i < len2 ? b[i] : 0) - borrow;
        if (tmp < 0) {
            tmp += 100;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        c[i] = tmp;
    }
    trim(c);
    return c;
}

BigInt mul(const BigInt& a, const BigInt& b) {
    int len1 = a.size(), len2 = b.size();
    int len = len1 + len2;
    BigInt c(len);
    for (int i = 0; i < len1; ++i) {
        int carry = 0;
        for (int j = 0; j < len2; ++j) {
            int tmp = a[i] * b[j] + carry + c[i + j];
            c[i + j] = tmp % 100;
            carry = tmp / 100;
        }
        if (carry > 0) {
            c[i + len2] += carry;
        }
    }
    trim(c);
    return c;
}

// 假设 b 不为
BigInt div(const BigInt& a, const BigInt& b) {
    int len1 = a.size(), len2 = b.size();
    if (len1 < len2) {
        return BigInt(1, 0);
    }
    BigInt c(len1 - len2 + 1);
    BigInt r(a);
    reverse(r.begin(), r.end());
    reverse(b.begin(), b.end());
    BigInt d = b.back() * 100 + (len2 > 1 ? b[len2 - 2] : 0);
    for (int i = len1 - len2; i >= 0; --i) {
        int tmp = r[i + len2] * 100 + r[i + len2 - 1];
        int q = tmp / d, rem = tmp % d;
        while (rem * 100 + r[i + len2 - 2] < b.back() * q) {
            --q;
            rem += d;
        }
        for (int j = len2 - 1; j >= 0; --j) {
            int k = i + j;
            int tmp = b[j] * q + c[k];
            c[k] = tmp % 100;
            tmp /= 100;
            r[i + j] -= tmp;
            if (r[i + j] < 0) {
                r[i + j] += 100;
                --r[i + j - 1];
            }
        }
    }
    trim(c);
    reverse(c.begin(), c.end());
    return c;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    BigInt a = from_string(s1);
    BigInt b = from_string(s2);
    output(add(a, b));
    output(sub(a, b));
    output(mul(a, b));
    output(div(a, b));
    return 0;
}