#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
 /*Вам даны пары чисел (a_i, b_i), Вам необходимо построить декартово дерево, такое что i-ая вершина имеет ключи (a_i, b_i), вершины с ключом a_i образуют бинарное дерево поиска, а вершины с ключом b_i образуют кучу.
Формат входных данных
В первой строке записано число N — количество пар. Далее следует N (1 ≤ N ≤ 50000) пар (a_i, b_i). Для всех пар |a_i|, |b_i| ≤ 30000 . a_i ≠ a_j и b_i ≠ b_j для всех i ≠ j .
Формат результата
Если декартово дерево с таким набором ключей построить возможно, выведите в первой строке YES, в противном случае выведите NO. В случае ответа YES, выведите N строк, каждая из которых должна описывать вершину. Описание вершины состоит из трёх чисел: номер предка, номер левого сына и номер правого сына. Если у вершины отсутствует предок или какой-либо из сыновей, то выводите на его месте число 0.

Если подходящих деревьев несколько, выведите любое.
 Входные данные:
7
5 4
2 2
3 9
0 5
1 3
6 6
4 11
 Результат работы:
YES
2 3 6
0 5 1
1 0 7
5 0 0
2 4 0
1 0 0
3 0 0
  */
class Treap {
public:
    int key;
    int priority;
    int index;
    Treap* left;
    Treap* right;
    Treap* parent;

    Treap(pair<int, pair<int, int>> values) : key(values.first), priority(values.second.first),
                                              index(values.second.second), left(NULL), right(NULL), parent(NULL) {}
};

int get_index(Treap* vertex) {
    return ((vertex == NULL) ? 0 : vertex->index);
}

struct answer {
    vector<int> parent, left, right;
    answer(int n) {
        parent.resize(n);
        left.resize(n);
        right.resize(n);
    }
};

void get_result(Treap* root, answer& result) {
    if (root != NULL) {
        result.parent[root->index - 1] = get_index(root->parent);
        result.left[root->index - 1] = get_index(root->left);
        result.right[root->index - 1] = get_index(root->right);
        get_result(root->left, result);
        get_result(root->right, result);
    }
}

bool compare(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
    return ((a.first < b.first) ? true : false);
}

int main() {
    Treap* root = NULL;
    int n;
    cin >> n;
    vector<pair<int, pair<int, int>>> array(n);
    int key, priority;
    for (int i = 0; i < n; i++) {
        cin >> key >> priority;
        array[i] = make_pair(key, make_pair(priority, i + 1));
    }
    sort(array.begin(), array.end(), compare);
    Treap* right_path = new Treap(array[0]);
    root = right_path;
    for (int i = 1; i < n; i++) {
        Treap* current = right_path->right;
        while (right_path != NULL && array[i].second.first < right_path->priority) {
            current = right_path;
            right_path = right_path->parent;
        }
        Treap* new_vertex = new Treap(array[i]);
        if (right_path == NULL) {
            new_vertex->left = current;
            current->parent = new_vertex;
            right_path = new_vertex;
            root = new_vertex;
        }
        else {
            if (current != NULL) {
                current->parent = new_vertex;
            }
            new_vertex->left = current;
            new_vertex->parent = right_path;
            right_path->right = new_vertex;
            right_path = new_vertex;
        }
    }
    answer result(n);
    cout << "YES" << endl;
    get_result(root, result);
    for (int i = 0; i < n; i++) {
        cout << result.parent[i] << ' ' << result.left[i] << ' ' << result.right[i] << endl;
    }
    return 0;
}