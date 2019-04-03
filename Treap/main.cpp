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
/*Капрал Питуца любит командовать своим отрядом. Его любимый приказ "в начало строя". Он выстраивает свой отряд в шеренгу и оглашает последовательность приказов. Каждая приказ имеет вид "Солдаты с li по ri - в начало строя!"

Пронумеруем солдат в начальном положении с 1 до n, слева направо. Приказ "Солдаты с li по ri - в начало строя!" означает, что солдаты, стоящие с li по ri включительно перемещаются в начало строя, сохраняя относительный порядок.

Например, если в некотрый момент солдаты стоят в порядке {2, 3, 6, 1, 5, 4}, после приказа: "Солдаты с 2 по 4 - в начало строя!" порядок будет {3, 6, 1, 2, 5, 4}.

По данной последовательности приказов найти конечный порядок солдат в строю.
Формат входных данных
В первой строке два целых числа n and m (2 ≤ n ≤ 100000, 1 ≤ m ≤ 100000) - количество солдат и количество приказов. Следующие m строк содержат по два целых числа li и ri (1 ≤ li ≤ ri ≤ n).
Формат результата
Выведите n целых чисел - порядок солдат в конечном положении после выполнения всех приказов.
 Входные данные:
6 3
2 4
3 5
2 2
 Результат работы:
1 4 5 2 3 6
 */
class Treap {
public:
    int x;
    int y;
    long long size;

    Treap *left ;
    Treap *right;

    Treap(): x(0), y(0), left(NULL), right(NULL), size(0)
    {}
    Treap(int key): x(key), y(rand()), left(NULL), right(NULL), size(1)
    {}

};

long long getSize(Treap *root){
    return ((root == NULL) ? 0 : root->size);
}

void update(Treap *root){
    root->size = 1 + getSize(root->left) + getSize(root->right);
}

Treap* merge(Treap *Left, Treap *Right){
    if(Left == NULL)
        return Right;
    if(Right == NULL)
        return Left;
    if(Left->y >= Right->y){
        Left->right = merge(Left->right, Right);
        update(Left);
        return Left;
    }
    else{
        Right->left = merge(Left, Right->left);
        update(Right);
        return Right;
    }
}

void split(Treap *root, int key, Treap *&L, Treap *&R, int left = 0){
    if(root == NULL){
        L = NULL;
        R = NULL;
        return;
    }
    int newKey = left + getSize(root->left);
    if (newKey <= key){
        L = root;
        split(root->right, key, root->right, R, newKey + 1);
    }
    else{
        R = root;
        split(root->left, key, L, root->left, left);
    }
    update(root);
}



void insert(Treap *&root, long long val){
    Treap *newRoot = new Treap(val);
    Treap *L, *R;
    split(root, -1, L, R);
    root = merge(merge(L, newRoot), R);

}

void print(Treap* root) {
    if (root != NULL) {
        print(root->left);
        cout << root->x << ' ';
        print(root->right);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    Treap *root = NULL;
    for (int i = n - 1; i >= 0; i--) {
        insert(root, i + 1);
    }
    int left, right;
    for (int i = 0; i < m; i++) {
        cin >> left >> right;
        Treap* first, *second, *third, *fourth;
        split(root, right - 1, first, second);
        split(first, left - 2, third, fourth);
        root = merge(merge(fourth, third), second);
    }
    print(root);
}