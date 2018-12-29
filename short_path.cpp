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

class Crawler {
	private:
		vector<int> _path;
		int _node;
	public:
		bool active;

		Crawler(int start_node) {
			active = true;
			_node = start_node;
			_path = {_node};
		}

		Crawler(int start_node, vector<int> start_path) {
			active = true;
			_node = start_node;
			_path = start_path;
			_path.push_back(_node);
		}

		bool step();
};

vector<Crawler> crawlers;
vector<vector<int>> edges;
vector<int> seen;
int target;

bool contains(int element) {
	for(auto e : seen)
		if (e == element)
			return true;
	return false;
}

bool Crawler::step() {
	vector<int> unseen_neighbours;
	for(auto e : edges) {
		if(e[0] == _node) {
			if(e[1] == target) {
				for(auto v : _path)
					cout << v << " ";
				cout << target;
				return true;
			}

			if(!contains(e[1]))
					unseen_neighbours.push_back(e[1]);
		}
	}

	if (unseen_neighbours.size()) {
		for(int i = 1; i < unseen_neighbours.size(); ++i) {
			crawlers.push_back(Crawler(unseen_neighbours[i], _path));
			seen.push_back(unseen_neighbours[i]);
		}
		_node = unseen_neighbours[0];
		_path.push_back(_node);
	} else {
		active = false;
	}

	return false;
}


int main(int argc, char *argv[]) {
	int node_n, start;
	cin >> node_n;
	cin >> start >> target;

	string line;
	int a,b;
	getline(cin, line); //TRASH FIRST LINE
	while(getline(cin, line)) {
		sscanf(line.data(), "%d %d\n", &a, &b);
		vector<int> edge = {a,b};
		edges.push_back(edge);
	}

	sort(edges.begin(), edges.end(), sort_edges_key());

	if (start == target) {
		cout << start;
	} else {
		crawlers.push_back(Crawler(start));

		bool found;
		while (true){
			for(int i = 0; i < crawlers.size(); ++i){
				if (crawlers[i].active) {
					found = crawlers[i].step();
					if (found) break;
				}else{
					crawlers.erase(crawlers.begin() + i);
				}
			}
			if(found) break;
		}
	}

	return 0;
}

