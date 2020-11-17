//
//  NOde.hpp
//  Lab1
//
//  Created by Hong-Ming on 6/9/19.
//  Copyright © 2019 HongMing. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp
#include <stdio.h>
#include <vector>
using namespace std;
#endif /* Node_hpp */

class Node{
public:
    vector<int> inward;
    
    Node(){;};
    void AddInwardEdge(int);
    
};
