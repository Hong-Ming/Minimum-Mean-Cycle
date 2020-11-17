//
//  parser.cpp
//  Lab1
//
//  Created by Hong-Ming on 6/8/19.
//  Copyright © 2019 HongMing. All rights reserved.
//

#include "parser.h"
#include <cstdio>
#include <stdlib.h>
#include <cassert>
#include <fstream>
#include <string>
#include <cstring>
//----------------------------------------------------------------------------------------------------------------------
parser_S::parser_S(const char* p_caCase) : _caCase(p_caCase), _caSol(0), _dMMC(0), _vCycle(0)
{
    if (!_isFileExist(_caCase)) { assert(0); }
}
//----------------------------------------------------------------------------------------------------------------------
parser_S::parser_S(const char* p_caCase, const char* p_caSol) : _caCase(p_caCase), _caSol(p_caSol), _dMMC(0), _vCycle(0)
{
    if (!_isFileExist(_caCase)) { assert(0); }
    if (!_isFileExist(_caSol))  { assert(0); }
}
//----------------------------------------------------------------------------------------------------------------------
bool parser_S::_isFileExist(const char* p_caFile)
{
    _input.open(p_caFile, ios::in);
    if(!_input){
        printf("Warning: can not find file: %s !\n", p_caFile);
        _input.close();
        return false;
    }
    
    printf("File %s Open Success\n", p_caFile);
    _input.close();
    return true;
}
//----------------------------------------------------------------------------------------------------------------------
bool parser_S::parse()
{
    parseInput();
    if (_caSol) {
        return parseSol();
    }
    return true;
}
//----------------------------------------------------------------------------------------------------------------------
bool parser_S::parseSol()
{
    _input.open(_caSol, ios::in);
    _getLine();
    if (0 == strcmp(_buffer, "No cycle")) {
        printf("[parse - solution] No cycle\n");
        return false;
    } else {
        sscanf(_buffer, "%lf", &_dMMC);
        char* pCh;
        while (_getLine()) {
            pCh = strtok(_buffer, " \n");
            while (pCh) {
                _vCycle.push_back(atoi(pCh));
                pCh = strtok(NULL, " \n");
            }
        }
        printf("[parse - solution] MMC: %.2f\n", _dMMC);
        printf("[parse - solution] Cycle: ");
        for (auto n : _vCycle) {
            printf("%d ", n);
        }
        printf("\n");
    }
    return true;
}
//----------------------------------------------------------------------------------------------------------------------
void parser_S::parseInput()
{
    _input.open(_caCase, ios::in);
    //src
    _getLine();
    int numNode(0), numEdge(0), from, to, weight;
    set<int> n;
    sscanf(_buffer, "%d %d", &numNode, &numEdge);
    while (_getLine()) {
        sscanf(_buffer, "%d %d %d", &from, &to, &weight);
        edge_S* pEdge = new edge_S(from, to, weight);
        _vEdge.push_back(pEdge);
        if (n.count(from) == 0) {
            node_S* pFrom = new node_S(from);
            _vNode.push_back(pFrom);
            n.insert(from);
        }
        if (n.count(to) == 0) {
            node_S* pTo = new node_S(to);
            _vNode.push_back(pTo);
            n.insert(to);
        }
    }
    if ((int) _vEdge.size() != numEdge) {
        printf("[parser] Warning: edge inconsistency, there should be %d edges, but only %d edges are parsed\n", numEdge, (int) _vEdge.size());
        assert(0);
    }
    if ((int) _vNode.size() != numNode) {
        printf("[parser] Warning: node inconsistency, there should be %d nodes, but only %d nodes are parsed\n", numNode, (int) _vNode.size());
    }
    _input.close();
}
//----------------------------------------------------------------------------------------------------------------------
bool parser_S::_getLine()
{
    string buffer;
    if (_input.eof()) {return false;}
    getline(_input,buffer);
    while (buffer.empty()) {
        if (_input.eof()) {return false;}
        getline(_input,buffer);
    }
    strcpy(_buffer, buffer.c_str());
    return true;
}
//----------------------------------------------------------------------------------------------------------------------
void parser_S::dump()
{
    FILE *pFile;
    pFile = fopen("dumpParser.txt", "w");
    //edge
    fprintf(pFile,"//#edge %d\n", (int) _vEdge.size());
    for(auto & edge: _vEdge) {
        fprintf(pFile,"%d %d %d\n", edge->_fromNode, edge->_toNode, edge->_weight);
    }
    //node
    fprintf(pFile,"\n//#node %d\n", (int) _vNode.size());
    for(auto & node : _vNode) {
        fprintf(pFile,"%d\n", node->_id);
    }
    fclose(pFile);
}
//----------------------------------------------------------------------------------------------------------------------


