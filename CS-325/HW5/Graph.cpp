#include "Graph.h"
#include <cmath>
#include <limits>
#include <iostream>

using namespace std;

#define MAX numeric_limits<int>::max()

//I never use the default constructor in this program, so I wont bother implementing it
Graph::Graph(){

}

//constructor
Graph::Graph(int num_verts){
    curr_index = -1;
    this->num_verts = num_verts;

    adj_arr = new int*[num_verts];
    vert_arr = new Vertex[num_verts];

    //init 2d array
    for(int i = 0; i < num_verts; i++){
        adj_arr[i] = new int[num_verts];
    }
}

//destructor
Graph::~Graph(){
    delete[] vert_arr;
    for(int i = 0; i < num_verts; i++){
        delete[] adj_arr[i];
    }
    delete[] adj_arr;
}

//precondition: num_verts>0
//creates and initializes the adjacency matrix
void Graph::init_matrix(){
    for(int i = 0; i < num_verts; i++){
        Vertex a = vert_arr[i];
        for(int j = 0; j < num_verts; j++){
            Vertex b = vert_arr[j];
            adj_arr[i][j] = get_distance(&a, &b);
        }
    }

    //Put max in diagonal of matrix
    for(int i = 0; i < num_verts; i++){
        adj_arr[i][i] = -1;
    }
}

//adds a vertex to the graph
void Graph::addVertex(Vertex v){
    curr_index++;
    vert_arr[curr_index] = v;
}

//gets the distance between two points
int Graph::get_distance(Vertex* a, Vertex* b){
    double d_distance = sqrt(pow(a->get_x() - b->get_x(), 2) + pow(a->get_y() - b->get_y(), 2));
    return round(d_distance); //Round to nearest integer
}

//This function finds the vertex with the minimum key value
int Graph::get_min_key(int key[], bool set[]){
    int min = MAX;  //Initialize the min value
    int min_index;

    for(int i = 0; i < num_verts; i++){
        if(set[i]==false && key[i] < min){
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}

void Graph::prims(){
    int *parent = new int[num_verts];
    int *key = new int[num_verts];
    bool *set = new bool[num_verts]; //set of mst

    //everything is infinitly far away.
    for(int i = 0; i < num_verts; i++){
        key[i] = MAX;
        set[i] = false;
    }

    //include first vertex in our set
    key[0] = 0;
    parent[0] = -1;

    //Loop through each vertex until all vertices have been added to the set
    for(int i = 0; i < num_verts; i++){
        int next_key = get_min_key(key, set);
        //add picked value to set
        set[next_key] = true;

        for(int j = 0; j < num_verts; j++){

            //find min key and corresponding parent
            if(adj_arr[next_key][j] && set[j] == false && adj_arr[next_key][j] < key[j]){
                parent[j] = next_key; //Update parents
                key[j] = adj_arr[next_key][j]; //update the key values
            }
        }
    }

    print_total(parent);

}

//prints the total weight of the MST
void Graph::print_total(int* v){
    int total = 0;
    for(int i = 1; i < num_verts; i++){
        total += adj_arr[i][v[i]];
    }

    cout << "MST weight " << total << endl;
}
