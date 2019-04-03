#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <set>
using namespace std;

vector<int> color;
vector<int> cycle;
int findCycle(int v, vector<vector<int> > &G){
    color[v] = 1;
    for(int i = 0; i < G[v].size(); ++i){
        int to = G[v][i];
        if(color[to] == 0){
            int res = findCycle(to, G);
            if(res == -2)
                return res;
            else if(res >= 0){
                cycle.push_back(v);
                return res == v ? -2 : res;
            }
        }
        else if (color[to] == 1){
            cycle.push_back(v);
            return to;
        }
    }
    color[v] = 2;
    return -1;
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int> > G(n);
    cycle.resize(0);
    for(int i = 0 ; i < m; ++i){
        int l, r;
        cin >> l >> r;
        l--; r--;
        G[l].push_back(r);
    }
    color.assign(n, 0);

    for(int i = 0; i < n; ++i){
        int res = findCycle(i, G);
        if(res == -2){
            cout << "YES" << endl;
            for(int j = cycle.size() - 1; j >= 0; --j){
                cout << cycle[j]  + 1<< " ";
            }
            return 0;
        }
    }
    cout << "NO";
}