#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include <unordered_map>
#include <array>

const std::string PUZZLE_FILE{"word_search"};
std::unordered_map<std::string, std::array<int,2>> directions = {
  {"up", std::array<int,2>{-1,0}},
  {"down", std::array<int,2>{1, 0}},
  {"left", std::array<int,2>{0, -1}},
  {"right", std::array<int,2>{0, 1}},
  {"upleft", std::array<int,2>{-1, -1}},
  {"upright", std::array<int,2>{-1, 1}},
  {"downleft", std::array<int,2>{1, -1}},
  {"downright", std::array<int,2>{1, 1}},
};

std::vector<std::vector<char>> create_puzzle(const std::string filename);
bool in_bounds(int i, int j, int n);
int check_neighbor(char letter, int i, int j, std::string direction, std::vector<std::vector<char>>& puzzle);

auto main() -> int
{
  int count{};
  std::vector<std::vector<char>> puzzle = create_puzzle(PUZZLE_FILE);
  int n = static_cast<int>(puzzle.size());

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (puzzle[i][j] == 'X')
      {
        auto [ui, uj] = directions["up"];
        count += check_neighbor('M', i + ui, j + uj, "up", puzzle);

        auto [di, dj] = directions["down"];
        count += check_neighbor('M', i + di, j + dj, "down", puzzle);

        auto [li, lj] = directions["left"];
        count += check_neighbor('M', i + li, j + lj, "left", puzzle);

        auto [ri, rj] = directions["right"];
        count += check_neighbor('M', i + ri, j + rj, "right", puzzle);

        auto [uli, ulj] = directions["upleft"];
        count += check_neighbor('M', i + uli, j + ulj, "upleft", puzzle);

        auto [uri, urj] = directions["upright"];
        count += check_neighbor('M', i + uri, j + urj, "upright", puzzle);

        auto [dli, dlj] = directions["downleft"];
        count += check_neighbor('M', i + dli, j + dlj, "downleft", puzzle);

        auto [dri, drj] = directions["downright"];
        count += check_neighbor('M', i + dri, j + drj, "downright", puzzle);
      }
    }
  }

  std::cout << "Xmas count: " << count << '\n';

  return 0;
}

std::vector<std::vector<char>> create_puzzle(const std::string filename)
{
  std::fstream file{PUZZLE_FILE};
  std::string line{};
  std::vector<std::vector<char>> puzzle{};
  if (file.is_open())
  {
    while(std::getline(file, line))
    {
      std::vector<char> row(line.begin(), line.end());
      puzzle.push_back(row);
    }
  }
  file.close();
  return puzzle;
}

bool in_bounds(int i, int j, int n)
{
  return i >= 0 && i < n && j >= 0 && j < n;
}

int check_neighbor(char letter, int i, int j, std::string direction, std::vector<std::vector<char>>& puzzle)
{
  if (in_bounds(i, j, puzzle.size()))
  {

    char l = puzzle[i][j];


    if (letter == l)
    {
      auto [x, y] = directions[direction];
      int new_i = i + x;
      int new_j = j + y;


      if (l == 'M')
      {
        return check_neighbor('A', new_i, new_j, direction, puzzle);
      }
      if (l == 'A')
      {
        return check_neighbor('S', new_i, new_j, direction, puzzle);
      }
      if (l == 'S')
      {
        return 1;
      }

      return 0;   

    }
  }

  return 0;
}
