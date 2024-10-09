#pragma once
#include <vector>

std::vector<float> quad_vertices = {
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f,   
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f    
};

std::vector<unsigned int> quad_indices = {
    0, 1, 2,   
    2, 3, 0    
};