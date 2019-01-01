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
    inline bool operator() (const vector<int> a, const vector<int> b) {
			if (a[0] == b[0]) {
				return (a[1] < b[1]);
			} else {
				return (a[0] < b[0]);
			}
    }
};

class Queue {
	public:
		int ids[1000001];
		int prevs[1000001];

		int begin, end;

		//constructor
		Queue(int);
		//adds element to back
		void push(int);
		//returns (and removes) element at front
		int pop();
};

Queue::Queue(int id) {
	begin = 0;
	end = 1;
	ids[begin] = id;
	prevs[begin] = begin;
}

void Queue::push(int id) {
	//Timer t(&push_times);
	prevs[end] = begin-1;
	ids[end] = id;
	++end;
}

int Queue::pop() {
	//Timer t(&pop_times);
	++begin;
	return ids[begin-1];
}


vector<vector<int>> edges;
vector<vector<int>> adj_list;
int target, start;

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

void foundOut(Queue* q, int addr) {
	if (addr != target)
		cout << "foundOut run wrong" << endl;

	int dis = 1;
	int n = addr;

	while(true) {
		n = q->prevs[n];
		++dis;

		if (n == q->prevs[n])
			break;
	}

	cout << dis << endl;

	int path[dis];
	n = addr;
	for(int i = 0; i < dis; ++i) {
		path[i] = q->ids[n];
		n = q->prevs[n];
	}


	for(int i = (dis-1); i > 0; --i)
		cout << path[i] << " ";
	cout << path[0];
}

int main(int argc, char *argv[]) {

	int vertex_n;
	cin >> vertex_n;
	bool notseen[vertex_n];
	for(int i = 0; i < vertex_n; ++i)
		notseen[i] = true;

	cin >> start >> target;

	{
		//Timer t("read-input");
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
		//Timer t("build adj list");
		for(int i = 0; i < vertex_n; ++i)
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
			Queue q(start);

			bool found = false;
			while (!found) {
				//Timer t(&loop_times);

				int n = q.pop();


				for(int connected : adj_list[n]) {
					if (connected == target) {
						q.push(connected);
						foundOut(&q, connected);
						//cout << endl;
						//cout << sizeof(q.data) << endl;
						//cout << sizeof(adj_list) << endl;
						//cout << sizeof(notseen) << endl;
						//cout << (sizeof(q.data) + sizeof(adj_list) + sizeof(notseen)) << endl;
						found = true;
						break;
					} else if (notseen[connected]){
						notseen[connected] = false;
						q.push(connected);
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
