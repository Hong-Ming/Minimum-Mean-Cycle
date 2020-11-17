//
//  DistanceList.cpp
//  Lab1
//
//  Created by Hong-Ming on 6/8/19.
//  Copyright © 2019 HongMing. All rights reserved.
//

#include "DistanceList.h"
#include <iostream>
using namespace std;

DistanceList::DistanceList(){
    distance = 0;
    ancestor = -1;
    isinf = true;
}

DistanceList DistanceList::operator+(const DistanceList& x){
    DistanceList y;
    if (!isinf && !x.isinf) {
        y.distance = distance + x.distance;
        y.isinf = false;
    }
    return y;
}

DistanceList DistanceList::operator+(double x){
    DistanceList y;
    if (!isinf) {
        y.distance = distance + x;
        y.isinf = false;
        y.ancestor = ancestor;
    }
    return y;
}


DistanceList DistanceList::operator-(const DistanceList& x){
    DistanceList y;
    if (!(isinf || x.isinf)) {
        y.distance = distance - x.distance;
        y.isinf = false;
    }
    return y;
}

DistanceList DistanceList::operator/(const double& x){
    DistanceList y;
    if (!isinf) {
        y.distance = distance / x;
        y.isinf = false;
    }
    return y;
}
