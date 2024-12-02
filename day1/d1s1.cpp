#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<boost/algorithm/string/classification.hpp>
#include<boost/algorithm/string/split.hpp>

auto main() -> int
{
  int dist{};
  std::vector<int> left{};
  std::vector<int> right{};

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

  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());

  for(auto lit = left.begin(), rit = right.begin(); lit != left.end() && rit != right.end(); lit++, rit++)
  {
    dist += std::abs(*lit - *rit);
  }

  std::cout << "Total distance: " << dist << '\n';

  file.close();

  return 0;
}
