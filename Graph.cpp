#include"Graph.h"
#include <queue> 
#include <stack>
#include <list>
#include <set>
#define INF 10000000

using namespace std;

Graph::Graph(int V_) {
	this->V = V_; 
	this->g = new vector<pair<int, Bus_Line*> >[V_]; 
}

void Graph::addEdge(int u, int v, Bus_Line* B) {
	g[u].push_back(make_pair(v, B)); 
	g[v].push_back(make_pair(u, B)); 
}

void Graph::setupGraph(Network_Display* N) {
	for (int i = 0; i < N->lines.size(); i++) {
		for (int j = 0; j < N->lines[i]->stops.size() - 1; j++) {
			//addEdge(N->getCompressedFromNumber(N->lines[i]->stops[j]), N->getCompressedFromNumber(N->lines[i]->stops[j + 1]), N->lines[i]->)
			addEdge(N->getCompressedFromNumber(N->lines[i]->stops[j]), N->getCompressedFromNumber(N->lines[i]->stops[j + 1]), N->lines[i]);
			addEdge(N->getCompressedFromNumber(N->lines[i]->stops[j + 1]), N->getCompressedFromNumber(N->lines[i]->stops[j]), N->lines[i]);
		}
	}
}

void Graph::anyPath(int code1, int code2, Network_Display* N) {
	int source = N->getCompressedFromNumber(code1);
	int target = N->getCompressedFromNumber(code2);

	//char *c = new char[length];
	int* visit = new int[V]; 
	for (int i = 0; i < this->V; i++) visit[i] = 0;

	pair<int, Bus_Line*>* par = new pair<int, Bus_Line*>[V]; 
	//par = (pair<int, Bus_Line*>*)malloc(this->V * sizeof(pair<int, Bus_Line*>)); 
	for (int i = 0; i < this->V; i++) par[i] = make_pair(-1, new Bus_Line); 

	list<int> queue; 
	queue.push_back(source); 
	visit[source] = 1;

	while (!queue.empty()) {
		int now = queue.front(); 
		queue.pop_front(); 

		if (now == target) {
			printPath(par, source, target, N);
			return; 
		}

		for (pair<int, Bus_Line*> it : g[now]) {
			if (!visit[it.first]) {
				visit[it.first] = 1;
				par[it.first] = make_pair(now, it.second); 
				queue.push_back(it.first);
			}
		}
	}

}

void Graph::bestTimePath(int code1, int code2, string s, Network_Display* N) {
	int source = N->getCompressedFromNumber(code1);
	int target = N->getCompressedFromNumber(code2); 
	Clock_Time start;
	start.read(s); 
	/*start.addMinutes(3);
	cout << start.minute;*/
	int T = 0; 
	int* dist = new int[V]; 

	int* visit = new int[V];
	for (int i = 0; i < this->V; i++) visit[i] = 0;

	pair<int, Bus_Line*>* par = new pair<int, Bus_Line*>[V];
	for (int i = 0; i < this->V; i++) par[i] = make_pair(-1, new Bus_Line);

	for (int i = 0; i < this->V; i++) dist[i] = 10000000;

	dist[source] = 0; 
	set<pair<int, int> > ss;
	ss.insert(make_pair(dist[source], source)); 

	while (!ss.empty()) {
		int d = ss.begin()->first;
		int y = ss.begin()->second;
		ss.erase(ss.begin()); 

		if (visit[y]) continue;
		visit[y] = true;

		for (pair<int, Bus_Line*> it : g[y]) {
			int wait_time;
			int nxt = it.first;
			Bus_Line* b = it.second;

			int idx = 0;
			int idx2 = 0;
			//cout << b->stops_better[0]->number << " " << N->all_stops[nxt]->number << "AAA" << endl;
			for (int i = 0; i < b->stops_better.size(); i++) if (b->stops_better[i]->number == N->all_stops[nxt]->number) idx = i;
			for (int i = 0; i < b->stops_better.size(); i++) if (b->stops_better[i]->number == N->all_stops[y]->number) idx2 = i;
			if(idx2 < idx) wait_time = 3 * idx2;
			if (idx2 > idx) wait_time = 3 * (b->stops_better.size() - 1 - idx2);
			//cout << idx << " " << idx2 << endl;
			Clock_Time tmp;
			tmp.hour = start.hour;
			tmp.minute = start.minute;
			tmp.addMinutes(dist[y]);
			// u trenutku tmp je stigao do y
			// ceka wait_time2 do sledeceg polaska
			// wait_time2 = odgovarajuci polazak - tmp
			// odgpol + 3*(idx-1) < tmp <= odgpol + 3*idx

			int wait_time2=0;
			
			//if (N->all_stops[y]->number == 154 && N->all_stops[nxt]->number == 578) cout << wait_time;

			for (int i = 0; i < b->departures.size(); i++) {
				Clock_Time tmp2 = b->departures[i];
				tmp2.addMinutes(wait_time); 
				if (tmp <= tmp2) {
					wait_time2 = tmp2 - tmp; 
					break;
				}
			}

			if (dist[nxt] > dist[y] + wait_time2 + 3) {
				ss.erase(make_pair(dist[nxt], nxt));
				dist[nxt] = dist[y] + wait_time2 + 3; 
				ss.insert(make_pair(dist[nxt], nxt)); 
				par[nxt] = make_pair(y, it.second); 
			}
		}

	}
	cout << dist[target] << endl;
	printPath(par, source, target, N);
	return;
}

