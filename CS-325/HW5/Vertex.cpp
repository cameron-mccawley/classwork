#include "Vertex.h"

Vertex::Vertex(){
    x = -1;
    y = -1;
}

//Constructor
Vertex::Vertex(int x, int y){
    this->x = x;
    this->y = y;
}

Vertex::~Vertex(){

}

//These are just getters and setter, nothing special

int Vertex::get_x(){
    return x;
}

int Vertex::get_y(){
    return y;
}

void Vertex::set_x(int x){
    this->x = x;
}

void Vertex::set_y(int y){
    this->y = y;
}
