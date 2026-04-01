#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class mystring {
private:
    char *ch = nullptr;
    int len = 0;

public:
    mystring() : ch(nullptr), len(0) {}

    mystring(int _len, int c) {
        if (_len < 0) _len = 0;
        len = _len;
        if (len > 0) {
            ch = new char[len];
            for (int i = 0; i < len; ++i) ch[i] = static_cast<char>(c);
        } else {
            ch = nullptr;
        }
    }

    mystring(string &c) {
        len = static_cast<int>(c.length());
        if (len > 0) {
            ch = new char[len];
            for (int i = 0; i < len; ++i) ch[i] = c[i];
        } else {
            ch = nullptr;
        }
    }

    ~mystring() {
        if (ch) {
            delete[] ch;
            ch = nullptr;
        }
        len = 0;
    }

    // index operator: return character or '\0' if out of range
    char operator[](int idx) const {
        if (idx < 0 || idx >= len) return '\0';
        return ch[idx];
    }

    // compare: lexicographic by characters, then by length
    bool operator<(const mystring &other) const {
        int n = min(len, other.len);
        for (int i = 0; i < n; ++i) {
            if (ch[i] != other.ch[i]) return ch[i] < other.ch[i];
        }
        return len < other.len;
    }

    // concatenate other to this
    void ADD(const mystring &other) {
        int newlen = len + other.len;
        char *nch = nullptr;
        if (newlen > 0) {
            nch = new char[newlen];
            for (int i = 0; i < len; ++i) nch[i] = ch ? ch[i] : '\0';
            for (int i = 0; i < other.len; ++i) nch[len + i] = other.ch[i];
        }
        if (ch) delete[] ch;
        ch = nch;
        len = newlen;
    }

    // output without newline
    void out() const {
        for (int i = 0; i < len; ++i) cout << ch[i];
    }

    int get_len() const { return len; }
};

string str_in1, str_in2;
int n, id;

int main() {
    // keep C++ iostreams in default sync mode to avoid reordering

    if (!(cin >> id)) return 0;
    if (id == 1) {
        mystring str1(100, 'a');
        str1.out();
        cout << '\n';
        // cout << str1 << endl;
    } else if (id == 2) {
        cin >> str_in1;
        mystring str2 = str_in1;
        cin >> n;
        for (int i = 0, x; i < n; ++i) {
            cin >> x;
            cout << str2[x] << '\n';
        }
    } else if (id == 3) {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        cout << (int)(str2 < str3) << '\n';
    } else if (id == 4) {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        str2.ADD(str3);
        str2.out();
        cout << '\n';
        // cout << str2 << endl;
    } else {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        cin >> n;
        for (int i = 0, x; i < n; ++i) {
            cin >> x;
            cout << str3[x] << '\n';
        }
        cout << str2.get_len() << " " << str3.get_len() << '\n';
        cout << (int)(str2 < str3) << '\n';
        str2.ADD(str3);
        str2.out();
        cout << '\n';
        // cout << str2 << endl;
        cout << str2.get_len() << '\n';
    }
    return 0;
}
