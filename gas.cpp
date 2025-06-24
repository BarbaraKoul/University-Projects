#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();
const int MAXN = 10005;
const int MAXC = 1005;

struct State {
    int refills;
    int city;
    int fuel_left;

    State(int r, int c, int f) : refills(r), city(c), fuel_left(f) {}

    bool operator>(const State& other) const {
        return refills > other.refills;
    }
};

int parent_city[MAXN][MAXC];
int parent_fuel[MAXN][MAXC];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    vector<vector<pair<int, int>>> graph(N);
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(make_pair(v, w));
        graph[v].push_back(make_pair(u, w));
    }

    int Q;
    cin >> Q;
    while (Q--) {
        int A, B, C;
        cin >> A >> B >> C;

        vector<vector<int>> visited(N, vector<int>(C + 1, INF));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j <= C; ++j)
                parent_city[i][j] = parent_fuel[i][j] = -1;

        priority_queue<State, vector<State>, greater<State>> pq;
        pq.push(State(1, A, C));
        visited[A][C] = 1;

        pair<int, int> destination = {-1, -1};

        while (!pq.empty()) {
            State current = pq.top(); pq.pop();
            int refills = current.refills;
            int u = current.city;
            int fuel = current.fuel_left;

            if (u == B) {
                destination = {u, fuel};
                break;
            }

            if (fuel < C && refills + 1 < visited[u][C]) {
                visited[u][C] = refills + 1;
                parent_city[u][C] = parent_city[u][fuel];
                parent_fuel[u][C] = parent_fuel[u][fuel];
                pq.push(State(refills + 1, u, C));
            }

            for (size_t i = 0; i < graph[u].size(); ++i) {
                int v = graph[u][i].first;
                int w = graph[u][i].second;
                if (w > C) continue;

                if (fuel >= w && refills < visited[v][fuel - w]) {
                    visited[v][fuel - w] = refills;
                    parent_city[v][fuel - w] = u;
                    parent_fuel[v][fuel - w] = fuel;
                    pq.push(State(refills, v, fuel - w));
                }
            }
        }

        if (destination.first == -1) {
            cout << "IMPOSSIBLE\n";
        } else {
            int min_refills = visited[destination.first][destination.second];
            vector<int> path;
            int curr = destination.first;
            int fuel = destination.second;

            while (curr != -1) {
                path.push_back(curr);
                int prev = parent_city[curr][fuel];
                int prev_f = parent_fuel[curr][fuel];
                curr = prev;
                fuel = prev_f;
            }
            reverse(path.begin(), path.end());

            cout << "POSSIBLE: " << min_refills << " fill(s),";
            for (size_t i = 0; i < path.size(); ++i)
                cout << " " << path[i];
            cout << "\n";
        }
    }

    return 0;
}
