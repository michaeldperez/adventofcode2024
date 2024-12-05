#include<iostream>
#include<string>
#include<regex>
#include<iterator>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<functional>
#include<numeric>
#include<boost/regex.hpp>

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
  std::regex mul{"(mul\\(\\d+,\\d+\\))"};
  std::regex comma_re{","};

 // boost::regex remove_between("(?<=don't\\(\\))(.*?)(?=do\\(\\))");
//  boost::regex remove_end("(?<=don't\\(\\))(.*?)(?=!do\\(\\))");
//  boost::regex remove_end("(?<=don't\\(\\))(.*?)(?=[^do\\(\\)])$");

  std::string line{};
  std::fstream file{"instructions"};

  if (file.is_open())
  {
    
    while (std::getline(file, line))
    { 
//      line = boost::regex_replace(line, remove_between, "#####", boost::match_extra);
  //    std::cout << "line: " << line << '\n';

  //    std::cout << '\n';

 //     line = boost::regex_replace(line, remove_end, "#####", boost::match_extra);

  //    std::cout << "line: " << line << '\n';

      auto instructions_begin = std::sregex_iterator(line.begin(), line.end(), mul);

      auto instructions_end = std::sregex_iterator();

      for (std::sregex_iterator i = instructions_begin; i != instructions_end; i++)
      {
        std::vector<int> nums{};
        std::smatch match = *i;
        std::string match_str = match.str();
        std::cout << "Match: " << match_str << '\n';
        match_str = std::regex_replace(match_str, comma_re, " ");

        not_digit not_a_digit;

        std::string::iterator end = std::remove_if(match_str.begin(), match_str.end(), not_a_digit);

        std::string only_numbers(match_str.begin(), end);

        std::stringstream sstr(only_numbers);

        for (int i = 0; sstr >> i;)
        {
          nums.push_back(i);
        }

        sum_of_multiplies += std::accumulate(nums.begin(), nums.end(), 1, std::multiplies<int>());
      }
    }
  }

  file.close();

  std::cout << "sum of multiplies: " << sum_of_multiplies << '\n';

  return 0;
}
