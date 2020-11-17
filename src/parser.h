//
//  parser.hpp
//  Lab1
//
//  Created by Hong-Ming on 6/8/19.
//  Copyright © 2019 HongMing. All rights reserved.
//

#ifndef __PARSER_H__
#define __PARSER_H__
#include <vector>
#include <fstream>
#include <set>
using namespace std;

//----------------------------------------------------------------------------------------------------------------------
struct node_S{
public:
    node_S(int id) : _id(id) {}
    int _id;
};
//----------------------------------------------------------------------------------------------------------------------
struct edge_S{
public:
    edge_S(int fromNode, int toNode,int weight) : _fromNode(fromNode), _toNode(toNode), _weight(weight) {}
    int _fromNode;
    int _toNode;
    int _weight;
};
//----------------------------------------------------------------------------------------------------------------------
struct parser_S{
public:
    parser_S(const char* p_caCase);
    parser_S(const char* p_caCase, const char* p_caSol);
    ~parser_S() {}
    bool parse();
    void dump();
    
    //data
    vector<edge_S*>     _vEdge;
    vector<node_S*>     _vNode;
    
private:
    void parseInput();
    bool parseSol();
    bool _getLine();
    bool _isFileExist(const char*);
    
    //data
    ifstream    _input;
    const char* _caCase;
    const char* _caSol;
    char        _buffer[512];
    double      _dMMC;
    vector<int> _vCycle;
};
//----------------------------------------------------------------------------------------------------------------------

#endif
