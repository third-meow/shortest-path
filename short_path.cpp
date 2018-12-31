#include<bits/stdc++.h>
#include<sys/time.h>
using namespace std;

vector<double> construct_times;
vector<double> sort_times; vector<double> pop_times;
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
    inline bool operator() (const vector<int32_t> a, const vector<int> b) {
			if (a[0] == b[0]) {
				return (a[1] < b[1]);
			} else {
				return (a[0] < b[0]);
			}
    }
};

struct Node {
		int32_t id;
		int32_t dis;
		Node* prev;

		Node() {
			id = dis = -1;
			prev = nullptr;
		}

		Node(int32_t init_id, int32_t init_dis) {
			id = init_id;
			dis = init_dis;
			prev = nullptr;
		}
};

class Queue {
	public:
		Node data[1000001];
		int32_t begin, end;

		//constructor
		Queue(Node init_node);
		//adds element to back
		void push(Node n);
		//returns (and removes) element at front
		Node* pop();
};

Queue::Queue(Node init_node) {
	data[0] = init_node;
	data[0].prev = &data[0];
	begin = 0;
	end = 1;
}

void Queue::push(Node n) {
	//Timer t(&push_times);
	n.prev = &data[begin-1];
	data[end] = n;
	++end;
}

Node* Queue::pop() {
	//Timer t(&pop_times);
	++begin;
	return &data[begin-1];
}


vector<vector<int32_t>> edges;
vector<vector<int32_t>> adj_list;
int32_t target, start;

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

	//cout << u64useconds << endl;
}

void foundOut(Node* n) {
	int dis = n->dis;
	int path[dis];
	for(int i = 0; i < dis; ++i) {
		path[i] = n->id;
		n = n->prev;
	}
	cout << start << " ";
	for(int i = (dis-1); i >= 0; --i)
		cout << path[i] << " ";
	cout << target;
}

int main(int argc, char *argv[]) {

	int32_t vertex_n;
	cin >> vertex_n;
	bool notseen[vertex_n];
	for(int32_t i = 0; i < vertex_n; ++i)
		notseen[i] = true;

	cin >> start >> target;

	{
		//Timer t("read-input");
		string line;
		int32_t a,b;
		getline(cin, line); //TRASH FIRST LINE
		while(getline(cin, line)) {
			sscanf(line.data(), "%d %d\n", &a, &b);
			vector<int32_t> edge = {a,b};
			edges.push_back(edge);
		}
	}

	{
		//Timer t("build adj list");
		for(int32_t i = 0; i < vertex_n; ++i)
			adj_list.push_back({});

		for(auto e : edges)
			adj_list[e[0]].push_back(e[1]);
	}


	long loop_count = 0;
	if (start == target) {
		cout << start << endl;
	} else {
		{
			//Timer t("shortest path algo");
			Queue q(Node(start, 0));

			bool found = false;
			while (!found) {
				//Timer t(&loop_times);

				Node* n = q.pop();


				for(int32_t connected : adj_list[n->id]) {
					if (connected == target) {
						foundOut(n);
						//cout << endl;
						//cout << sizeof(q.data) << endl;
						//cout << sizeof(adj_list) << endl;
						//cout << sizeof(notseen) << endl;
						//cout << (sizeof(q.data) + sizeof(adj_list) + sizeof(notseen)) << endl;
						found = true;
						break;
					} else if (notseen[connected]){
						notseen[connected] = false;
						q.push(Node(connected, n->dis+1));
					}
				}
				++loop_count;
			}
		}

		//cout << "avg loop time: " << avgVec(&loop_times) << endl;
		//cout << "loop count: " << loop_count << "  total: " << totalVec(&loop_times) << endl;

		//cout << "avg sort time: " << avgVec(&sort_times) << endl;
		//cout << "sorts: " << sort_times.size() << " total : " << totalVec(&sort_times) << endl;

		//cout << "avg pop time: " << avgVec(&pop_times) << endl;
		//cout << "pops: " << pop_times.size() << " total : " << totalVec(&pop_times)  << endl;

		//cout << "avg push time: " << avgVec(&push_times) << endl;
		//cout << "pushs: " << push_times.size() << " total : " << totalVec(&push_times) << endl;
	}

	return 0;
}
