#include <iostream>
#include <fstream>
#include "Vertex.h"
#include "Graph.h"

using namespace std;

int main(int argc, char* argv[]){

    ifstream input ("graph.txt"); //Open file stream for graph

    if(input.is_open()){
        int cases;
        input >> cases;

        for(int i = 0; i < cases; i++){
            int num_verts;
            input >> num_verts; //Get the number of verticies in our test case

            Graph graph(num_verts); //Create our graph object

            int x, y;

            for(int j = 0; j < num_verts; j++){
                input >> x;
                input >> y;

                Vertex v(x, y); //create our vertex
                graph.addVertex(v); //And add it to the graph

            }

            graph.init_matrix();
            cout << "Test case " << i+1 << ": ";
            graph.prims(); //Do the algo magic
        }

        input.close();

    }else{
        cout << "Error: graph.txt not found." << endl;
    }

    return 0;
}