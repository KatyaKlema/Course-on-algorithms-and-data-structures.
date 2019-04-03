#include <iostream>
#include <vector>
using namespace std;
/*
 Реализуйте структуру данных для хранения элементов и увеличения нескольких подряд идущих элементов на одно и то же число.
Формат входных данных
В первой строке вводится одно натуральное число N(1 ≤ N ≤ 105) - количество чисел в массиве.

Во второй строке вводятся N чисел от 1 до 100000 - элементы массива.

В третьей строке вводится одно натуральное число M(1 ≤ M ≤ 500000) - количество запросов.

Каждая из следующих M строк представляет собой описание запроса. Сначала вводится одна буква, кодирующая вид запроса (g - получить текущее значение элемента по номеру, a - увеличить все элементы на отрезке). Следом за g вводится одно число - номер элемента. Следом за a вводится три числа - левый и правый концы отрезка и число add, на которое нужно увеличить все элементы данного отрезка массва(1 ≤ add ≤ 100000).
Формат результата
Выведите ответы на запросы вида g, разделяя их переводами строк.
 Входные данные:
5
2 4 3 5 2
5
g 2
g 5
a 1 3 10
g 2
g 4
 Результат работы:
4
2
14
5
 */
int min(int a, int b) {
    return ((a < b) ? a : b);
}

int max(int a, int b) {
    return ((a < b) ? b : a);
}

void add(vector<long long int>& segment_tree, int vertex, int left_pos, int right_pos, int left, int right, int value) {
    if (left <= right) {
        if (left_pos == left && right_pos == right) {
            segment_tree[vertex] += value;
        }
        else {
            int middle = (left_pos + right_pos) / 2;
            add(segment_tree, 2 * vertex + 1, left_pos, middle, left, min(middle, right), value);
            add(segment_tree, 2 * vertex + 2, middle + 1, right_pos, max(middle + 1, left), right, value);
        }
    }
}

long long int get(vector<long long int>& segment_tree, int vertex, int left_pos, int right_pos, int index, long long int sum) {
    if (vertex == index) {
        return sum + segment_tree[vertex];
    }
    else{
        sum += segment_tree[vertex];
        int middle = (left_pos + right_pos) / 2;
        if (index + 1 - (segment_tree.size() + 1) / 2 <= middle) {
            get(segment_tree, 2 * vertex + 1, left_pos, middle, index, sum);
        }
        else {
            get(segment_tree, 2 * vertex + 2, middle + 1, right_pos, index, sum);
        }
    }
}

int main() {
    int n;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    vector<int> array(n);
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        array[i] = value;
    }
    int k = 0;
    for (; (1 << k) < array.size(); k++);
    array.resize((1 << k), 0);
    vector<long long int> segment_tree(2 * array.size() - 1, 0);
    for (int i = 0; i < array.size(); i++) {
        segment_tree[array.size() + i - 1] = array[i];
    }
    int m;
    cin >> m;
    char command;
    int size = array.size();
    for (int i = 0; i < m; i++) {
        cin >> command;
        if (command == 'g') {
            int index;
            cin >> index;
            cout << get(segment_tree, 0, 0, size - 1, size + index - 2, 0) << endl;
        }
        else {
            int left, right, value;
            cin >> left >> right >> value;
            add(segment_tree, 0, 0, size - 1, left - 1, right - 1, value);
        }
    }
    return 0;
}