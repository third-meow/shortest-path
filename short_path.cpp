#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> edges;

template <typename T>
bool contains(vector<T> vec, T element) {
	for(auto e : vec) {
		if (e == element) {
			//cout << "conts" << endl;
			return true;
		}
	}

	//cout << "doesnt cont" << endl;
	return false;
}

struct sort_edges_key{
    inline bool operator() (const vector<int> a, const vector<int> b) {
			if (a[0] == b[0]) {
				return (a[1] > b[1]);
			} else {
				return (a[0] > b[0]);
			}
    }
};

struct sort_options_key {
    inline bool operator() (const vector<int> a, const vector<int> b) {
					return (a.size() <  b.size());
    }
};

vector<int> best_path(int end, int start, vector<int> used) {
	cout << "<>"  << endl;
	if (start == end)
		return {start};

	//search for direct hits
	for(auto vec : edges) {
		if (vec[0] == start) {
			if (vec[1] == end) {
				//found it
				return {end, start};
			}
		}
	}

	//send search for recursive hits
	vector<vector<int>> options;
	used.push_back(start);
	for(auto vec : edges) {
		if (vec[0] == start) {
			if (!contains<int>(used, vec[1])) {
				options.push_back(best_path(end, vec[1], used));
			}
		}
	}
		
	sort(options.begin(), options.end(), sort_options_key());
	options[0].push_back(start);
	return options[0];
}

int main(int argc, char *argv[]) {
	int node_n, start, end;
	cin >> node_n;
	cin >> start >> end;

	string line;
	int a,b;
	getline(cin, line); //TRASH FIRST LINE
	while(getline(cin, line)) {
		sscanf(line.data(), "%d %d\n", &a, &b);

		vector<int> edge = {a,b};
		edges.push_back(edge);
	}

	sort(edges.begin(), edges.end(), sort_edges_key());

	for(auto e : edges)
		cout << e[0] << " " << e[1] << endl;

	if (start == end) {
		cout << start;
	} else {
		vector<int> path = {};
		path = best_path(end, start, path);

		cout << path.back();
		for(int i = (path.size() - 2); i >= 0; --i)
			cout << " " << path[i];
	}

	return 0;
}