void Graph::mostComfortablePath(int code1, int code2, Network_Display* N) {
	int source = N->getCompressedFromNumber(code1);
	int target = N->getCompressedFromNumber(code2);

	//char *c = new char[length];
	int* visit = new int[V];
	for (int i = 0; i < this->V; i++) visit[i] = 0;

	pair<int, Bus_Line*>* par = new pair<int, Bus_Line*>[V];
	//par = (pair<int, Bus_Line*>*)malloc(this->V * sizeof(pair<int, Bus_Line*>)); 
	for (int i = 0; i < this->V; i++) par[i] = make_pair(-1, new Bus_Line);

	int* dist = new int[V];
	for (int i = 0; i < this->V; i++) dist[i] = 10000000;
	
	dist[source] = 0;
	//visit[source] = 1;

	for (int i = 0; i < N->all_stops[source]->reachable.size(); i++) cout << source << ":::" << N->all_stops[source]->reachable[i]->number << endl;

	set<pair<int, int> >ss;
	ss.insert({ dist[source], source });
	while (!ss.empty()) {
		int d = ss.begin()->first;
		int now = ss.begin()->second;
		ss.erase(ss.begin()); 

		if (visit[now]) continue;
		visit[now] = 1;

		for (pair<int, Bus_Line*> it : g[now]) {
			int add = 1; 
			for (int i = 0; i < N->all_stops[now]->reachable.size(); i++) if (N->all_stops[now]->reachable[i]->number == N->all_stops[it.first]->number) add = 0;
			if (dist[it.first] > dist[now] + add) {
				ss.erase({ dist[it.first], it.first }); 
				dist[it.first] = dist[now] + add; 
				ss.insert({ dist[it.first], it.first }); 
				par[it.first] = make_pair(now, it.second);
			}
		}

	}

	for (int i = 0; i < V; i++) cout << dist[i] << " ";
	printPath(par, source, target, N);
	return;
}

void Graph::printPath(pair<int, Bus_Line*>* par, int source, int target, Network_Display* N) {
	int x = target;
	string last = ""; 
	stack<pair<int, string> > S;
	while (x != -1) {
		//cout << N->all_stops[x]->number << endl;
		//cout << "linija: " << par[x].second->line_label << endl;
		string in = par[x].second->line_label;
		if (par[x].second->line_label == "") in = last;
		else last = par[x].second->line_label;

		S.push(make_pair( N->all_stops[x]->number, in )); 
		//cout << "A" << endl;
		x = par[x].first;
	}
	int carry = 0;
	//cout << "143twergwr" << endl;
	cout << "->" << last << endl;
	while (!S.empty()) {
		string go = last;
		while (!S.empty()) {
			pair<int, string> pp = S.top();
			S.pop(); 
			go = pp.second; 
			if (go != last) {
				carry = pp.first;
				break;
			}
			cout << pp.first << " "; 
		}
		cout << endl; 
		if(go!=last) cout << last << "->" << go << endl;
		if (carry != 0) {
			cout << carry << " ";
			carry = 0;
		}
		last = go;
	}
	cout << "END" << endl;
	return;
}