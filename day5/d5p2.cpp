#include<iostream>
#include<algorithm>
#include<numeric>
#include<vector>
#include<fstream>
#include<sstream>
#include<limits>
#include<map>
#include<unordered_set>

const int ORDERINGS{1176};
const int LINES{1178};
const std::string FILENAME{"ordering.txt"};

std::fstream& go_to_line(std::fstream& file, unsigned int line_No);
bool in_order(const std::vector<int>&update, std::map<int, std::vector<int>>& successors);
std::vector<int> toposort(std::vector<int>& v, std::map<int, std::vector<int>>& adj);
void dfs(int v, std::vector<int>& update, std::map<int, std::vector<int>>& adj, std::unordered_set<int>& visited, std::vector<int>& ans);

int main()
{
  std::vector<std::vector<int>> updates;
  std::map<int, std::vector<int>> successors;
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
        successors[x].push_back(y);
      } else {
        successors.insert(std::make_pair(x, std::vector<int>{y}));
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

  auto new_beg = std::remove_if(updates.begin(), updates.end(), [&](std::vector<int>& update) { return in_order(update, successors); });

  updates.erase(new_beg, updates.end());

  std::vector<std::vector<int>>sorted_updates;

  for (auto update : updates)
  {
    auto u = toposort(update, successors);
    sorted_updates.push_back(u);
  }

  int sum_of_mids = std::accumulate(sorted_updates.begin(), sorted_updates.end(), 0, [](int sum, std::vector<int>& update){
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

bool in_order(const std::vector<int>&update, std::map<int, std::vector<int>>& successors)
{
  std::unordered_set<int> seen;

  for (auto& num : update)
  {
    std::vector<int>& successor = successors[num];
    
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

std::vector<int> toposort(std::vector<int>& v, std::map<int, std::vector<int>>& adj)
{
  std::unordered_set<int>visited;
  std::vector<int> ans;

  for (int i : v)
  {
    if (!visited.contains(i))
    {
      dfs(i, v, adj, visited, ans);
    }
  }
  std::reverse(ans.begin(), ans.end());
  return ans;
}

void dfs(int v, std::vector<int>& update, std::map<int, std::vector<int>>& adj, std::unordered_set<int>& visited, std::vector<int>& ans)
{
  visited.insert(v);
  for (int i : adj[v])
  {
    auto found = std::find(update.begin(), update.end(), i) != update.end();
    if (found && !visited.contains(i))
    {
      dfs(i, update, adj, visited, ans);
    }
  }
  ans.push_back(v);
}
