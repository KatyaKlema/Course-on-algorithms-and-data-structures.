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
 Реализуйте структуру данных, которая поддерживает множество S целых чисел, с котором разрешается производить следующие операции:

• add(i) - добавить в множество S число i (если оно там уже есть, то множество не меняется);
• sum(l, r) - вывести сумму всех элементов x из S, которые удовлетворяют неравенству l ≤ x ≤ r.
Формат входных данных
Исходно множество S пусто. Первая строка входного файла содержит n - количество операций (1 ≤ n ≤ 300000). Следующие n строк содержат операции. Каждая операция имеет вид либо "+ i", либо "? l r". Операция "? l r" задает запрос sum(l, r).

Если операция "+ i" идет во входном файле в начале или после другой операции "+", то она задает операцию add(i). Если же она идет после запроса "?", и результат этого запроса был y, то выполняется операция add((i + y) % 109). Во всех запросах и операциях добавления параметры лежат в интервале от 0 до 109.
Формат результата
Для каждого запроса выведите одно число - ответ на запрос.
 Входные данные:
6
+ 1
+ 3
+ 3
? 2 4
+ 1
? 2 4
 Результат работы:
3
7
 */
class Treap {
public:
    int x;
    int y;
    long long sum;

    Treap *left ;
    Treap *right;

    Treap(): x(0), y(0), left(NULL), right(NULL), sum(0)
    {}
    Treap(int key): x(key), y(rand()), left(NULL), right(NULL), sum(key)
    {}

};

long long getSum(Treap *root){
    return ((root == NULL) ? 0 : root->sum);
}

void update(Treap *root){
    root->sum = root->x + getSum(root->left) + getSum(root->right);
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

void split(Treap *root, int key, Treap *&L, Treap *&R){
    if(root == NULL){
        L = NULL;
        R = NULL;
        return;
    }
    else if (key >= root->x){
        split(root->right, key, root->right, R);
        L = root;
    }
    else{
        split(root->left, key, L, root->left);
        R = root;
    }
    update(root);
}

bool search(Treap *root, int val){
    if(root == NULL)
        return false;
    else if (root->x == val)
        return true;
    if(val < root->x)
        return search(root->left, val);
    else if (root->x < val)
        return search(root->right, val);
}

void insert(Treap *&root, long long val){
    if(!search(root, val)){
        Treap *newRoot = new Treap(val);
        Treap *L, *R;
        split(root, val, L, R);
        root = merge(merge(L, newRoot), R);
    }
}

long long int sum(Treap *root, int left, int right) {
    Treap* T1, * T2, * T3, * T4;
    split(root, right, T1, T2);
    split(T1, left - 1, T3, T4);
    long long int result = getSum(T4);
    merge(merge(T3, T4), T2);
    return result;
}

int main(){
    int n;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    char prevCmd = '-';
    long long prev;
    Treap *root = NULL;
    for(int i = 0; i < n; ++i){
        char cmd;
        cin >> cmd;
        if(cmd == '+' && (i == 0 || prevCmd == '+')){
            int add;
            cin >> add;
            insert(root, add);
        }
        else if (cmd == '+' && prevCmd == '?'){
            long long add;
            cin >> add;
            insert(root, (prev + add) % 1000000000);
        }
        else{
            int l, r;
            cin >> l >> r;
            prev = sum(root, l, r);
            cout << prev << endl;
        }
        prevCmd = cmd;
    }
}