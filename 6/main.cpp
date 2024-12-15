#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <unordered_set>


class TSolution {
public:

    class TPosition {
    public:
        int curi;
        int curj;
        int diri;
        int dirj;

        bool operator==(const TPosition& other) const {
            return curi == other.curi && curj == other.curj && diri == other.diri && dirj == other.dirj;
        }
    };

    struct TPositionHash {
        std::size_t operator () (const TPosition &p) const {
            auto h1 = std::hash<int>{}(p.curi);
            auto h2 = std::hash<int>{}(p.curj);
            auto h3 = std::hash<int>{}(p.diri);
            auto h4 = std::hash<int>{}(p.dirj);

            // Mainly for demonstration purposes, i.e. works but is overly simple
            // In the real world, use sth. like boost.hash_combine
            return (h1 * 1000 +  h2) ^ (h3 * 1000 + h4);  
        }
    };

    enum class TDirection {
        Up,
        Right,
        Down,
        Left,
    };

    std::string DirToStr(TDirection dir) {
        switch(dir) {
        case TDirection::Up:
            return "UP";
        case TDirection::Right:
            return "RIGHT";
        case TDirection::Down:
            return "DOWN";
        case TDirection::Left:
            return "LEFT";
        }
    }

    std::pair<int, int> GetCurrentDirection() {
        switch (curdir) {
            case TDirection::Up:
                return std::make_pair(-1, 0);
            case TDirection::Right:
                return std::make_pair(0, 1);
            case TDirection::Down:
                return std::make_pair(1, 0);
            case TDirection::Left:
                return std::make_pair(0, -1);
        }
    };

    void ChangeDirection() {
        switch (curdir) {
        case TDirection::Up:
            curdir = TDirection::Right;
            return;
        case TDirection::Right:
            curdir = TDirection::Down;
            return;
        case TDirection::Down:
            curdir = TDirection::Left;
            return;
        case TDirection::Left:
            curdir = TDirection::Up;
            return;
        }
    }

     bool UpdateDirection() {
        auto dirbefore = curdir;
        while(true) {
            const auto[diri, dirj] = GetCurrentDirection();
            auto nexti = curi + diri;
            auto nextj = curj + dirj;

            if (!IsBlockedCell(nexti, nextj)) {
                if (dirbefore != curdir) {
                    std::cerr << DirToStr(dirbefore) << "->" << DirToStr(curdir) << std::endl;
                }
                return true;
            }
            ChangeDirection();

            if (curdir == dirbefore) return false;
        }
    };

    void ReadInput() {
        std::ifstream file("input.txt");
        std::string str;

        while (getline(file, str)) {
            MappedArea.push_back(str);
        }
    }

    void FindCurrentPosition() {
        for (int i = 0; i < MappedArea.size(); ++i) {
            for (int j = 0; j < MappedArea[0].size(); ++j) {
                if (MappedArea[i][j] == '^') {
                    curj = j;
                    curi = i;
                    std::cerr << curi << " " << curj << std::endl;
                    return;
                }
            }
        }
        assert(false);
    }

    bool IsOutOfMap(int i, int j) {
        return i < 0 || j < 0 || i >= MappedArea.size() || j >= MappedArea[0].size();
    }

    bool IsBlockedCell(int i, int j) {
        if (IsOutOfMap(i, j)) return false;
        if (i == obsi && j == obsj) return true;
        return MappedArea[i][j] == '#';
    }
    
    bool IsNextStepOutOfMap() {
        auto [diri, dirj] = GetCurrentDirection();
        return IsOutOfMap(curi + diri, curj + dirj);
    }

    void MakeStep() {
        auto [diri, dirj] = GetCurrentDirection();
        curi += diri;
        curj += dirj;
        std::cerr << curi << " " << curj << std::endl;
        ++steps;
    }

    bool SaveCurrentPosition() {
        auto [diri, dirj] = GetCurrentDirection();
        TPosition pos{curi, curj, diri, dirj};
        if (visited.count(pos)) return false;
        visited.insert(pos);
        return true;
    }

    bool Go() {
        FindCurrentPosition();

        if (obsi == curi && obsj == curj) return true;

        while (true) {
            if (!SaveCurrentPosition()) return false;
            UpdateDirection();
            if (IsNextStepOutOfMap()) return true;
            
            MakeStep();
        }
    }

    int solveFull() {
        int count = 0;

        for (int i = 0; i < MappedArea.size(); ++i) {
            for (int j = 0; j < MappedArea[0].size(); ++j) {
                std::cout << i << " " << j << " " << count << std::endl;
                curdir = TDirection::Up;
                visited.clear();
                obsi = i;
                obsj = j;
                std::cerr << "----------------------" << std::endl;
                count += !Go();
            }
        }
        return count;
    }

    int solve() {
        Go();
        auto InitVisited = visited;
        int count = 0;

        for (auto dir : InitVisited) {
            int i = dir.curi;
            int j = dir.curj;
            std::cout << i << " " << j << " " << count << std::endl;
            curdir = TDirection::Up;
            visited.clear();
            obsi = i;
            obsj = j;
            std::cerr << "----------------------" << std::endl;
            count += !Go();
        }
        return count;
    }

private:
    std::vector<std::string> MappedArea;
    int curi = -1;
    int curj = -1;

    int diri = -1;
    int dirj = 0;

    int obsi = 0;
    int obsj = 0;

    int steps = 0;

    TDirection curdir = TDirection::Up;

    std::unordered_set<TPosition, TPositionHash> visited;
};

int main() {

    TSolution s;
    s.ReadInput();
    std::cout << s.solveFull() << std::endl;

}
