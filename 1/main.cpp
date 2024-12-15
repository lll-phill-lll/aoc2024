#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main() {
    // Открытие файла
    std::ifstream file("input.txt");

    // Инициализация векторов
    std::vector<int> v1;
    std::unordered_map<int, int> v2;

    // Чтение данных из файла
    int num;
    while (file >> num) {
        if (file.peek() == ' ') {
            v1.push_back(num);
            file >> num;
            v2[num]++;
        }
    }

    // Закрытие файла
    file.close();

    std::sort(v1.begin(), v1.end());

    uint64_t total = 0;
    for (auto num : v1) {
        if (!v2.count(num)) continue;
        total += num * v2[num];
    }

    std::cout << total << std::endl;

    return 0;
}
