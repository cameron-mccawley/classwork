#pragma once

#include "Vertex.h"

class Graph{
    public:
        Graph();
        Graph(int);
        ~Graph();

        void init_matrix();
        void addVertex(Vertex);

        int get_distance(Vertex*, Vertex*);

        int get_min_key(int [], bool []);
        void prims();

        void print_total(int *);

    private:
        int num_verts, curr_index;
        int** adj_arr;
        Vertex *vert_arr;
};