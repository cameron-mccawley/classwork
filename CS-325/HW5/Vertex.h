#pragma once

class Vertex{
    public:
        Vertex();
        Vertex(int, int);
        Vertex(int, int, int);
        ~Vertex();

        int get_x();
        void set_x(int);
        
        int get_y();
        void set_y(int);
    
    private:
        int x, y;
        
};