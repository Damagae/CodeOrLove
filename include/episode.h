#ifndef __EPISODE_H_INCLUDED__
#define __EPISODE_H_INCLUDED__

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <ctime>
#include "graph.h"
#include "common.h"
#include "error.h"

class Episode
{
private:
  Node * _index;
  Graph * _episode_graph;
  std::string _title;
  int _endNbr;
  std::vector<int> _endNbrList;

public:
  Episode(int episode_nbr, int gender, std::string name);
  Node * getIndex();
  void setIndex(Node * index);
  std::vector<int> getEndNbrList();
  void introduction(int level);
  std::vector<std::string> loadFile(int episode_nbr);
  void create(std::vector<std::string> values, int gender, std::string name);
  void displayText(Node * node);
  void displayChoices(Node * node);
  void choose();
  void fillPlaceholders(std::string * s, int gender, std::string name);

};

#endif
