#include<bits/stdc++.h>
#include<sys/time.h>
using namespace std;

vector<double> construct_times;
vector<double> sort_times;
vector<double> pop_times;
vector<double> push_times;
vector<double> loop_times;

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
		//sort by node dis
		void sort();
		//adds element to back
		void push(Node);
		//returns (and removes) element at front
		Node pop();
};

Queue::Queue(Node init_node) {
	Timer t("queue construct");
	data = {init_node};
	data[0].path = {data[0].id};
	data.reserve(1000000);
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
int target;

double avgVec(vector<double>* vec) {
	double total;
	double len = (double) vec->size();

	for(auto e : *vec)
		total += e;

	return total / len;
}

double totalVec(vector<double>* vec) {
	double total;

	for(auto e : *vec)
		total += e;

	return total;
}

void timehere() {

	unsigned long long u64useconds;
	struct timeval tv;

	gettimeofday(&tv,NULL);
	u64useconds = (1000000*tv.tv_sec) + tv.tv_usec;

	cout << u64useconds << endl;
}


int main(int argc, char *argv[]) {

	int vertex_n, start;
	cin >> vertex_n;
	bool notseen[vertex_n];
	for(int i = 0; i < vertex_n; ++i)
		notseen[i] = true;

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


	long loop_count = 0;
	if (start == target) {
		//cout << "found";
		cout << start << endl;
	} else {
		{
			Timer t("shortest path algo");
			Queue q(Node(start, 0));

			bool found = false;
			while (!found) {
				Timer t(&loop_times);

				Node n = q.pop();


				for(int connected : adj_list[n.id]) {
					if (connected == target) {
						//for(auto v: n.path) 
							//cout << v << " ";
						//cout << target;
						cout << "found" << endl;
						found = true;
						break;
					} else if (notseen[connected]){
						notseen[connected] = false;
						q.push(Node(connected, n.dis+1, n.path));
					}
				}
				q.sort();
				++loop_count;
			}
		}

		cout << endl;
		cout << "avg loop time: " << avgVec(&loop_times) << endl;
		cout << "loop count: " << loop_count << "  total: " << totalVec(&loop_times) << endl;

		cout << "avg sort time: " << avgVec(&sort_times) << endl;
		cout << "sorts: " << sort_times.size() << " total : " << totalVec(&sort_times) << endl;

		cout << "avg pop time: " << avgVec(&pop_times) << endl;
		cout << "pops: " << pop_times.size() << " total : " << totalVec(&pop_times)  << endl;

		cout << "avg push time: " << avgVec(&push_times) << endl;
		cout << "pushs: " << push_times.size() << " total : " << totalVec(&push_times) << endl;

	}
	return 0;
}
