#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<boost/algorithm/string/classification.hpp>
#include<boost/algorithm/string/split.hpp>


bool is_safe(std::vector<int>);

auto main() -> int
{
  std::fstream file("reports");
  std::string line{};

  int safe_reports{};

  if (file.is_open())
  {
    while(std::getline(file, line))
    {
      std::vector<std::string> raw_report{};

      boost::split(raw_report, line, boost::is_any_of(" "), boost::token_compress_on);

      std::vector<int> report(raw_report.size());

      std::transform(raw_report.begin(), raw_report.end(), report.begin(), [&](auto n){ return std::stoi(n); });


      if (is_safe(report))
      {
        safe_reports++;
      }
    }

  }

  file.close();

  std::cout << "Safe reports: " << safe_reports << '\n';

  return 0;
}

auto is_safe(std::vector<int> report) -> bool
{
  bool inc{};
  int fixed{};

  if(report[1] > report[0])
  {
    inc = true;
  } 

  for(int i = 0; i < report.size() - 1; i++)
  {
    int diff = report[i] - report[i + 1];
    if ((inc && diff >= 0) || diff < -3)
    {
      if (fixed)
      {
        return false;
      }
      fixed++;
    } 

    if (!inc && diff <= 0 || diff > 3)
    {
      if (fixed)
      {
        return false;
      }
      fixed++;
    }
  }

  return true;
}
