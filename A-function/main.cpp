#include <iostream>
#include <vector>
#include<algorithm>
/* Дана строка S, состоящая из N символов. Определим функцию A(i) от первых i символов этой сроки следующим образом:

A(i) = максимально возможному k, что равны следующие строки:

S[1]+S[2]+S[3]+…+S[k]

S[i]+S[i–1]+S[i–2]+…+S[i–k+1]

где S[i] – i-ый символ строки S, а знак + означает, что символы записываются в строчку непосредственно друг за другом.

Напишите программу, которая вычислит значения функции A для заданной строчки для всех возможных значений i от 1 до N.

Входные данные
В первой строке входного файла записано одно число N. 1≤N≤200000. Во второй строке записана строка длиной N символов, состоящая только из больших и/или маленьких латинских букв.

Выходные данные
В выходной файл выведите N чисел — значения функции A(1), A(2), … A(N).

 входные данные
5
aabaa
выходные данные
1 2 0 1 5
 */


using namespace std;

vector<int> Zfunc(string &str){
    vector<int> z(str.size());
    z[0] = str.size();
    int l = 0 , r = 0;
    for(int i = 1; i < str.size(); ++i){
        if(i > r)
            z[i] = 0;
        else
            z[i] = min(r - i + 1, z[i - l]);
        while(i + z[i] < str.size() && str[i + z[i]] == str[z[i]]){
            z[i]++;
        }
        if(i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}
int main() {
    string str, str_copy;
    int n;
    cin >> n;
    cin >> str;
    str_copy = str;
    reverse(str.begin(), str.end());
    string new_str = str_copy + '#' + str;
    vector<int> ans = Zfunc(new_str);
    for(int i = 2 * n; i > n; --i)
        cout << ans[i] << " ";
}
