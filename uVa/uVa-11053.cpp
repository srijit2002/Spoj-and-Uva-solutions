/*
1)Find the length of the cycle using Floyd's cycle detection algorithm.
2)Now find the length of the cycle by running a pointer from starting point of the loop
3)Now the answer is total_numer_of_soldiers-length_of_loop.
*/
#include <iostream>
#include <bits/stdc++.h>
#define ll long long int
using namespace std;
int main() {
    ll n;
    while (cin >> n) {
        if (n == 0)
            break;
        solve(n);
    }
}
ll getPos(ll a, ll b, ll x, ll n) {
    ll v1 = ((a % n) * (((x % n) * (x % n) % n)) % n) % n;
    ll v2 = b % n;
    return ((v1 % n) + (v2 % n)) % n;
}
void solve(ll n) {
    ll a, b;
    cin >> a >> b;
    ll hare = 0, tortoise = 0;
    //speed_of_hare=2*speed_of_tortoise
    //running the loop till they meet
    do {
        tortoise = getPos(a, b, tortoise, n);
        hare = getPos(a, b, getPos(a, b, hare, n), n);
    } while (hare != tortoise);
    //setting the hare pointer to starting index(0) 
    //and again running the loop but this time
    //speed_of_hare=speed_of_tortoise
    hare = 0;
    while (hare != tortoise) {
        hare = getPos(a, b, hare, n);
        tortoise = getPos(a, b, tortoise, n);
    }
    //finding the length of cycle
    ll length_of_cycle = 0;
    do {
        tortoise = getPos(a, b, tortoise, n);
        length_of_cycle++;
    } while (hare != tortoise);
    cout << n - length_of_cycle << endl;
}