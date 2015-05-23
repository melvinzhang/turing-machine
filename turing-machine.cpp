/*
 * Reference: http://plms.oxfordjournals.org/content/s2-42/1/230.full.pdf+html
 *
 * Instruction set
 * ===============
 * m-config   symbol   operations   final m-config
 * string     char     op,...       string
 *
 * op: L, R, P<symbol>, E
 */

#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <vector>
#include <queue>

using namespace std;

struct Configuration {
    string state;
    char symbol;
    bool operator<(const Configuration &o) const {
        return state < o.state || (state == o.state && symbol < o.symbol);
    }
};

struct Action {
    string ops;
    string state;
};

string start;
map< Configuration, Action > program;
map< int, char > tape;
    
void load_program() {
    cin.sync_with_stdio(false);
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string state, symbol, ops, fstate;
        iss >> state >> symbol >> ops >> fstate;
        
        if (start.length() == 0) {
            start = state;
        }
        
        Configuration c = {state, symbol.at(0)};
        Action a = {ops, fstate};
        program[c] = a;
    }
}

void print_program() {
    for (auto it=program.begin(); it != program.end(); it++) {
        cout << it->first.state << " ";
        cout << it->first.symbol << " ";
        cout << it->second.ops << " ";
        cout << it->second.state << endl;
    }
}

void print_tape() {
    cout << "tape: ";
    for (auto it=tape.begin(); it != tape.end(); it++) {
        cout << it->second;
    }
    cout << endl;
}

void print_config(Configuration c) {
    cout << "conf: " << c.state << " " << c.symbol << endl;
}

char read_tape(int tp) {
    if (tape.count(tp)) {
        return tape[tp];
    } else {
        return '~';
    }
}

int perform_ops(int tp, string ops) {
    for (int i = 0; i < ops.length(); i++) {
        char op = ops.at(i);
        switch (op) {
            case 'R':
                tp++;
                break;
            case 'L':
                tp--;
                break;
            case 'E':
                tape[tp] = '~';
                break;
            case 'P':
                i++;
                tape[tp] = ops.at(i);
            case ',':
                break;
            default:
                cout << "unknown op: " << op << endl;
                exit(1);
        }
    }
    return tp;
}

void eval(string curr, int tp) {
    while (true) {
        char s = read_tape(tp);
        Configuration c = {curr, s};
        if (program.count(c) == 0) {
            break;
        }
        Action a = program[c];
        tp = perform_ops(tp, a.ops);
        curr = a.state;
        print_config(c);
        print_tape();
    }
}

int main() {
    load_program();
    print_program();
    eval(start, 0);
    print_tape();
    return 0;
}
