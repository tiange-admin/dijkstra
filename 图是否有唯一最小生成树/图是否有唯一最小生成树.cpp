#include <iostream>
#include <vector>
using namespace::std;
const int MAXN =500;
const int INF = 1 <<30;

struct edge {
	int V1;
	int V2;
	int val;
};

struct Graph {
	int  graph[MAXN][MAXN];
	vector<edge>s;
	int time;

	Graph() {
		int i;
		int j;
		for (i = 0; i < MAXN; i++)
			for (j = 0; j < MAXN; j++)
			{
		         graph[i][j] = INF;
				if (i == j)  graph[i][j] = 0;
			}
		time = 1;
	}
	int Prim(int n);
};

int Graph::Prim(int n) {
	int i, j;
	vector< int> lowcost(n);
	vector<int> nearvex(n);
	lowcost[0] = 0;
	nearvex[0] = -1;
	for (i = 1; i < n; i++) {
		lowcost[i] = graph[0][i];
		nearvex[i] = 0;
	} //从零开始

	for (i = 1; i < n; i++)//n-1次
	{
		int Min = INF;
		int v = 0;
		for (j = 0; j < n; j++)
			if (nearvex[j] != -1 && lowcost[j] < Min)
			{
				v = j;
				Min = lowcost[j];
			}

		if (v) {
			if (time)  s.push_back(edge{ v,nearvex[v],lowcost[v] });
			nearvex[v] = -1;
			for (j = 1; j < n; j++)
				if (nearvex[j] != -1 && graph[v][j] < lowcost[j])
				{
					lowcost[j] = graph[v][j];
					nearvex[j] = v;
				}
		}
	}
        int sum = 0;
		for (i= 0; i < n; i++) {
			sum += lowcost[i];
		}
		return sum;
}

int main() {
	int v, edgenum;
	int flg = 1;
	cin >> v >> edgenum;
	int i = 0;
	int v1, v2, val;
	Graph G;
	while (i < edgenum) {
		cin >> v1 >> v2 >> val;
		G.graph[v1 - 1][v2 - 1] = val;
		G.graph[v2- 1][v1 - 1] = val;
		i++;
	}
	int s2 = G.Prim(v);
	G.time = 0;

	int s3;
	for (int j = 0; j <v-1; j++) {
		G.graph[G.s[j].V1][G.s[j].V2] = INF;
		G.graph[G.s[j].V2][G.s[j].V1] = INF;
		if (G.Prim(v) == s2) { flg = 0; break; }
		G.graph[G.s[j].V1][G.s[j].V2] = G.s[j].val;
		G.graph[G.s[j].V2][G.s[j].V1] = G.s[j].val;
	}

	if (flg)  cout << s2;
	else cout << "Not Unique!";
	return 0;
}