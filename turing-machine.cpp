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
#include <algorithm>
#include <unistd.h>

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
        string input;
        while (getline(cin, line)) {
            // skip empty lines
            if (line.length() == 0) {
                continue;
            }

            // lines begining with # are comments
            if (line.at(0) == '#') {
                continue;
            }

            size_t n = std::count(line.begin(), line.end(), ' ');
            // part of the machine table
            if (n == 3) {
                istringstream iss(line);
                string state, symbol, ops, fstate;
                iss >> state >> symbol >> ops >> fstate;

                if (curr.length() == 0) {
                    curr = state;
                }

                Configuration c = {state, symbol.at(0)};
                Action a = {ops, fstate};
                program[c] = a;
            // part of the input
            } else {
                input += line;
            }
        }

        for (int i = 0; i < input.length(); i++) {
            tape[i] = input.at(i);
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
        const int first = min(tp, tape.begin()->first);
        const int last  = max(tp, tape.rbegin()->first);
        for (int i = first; i <= last; i++) {
            cout << read_tape(i);
        }
        cout << endl;
    }

    void print_head() {
        cout << "head: ";
        const int first = min(tp, tape.begin()->first);
        const int last  = tp;
        for (int i = first; i <= last; i++) {
            if (i == tp) {
                cout << 'v';
                cout << " (" << curr << ")";
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }

    char read_tape(int p) {
        if (tape.count(p)) {
            return tape[p];
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
                    break;
                case ',':
                    break;
                default:
                    cout << "unknown op: " << op << endl;
                    exit(1);
            }
        }
        return tp;
    }

    void run(int max, int fps) {
        int cnt = 0;
        while (cnt < max) {
            Configuration c = {curr, read_tape(tp)};
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
            if (cnt > 1 && fps > 0) {
                clear_previous(fps);
            }
            print_action(a);
            print_head();
            print_tape();
        }
    }

    void clear_previous(int fps) {
        usleep(1000000 / fps);
        for (int i = 0; i < 3; i++) {
            cout << "\x1B[1A"; // Move the cursor up one line
            cout << "\x1B[2K"; // Erase the entire current line
        }
    }

    void print_config(Configuration c) {
        cout << "conf: " << c.state << " " << c.symbol << endl;
    }

    void print_action(Action a) {
        cout << "ops : " << a.ops << endl;
    }
};

int main(int argc, char *argv[]) {
    Machine m;
    m.load_program();
    m.print_program();
    cout << endl;
    if (argc == 1) {
        m.run(1000, 10);
    } else if (argc == 2) {
        m.run(atoi(argv[1]), 10);
    } else if (argc == 3) {
        m.run(atoi(argv[1]), atoi(argv[2]));
    }
    return 0;
}
