#include<iostream>
#include<algorithm>
#include<numeric>
#include<vector>
#include<fstream>
#include<sstream>
#include<limits>
#include<unordered_map>
#include<unordered_set>

const int ORDERINGS{1176};
const int LINES{1178};
const std::string FILENAME{"ordering.txt"};

std::fstream& go_to_line(std::fstream& file, unsigned int line_No);
bool in_order(const std::vector<int>&update, std::unordered_map<int, std::unordered_set<int>>& successors);

int main()
{
  std::vector<std::vector<int>> updates;
  std::unordered_map<int, std::unordered_set<int>> successors;
  std::fstream file{FILENAME};
  std::string line;


  if (file.is_open())
  {
    for (int i = 0; i < ORDERINGS; i++)
    {
      int x, y;
      getline(file, line);
      sscanf(line.c_str(), "%d|%d", &x, &y);

      if (successors.contains(x))
      {
        successors[x].insert(y);
      } else {
        successors.insert(std::make_pair(x, std::unordered_set<int>{y}));
      }
    } 
  }

  go_to_line(file, LINES);

  while (getline(file, line))
  {
    std::replace(line.begin(), line.end(), ',', ' ');
    std::stringstream ss(line);
    std::vector<int> update;

    for (int i = 0; ss >> i;)
    {
      update.push_back(i);
    }

    updates.push_back(update);
  }

  auto new_beg = std::remove_if(updates.begin(), updates.end(), [&](std::vector<int>& update) { return !in_order(update, successors); });

  updates.erase(new_beg, updates.end());

  int sum_of_mids = std::accumulate(updates.begin(), updates.end(), 0, [](int sum, std::vector<int>&update){
     auto mid = update.begin() + update.size() / 2;
     return sum + *mid;
  });

  std::cout << "Sum of middle values: " << sum_of_mids << '\n';
}

std::fstream& go_to_line(std::fstream& file, unsigned int line_no)
{
  constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

  file.seekg(std::ios::beg);

  for (int i = 0; i < line_no - 1; i++)
  {
    file.ignore(max_size, '\n');
  }

  return file;
}

bool in_order(const std::vector<int>&update, std::unordered_map<int, std::unordered_set<int>>& successors)
{
  std::unordered_set<int> seen;

  for (auto& num : update)
  {
    std::unordered_set<int>& successor = successors[num];
    
    for (auto& n : successor)
    {
      if (!seen.empty() && seen.contains(n))
      {
        return false;
      }
    }
    seen.insert(num);
  }
  return true;
}
