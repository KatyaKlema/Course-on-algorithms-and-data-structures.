#include <iostream>
#include <vector>
#include<algorithm>
#include<stack>
using namespace std;
/*
 Компания Shaverma открывает свой новый офис в Долгопрудном, и вы приглашены на собеседование. Ваша задача - решить поставленную задачу.

Вам нужно создать структуру данных, которая представляет из себя массив целых чисел. Изначально массив пуст. Вам нужно поддерживать две операции:

• запрос: "? i j" - возвращает минимальный элемент между i-ым и j-м, включительно;
• изменение: "+ i x" - добавить элемент x после i-го элемента списка. Если i = 0, то элемент добавляется в начало массива.

Конечно, эта структура должна быть достаточно хорошей.
Формат входных данных
Первая строка входного файла содержит единственное целое число n - число операций над массивом (1 ≤ n ≤ 200000). Следующие n строк описывают сами операции. Все операции добавления являются корректными. Все числа, хранящиеся в массиве, по модулю не превосходят 109.
Формат результата
Для каждой операции запроса в отдельной строке выведите её результат.
 Входные данные:
8
+ 0 5
+ 1 3
+ 1 4
? 1 2
+ 0 2
? 2 4
+ 4 1
? 3 5
 Результат работы:
4
3
1
 */
class Treap {
public:
    int x;
    int y;
    long long size;
    int Min;

    Treap *left ;
    Treap *right;

    Treap(): x(0), y(0), left(NULL), right(NULL), size(0), Min(0)
    {}
    Treap(int key): x(key), y(rand()), left(NULL), right(NULL), size(1),  Min(key)
    {}

};

long long getSize(Treap *root){
    return ((root == NULL) ? 0 : root->size);
}

int getMin(Treap *root){
    return ((root == NULL) ? 1000000001 : root->Min);
}

void update(Treap *root){
    root->size = 1 + getSize(root->left) + getSize(root->right);
    root->Min = min(root->x, min(getMin(root->left), getMin(root->right)));
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

void split(Treap *root, int index, Treap *&L, Treap *&R, int left = 0){
    if(root == NULL){
        L = NULL;
        R = NULL;
        return;
    }
    int newKey = left + getSize(root->left);
    if (newKey <= index){
        split(root->right, index, root->right, R, newKey + 1);
        L = root;
    }
    else{
        split(root->left, index, L, root->left, left);
        R = root;
    }
    update(root);
}

void insert(Treap *&root, long long val, int pos){
    Treap *newRoot = new Treap(val);
    Treap *L, *R;
    split(root, pos, L, R);
    root = merge(merge(L, newRoot), R);

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    char cmd;
    Treap *root = NULL;
    for(int i = 0; i < n; ++i){
        cin >> cmd;
        if(cmd == '+'){
            int pos, value;
            cin >> pos >> value;
            insert(root, value, pos - 1);
        }
        else{
            int l, r;
            cin >> l >> r;
            Treap *T1, *T2, *T3, *T4;
            split(root, r - 1, T1, T2);
            split(T1, l - 2, T3, T4);
            cout << T4->Min << endl;
            root = merge(merge(T3, T4), T2);
        }
    }
}