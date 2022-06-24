#include <bits/stdc++.h>
#include <string.h>

using namespace std;
//-------------------------------------macros-----------------------------------------------
#define ll long long int
#define FOR(index, lower, upper) for (ll index = lower; index < upper; index++)
//-------------------------------------------- fast-io----------------------------------------
void io() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

void solve(ll);

int main() {
    io();
    ll T = 1ll;
    cin >> T;
    FOR(i, 1, T + 1) {
        solve(i);
    }
}
/*
    Topic: Segment tree with lazy Propagation
    Everything is almost same as standard dynamic range sum problem except the
    propagate function.

    Logic of lazy propagation:
        Representations:
            tree[node] -> number of nodes which are colored 1 in its subtree
            lazy[x] ->
                x:
                    -1 -> do nothing
                    0 -> color subtree nodes with 0
                    1 -> color subtree nodes with 1
                    2 -> reverse the color of all subtree nodes
        Steps:
            if lazy[current_node]== 0:
                That means we have to color all the subtree nodes
                with color 0 , as a result we have to set tree[current_node]=0
            if lazy[current_node]== 1:
                That means we have to color all the subtree nodes
                with color 1 , as a result we have to set tree[current_node] = number_of_nodes_in_substree = (end-start+1)
            if lazy[current_node]==2:
                That means we have to invert the color of all the subtree nodes
                as a result we have to set tree[current_node] = number_of_nodes_in_substree - tree[current_node]

            Now we need to update the value of child lazy nodes:
                if lazy[current_node]==1 or lazy[current_node]==0:
                    In this case we can assign the child nodes the value of current node.
                    as in case of assigning previous values does not not matter
                if lazy[current_node]==2
                    if the child lazy nodes are also colord 0 or 1 then we have to invert
                    their values, we can do that by taking XOR with 1

                    if the lazy child nodes are also previously colored 2 then
                    we can update the value of child nodes to -1. As inverting 
                    even times does not change the value

                    if the lazy child nodes are previously colored -1 then
                    we can update the value of child nodes to 2.

            at last set the value of lazy[current_node] = -1
    NB:
        if(value == 1 ) value = 0;
        else if(value == 0)value = 1;

        value^=1 -> this line is same as above code.
*/
class SegmentTree {
    ll n;
    vector<ll> lazy;
    vector<ll> tree;
    ll query(ll node, ll start, ll end, ll left, ll right) {
        propagate(node, start, end);
        if (end < left || right < start)
            return 0;
        if (left <= start && right >= end)
            return tree[node];
        ll mid = start + (end - start) / 2;
        return query(2 * node, start, mid, left, right) + query(2 * node + 1, mid + 1, end, left, right);
    }
    void propagate(ll node, ll start, ll end) {
        if (lazy[node] == -1)
            return;
        if (lazy[node] == 0) {
            tree[node] = 0;
        } else if (lazy[node] == 1) {
            tree[node] = end - start + 1;
        } else {
            tree[node] = (end - start + 1) - tree[node];
        }
        if (start != end) {
            if (lazy[node] < 2) {
                lazy[2 * node] = lazy[node];
                lazy[2 * node + 1] = lazy[node];
            } else {
                if (lazy[2 * node] == -1) {
                    lazy[2 * node] = 2;
                } else if (lazy[2 * node] < 2) {
                    lazy[2 * node] ^= 1;
                } else {
                    lazy[2 * node] = -1;
                }
                if (lazy[2 * node + 1] == -1) {
                    lazy[2 * node + 1] = 2;
                } else if (lazy[2 * node + 1] < 2)
                    lazy[2 * node + 1] ^= 1;
                else
                    lazy[2 * node + 1] = -1;
            }
        }
        lazy[node] = -1;
    }
    void update(ll node, ll start, ll end, ll left, ll right, ll val) {
        propagate(node, start, end);
        if (end < left || right < start)
            return;
        if (start >= left && end <= right) {
            lazy[node] = val;
            propagate(node, start, end);
            return;
        }
        ll mid = start + (end - start) / 2;
        update(2 * node, start, mid, left, right, val);
        update(2 * node + 1, mid + 1, end, left, right, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    void build(ll node, ll start, ll end, string &data) {
        if (start == end) {
            tree[node] = (data[start] - '0');
            return;
        }
        ll mid = start + (end - start) / 2;
        build(2 * node, start, mid, data);
        build(2 * node + 1, mid + 1, end, data);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

public:
    SegmentTree(string &s) : n(s.size()) {
        lazy.resize(4 * n, -1);
        tree.resize(4 * n);
        build(1, 0, n - 1, s);
    }
    ll query(ll left, ll right) {
        return query(1, 0, n - 1, left, right);
    }
    void update(ll left, ll right, ll val) {
        update(1, 0, n - 1, left, right, val);
    }
};

void solve(ll TC) {
    cout << "Case " << TC << ":" << endl;
    ll m;
    cin >> m;
    string s = "";
    while (m--) {
        ll t;
        cin >> t;
        string ss;
        cin >> ss;
        FOR(i, 0, t)
        s += ss;
    }
    SegmentTree st(s);
    ll q;
    cin >> q;
    ll idx = 1;
    while (q--) {
        char t;
        cin >> t;
        ll l, r;
        cin >> l >> r;
        if (t == 'F') {
            st.update(l, r, 1);
        } else if (t == 'E') {
            st.update(l, r, 0);
        } else if (t == 'I') {
            st.update(l, r, 2);
        } else {
            cout << "Q" << idx++ << ": " << st.query(l, r) << endl;
        }
    }
}
