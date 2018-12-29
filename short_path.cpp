#include<bits/stdc++.h>
using namespace std;


struct sort_edges_key{
    inline bool operator() (const vector<int> a, const vector<int> b) {
			if (a[0] == b[0]) {
				return (a[1] < b[1]);
			} else {
				return (a[0] < b[0]);
			}
    }
};

struct Node {
		int id;
		int dis;
		vector<int> path;

		Node(int init_id) {
			id = init_id;
			dis = -1;
			path = {id};
		}

		Node(int init_id, int init_dis) {
			id = init_id;
			dis = init_dis;
			path = {id};
		}

		Node(int init_id, int init_dis, vector<int> init_path) {
			id = init_id;
			dis = init_dis;
			path = init_path;
			path.push_back(id);
		}
};

class Queue {
	public:
		vector<Node> data;
		Queue(Node init_node);
		Queue(vector<Node> init_data);
		void sort();
		//adds element to back
		void push(Node);
		//returns (and removes)element at front
		Node pop();
};

Queue::Queue(Node init_node) {
	data = {init_node};
	data[0].path = {data[0].id};
}

void Queue::sort() {
	struct data_sort_key{
			inline bool operator() (const Node a, const Node b) {
					return (a.dis < b.dis);
			}
	};

	std::sort(data.begin(), data.end(), data_sort_key());
}


void Queue::push(Node n){
	data.push_back(n);
}

Node Queue::pop() {
	if (data.empty() == false) {
		Node n = data[0];
		data.erase(data.begin());
		return n;
	} else {
		cout << "queue empty" << endl;
	}
}


vector<vector<int>> edges;
vector<vector<int>> adj_list;
vector<int> distances;
int target;


int main(int argc, char *argv[]) {
	int vertex_n, start;
	cin >> vertex_n;
	cin >> start >> target;

	{
		string line;
		int a,b;
		getline(cin, line); //TRASH FIRST LINE
		while(getline(cin, line)) {
			sscanf(line.data(), "%d %d\n", &a, &b);
			vector<int> edge = {a,b};
			edges.push_back(edge);
		}
	}

	for(int i = 0; i < vertex_n; ++i)
		adj_list.push_back({});

	for(auto e : edges)
		adj_list[e[0]].push_back(e[1]);
	
	for(int i = 0; i < vertex_n; ++i) {
		if (i == start)
			distances.push_back(0);
		else
			distances.push_back(-1);
	}

	if (start == target) {
		cout << start;
	} else {
		Queue q(Node(start, 0));

		bool found = false;
		while (!found) {
			Node n = q.pop();

			for(int connected : adj_list[n.id]) {
				if (connected == target) {
					for(auto v: n.path) 
						cout << v << " ";
					cout << target;
					found = true;
					break;
				} else {
					if (distances[connected] == -1) {
						distances[connected] = n.dis + 1;
						q.push(Node(connected, n.dis+1, n.path));
						q.sort();
					}
				}
			}
		}
	}
	return 0;
}
