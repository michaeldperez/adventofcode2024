#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

const std::string PUZZLE_FILE{"word_search"};

void print_puzzle(const std::vector<std::vector<char>> puzzle);
int count_xmas(const std::vector<char>& s);
int count_xmas_diag_right(const std::vector<std::vector<char>>& puzzle);
int count_xmas_diag_left(const std::vector<std::vector<char>>& puzzle);
int count_xmas_diag_right_up(const std::vector<std::vector<char>>& puzzle);
int count_xmas_diag_left_up(const std::vector<std::vector<char>>& puzzle);
std::vector<char> create_column(int col, const std::vector<std::vector<char>>& puzzle);
std::vector<std::vector<char>> create_puzzle(const std::string filename);
std::vector<std::vector<char>> reverse_puzzle_rows(const std::vector<std::vector<char>>& puzzle);
std::vector<std::vector<char>> reverse_puzzle(const std::vector<std::vector<char>>& puzzle);

auto main() -> int
{
  int count{};
  std::vector<std::vector<char>> puzzle = create_puzzle(PUZZLE_FILE);

  int n = static_cast<int>(puzzle.size());

  for (int i = 0; i < n; i++)
  {
    // check rows
    std::vector<char> row = puzzle[i];
    count += count_xmas(row);
    std::reverse(row.begin(), row.end()); 
    count += count_xmas(row);

    // check columns
    std::vector<char> col = create_column(i, puzzle);
    count += count_xmas(col);
    std::reverse(col.begin(), col.end());
    count += count_xmas(col);
  }

  // count diagonal down and to the right
  count += count_xmas_diag_right(puzzle);
  count += count_xmas_diag_left(puzzle);
  count += count_xmas_diag_right_up(puzzle);
  count += count_xmas_diag_left_up(puzzle);

  //std::vector<std::vector<char>> rev_puzzle_rows = reverse_puzzle_rows(puzzle);

  // reverse the content of the rows, and count down and to the right to simulate down and to the left
  //count += count_xmas_diag_right(rev_puzzle_rows);
  
  // reverse the puzzle so top row goes to bottom and bottom row goes to the top
  //std::vector<std::vector<char>> rev_puzzle = reverse_puzzle(puzzle);

  // count the diagonal down and the to right to simulate up and to the left
  //count += count_xmas_diag_right(rev_puzzle);

  // reverse the content of the rows and count down and to the right to simulate up and to the right
  //std::vector<std::vector<char>> rev_puzzle_rev_rows = reverse_puzzle_rows(rev_puzzle);

  //count += count_xmas_diag_right(rev_puzzle_rev_rows);

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

std::vector<char> create_column(int col, const std::vector<std::vector<char>>& puzzle)
{
  int n = static_cast<int> (puzzle.size());
  std::vector<char> column;
  column.reserve(n);
  for (int i = 0; i < n; i++)
  {
    column.push_back(puzzle[i][col]);
  }
  return column;
}

int count_xmas(const std::vector<char>& s)
{
  int count{};
  int n = static_cast<int>(s.size());

  for (int i = 0; i < n - 4; i++)
  {
    if (s[i] == 'X' && s[i+1] == 'M' && s[i+2] == 'A' && s[i+3] == 'S')
    {
      count++;
      i += 4; 
    }
  }
  return count;
}

int count_xmas_diag_right(const std::vector<std::vector<char>>& puzzle)
{
  int count{};
  int n = static_cast<int>(puzzle.size());

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (puzzle[i][j] == 'X')
      {
        if (i + 1 < n && j + 1 < n && puzzle[i+1][j+1] == 'M')
        {
          if (i + 2 < n && j + 2 < n && puzzle[i+2][j+2] == 'A')
          {
            if (i + 3 < n && j + 3 < n && puzzle[i+3][j+3] == 'S')
            {
              count++;
            }
          } 
        }
      }
    }
  }
  return count;
}

int count_xmas_diag_left(const std::vector<std::vector<char>>& puzzle)
{
  int count{};
  int n = static_cast<int>(puzzle.size());

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (puzzle[i][j] == 'X')
      {
        if (i + 1 < n && j - 1 >= 0 && puzzle[i+1][j-1] == 'M')
        {
          if (i + 2 < n && j - 2 >= 0 && puzzle[i+2][j-2] == 'A')
          {
            if (i + 3 < n && j - 3 >= 0 && puzzle[i+3][j-3] == 'S')
            {
              count++;
            }
          } 
        }
      }
    }
  }
  return count;
}

int count_xmas_diag_right_up(const std::vector<std::vector<char>>& puzzle)
{
  int count{};
  int n = static_cast<int>(puzzle.size());

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (puzzle[i][j] == 'X')
      {
        if (i - 1 >= 0 && j + 1 < n && puzzle[i-1][j+1] == 'M')
        {
          if (i - 2 >= 0 && j + 2 < n && puzzle[i-2][j+2] == 'A')
          {
            if (i - 3 >= 0 && j + 3 < n && puzzle[i-3][j+3] == 'S')
            {
              count++;
            }
          } 
        }
      }
    }
  }
  return count;
}

int count_xmas_diag_left_up(const std::vector<std::vector<char>>& puzzle)
{
  int count{};
  int n = static_cast<int>(puzzle.size());

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (puzzle[i][j] == 'X')
      {
        if (i - 1 >= 0 && j - 1 >= 0 && puzzle[i-1][j-1] == 'M')
        {
          if (i - 2 >= 0 && j - 2 >= 0 && puzzle[i-2][j-2] == 'A')
          {
            if (i - 3 >= 0 && j - 3 >= 0 && puzzle[i-3][j-3] == 'S')
            {
              count++;
            }
          } 
        }
      }
    }
  }
  return count;
}

std::vector<std::vector<char>> reverse_puzzle_rows(const std::vector<std::vector<char>>& puzzle)
{
  std::vector<std::vector<char>> rev_puzzle;
  rev_puzzle.reserve(puzzle.size());
  for (auto row : puzzle)
  {
    std::reverse(row.begin(), row.end());
    rev_puzzle.push_back(row);
  }
  return rev_puzzle;
}

std::vector<std::vector<char>> reverse_puzzle(const std::vector<std::vector<char>>& puzzle)
{
  std::vector<std::vector<char>> rev_puzzle = puzzle;
  std::reverse(rev_puzzle.begin(), rev_puzzle.end());
  return rev_puzzle;
}


void print_puzzle(const std::vector<std::vector<char>> puzzle)
{
  for (auto& row : puzzle)
  {
    for (auto& ch : row)
    {
      std::cout << ch;
    }
    std::cout << '\n';
  }
}
