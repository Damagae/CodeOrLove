#ifndef __GRAPH_H_INCLUDED__
#define __GRAPH_H_INCLUDED__

#include <iostream>
#include <vector>
#include <string>

#define DIM 10

class Node
{
private:
    std::vector<Node *> listNeighbour;
    std::vector<int> listNeighbourIndexes;
    std::string text;
    std::vector<std::string> listChoices;
    int _nbr;
public:
    std::string getText();
    void setNbr(int nbr);
    int getNbr();
    void setText(std::string value);
    void addChoice(std::string new_choice);
    void addNeighbour(Node * new_node);
    void addlistNeighbourIndex(int new_index);
    std::vector<int> getlistNeighbourIndexes();
    std::vector<std::string> getlistChoices();
    std::vector<Node *> getlistNeighbour();
};

class Graph
{
private:
    std::vector<Node *> _listNode;
public:
    Graph(std::vector<Node *> listNode);
    std::vector<Node *> getListNode();
    Node * getFirstNode();
};

#endif
