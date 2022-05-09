#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
//-------------------------------------macros-----------------------------------------------
#define color(array, value) memset(array, value, sizeof(array))
#define ld long double
#define ll long long int
#define mp(x, y) make_pair(x, y)
#define M_PI 3.14159265358979323846
#define yes cout << "YES" \
                 << "\n"
#define no cout << "NO" \
                << "\n"
#define fl endl
#define endl "\n"
#define FOR(index, lower, upper) for (ll index = lower; index < upper; index++)
#define FORD(index, upper, lower) for (ll index = upper; index > lower; index--)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define containsKey(map, key) (map.find(key) != map.end())
#define umap unordered_map
#define uset unordered_set
const ll MOD = 1e9 + 7;
//------------------------------------macros---------------------------------------------
using namespace std;

ll direction_sides[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
ll directions_corner[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
vector<bool> prime;
ll ceil_div(ll a, ll b) {
    return a / b + ((a ^ b) > 0 && a % b != 0);
}
bool sort_points(pair<ld, ld> &p1, pair<ld, ld> &p2) {
    if (p1.first != p2.first) {
        return p1.first < p2.first;
    }
    return p1.second < p2.second;
}
bool comp_second(pair<ll, ll> &a, pair<ll, ll> &b) {
    return a.second < b.second;
}
bool comp_first(pair<ll, ll> &a, pair<ll, ll> &b) {
    if (a.first != b.first)
        return a.first < b.first;
    return a.second > b.second;
}
bool comp_first_reverse(pair<ll, ll> &a, pair<ll, ll> &b) {
    if (a.first != b.first)
        return a.first > b.first;
    return a.second > b.second;
}

ll __lcm(ll a, ll b) {
    return (a / __gcd(a, b)) * b;
}
void SieveOfEratosthenes(ll n) {
    prime = vector<bool>(n + 1, true);
    prime[0] = false;
    prime[1] = false;
    for (ll p = 2; p * p <= n; p++) {

        if (prime[p] == true) {

            for (ll i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
}
//-------------------------------------------- fast-io----------------------------------------
void io() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

//-----------------------------------------Operator overloads----------------------------------
template <typename T1, typename T2> // cin >> pair<T1, T2>
istream &operator>>(istream &istream, pair<T1, T2> &p) { return (istream >> p.first >> p.second); }
template <typename T> // cin >> vector<T>
istream &operator>>(istream &istream, vector<T> &v) {
    for (auto &it : v)
        cin >> it;
    return istream;
}
template <typename T1, typename T2> // cout << pair<T1, T2>
ostream &operator<<(ostream &ostream, const pair<T1, T2> &p) { return (ostream << p.first << " " << p.second); }
template <typename T> // cout << vector<T>
ostream &operator<<(ostream &ostream, const vector<T> &c) {
    for (auto &it : c)
        cout << it << " ";
    return ostream;
}
template <typename T> // cout << unordered_set<T>
ostream &operator<<(ostream &ostream, const unordered_set<T> &c) {
    for (auto &it : c)
        cout << it << " ";
    return ostream;
}
template <typename T> // cout << ordered_set<T>
ostream &operator<<(ostream &ostream, const set<T> &c) {
    for (auto &it : c)
        cout << it << " ";
    return ostream;
}
//-----------------------------------------Operator overloads----------------------------------
void solve(ll, ll);
int main() {
    io();
#ifndef ONLINE_JUDGE
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
#endif

    ll T = 1ll;
    // cin >> T;
    // FOR(i, 1, T + 1) {
    while (true) {
        ll m, n;
        cin >> m >> n;
        if (n == 0 && m == 0)
            break;
        solve(n, m);
    }
    // }
}
class Edge {
public:
    ll nbr;
    ll wgt;
};

const ll M = 21;
ll pathlength[M][M];
ll indexofnode[M][M];
vector<string> grid;
ll totalnumberofdirtytiles = 0ll;
ll travellingsalesman(ll src, ll visited) {
    if (visited == 0)
        return 0;
    ll ans = INT_MAX;
    FOR(i, 0, totalnumberofdirtytiles) {
        if ((1ll << i) & visited) {
            ll newvisited = visited;
            newvisited &= (~(1ll << i));
            ll cost = pathlength[src][i] + travellingsalesman(i, newvisited);
            ans = min(ans, cost);
        }
    }
    return ans;
}
bool bfs(ll rr, ll rc, ll n, ll m) {
    bool visited[n][m];
    color(visited, false);
    ll distance = 0;
    queue<pair<ll, ll>> queue;
    queue.push(mp(rr, rc));
    ll totalreaced = 1;
    while (!queue.empty()) {
        ll size = queue.size();
        while (size--) {
            auto node = queue.front();
            queue.pop();
            ll r = node.first, c = node.second;
            if (visited[r][c])
                continue;
            visited[r][c] = true;
            if (grid[r][c] == '*') {
                pathlength[indexofnode[rr][rc]][indexofnode[r][c]] = distance;
                totalreaced++;
            }
            for (auto &pos : direction_sides) {
                ll nr = r + pos[0], nc = c + pos[1];
                if (nr < 0 || nc < 0 || nr >= n || nc >= m || grid[nr][nc] == 'x' || visited[nr][nc])
                    continue;
                queue.push(mp(nr, nc));
            }
        }
        distance++;
    }
    return totalreaced == totalnumberofdirtytiles;
}
void solve(ll n, ll m) {
    totalnumberofdirtytiles = 0ll;
    grid.resize(n);
    cin >> grid;
    ll startingposx = -1, startingposy = -1;
    vector<pair<ll, ll>> dirtytiles;
    FOR(i, 0, n) {
        FOR(j, 0, m) {
            if (grid[i][j] == 'o' || grid[i][j] == '*') {
                if (grid[i][j] == 'o')
                    startingposx = i, startingposy = j;
                indexofnode[i][j] = totalnumberofdirtytiles;
                dirtytiles.emplace_back(mp(i, j));
                totalnumberofdirtytiles++;
            }
        }
    }
    if (startingposx == -1) {
        cout << -1 << endl;
        return;
    }
    FOR(i, 0, totalnumberofdirtytiles) {
        if (!bfs(dirtytiles[i].first, dirtytiles[i].second, n, m)) {
            cout << -1 << endl;
            return;
        }
    }
    ll mask = (1ll << totalnumberofdirtytiles) - 1;
    ll idx = indexofnode[startingposx][startingposy];
    mask &= (~(1ll << idx));
    cout << travellingsalesman(idx, mask) << endl;
}