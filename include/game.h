#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include <iostream>
#include <string>
#include <fstream>
#include "episode.h"

class Game
{
private:
  int charaGender; //0 for woman and 1 for man
  std::string charaName;
  Episode * currentEpisode;

public:
  Game();
  void choose();
  int playEpisode();
  int nextEpisodeId(std::vector<int> endNbrList, int endNbr);
  void loadNextEpisode(int level, int id);
  void playGame();
  void initGame();
  bool episodeExists(int level, int id);
  void instructions(std::string name);
  void conclusion();
};

#endif
