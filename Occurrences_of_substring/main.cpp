#include <iostream>
#include <vector
using namespace std;

/*Найти все вхождения строки T в строку S.
Формат входных данных
Первые две строки входных данных содержат строки S и T, соответственно. Длины строк больше 0 и меньше 50000, строки содержат только латинские буквы.
Формат результата
Выведите номера символов, начиная с которых строка T входит в строку S, в порядке возрастания.
 Входные данные:
ababbababa
aba
 Результат работы:
0 5 7
 */
vector<int> prefFun(string &str) {
    vector<int> pref(str.size());
    pref[0] = 0;
    for (int i = 1; i < str.size(); ++i) {
        int tmp = pref[i - 1];
        while (tmp > 0 && str[tmp] != str[i]) {
            tmp = pref[tmp - 1];
        }
        pref[i] = str[i] == str[tmp] ? tmp + 1 : 0;
    }

    return pref;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    string str, substr;
    cin >> str >> substr;
    str = substr + '#' + str;
    vector<int> res = prefFun(str);
    for(int i = substr.size(); i < res.size(); i++) {
        if (res[i] == substr.size()) {
            cout << i - 2 * substr.size() << ' ';
        }
    }
    return 0;
}