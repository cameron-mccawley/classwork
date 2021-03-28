#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

//returns max of two values
int max(int a, int b){
    return (a > b) ? a : b;
}

//returns max value that can be put in a knapsack of cap W using recursion
int rec_knapSack(int W, int wt[], int val[], int n){
    //base case
    if(n==0 || W==0){
        return 0;
    }
    if(wt[n-1] > W){
        return rec_knapSack(W, wt, val, n-1);
    }else{
        return max((val[n-1]+rec_knapSack(W-wt[n-1], wt, val, n-1)), rec_knapSack(W, wt, val, n-1));
    }
    
}

//returns max value that can be put in a knapsack of cap W using DP
//https://youtu.be/nLmhmB6NzcM for finding V[i][w]
int DP_knapSack(int W, int wt[], int val[], int n){
    int V[n+1][W+1];

    //build table V bottom up
    for(int i = 0; i <= n; i++){
        for(int w = 0; w <= W; w++){
            if(i == 0 || w == 0){
                V[i][w] = 0;
            }else if(wt[i-1] <= w){
                V[i][w] = max(val[i-1]+V[i-1][w-wt[i-1]], V[i-1][w]);
            }else{
                V[i][w] = V[i-1][w];
            }
        }
    }
    return V[n][W];
}

int main(){
    int W = 100;
    srand(0);
    for(int n = 10; n < 50; n += 5){
        int wt[n];
        int val[n];
        for(int i = 0; i <= n; i++){
            wt[i] = (rand() % 30)+1;
            val[i] = (rand() % 100) + 1;
        }
        
        auto start = high_resolution_clock::now();
        int rec_max = rec_knapSack(W, wt, val, n);
        auto stop = high_resolution_clock::now();

        auto rec_time = duration_cast<microseconds>(stop - start);

        start = high_resolution_clock::now();
        int dp_max = DP_knapSack(W, wt, val, n);
        stop = high_resolution_clock::now();

        auto dp_time = duration_cast<microseconds>(stop - start);

        cout << "N=" << n << " W=" << W << ", Rec time = " << rec_time.count() << " ms, DP time = " << dp_time.count() << " ms, Max rec = " << rec_max << ", max DP = " << dp_max << endl;

    }

    return 0;
}
