#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<utility>
#include<string>

int distinct_positions = 0;
int max_x;
int max_y;

std::string FILENAME = "input.txt";
std::unordered_map<std::string, std::pair<int,int>> DIRECTIONS = {
  { "UP",    std::make_pair(-1,0) },
  { "LEFT",  std::make_pair(0,-1) },
  { "DOWN",  std::make_pair(1,0)  },
  { "RIGHT", std::make_pair(0,1)  },
};

std::unordered_map<std::string, std::string> TURNS = {
  {"UP", "RIGHT"},
  {"RIGHT", "DOWN"},
  {"DOWN", "LEFT"},
  {"LEFT", "UP"},
};

bool in_bounds(int x, int y, int max_x, int max_y);

int main()
{
  std::fstream file{FILENAME};
  std::vector<std::vector<char>> map;

  if (file.is_open())
  {
    for(std::string line; std::getline(file, line);)
    {
      std::vector<char> row(line.begin(), line.end());
      map.push_back(row);
    }
  }

  file.close();

  max_x = map[0].size();
  max_y = map.size();

  std::pair<int,int> starting_pos;
  bool not_found = true;

  for (int i = 0; not_found && i < map.size(); i++)
  {
    for (int j = 0; not_found && j < map[i].size(); j++)
    {
      if (map[i][j] == '^')
      {
        starting_pos = std::make_pair(i, j);
        not_found = false;
      }
    }
  } 
  
  int x = starting_pos.first;
  int y = starting_pos.second;
  std::string direction = "UP";

  while (in_bounds(x, y, max_x, max_y))
  {

    if (map[x][y] != 'X')
    {
      map[x][y] = 'X';
      distinct_positions++;
    }

    int next_x = x + DIRECTIONS[direction].first;
    int next_y = y + DIRECTIONS[direction].second;

    if (in_bounds(next_x, next_y, max_x, max_y) && map[next_x][next_y] == '#')
    {
      direction = TURNS[direction];
      x += DIRECTIONS[direction].first;
      y += DIRECTIONS[direction].second;
    } else {
      x = next_x;
      y = next_y;
    }   

  }

  std::cout << "Distinct positions visited: " << distinct_positions << '\n';
}

bool in_bounds(int x, int y, int max_x, int max_y)
{
  return (x >= 0 && x < max_x) && (y >= 0 && y < max_y);
}

