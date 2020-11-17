//
//  main.cpp
//  Lab1
//
//  Created by Hong-Ming on 6/8/19.
//  Copyright © 2019 HongMing. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include "parser.h"
#include "DistanceList.h"
#include "Node.h"
using namespace std;

DistanceList minimum(DistanceList a, DistanceList b, int anc){
    DistanceList c;
    if (a.isinf && !b.isinf) {          // a = inf
        c.distance = b.distance;
        c.isinf = false;
        c.ancestor = anc;
    }
    else if (!a.isinf && b.isinf){      // b = inf
        c.distance = a.distance;
        c.isinf = false;
        c.ancestor = a.ancestor;
    }
    else if (!a.isinf && !b.isinf){     // a != inf, b != inf
        if (a.distance < b.distance){
            c.distance = a.distance;
            c.isinf = false;
            c.ancestor = a.ancestor;
        }
        else{
            c.distance = b.distance;
            c.isinf = false;
            c.ancestor = anc;
        }
    }
    else{
        c.distance = 0;
        c.isinf = true;
    }
    
    return c;
}

DistanceList maximum(DistanceList a, DistanceList b){
    DistanceList c;
    if (b.isinf){                       // b = a-inf = -inf
        c.distance = a.distance;
        c.isinf = false;
    }
    else{                               // b != inf
        if(a.distance > b.distance){
            c.distance = a.distance;
            c.isinf = false;
        }
        else{
            c.distance = b.distance;
            c.isinf = false;
        }
    }
    
    return c;
}


int main(int argc, char** argv)
{
    if(argc < 2){
        printf("Usage: ./Lab2 <.in>\n");
        return 0;
    }
    
    parser_S* pParser;
    if (argc == 2) {
        pParser = new parser_S(argv[1]);
        pParser->parse();
        pParser->dump();
    } else if (argc == 3) { //verifier
        pParser = new parser_S(argv[1], argv[2]);
        if (!pParser->parse()) {
            return 0;
        }
        pParser->dump();
    }
    
    /* Start your code */
    
    // 1. find minimum mean cycle
    
    // define input file
    ifstream infile(argv[1]);
    // define output file
    ofstream outfile("solution.txt");
    
    int num_of_node;                 // number of nodes
    int num_of_edge;                 // number of edges
    infile >> num_of_node;
    infile >> num_of_edge;
    
    double** adj;                    // adjacency matrix
    Node* con;                       // connectivity list
    DistanceList** dis;              // shortest distance from s to v contain exactly k edges
    DistanceList* maxcycle;          // maximum mean cycle of each nodes
    DistanceList minimum_mean_cycle; // answer
    stack<int> cycle;                // path of cycle
    // assign memory space
    con = new Node[num_of_node];
    maxcycle = new DistanceList[num_of_node];
    adj = new double*[num_of_node];
    for (int i = 0; i < num_of_node; i++) {
        adj[i] = new double[num_of_node];
        for (int j = 0; j < num_of_node; j++) {
            adj[i][j] = 0;
        }
    }
    dis = new DistanceList*[num_of_node+1];
    for (int i = 0; i <= num_of_node; i++) {
        dis[i] = new DistanceList[num_of_node];
    }
    // read file
    int u;              // from
    int v;              // to
    int w;              // weight
    while(infile >> u){
        infile >> v;
        infile >> w;
        adj[u-1][v-1] = w;
        con[v-1].AddInwardEdge(u-1);
    }
    // initialize first row
    for (int x = 0; x < num_of_node; x++) {
        dis[0][x].isinf = false;
    }
    // filling up the distance table
    for (int i = 1; i <= num_of_node; i++) {
        for (int j = 0; j < num_of_node; j++) {
            for (vector<int>::iterator k = con[j].inward.begin(); k != con[j].inward.end(); ++k) {
                dis[i][j] = minimum(dis[i][j],dis[i-1][*k]+adj[*k][j],*k);
            }
        }
    }
    // find maxcycle for each node
    for (int i = 0; i < num_of_node; i++) {
        if (!dis[num_of_node][i].isinf) {
            maxcycle[i].isinf = false;
            for (int j = 0; j < num_of_node; j++) {
                maxcycle[i] = maximum(maxcycle[i],(dis[num_of_node][i]-dis[j][i])/(num_of_node-j));
            }
        }
    }
    // find minimum mean cycle
    for (int i = 0; i < num_of_node; i++) {
        if (!maxcycle[i].isinf) {
            minimum_mean_cycle = minimum(minimum_mean_cycle,maxcycle[i],i);
        }
    }
    // traverse cycle
    vector<int> walked_path;
    int cyclestart = -1;
    int temp = minimum_mean_cycle.ancestor;
    cycle.push(temp+1);
    for (int i = num_of_node; i >=0; i--) {
        walked_path.push_back(temp+1);
        temp = dis[i][temp].ancestor;
        cycle.push(temp+1);
        for (vector<int>::iterator it = walked_path.begin(); it !=walked_path.end(); ++it) {
            if (temp+1 == *it) {
                cyclestart = *it;
            }
        }
        if (cyclestart != -1) {
            break;
        }
    }

     // 2. dump minimum mean weight and minimum mean cycle in "solution.txt"
    if (minimum_mean_cycle.isinf) {
        outfile << "No cycle" << endl;
    }
    else{
        outfile << minimum_mean_cycle.distance << endl;
        outfile << cycle.top() << " ";
        cycle.pop();
        while (!cycle.empty()) {
            outfile << cycle.top() << " ";
            if (cycle.top() == cyclestart) {
                break;
            }
            cycle.pop();
        }
        outfile << endl;
    }
    
    delete pParser;
    return 0;
}
