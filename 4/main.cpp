#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Solve {
public:

    bool IsLegalCell(int i, int j) {
        return i >= 0 && j >= 0 && i < Data.size() && j < Data[0].size();
    }

    bool IsXmas(int i, int j, int diri, int dirj) {
        return IsLegalCell(i + diri * 3, j + dirj * 3) &&
            Data[i + diri * 0][j + diri * 0] == 'X' &&
            Data[i + diri * 1][j + dirj * 1] == 'M' &&
            Data[i + diri * 2][j + dirj * 2] == 'A' &&
            Data[i + diri * 3][j + dirj * 3] == 'S';
        
    }

    int Check(int i, int j) {
        int total = 0;
        for (int x = -1; x < 2; ++x) {
            for (int y = -1; y < 2; ++y) {
                if (x == 0 && y == 0) continue;
                total += IsXmas(i, j, x, y);
            }
        }
        return total;
    }

    int CountXmas() {
        int total = 0;
        for (int i = 0; i < Data.size(); ++i) {
            for (int j = 0; j < Data[0].size(); ++j) {
                total += Check(i, j);
            }
        }
        return total;
    }


    std::vector<std::string> Data;

    void PrintInput() {
        for (const auto& s : Data) {
            std::cerr << s << std::endl;
        }
    }


};


int main() {
    std::ifstream file("input.txt");
    std::string str;

    Solve solve;

    while (getline(file, str)) {
        solve.Data.push_back(str);
    }

    // solve.PrintInput();

    std::cout << solve.CountXmas() << std::endl;

}
