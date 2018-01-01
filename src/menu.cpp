#include "menu.h"

Menu::Menu()
{

}

void Menu::splashscreen()
{
  clearConsole();
  std::cout << "*****************\n  CODE OR LOVE\n*****************\n\nPress enter to continue..." << std::endl;
  waitForPlayer();
}

void Menu::run()
{
  int choice = -1;

  while(1) {
    while (choice == -1)
    {
      printMenuOptions();
      choice = getMenuOption();
    }
    proceedAction(choice);
    choice = -1;
  }
}

void Menu::printMenuOptions() {
  std::cout << "Play (p) | Quit (q)" << std::endl;
}

int Menu::getMenuOption() {
  std::string choice;
  getline(std::cin, choice);
  if (choice == "p" || choice == "P")
  {
    return 0;
  }
  else if (choice == "q" || choice == "Q")
  {
    return 1;
  }
  else
  {
    return -1;
  }
}

void Menu::proceedAction(int action)
{
  if (action == 0)
  {
    play();
  }
  else if (action == 1)
  {
    quit();
  }
}

void Menu::play()
{
  Game game;
  try { game.playGame(); }
  catch (std::exception const& e) { }
}

void Menu::quit() {
  exit(EXIT_FAILURE);
}
