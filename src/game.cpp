#include "game.h"

Game::Game()
{
  initGame();
  try { currentEpisode = new Episode(101, charaGender, charaName); }
  catch (std::exception const& e) { std::cerr << "Cannot start game : " << e.what(); }
}

void Game::instructions(std::string name)
{
  clearConsole();
  std::cout << "You will now be playing " << name << ", your character. For each turn, you will read a part of the story that happens to your character. Then you will be able to chose between one or many given choices by typing the number of the choice and then pressing enter.\nAre you ready? (press enter if so)" << std::endl;
  waitForPlayer();
}

void Game::initGame()
{
  std::string gender;
  std::string name;

  clearConsole();
  std::cout << "What would your character's name will be?" << std::endl;
  while(1)
  {
    std::getline(std::cin, name);
    if (name.size() > 1 && name[0] != ' ' && name[1] != ' ')
    {
      name.erase(name.find_last_not_of(" \n\r\t")+1);
      nameFormate(&name);
      charaName = name;
      break;
    } else {
      std::cout << "Please enter a name that have more than 2 characters" << std::endl;
    }
  }

  clearConsole();
  std::cout << "What would your character be?\n1. A woman\n2. A man" << std::endl;
  while(1)
  {
    getline(std::cin, gender);
    if(isNumber(gender))
    {
      if(stoi(gender) == 1)
      {
        charaGender = 0;
        break;
      }
      else if (stoi(gender) == 2)
      {
        charaGender = 1;
        break;
      }
    }
    std::cout << "Please enter a valid number" << std::endl;
  }
}

void Game::choose()
{
  Node * index = currentEpisode->getIndex();
  if (!index->getlistNeighbourIndexes().empty())
  {
    std::string choice_index;
    do {
      getline(std::cin, choice_index);
    } while (!isNumber(choice_index) || stoi(choice_index) == 0 || (unsigned int) stoi(choice_index) > index->getlistNeighbour().size() );

    currentEpisode->setIndex(index->getlistNeighbour()[stoi(choice_index)-1]);
  }
}

int Game::playEpisode()
{
  Node * index;
  while(1)
  {
    index = currentEpisode->getIndex();
    currentEpisode->displayText(index);
    if(!index->getlistNeighbour().empty())
    {
      currentEpisode->displayChoices(index);
      choose();
    }
    else
    {
      return index->getNbr();
    }
  }
}

int Game::nextEpisodeId(std::vector<int> endNbrList, int endNbr)
{
  for(unsigned int i = 0; i < endNbrList.size(); ++i)
  {
    if (endNbrList[i]/10 == endNbr) {
      return endNbrList[i]%10;
    }
  }
   throw Error("No matching episode");
   return -1;
}

void Game::loadNextEpisode(int level, int id)
{
  int episodeNbr = level*100 + id;
  try { currentEpisode = new Episode(episodeNbr, charaGender, charaName); }
  catch (std::exception const& e) { throw e; }
}

bool Game::episodeExists(int level, int id)
{
  int episodeNbr = level*100 + id;
  std::string episode_file_path = "./data/episode";
  episode_file_path += std::to_string(episodeNbr);
  episode_file_path += ".txt";

  std::ifstream myfile(episode_file_path);
  if (myfile.is_open()) {
    myfile.close();
    return true;
  } else {
    return false;
  }
}

void Game::conclusion()
{
  std::cout << "\n\nPress enter to continue..." << std::endl;
  waitForPlayer();
  clearConsole();
  std::cout << "Congratulation, you finished the game!\nMaybe it didn't turn out the way you wished, but the good part is, you can play again and find out all of the possibilities. Have fun!\n\n" << std::endl;
}

void Game::playGame()
{
  instructions(charaName);
  currentEpisode->introduction(1);
  int episodeId;
  int end = playEpisode();
  try { episodeId = nextEpisodeId(currentEpisode->getEndNbrList(), end); }
  catch(std::exception const& e) { throw e; }

  for(int i = 2; i <= 3; ++i)
  {
    if(episodeExists(i, episodeId))
    {
      try { loadNextEpisode(i, episodeId); }
      catch(std::exception const& e) { throw e; }
      currentEpisode->introduction(i);
      end = playEpisode();
      if (!currentEpisode->getEndNbrList().empty())
      {
        try { episodeId = nextEpisodeId(currentEpisode->getEndNbrList(), end); }
        catch(std::exception const& e) { throw e; }
      }
    }
    else
    {
      conclusion();
      break;
    }
  }
}
