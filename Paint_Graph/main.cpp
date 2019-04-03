#include <iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
/*
 Даны N точек, занумерованных числами 1, 2, ..., N. От каждой точки с меньшим номером к каждой точке с большим номером ведет стрелка красного или синего цвета. Раскраска стрелок называется однотонной, если нет двух таких точек A и B, что от A до B можно добраться как только по красным стрелкам, так и только по синим.

Ваша задача — по заданной раскраске определить, является ли она однотонной.
Input format
В первой строке входных данных содержится единственное число N (3 ≤ N ≤ 5000).

В следующих N–1 строках идет описание раскраски. В (i+1)-й строке записано (N–i) символов R (красный) или B (синий), соответствующих цвету стрелок, выходящих из точки i и входящих в точки (i+1), (i+2), ..., N соответственно.
Output format
Выведите «YES», если приведенная раскраска является однотонной, и «NO» в противном случае.

 Входные данные:
3
RB
R
 Выходные данные:
NO

 Входные данные:
3
RR
R
 Выходные данные:
YES
 */

vector<bool> used;
vector<string> color;
vector<int> parent;
bool DFS(int v, vector<vector<int>>& graph) {
	used[v] = true;
	color[v] = "GRAY";
	for (int i = 0; i < graph[v].size(); ++i) {
		int to = graph[v][i];
		if (color[to] == "WHITE") {
			parent[to] = v;
			if (DFS(to, graph))
				return true;
		}
		else if (color[to] == "GRAY") {
			return true;
		}
	}
	color[v] = "BLACK";
	return false;
}

bool isContainsCicle(vector<vector<int> > &G){
	int n = G.size();
	for(int i = 0; i < n; ++i){
		if(!used[i]){
			if(DFS(i, G))
				return true;
		}
	}
	return false;
}

int main(){
	int n = 0;
	cin>>n;
	vector<vector<int> > G(n);
	for(int i = 0; i < n - 1; ++i){
		for(int j = 0; j < n - i - 1; ++j){
			char ch;
			cin>>ch;
			if(ch == 'R'){
				G[i + j + 1].push_back(i);
			}
			else{
				G[i].push_back(i + j + 1);
			}
		}
	}
	color.assign(n, "WHITE");
	parent.assign(n, -1);
	used.assign(n, false);

	if(isContainsCicle(G)) {
		cout << "NO";
		return 0;
	}
	else{
		cout<<"YES";
		return 0;
	}

}