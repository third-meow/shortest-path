#include<bits/stdc++.h>
#include<sys/time.h>
using namespace std;

struct Node {
	int val;
	int prev;
};

vector<vector<int>> adj_list;
int target, start;
vector<Node> all;

void foundOut(Node last) {
	vector<int> path;
	Node n = last;
	while(true) {
		path.push_back(n.val);
		if (n.prev == 0)
			break;
		n = all[n.prev];
	}
	reverse(path.begin(), path.end());
	path.push_back(target);
	cout << start;
	for(auto v : path)
		printf(" %d", v);
}

int main(int argc, char *argv[]) {
	int vertex_n;
	cin >> vertex_n;
	bool notseen[vertex_n];
	for(int i = 0; i < vertex_n; ++i)
		notseen[i] = true;

	cin >> start >> target;

	{
		vector<vector<int>> edges;
		{
			int a,b;
			while(scanf("%d %d", &a, &b) != EOF) {
				vector<int> edge = {a,b};
				edges.push_back(edge);
			}
		}

		{
			for(int i = 0; i < vertex_n; ++i)
				adj_list.push_back({});

			for(auto e : edges)
				adj_list[e[0]].push_back(e[1]);
		}
	}


	long loop_count = 0;
	if (start == target) {
		cout << start;
	} else {
		queue<Node> q;
		Node st;
		st.val = start;
		q.push(st);

		bool found = false;
		while (!found) {

			Node n = q.front();
			all.push_back(n);
			q.pop();


			for(int connected : adj_list[n.val]) {
				if (connected == target) {
					Node nw;
					nw.val = connected;
					nw.prev = all.size() - 1;
					q.push(nw);
					all[0].prev = 0;
					foundOut(all.back());
					found = true;
					break;
				} else if (notseen[connected]){
					notseen[connected] = false;
					Node nw;
					nw.val = connected;
					nw.prev = (all.size() - 1);
					q.push(nw);
				}
			}
		}
	}
	return 0;
}
