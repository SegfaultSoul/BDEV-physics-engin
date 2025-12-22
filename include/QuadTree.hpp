#pragma once

#include "Vector2D.hpp"
#include <vector>
template<typename T> 
class QuadtreeNode {
public:
    static const int MAX_CAPICITY = 4;

    double x, y, width, height;  // Position and dimensions
    std::vector<T*> data = {};  // Pointer to stored data

    QuadtreeNode* NW = nullptr;
    QuadtreeNode* NE = nullptr;
    QuadtreeNode* SW = nullptr;
    QuadtreeNode* SE = nullptr;

    bool is_leaf_node = false;

    QuadtreeNode(double x, double y, double width, double height)
        : x(x), y(y), width(width), height(height),
          NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr),
          data(nullptr), is_leaf_node(true) {}

    ~QuadtreeNode() {
        delete NW;
        delete NE;
        delete SW;
        delete SE;
    }

    bool isLeaf() const {
        return is_leaf_node;
    }

    bool contains(Vector2D<double>position) const {
        return (position.x >= x && position.x <= x + width &&
                position.y >= y && position.y <= y + height);
    }

    bool insert(T* entity, Vector2D<double>position){
      if(!this->contains(position)) return false;

      if (data.size() < MAX_CAPICITY){
        data.push_back(entity);
      }
      else {
        
      }
    }
};
