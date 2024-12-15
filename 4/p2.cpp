#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Solve {
public:

    bool IsLegalCell(int i, int j) {
        return i >= 0 && j >= 0 && i < Data.size() && j < Data[0].size();
    }

    bool IsXmas(int i, int j) {
        bool tlbr = IsLegalCell(i-1, j-1) && IsLegalCell(i+1, j+1) &&
            (Data[i-1][j-1] == 'S' && Data[i+1][j+1] == 'M' || Data[i-1][j-1] == 'M' && Data[i+1][j+1] == 'S');
        bool bltr = IsLegalCell(i+1, j-1) && IsLegalCell(i-1, j+1) &&
            (Data[i+1][j-1] == 'S' && Data[i-1][j+1] == 'M' || Data[i+1][j-1] == 'M' && Data[i-1][j+1] == 'S');

        return tlbr && bltr;
    }


    int CountXmas() {
        int total = 0;
        for (int i = 0; i < Data.size(); ++i) {
            for (int j = 0; j < Data[0].size(); ++j) {
                if (Data[i][j] == 'A') total += IsXmas(i, j);
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
