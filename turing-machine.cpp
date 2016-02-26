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
    string curr;
    map< Configuration, Action > program;
    map< int, char > tape;

    void load_program() {
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

            if (curr.length() == 0) {
                curr = state;
            }

            Configuration c = {state, symbol.at(0)};
            Action a = {ops, fstate};
            program[c] = a;
        }
    }

    void print_program() {
        for (auto it = program.begin(); it != program.end(); it++) {
            cout << it->first.state << " ";
            cout << it->first.symbol << " ";
            cout << it->second.ops << " ";
            cout << it->second.state << endl;
        }
    }

    void print_tape() {
        cout << "tape: ";
        for (auto it = tape.begin(); it != tape.end(); it++) {
            cout << it->second;
        }
        cout << endl;
    }

    char read_tape() {
        if (tape.count(tp)) {
            return tape[tp];
        } else {
            return '~';
        }
    }

    int perform_ops(string ops) {
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

    void run(int max) {
        int cnt = 0;
        while (cnt < max) {
            Configuration c = {curr, read_tape()};
            if (program.count(c) == 0) {
                c = {curr, '*'};
            }
            if (program.count(c) == 0) {
                break;
            }
            Action a = program[c];
            tp = perform_ops(a.ops);
            curr = a.state;

            cnt++;
            print_config(c);
            print_tape();
        }
    }

    void print_config(Configuration c) {
        cout << "conf: " << c.state << " " << c.symbol << endl;
    }
};

int main(int argc, char *argv[]) {
    Machine m;
    m.load_program();
    m.print_program();
    m.run(1000);
    return 0;
}
