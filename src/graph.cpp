#include "graph.h"

std::string Node::getText() { return text; }

void Node::setText(std::string value) { text = value; }

void Node::setNbr(int nbr) { _nbr = nbr; }

int Node::getNbr() { return _nbr; }

void Node::addChoice(std::string new_choice) { listChoices.push_back(new_choice); }

void Node::addNeighbour(Node * new_node) { listNeighbour.push_back(new_node); }

void Node::addlistNeighbourIndex(int new_index) { listNeighbourIndexes.push_back(new_index); }

std::vector<int> Node::getlistNeighbourIndexes() { return listNeighbourIndexes; }

std::vector<std::string> Node::getlistChoices() { return listChoices; }

std::vector<Node *> Node::getlistNeighbour() { return listNeighbour; }

Graph::Graph(std::vector<Node *> listNode) { _listNode = listNode; }

std::vector<Node *> Graph::getListNode() { return _listNode; }

Node * Graph::getFirstNode() { return _listNode[0]; }
