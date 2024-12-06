#include<iostream>
#include<string>
#include<regex>
#include<iterator>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<functional>
#include<numeric>

struct not_digit
{
  bool operator()(const char c)
  {
    return c != ' ' && !std::isdigit(c);
  }
};

auto main() -> int
{
  int sum_of_multiplies{};

  std::regex mul{"(mul\\(\\d{1,3},\\d{1,3}\\))"};
  std::regex comma_re{","};

  std::string line{};

  std::fstream file{"instructions"};

  if (file.is_open())
  {
    while (std::getline(file, line))
    { 
      std::string::size_type dont_pos{};

      while (dont_pos != std::string::npos)
      {
        std::string::size_type do_pos;
        
        dont_pos = line.find("don't()");

        if (dont_pos != std::string::npos)
        {
          do_pos = line.find("do()", dont_pos);

          if (do_pos != std::string::npos)
          {
            line.erase(dont_pos, do_pos - dont_pos); 
          } else {
            line.erase(dont_pos);
          }
        } 
      }

      auto instructions_begin = std::sregex_iterator(line.begin(), line.end(), mul);

      auto instructions_end = std::sregex_iterator();

      for (std::sregex_iterator i = instructions_begin; i != instructions_end; i++)
      {
        std::vector<int> nums{};
        std::smatch match = *i;
        std::string match_str = match.str();
        match_str = std::regex_replace(match_str, comma_re, " ");

        not_digit not_a_digit;

        std::string::iterator end = std::remove_if(match_str.begin(), match_str.end(), not_a_digit);

        std::string only_numbers(match_str.begin(), end);

        std::stringstream sstr(only_numbers);

        for (int i = 0; sstr >> i;)
        {
          nums.push_back(i);
        }

        sum_of_multiplies += nums[0] * nums[1];
      }
    }
  }

  file.close();

  std::cout << "sum of multiplies: " << sum_of_multiplies << '\n';

  return 0;
}
