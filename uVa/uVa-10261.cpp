#include <bits/stdc++.h>
#include <iostream>

//-------------------------------------macros-----------------------------------------------
#define ll long long int
#define color(array, value) memset(array, value, sizeof(array))
#define FOR(index, lower, upper) for (ll index = lower; index < upper; index++)
//------------------------------------macros---------------------------------------------
using namespace std;

//-------------------------------------------- fast-io----------------------------------------
void io() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

void solve(ll);

int main() {
    io();
#ifndef ONLINE_JUDGE
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
#endif
    ll T = 1ll;
    cin >> T;
    bool first = false;
    FOR(i, 1, T + 1) {
        if (first)
            cout << endl;
        solve(i);
        first = true;
    }
}
/*
    This is a variation of 0/1 knapsack problem.
    let's first think about a naive approach
    you can think of dp state as dp[idx][usedLeftLength][usedRightLength]
    where idx= Index of current car
    usedLeftLength = Total Length used of left side till the previous index
    usedRightLength = Total Length used of right side till the previous index

    so, if you follow this approach ,for each car you have two choises
        1) Either add this car on left-side (only if length_of_car+usedLeftLength<=total_length_of_ferry)
        2) Or add this car on right-side (only if length_of_car+usedRightLength<=total_length_of_ferry)
    if you can not do any of this then return as you can not skip any car.

    so transition state is 
    dp[idx][usedLeftLength][usedRightLength] = 1 + max(dp[idx+1][usedLeftLength+length_of_current_car][usedRightLength],dp[idx+1][usedLeftLength][usedRightLength+length_of_current_car]); 

    if you think carefully then you will notice that usedRightLength is not
    needed at all.

   suppose you are at a index "idx" that means you have selected all cars before
   idx.(because you can not skip any car in between).
   So,
   total_length_of_all_cars_till[idx-1] = usedLeftLength + usedRightLength
   => usedRightLength =  total_length_of_all_cars_till[idx-1] - usedLeftLength

  so,our new dp state is dp[idx][usedLeftLength]
  and the new transition state is
   
  dp[idx][usedLeftLength] = 1 + max(dp[idx + 1][usedLeftLength + length_of_current_car],dp[idx+1][usedLeftLength]); 
  
  you can calculate usedRightLength by using the above formula

  you can use prefix sum to calculate the value of
  "total_length_of_all_cars_till[]".
  
*/
ll ferrylength;                           // total length of ferry
vector<ll> cars;                          // all cars
vector<ll> total_length_of_all_cars_till; // prefix sum of length of cars
ll n;                                     // total number of cars
const ll N = 205;
const ll L = 1e4 + 5;
ll dp[N][L];
ll get_total_numbers_of_cars(ll idx, ll usedLeftLength) {
    if (idx >= min(N, n))
        return 0;
    if (dp[idx][usedLeftLength] != -1)  // check if this state already visited
        return dp[idx][usedLeftLength]; // if yes then return
    // calculate used length of right side
    ll usedRightLength = ((idx - 1 >= 0) ? total_length_of_all_cars_till[idx - 1] : 0) - usedLeftLength;

    ll loadleft = 0;  // number of cars that can be loaded on left side
    ll loadright = 0; // number of cars that can be loaded on left side

    // check if enough space is there for this car on left side
    
    if (usedLeftLength + cars[idx] <= ferrylength) {
        loadleft = 1 + get_total_numbers_of_cars(idx + 1, usedLeftLength + cars[idx]);
    }

    // check if enough space is there for this car on right side
    if (usedRightLength + cars[idx] <= ferrylength) {
        loadright = 1 + get_total_numbers_of_cars(idx + 1, usedLeftLength);
    }
    return dp[idx][usedLeftLength] = max(loadleft, loadright); // return their max
}
void print_path(ll idx, ll usedLeftLength, ll count) {
    if (count == 0)
        return;
    ll usedRightLength = (total_length_of_all_cars_till[idx - 1] - usedLeftLength);
    ll loadleft = 0, loadright = 0;
    if (usedLeftLength + cars[idx] <= ferrylength) {
        loadleft = 1 + dp[idx + 1][usedLeftLength + cars[idx]];
    }
    if (usedRightLength + cars[idx] <= ferrylength) {
        loadright = 1 + dp[idx + 1][usedLeftLength];
    }
    if (loadleft == get_total_numbers_of_cars(idx, usedLeftLength)) {
        cout << "port" << endl;
        print_path(idx + 1, usedLeftLength + cars[idx], count - 1);
    } else {
        cout << "starboard" << endl;
        print_path(idx + 1, usedLeftLength, count - 1);
    }
}
void take_input() {
    cin >> ferrylength;
    ferrylength *= 100; // ferry length is in meter but car length is in cm
    cars.resize(0);
    color(dp, -1);
    while (true) {
        ll length;
        cin >> length;
        if (length == 0)
            break;
        cars.emplace_back(length);
    }
}
void solve(ll TC) {
    take_input();
    n = cars.size();
    if (n == 0) {//if their is no car then return 
        cout << 0 << endl;
        return;
    }
    //calculating prefix sum of car lengths
    total_length_of_all_cars_till.resize(n, 0);
    total_length_of_all_cars_till[0] = cars[0];
    FOR(i, 1, n) {
        total_length_of_all_cars_till[i] = cars[i] + total_length_of_all_cars_till[i - 1];
    }
    ll total = get_total_numbers_of_cars(0, 0);
    cout << total << endl;
    print_path(0, 0, total);
}
