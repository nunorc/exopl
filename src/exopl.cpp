
#include <stdio.h>
#include <iostream>
#include <string>
#include <regex>
#include <sstream>

#include <curl/curl.h>
#include <json/json.h>

#include "exoplanet.hpp"
#include "exopl.hpp"

#define FMT_TXT 0
#define FMT_CSV 1

void exopl::op_list(ysapi api) {
  Json::Value root = api.list();

  for (unsigned int i=0; i < root.size(); ++i )
    std::cout << root[i].asString() << std::endl;
}

void exopl::op_filter(ysapi api, std::string expr) {
  std::string pl_id;
  Json::Value root;
  std::regex regexp("^([a-z_]+)(.)(.*?)$");
  std::smatch m;

  for (std::string pl_id; std::getline(std::cin, pl_id); ) {
    root = api.id(pl_id);
    exoplanet pl(pl_id, root);

    if (expr.empty()) {
      std::cout << pl_id << std::endl;
    }
    else {
      regex_search(expr, m, regexp);

      if (pl.check(m[1], m[2], m[3]))
        std::cout << pl_id << std::endl;
    }
  }
}

void exopl::op_select(ysapi api, std::string expr) {
  std::string pl_id;

  std::cout << "##SELECT:" << expr << std::endl;

  for (std::string pl_id; std::getline(std::cin, pl_id); ) {
    std::cout << pl_id << std::endl;
  }
}

std::vector<std::string> _pre_proc_select(std::string line) {
  std::vector<std::string> select;

  line.replace(0, 9, "");
  std::stringstream s_stream(line);
  while(s_stream.good()) {
    std::string substr;
    getline(s_stream, substr, ',');
    select.push_back(substr);
  }

  return select;
}

void _pp(ysapi api, int format) {
  std::string line, pl_id;
  Json::Value root;
  std::vector<std::string> select;

  for (std::string line; std::getline(std::cin, line); ) {
    if (line.find("##SELECT:") == 0) {
      select = _pre_proc_select(line);
    }
    else {
      pl_id = line;

      root = api.id(pl_id);
      exoplanet pl(pl_id, root);


      if (format == FMT_TXT)
        std::cout << pl.as_txt(select);
      if (format == FMT_CSV)
        std::cout << pl.as_csv(select);
    }
  }
}

void exopl::op_as_txt(ysapi api) {
  _pp(api, FMT_TXT);
}

void exopl::op_as_csv(ysapi api) {
  _pp(api, FMT_CSV);
}
