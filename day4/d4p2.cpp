#include<iostream>
#include<fstream>
#include<string>
#include<vector>

const std::string PUZZLE_FILE{"word_search"};

std::vector<std::vector<char>> create_puzzle(const std::string filename);
bool in_bounds(int i, int j, int n);
int check_cross(int i, int j, const std::vector<std::vector<char>>& puzzle);

auto main() -> int
{
  int count{};
  std::vector<std::vector<char>> puzzle = create_puzzle(PUZZLE_FILE);
  int n = static_cast<int>(puzzle.size());

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (puzzle[i][j] == 'A')
      {
        count += check_cross(i, j, puzzle);      
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

int check_cross(int i, int j, const std::vector<std::vector<char>>& puzzle)
{

  int n = puzzle.size();

  if (in_bounds(i-1, j-1, n) && in_bounds(i-1, j+1, n) && in_bounds(i+1, j-1, n) && in_bounds(i+1, j+1, n))
  {
    char top_left = puzzle[i-1][j-1];
    char top_right = puzzle[i-1][j+1];
    char bottom_left = puzzle[i+1][j-1];
    char bottom_right = puzzle[i+1][j+1];

    if (((top_left == 'M' && bottom_right == 'S') || (top_left == 'S' && bottom_right == 'M')) && ((top_right == 'M' && bottom_left == 'S') || (top_right == 'S' && bottom_left == 'M')))
    {
      return 1;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

