#include "episode.h"

Episode::Episode(int episode_nbr, int gender, std::string name)
{
  _index = NULL;
  _episode_graph = NULL;
  std::vector<std::string> values;
  try { values = this->loadFile(episode_nbr); }
  catch(std::exception const& e) { std::cerr << "Error : " << e.what() << std::endl; throw e; }
  try { this->create(values, gender, name); }
  catch (std::exception const& e) { std::cerr << "Error : " << e.what() << std::endl; throw e; }
}

Node * Episode::getIndex() { return _index; }

void Episode::setIndex(Node * index) { _index = index; }

std::vector<int> Episode::getEndNbrList() { return _endNbrList; }

void Episode::introduction(int level)
{
  clearConsole();
  std::cout << "| PART " << level << " |" << std::endl;
  usleep(500 * 1000);
  for(unsigned int i = 0; i < _title.length(); ++i)
  {
    std::cout << _title[i];
    fflush(stdout);
    usleep(200 * 1000);
  }
  fflush(stdout);
  usleep(1000 * 1000);
  std::cout << "\n\n\nPress enter to continue..." << std::endl;
  waitForPlayer();

}

std::vector<std::string> Episode::loadFile(int episode_nbr)
{
  std::string line;
  std::vector<std::string> values;
  std::string last_line;

  std::string episode_file_path = "./data/episode";
  episode_file_path += std::to_string(episode_nbr);
  episode_file_path += ".txt";

  std::cout << "Loading..." << std::endl;

  std::ifstream myfile(episode_file_path);
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      values.push_back(line);
    }
    myfile.close();
    if (values.empty()) {
      throw Error("Empty episode");
    }
  } else {
    throw Error("Unable to open file");
  }

  return values;
}

void Episode::create(std::vector<std::string> values, int gender, std::string name) {
    std::vector<Node *> nodes_tab;
    std::vector<int> endNbrList;
    int cntr = 0;
    unsigned int i = 1;

    _title = values[0]; /* Title */

    while (values[i] != "***") {
      if(isNumber(values[i]))
        endNbrList.push_back(stoi(values[i])); /* End keys */
      else
        throw Error("Invalid Episode");
      ++i;
      if (i >= values.size())
        throw Error("Invalid Episode");
    }

    // Creates all the nodes
    for (++i; i < values.size(); ++i) {
      Node * step = new Node();
      std::string new_text;

      ++i;
      if(values[i] != " ")
      {
        while(values[i] != "*") /* Story text */
        {
          new_text.append(values[i]);
          new_text += "\n";
          ++i;
        }
        fillPlaceholders(&new_text, gender, name);
        step->setText(new_text);

        while(values[++i] != "*") /* Link keys */
        {
          if(values[i] != "END")
          {
            step->addlistNeighbourIndex(atoi(values[i].data()));
          }
          else
            break;
        }

        while(values[++i] != "***") /* Choice text */
        {
          fillPlaceholders(&(values[i]), gender, name);
          step->addChoice(values[i]);
        }

        step->setNbr(++cntr);
        nodes_tab.push_back(step);
      }
    }

    // Creates links between nodes
    for(int i = 0; i < (int) nodes_tab.size(); ++i)
    {
      std::vector<int> IndexesTab;
      IndexesTab = nodes_tab[i]->getlistNeighbourIndexes();

      for(int j = 0; j < (int) IndexesTab.size(); ++j)
      {
        nodes_tab[i]->addNeighbour(nodes_tab[IndexesTab[j]-1]);
      }
    }

    _episode_graph = new Graph(nodes_tab);
    _endNbrList = endNbrList;
    _index = _episode_graph->getFirstNode();
}

void Episode::displayText(Node * node)
{
  clearConsole();
  std::cout << node->getText() << std::endl;
}

void Episode::displayChoices(Node * node)
{
  if (!node->getlistNeighbourIndexes().empty())
  {
    for (int i = 0; i < (int) node->getlistNeighbourIndexes().size(); ++i)
    {
      std::cout << i+1 << ". " << node->getlistChoices()[i] << std::endl;
    }
  }
}

void Episode::fillPlaceholders(std::string * s, int gender, std::string name)
{
  findReplace(s, "[P-NAME]", name);
  if (gender == 0)
  {
    findReplace(s, "[L-I-NAME]", "Nicolas");
    findReplace(s, "[L-I-PRONOUN-F]", "He");
    findReplace(s, "[L-I-PRONOUN]", "he");
    findReplace(s, "[L-I-PRONOUN2]", "him");
    findReplace(s, "[L-I-POSS-PRONOUN]", "his");
    findReplace(s, "[L-I-POSS-PRONOUN-F]", "His");
    findReplace(s, "[L-I-GENDER]", "boy");
    findReplace(s, "[L-I-S-NAME]", "Amélie");
    findReplace(s, "[L-I-S-PRONOUN2]", "her");
    findReplace(s, "[L-I-S-PRONOUN-F]", "She");
  }
  if (gender == 1)
  {
    findReplace(s, "[L-I-NAME]", "Charlotte");
    findReplace(s, "[L-I-PRONOUN-F]", "She");
    findReplace(s, "[L-I-PRONOUN]", "she");
    findReplace(s, "[L-I-PRONOUN2]", "her");
    findReplace(s, "[L-I-POSS-PRONOUN]", "her");
    findReplace(s, "[L-I-POSS-PRONOUN-F]", "Her");
    findReplace(s, "[L-I-GENDER]", "girl");
    findReplace(s, "[L-I-S-NAME]", "Thomas");
    findReplace(s, "[L-I-S-PRONOUN2]", "him");
    findReplace(s, "[L-I-S-PRONOUN-F]", "He");
  }

}
