/*
 * Reference: http://plms.oxfordjournals.org/content/s2-42/1/230.full.pdf+html
 *
 * Instruction set
 * ===============
 * m-config   symbol   operations   final m-config
 * string     char     op1,op2,...  string
 *
 * op:
 *   L - move left one step
 *   R - move right one step
 *   P<symbol> - print symbol on tap
 *   E - erase symbol from tap
 * symbol:
 *   ~ - matches blank cell
 *   * - matches any symbol
 *   other char matches themselves
 *
 * Lines starting with # are ignored by the interpreter
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

struct Machine {
    int tp = 0;
    string start;
    map< Configuration, Action > program;
    map< int, char > tape;
};
    
void load_program(Machine &m) {
    cin.sync_with_stdio(false);
    string line;
    while (getline(cin, line)) {
        // skip empty lines
        if (line.length() == 0) {
            continue;
        }
        
        // lines begining with # are comments
        if (line.at(0) == '#') {
            continue;
        }

        istringstream iss(line);
        string state, symbol, ops, fstate;
        iss >> state >> symbol >> ops >> fstate;
        
        if (m.start.length() == 0) {
            m.start = state;
        }
        
        Configuration c = {state, symbol.at(0)};
        Action a = {ops, fstate};
        m.program[c] = a;
    }
}

void print_program(const Machine &m) {
    for (auto it=m.program.begin(); it != m.program.end(); it++) {
        cout << it->first.state << " ";
        cout << it->first.symbol << " ";
        cout << it->second.ops << " ";
        cout << it->second.state << endl;
    }
}

void print_tape(const Machine &m) {
    cout << "tape: ";
    for (auto it=m.tape.begin(); it != m.tape.end(); it++) {
        cout << it->second;
    }
    cout << endl;
}

void print_config(Configuration c) {
    cout << "conf: " << c.state << " " << c.symbol << endl;
}

char read_tape(Machine &m, int tp) {
    if (m.tape.count(tp)) {
        return m.tape[tp];
    } else {
        return '~';
    }
}

int perform_ops(Machine &m, int tp, string ops) {
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
                m.tape[tp] = '~';
                break;
            case 'P':
                i++;
                m.tape[tp] = ops.at(i);
            case ',':
                break;
            default:
                cout << "unknown op: " << op << endl;
                exit(1);
        }
    }
    return tp;
}

void eval(Machine &m, int max) {
    string curr = m.start;
    int cnt = 0;
    while (cnt < max) {
        cnt++;
        char s = read_tape(m, m.tp);
        Configuration c = {curr, s};
        if (m.program.count(c) == 0) {
            c = {curr, '*'};
        }
        if (m.program.count(c) == 0) {
            break;
        }
        Action a = m.program[c];
        m.tp = perform_ops(m, m.tp, a.ops);
        curr = a.state;
        print_config(c);
        print_tape(m);
    }
}

int main(int argc, char *argv[]) {
    Machine m;
    load_program(m);
    print_program(m);
    eval(m, 1000);
    print_tape(m);
    return 0;
}
