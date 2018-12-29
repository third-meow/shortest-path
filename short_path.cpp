#include<bits/stdc++.h>
using namespace std;

vector<double> construct_times;
vector<double> sort_times;
vector<double> pop_times;
vector<double> push_times;

struct Timer {
	vector<double>* vec;
	string name;
	chrono::time_point<chrono::high_resolution_clock> start;
	chrono::time_point<chrono::high_resolution_clock> end;
	chrono::duration<double> duration;


	Timer() {
		name = "unnamed";
		start = chrono::high_resolution_clock::now();
	}

	Timer(vector<double>* init_vec) {
		vec = init_vec;
		start = chrono::high_resolution_clock::now();
	}

	Timer(string init_name) {
		name = init_name;
		start = chrono::high_resolution_clock::now();
	}

	~Timer() {
		end = chrono::high_resolution_clock::now();
		duration = end - start;

		double ms = duration.count() * 1000.0f;
		if (name.size()) 
			cout << "timer: " << name << " took: " << ms << endl;
		else if (vec != nullptr)
			vec->push_back(ms);
	}
};

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
	Timer t(&construct_times);
	data = {init_node};
	data[0].path = {data[0].id};
}

void Queue::sort() {
	Timer t(&sort_times);
	struct data_sort_key{
			inline bool operator() (const Node a, const Node b) {
					return (a.dis > b.dis);
			}
	};

	std::sort(data.begin(), data.end(), data_sort_key());
}


void Queue::push(Node n){
	Timer t(&push_times);
	data.push_back(n);
}

Node Queue::pop() {
	Timer t(&pop_times);
	Node n = data.back();
	data.pop_back();
	return n;
}


vector<vector<int>> edges;
vector<vector<int>> adj_list;
vector<int> distances;
int target;

double avgVec(vector<double>* vec) {
	double total;
	double len = (double) vec->size();

	for(auto e : *vec)
		total += e;

	return total / len;
}


int main(int argc, char *argv[]) {
	int vertex_n, start;
	cin >> vertex_n;
	cin >> start >> target;

	{
		Timer t("read-input");
		string line;
		int a,b;
		getline(cin, line); //TRASH FIRST LINE
		while(getline(cin, line)) {
			sscanf(line.data(), "%d %d\n", &a, &b);
			vector<int> edge = {a,b};
			edges.push_back(edge);
		}
	}

	{
		Timer t("build adj list");
		for(int i = 0; i < vertex_n; ++i)
			adj_list.push_back({});

		for(auto e : edges)
			adj_list[e[0]].push_back(e[1]);
	}

	{
		Timer t("build distances list");
		for(int i = 0; i < vertex_n; ++i) {
			if (i == start)
				distances.push_back(0);
			else
				distances.push_back(-1);
		}
	}


	if (start == target) {
		cout << start;
	} else {
		Timer t("shortest path algo");
		Queue q(Node(start, 0));

		bool found = false;
		while (!found) {
			Node n = q.pop();

			for(int connected : adj_list[n.id]) {
				if (connected == target) {
					//for(auto v: n.path) 
						//cout << v << " ";
					//cout << target;
					cout << "found" << endl;
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
		cout << "avg construct time: " << avgVec(&construct_times) << endl;
		cout << "avg sort time: " << avgVec(&sort_times) << endl;
		cout << "avg pop time: " << avgVec(&pop_times) << endl;
		cout << "avg push time: " << avgVec(&push_times) << endl;
	}
	return 0;
}
