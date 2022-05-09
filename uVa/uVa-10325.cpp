#include <bits/stdc++.h>
#include <iostream>
typedef long long int ll;
using namespace std;
ll __lcm(ll a, ll b) {
    return (a / __gcd(a, b)) * b;
}
int main() {
    /*
     Hint-1:
     Study the similarities between binary representation
     of numbers and union formula of set theory.
     Example:- n(A union B)=n(A)+n(B)-n(A intersection B)
                numbers from 1 to 3(1 to 2^number of variables in union formula-1)
                10   01    11

    Hint-2:
      if A and B are two numbers then the count of numbers
      between 1 to n which are divisible by atleast one of these
      is = n/A + n/B - n/lcm(A,B)      
    */
    ll n, m;
    while (cin >> n >> m) {
        vector<ll> vc(m);
        for (ll i = 0; i < m; i++) {
            cin >> vc[i];
        }
        ll start = 1, end = 1ll << m;
        ll ans = 0ll;
        for (ll i = start; i < end; i++) {
            ll bitcount = 0;
            ll divider = 1ll;
            for (ll j = 0; j < m; j++) {
                bool flag = ((1ll << j) & i); // checking if jth bit is 1 or not
                if (flag) {
                    bitcount++;
                    divider = __lcm(divider, vc[j]);
                }
            }
            ll nums = n / divider;
            if (bitcount % 2 == 0)
                ans -= nums;
            else
                ans += nums;
        }
        cout << n - ans << endl;
    }
}
