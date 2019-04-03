#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <queue>
#include<map>
#include<set>
#include<algorithm>
#include<stack>
using namespace std;
/*
 У Сережи есть скобочная последовательность s1, s2, ..., sn, или, другими словами, строка s длины n, состоящая из символов ( и ).

Сереже нужно ответить на m запросов, каждый из которых характеризуется двумя целыми числами li, ri (1 ≤ li ≤ ri ≤ n). Ответом на i-ый запрос является длина наибольшей правильной скобочной подпоследовательности последовательности sli, sli + 1, ..., sri. Помогите Сереже ответить на все запросы.
Формат входных данных
Первая строка содержит последовательность символов без пробелов s1, s2, ..., sn (1 ≤ n ≤ 106). Каждый символ это либо (, либо ). Вторая строка содержит целое число m (1 ≤ m ≤ 105) количество запросов. Каждая из следующих m строк содержит пару целых чисел. В i-ой строке записаны числа li, ri (1 ≤ li ≤ ri ≤ n) - описание i-го запроса.
Формат результата
Выведите ответ на каждый запрос в отдельной строке. Ответы выводите в порядке следования запросов во входных данных.
 Входные данные:
())(())(())(
7
1 1
2 3
1 2
1 12
8 12
5 11
2 10
 Результат работы:
0
0
2
10
4
6
6
 */
struct Node {
    int amount_subsequences;
    int amount_opening_brackets;
    int amount_closing_brackets;
    Node() : amount_subsequences(0), amount_opening_brackets(0), amount_closing_brackets(0) {}
    Node(int a, int b, int c) : amount_subsequences(a), amount_opening_brackets(b), amount_closing_brackets(c) {}
};

class Segment_tree {
private:
    vector<Node> tree;
public:
    Segment_tree(string& sequences);
    int find_amount_subsequences(int left, int right);
};

Segment_tree::Segment_tree(string& sequences) {
    int new_size = 1;
    while (new_size < sequences.size()) {
        new_size *= 2;
    }
    sequences.resize(new_size, ' ');
    tree.resize(2 * sequences.size() - 1);
    for (int i = 0; i < sequences.size(); i++) {
        if (sequences[i] == '(') {
            tree[sequences.size() + i - 1] = Node(0, 1, 0);
        }
        else if (sequences[i] == ')') {
            tree[sequences.size() + i - 1] = Node(0, 0, 1);
        }
        else {
            tree[sequences.size() + i - 1] = Node(0, 0, 0);
        }
    }
    for (int i = sequences.size() - 2; i >= 0; i--) {
        int new_subsequences = min(tree[2 * i + 1].amount_opening_brackets, tree[2 * i + 2].amount_closing_brackets);
        tree[i].amount_subsequences = tree[2 * i + 1].amount_subsequences + tree[2 * i + 2].amount_subsequences
                                      + 2 * new_subsequences;
        tree[i].amount_opening_brackets = tree[2 * i + 1].amount_opening_brackets + tree[2 * i + 2].amount_opening_brackets
                                          - new_subsequences;
        tree[i].amount_closing_brackets = tree[2 * i + 1].amount_closing_brackets + tree[2 * i + 2].amount_closing_brackets
                                          - new_subsequences;
    }
}

int Segment_tree::find_amount_subsequences(int left, int right) {
    Node left_answer, right_answer;
    left += tree.size() / 2;
    right += tree.size() / 2;
    while (left <= right) {
        if (left % 2 == 0) {
            int new_subsequences = min(left_answer.amount_opening_brackets, tree[left].amount_closing_brackets);
            left_answer.amount_subsequences += tree[left].amount_subsequences + 2 * new_subsequences;
            left_answer.amount_opening_brackets += tree[left].amount_opening_brackets - new_subsequences;
            left_answer.amount_closing_brackets += tree[left].amount_closing_brackets - new_subsequences;
            left++;
        }
        if (right % 2 == 1) {
            int new_subsequences = min(tree[right].amount_opening_brackets, right_answer.amount_closing_brackets);
            right_answer.amount_subsequences += tree[right].amount_subsequences + 2 * new_subsequences;
            right_answer.amount_opening_brackets += tree[right].amount_opening_brackets - new_subsequences;
            right_answer.amount_closing_brackets += tree[right].amount_closing_brackets - new_subsequences;
            right--;
        }
        if (left > right) {
            break;
        }
        left = (left - 1) / 2;
        right = (right - 1) / 2;
    }
    return left_answer.amount_subsequences + right_answer.amount_subsequences
           + 2 * min(right_answer.amount_closing_brackets, left_answer.amount_opening_brackets);
}


int main() {
    string sequences;
    cin >> sequences;
    Segment_tree segment_tree(sequences);
    int m, left, right;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> left >> right;
        cout << segment_tree.find_amount_subsequences(left - 1, right - 1) << endl;
    }
    return 0;
}