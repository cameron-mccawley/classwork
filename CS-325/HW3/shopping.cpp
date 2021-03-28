#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//returns max value that can be put in a knapsack of cap W using DP
//https://youtu.be/nLmhmB6NzcM for finding V[i][w]
//https://www.geeksforgeeks.org/printing-items-01-knapsack/ for backtracing
int knapSack(int W, vector<int> wt, vector<int> val, int n, vector<int> &items){
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

    //Backtrace to find items that make up knapsack

    int weight = W;
    int max = V[n][W];
    for(int i = n; i > 0 && max > 0; i--){
        if(max != V[i-1][weight]){
            items.insert(items.begin(), i);
            max -= val[i-1];
            weight -= wt[i-1];
        }
    }

    return V[n][W];
}

int main(){
    ifstream input;
	ofstream output;
	input.open("shopping.txt");
	output.open("results.txt");

	if (input.is_open()){
        int  n, v, w, testCases, family, W;
        input >> testCases;

        for(int i = 0; i < testCases; i++){
            input >> n;
            vector<int> val;
            vector<int> wt;
            int maxVal = 0;
            for(int j = 0; j < n; j++){
                input >> v;
                input >> w;
                val.push_back(v);
                wt.push_back(w);
            }
            input >> family;
            output << "Test Case " << (i+1) << endl;
            output << "Member Items:" << endl;
            for(int k = 0; k < family; k++){
                input >> W;
                vector<int> items;
                maxVal += knapSack(W, wt, val, n, items);
                output << (k+1) << ": "; 
                for(int l = 0; l < items.size(); l++){
                    output << items[l] << " ";
                }
                output << endl;
            }
            output << "Total Price: " << maxVal << endl;
            output << endl;

        }
        input.close();
    }
	
	return 0;
}