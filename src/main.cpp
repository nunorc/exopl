
#include <stdio.h>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json/json.h>

#include "ysapi.hpp"
#include "exopl.hpp"

static void show_usage() {
  std::cerr << "\nUsage: exopl <command> [expr]\n\n"
            << "Commands:\n" 
            << " list\t  list all exoplanets\n"
            << " filter\t  filter exoplanets based on a given expreesion\n"
            << " select\t  select parameters when exporting based on a given expression\n"
            << " as_txt\t  print as text\n"
            << " as_csv\t  print as CSV\n\n";
}

int main(int argc, char *argv[]) {
  ysapi api("http://api.y-space.pw");
  std::string op = "", expr = "";

  if (argc < 2) {
    show_usage();
    return 1;
  }

  op = argv[1];

  if (argc > 2)
    expr = argv[2];

  if (op.compare("list") == 0) {
    exopl::op_list(api);
  }
  else if (op.compare("filter") == 0) {
    exopl::op_filter(api, expr);
  }
  else if (op.compare("select") == 0) {
    exopl::op_select(api, expr);
  }
  else if (op.compare("as_txt") == 0) {
    exopl::op_as_txt(api);
  }
  else if (op.compare("as_csv") == 0) {
    exopl::op_as_csv(api);
  }
  else {
    show_usage();
    return 1;
  }

  return 0;
}
