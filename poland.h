#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

const double EPS = 0.000001;
static const size_t npos = -1;

struct Stack {
    double number;
    char znak;
    Stack* next;
};

Stack*top1 = nullptr;
Stack*top2 = nullptr;

void push(Stack*&t, double number, char znak) {
    Stack*p = new(Stack);
    p -> number = number;
    p -> znak = znak;
    p -> next = t;
    t = p;
}

Stack pop(Stack*&t) {
    Stack st = *t;
    t = t -> next;
    return st;
}

int r = 0;

void apply(char znak) {
    r = 0;
    if (znak == '+' || znak == '-' || znak == '*' || znak == '/' || znak == '^') {
        double b = pop(top1).number;
        double a = pop(top1).number;
        double c;
        if (znak == '+') {
            c = a + b;
        }
        if (znak == '-') {
            c = a - b;
        }
        if (znak == '/' && abs(b) >= EPS) {
            c = a / b;
        } else if (znak == '/' && abs(b) < EPS) {
            r = -1;
        }
        if (znak == '*') {
            c = a * b;
        }
        if (znak == '^') {
            c = pow(a, b);
        }
        if (r == 0) {
            push(top1, c, '@');
        }
    } else {
        double b = pop(top1).number;
        double c;
        if (znak == 'S') {
            c = sin(b);
        }
        if (znak == 'C') {
            c = cos(b);
        }
        if (znak == 'T') {
            c = tan(b);
        }
        if (znak == 'L' && b > 0) {
            c = log(b);
        } else if (znak == 'L' && b <= 0) {
            r = -1;
        }
        if (znak == 'Q' && b >= 0) {
            c = sqrt(b);
        } else if (znak == 'Q' && b < 0) {
            r = -1;
        }
        if (r == 0) {
            push(top1, c, '@');
        }
    }
}

int prior(char el) {
    if (el == '(' || el == ')') {
        return 0;
    }
    if (el == '+' || el == '-') {
        return 1;
    }
    if (el == '*' || el == '/') {
        return 2;
    }
    if (el == '^') {
        return 3;
    }
    if (el == 'S' || el == 'C' || el == 'T' || el == 'L' || el == 'Q') {
        return 4;
    }
}

int Error(string s) {
    int t = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            t += 1;
        }
        if (s[i] == ')') {
            t -= 1;
        }
    }
    if (t != 0) {
        return -1;
    }
    for (int i = 0; i < s.size() - 1; i++) {
        if ((s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-' || s[i] == '^')
            && (s[i + 1] == '-' || s[i + 1] == '+' || s[i + 1] == '*'
            || s[i + 1] == '/'|| s[i + 1] == '^')) {
            return -1;
        }
    }
    if (s[0] == '*' || s[0] == '/' || s[0] == '^') {
        return -1;
    }
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == '(' && (s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '^')) {
            return -1;
        }
    }
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-'
             || s[i] == '^') && s[i + 1] == ')') {
            return -1;
        }
    }
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '(' && s[i] != ')' && s[i] != '*' && s[i] != '/'
            && s[i] != '-' && s[i] != '+' && s[i] != '0' && s[i] != '9'
            && s[i] != '1' && s[i] != '2' && s[i] != '3' && s[i] != '4'
            && s[i] != '5' && s[i] != '6' && s[i] != '7' && s[i] != '8'
            && s[i] != 'S' && s[i] != 'C' && s[i] != 'T' && s[i] != 'Q'
            && s[i] != 'L' && s[i] != '^' && s[i] != '.') {
            return -1;
        }
    }
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == '(' && s[i + 1] == ')') {
            return -1;
        }
        if (s[i] == ')' && s[i + 1] == '(') {
            return -1;
        }
    }
    if (s[s.size() - 1] == '+' || s[s.size() - 1] == '-'
        || s[s.size() - 1] == '/' || s[s.size() - 1] == '*' || s[s.size() - 1] == '^') {
        return -1;
    }
    for (int i = 0; i < s.size() - 1; i++) {
        if ((s[i] == 'S' || s[i] == 'C' || s[i] == 'T' || s[i] == 'Q' || s[i] == 'L')
            && (s[i + 1] != '(')) {
            return -1;
        }
    }
}

void replace_ALL(string &s, string s1, string s2) {
     size_t ind = s.find(s1);
     while (ind != npos) {
        s.replace(ind, s1.size(), s2);
        ind = s.find(s1, ind + s2.size());
     }
}

int calc(string s, double &rez) {
    string ss;

    if (s[0] == '-') {
        s = '0' + s;
    }
    s += ' ';
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == '(' && s[i + 1] == '-') {
            ss += s[i];
            ss += '0';
        } else {
            ss += s[i];
        }
    }
    s = ss;
    replace_ALL(s, "sin", "S");
    replace_ALL(s, "cos", "C");
    replace_ALL(s, "tg", "T");
    replace_ALL(s, "sqrt", "Q");
    replace_ALL(s, "ln", "L");

    if (Error(s) == -1) {
        return -1;
    }

    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            double x = 0.0;
            double y = 0.0;
            int m = 0;
            while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
                x = x * 10 + (s[i] - '0');
                i++;
            }
            if (s[i] == '.') {
                i++;
                while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
                    y = y * 10 + (s[i] - '0');
                    m++;
                    i++;
                }
                y /= pow(10, m);
                x += y;
            }
            i--;
            push(top1, x, '@');
        } else if (s[i] == '(') {
            push(top2, 0.0, s[i]);
        } else if (s[i] == ')') {
            while ((*top2).znak != '(') {
                apply(pop(top2).znak);
                if (r == -1) {
                    return -1;
                }
            }
            pop(top2);
        } else {
                while (top2 != nullptr && prior((*top2).znak) >= prior(s[i])) {
                    apply(pop(top2).znak);
                if (r == -1) {
                    return -1;
                }
            }
            push(top2, 0.0, s[i]);
        }
    }
    while (top2 != nullptr) {
        apply(pop(top2).znak);
        if (r == -1) {
            return -1;
        }
    }

    rez = pop(top1).number;
    return 0;
}
