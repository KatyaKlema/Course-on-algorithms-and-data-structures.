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
/*Реализуйте сбалансированное двоичное дерево поиска.
Формат входных данных
Входной файл содержит описание операций с деревом, их количество не превышает 105. В каждой строке находится одна из следующих операций.

• insert x - добавить в дерево ключ x.
• delete x - удалить из дерева ключ x. Если его там нет, то ничего делать не надо.
• exists x - если ключ x есть в дереве, выведите "true", иначе, "false"
• next x - выведите минимальный элемент в дереве, строго больший x или "none", если такого нет.
• prev x - выведите максимальный элемент в дереве, строго меньший x или "none", если такого нет.
• kth x - выведите k-тый по величине элемент(нумерация с единицы). Если такого не существует, то выведите "none".

Все числа во входном файле не превышают 109.
Формат результата
Выведите последовательно результат выполнения всех операций exists, next, prev. Следуйте формату выходного файла из примера.
 Входные данные:
insert 2
insert 5
insert 3
exists 2
exists 4
next 4
prev 4
delete 5
next 4
prev 4
kth 1
kth 3
 Результат работы:
true
false
5
3
none
3
2
none
 */
class Treap {
public:
    int x;
    int y;
    size_t size ;

    Treap *left ;
    Treap *right;

    Treap(): x(0), y(0), left(NULL), right(NULL), size(0)
    {}
    Treap(int xx, int yy, Treap *left = NULL, Treap *right = NULL): x(xx), y(yy), left(left), right(right), size(1)
    {}
    Treap(int key): x(key), y(rand()), left(NULL), right(NULL), size(1)
    {}

};

size_t getSize(Treap *root){
    return ((root == NULL) ? 0 : root->size);
}

void resize(Treap *root){
    root->size = 1 + getSize(root->left) + getSize(root->right);
}

Treap* merge(Treap *Left, Treap *Right){
    if(Left == NULL)
        return Right;
    if(Right == NULL)
        return Left;
    if(Left->y >= Right->y){
        Left->right = merge(Left->right, Right);
        resize(Left);
        return Left;
    }
    else{
        Right->left = merge(Left, Right->left);
        resize(Right);
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
    resize(root);
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

void insert(Treap *&root, int val){
    if(!search(root, val)){
        Treap *newRoot = new Treap(val);
        Treap *L, *R;
        split(root, val, L, R);
        root = merge(merge(L, newRoot), R);
    }
}

void remove(Treap *&root, int val){
    if(search(root, val)){
        Treap *L, *R, *newLeft, *newRight;
        split(root, val, L, R);
        split(L, val - 1, newLeft, newRight);
        root = merge(newLeft, R);
    }
}

Treap* next(Treap *root, int val){
    Treap *current = root, *successor = NULL;
    while(current != NULL){
        if(current->x > val){
            successor = current;
            current = current->left;
        }
        else
            current = current->right;
    }
    return successor;
}

Treap* prev(Treap *root, int val){
    Treap *current = root, *successor = NULL;
    while(current != NULL){
        if(current->x < val){
            successor = current;
            current = current->right;
        }
        else
            current = current->left;
    }
    return successor;
}


void kth(Treap* root, int k) {
    if (k > getSize(root)) {
        cout << "none" << endl;
    }
    else {
        if (getSize(root->left) == k - 1) {
            cout << root->x << endl;
        }
        else if (getSize(root->left) < k - 1) {
            kth(root->right, k - getSize(root->left) - 1);
        }
        else {
            kth(root->left, k);
        }
    }
}


int main(){
    string command;
    int value;
    Treap *root = NULL;
    while (cin >> command >> value) {
        if (command == "insert") {
            insert(root, value);
        }
        else if (command == "exists") {
            if (search(root, value)) {
                cout << "true" << endl;
            }
            else {
                cout << "false" << endl;
            }
        }
        else if (command == "delete") {
            remove(root, value);
        }
        else if (command == "next") {
            Treap *temp = next(root, value);
            if(temp == NULL)
                cout << "none" << endl;
            else
                cout << temp->x << endl;
        }
        else if (command == "prev") {
            Treap *temp = prev(root, value);
            if(temp == NULL)
                cout << "none" << endl;
            else
                cout << temp->x << endl;
        }
        else if (command == "kth") {
            kth(root, value);
        }
    }
}