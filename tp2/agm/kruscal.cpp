
#include <bits/stdc++.h>

using namespace std;


class DisjointSet {

    vector<int> rank, parent;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for(int i = 0; i < n + 1; i++){
            parent[i] = i;
        }
    }

    //Find implementado con path compression
    int findSet(int node){

        // En caso que nodo sea el representante
        if (node == parent[node]) return node;

        // Hago path compression
        //En c++ return de una asignacion devuelve una referencia a lo que esta a la izquiereda del =
        //Es decir esto retorna una referencia al padre del nodo actual
        return parent[node] = findSet(parent[node]);
    }

    void unionByRank(int u, int v) {
        int uRepresentative = findSet(u);
        int vRepresentative = findSet(v);

        // Si tienen el mismo representante, entonces pertenece al
        // mismo conjunto
        if (uRepresentative == vRepresentative) return;

        // Actualizamos el representante segun el caso del rank
        if (rank[uRepresentative] < rank[vRepresentative]) {
            parent[vRepresentative] = uRepresentative;
        } else if(rank[uRepresentative] > rank[vRepresentative]) {
            parent[uRepresentative] = vRepresentative;
        } else {
            parent[vRepresentative] = uRepresentative;
            rank[uRepresentative]++;
        }
    }
};

bool comp(tuple<int, int, int> a, tuple<int, int, int> b){

    if (std::get<2>(a) <= std::get<2>(b))
    {
        return true;
    }else{
        return false;
    }
}

void kruskal(vector<tuple<int, int, int>> &E, int n){

    long long res = 0;

    sort(E.begin(), E.end(), comp);

    DisjointSet dsu = DisjointSet(n);

    int aristas = 0;

    for(auto [u, v, w] : E){
        //u y v estan en distinta cc?
        if(dsu.findSet(u) != dsu.findSet(v)){
            dsu.unionByRank(u,v);
            res += w;
            aristas++;
        }
        if(aristas == (n - 1)) break;
    }
    
    if(aristas == (n - 1)) cout << res << '\n';
    else cout << "IMPOSSIBLE\n";
}

int main() {

    //Codigo para hacer la entrada y salida de datos mas eficiente
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, u, v, w;

    cin >> n >> m;

    vector<tuple<int, int, int> > lAristas(m);
    tuple<int, int, int> aux;

    for (int i = 0; i < m; i++)
    {
        cin >> u >>  v >> w;
        aux = make_tuple(u, v, w);
        lAristas[i] = aux;
    }

    kruskal(lAristas, n);
    


}