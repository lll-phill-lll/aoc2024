#include <iostream>
#include <fstream>
#include <streambuf>

class TSolve {
public:

    enum class TState {
        None,
        M,
        U,
        L,
        OpenBr,
        Digit,
        Comma,
        CloseBr,
        D,
        O,
        N,
        Tick,
        T,
    };

    bool isTransitionAllowed(TState to) {
        if (to == TState::None) return true;

        switch(State) {
            case TState::None:
                return to == TState::M || to == TState::D;
            case TState::M:
                return to == TState::U;
            case TState::U:
                return to == TState::L;
            case TState::L:
                return to == TState::OpenBr;
            case TState::D:
                return to == TState::O;
            case TState::O:
                return to == TState::N || to == TState::OpenBr;
            case TState::N:
                return to == TState::Tick;
            case TState::Tick:
                return to == TState::T;
            case TState::T:
                return to == TState::OpenBr;
            case TState::OpenBr:
                return to == TState::Digit || to == TState::CloseBr && (WasDo || WasDont);
            case TState::Digit:
                return to == TState::Digit && ConsequentDigits < 3 || to == TState::Comma && ConsequentDigits > 0 || to == TState::CloseBr && ConsequentDigits <= 3 && ConsequentDigits > 0;
            case TState::Comma:
                return to == TState::Digit;
            case TState::CloseBr:
                return to == TState::None;
              break;
            }
        return false;
    }

    std::string ToString(TState state) {
        switch (state) {
        case TState::None:
            return "None";
        case TState::M:
            return "M";
        case TState::U:
            return "U";
        case TState::L:
            return "L";
        case TState::OpenBr:
            return "OpenBr";
        case TState::Digit:
            return "Digit";
        case TState::Comma:
            return "Comma";
        case TState::CloseBr:
            return "CloseBr";
        case TState::D:
            return "D";
        case TState::O:
            return "O";
        case TState::N:
            return "N";
        case TState::Tick:
            return "Tick";
        case TState::T:
            return "T";
          break;
        }
    }

    void makeTransition(TState to, char c) {
        std::cerr << "Switch: " << c << ": " << ToString(State) << "->" << ToString(to) << std::endl;
        State = to;

        if (State == TState::None) {
            ConsequentDigits = 0;
            Num1 = 0;
            Num2 = 0;
            WasDo = false;
            WasMul = false;
            WasDont = false;
            return;
        }

        if (State == TState::Digit) {
            ConsequentDigits++;
            Num1 *= 10;
            Num1 += c - '0';
            return;
        }

        ConsequentDigits = 0;

        if (State == TState::Comma) {
            Num2 = Num1;
            Num1 = 0;
            return;
        }

        if (State == TState::T) {
            WasDont = true;
            WasDo = false;
            return;
        }
        if (State == TState::L) {
            WasMul = true;
            return;
        }
        if (State == TState::O) {
            WasDo = true;
            return;
        }

        if (State == TState::CloseBr) {
            if (WasDont) {
                Enabled = false;
                std::cerr << "Disabled" << std::endl;
            } else if (WasDo) {
                Enabled = true;
                std::cerr << "Enabled" << std::endl;
            } else if (WasMul) {
                if (Enabled) {
                    std::cerr << "Mul" << std::endl;
                    Total += Num1 * Num2;
                } else {
                    std::cerr << "No mul" << std::endl;
                }
            }
            makeTransition(TState::None, c);
        }
    }

    TState getNextState(char c) {
        switch (c) {
            case 'm':
                return TState::M;
            case 'u':
                return TState::U;
            case 'l':
                return TState::L;
            case 'd':
                return TState::D;
            case 'o':
                return TState::O;
            case 'n':
                return TState::N;
            case '\'':
                return TState::Tick;
            case 't':
                return TState::T;
            case '(':
                return TState::OpenBr;
            case ',':
                return TState::Comma;
            case ')':
                return TState::CloseBr;
            default:
                if (std::isdigit(c)) return TState::Digit;
                return TState::None;
        }
    }

    void parse(const std::string& s) {
        for (auto c : s) {
            TState next = getNextState(c);
            if (isTransitionAllowed(next)) {
                makeTransition(next, c);
            } else {
                makeTransition(TState::None, c);
            }
            
        }
    }

    TState State = TState::None;
    int ConsequentDigits = 0;
    int Num1 = 0;
    int Num2 = 0;

    int Total = 0;

    bool Enabled = true;

    bool WasMul = false;
    bool WasDo = false;
    bool WasDont = false;
};

int main() {

    std::ifstream t("input.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());

    TSolve solve;
    solve.parse(str);

    std::cout << solve.Total << std::endl;

}
