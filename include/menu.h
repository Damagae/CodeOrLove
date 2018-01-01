#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "game.h"
#include "error.h"

class Menu
{
private:

public:
  Menu();
  void splashscreen();
  void run();
  void printMenuOptions();
  int getMenuOption();
  void proceedAction(int action);
  void play();
  void quit();
};

#endif
