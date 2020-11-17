//
//  DistanceList.hpp
//  Lab1
//
//  Created by Hong-Ming on 6/8/19.
//  Copyright © 2019 HongMing. All rights reserved.
//

#ifndef DistanceList_h
#define DistanceList_h
#include <stdio.h>
#endif /* DistanceList_hpp */

class DistanceList{
public:
    double distance;
    int ancestor;
    bool isinf;
    
    DistanceList();
    DistanceList operator+ (const DistanceList&);
    DistanceList operator+ (double);
    DistanceList operator- (const DistanceList&);
    DistanceList operator/ (const double&);
};

