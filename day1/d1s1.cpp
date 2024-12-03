#include<vector>
#include<unordered_map>
#include<iostream>
#include<fstream>
#include<string>
#include<boost/algorithm/string/classification.hpp>
#include<boost/algorithm/string/split.hpp>

auto main() -> int
{
  int dist{};
  long simularity{};

  std::vector<int> left{};
  std::vector<int> right{};

  std::unordered_map<int, int> freq{};

  std::string line{};

  std::ifstream file("input");

  if (file.is_open())
  {
    while(std::getline(file, line))
    {
      std::vector<std::string> nums{};
      boost::split(nums, line, boost::is_any_of(" "), boost::token_compress_on);  
      left.push_back(std::stoi(nums[0]));
      right.push_back(std::stoi(nums[1]));
    }
  }

  file.close();

  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());

  for(auto lit = left.begin(), rit = right.begin(); lit != left.end() && rit != right.end(); lit++, rit++)
  {
    dist += std::abs(*lit - *rit);
  }

  std::cout << "Part 1 - Total distance: " << dist << '\n';


  for (auto num : left)
  {
    if (!freq.contains(num))
    {
      freq.insert(std::make_pair(num, 0));
    }
  } 

  for (auto num : right)
  {
    if (freq.contains(num))
    {
      freq[num] += 1;
    }
  }

  for (auto const& [key, val] : freq)
  {
    simularity += (key * val);
  }

  std::cout << "Part 2 - Simularity score: " << simularity << '\n';

  return 0;
}
