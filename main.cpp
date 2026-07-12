#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Оптимизация ввода-вывода для олимпиадных задач
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> chains(n);
    for (int i = 0; i < n; ++i) {
        cin >> chains[i];
    }

    // Сортируем куски по возрастанию длины
    sort(chains.begin(), chains.end());

    int left = 0;       // Указатель на самый маленький кусок
    int right = n - 1;  // Указатель на самый большой кусок
    int time = 0;       // Общее время (количество операций)

    // Пока у нас есть хотя бы два отдельных куска, их нужно соединять
    while (left < right) {
        // Если в текущем маленьком куске есть звенья
        if (chains[left] > 0) {
            chains[left]--; // Расходуем одно звено
            right--;        // Соединяем два больших куска на правом конце (минус один кусок)
            time++;         // На это уходит 1 минута
        } else {
            // Если маленький кусок полностью разобрали, переходим к следующему
            left++;
        }
    }

    cout << time << "\n";

    return 0;
}