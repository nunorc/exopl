
#include <iostream>

#include <json/json.h>
#include "exoplanet.hpp"

exoplanet::exoplanet(std::string id, Json::Value root) {
  pl_id = id;

  for (std::string p : PARAMS)
    params[p] = root[p].asString();
}

bool _select(std::vector<std::string> select, std::string param) {
  if (select.empty())
    return true;

  for(auto s : select) {
    if (s.compare(param) == 0)
      return true;
  }

  return false;
}

std::string exoplanet::as_txt(std::vector<std::string> select) {
  std::string txt = "";

  for (std::string p : PARAMS)
    if (_select(select, p))
      txt = txt + p + ": " + params[p] + "\n";

  txt = txt + "\n";

  return txt;
}

std::string exoplanet::as_csv(std::vector<std::string> select) {
  std::string csv = pl_id;

  for (std::string p : PARAMS)
    if (_select(select, p))
      csv = csv + "," + params[p];

  csv = csv + "\n";

  return csv;
}

bool exoplanet::check(std::string param, std::string op, std::string val) {
  if (params[param].empty())
    return false;

  float p = std::stof(params[param]), v = std::stof(val);

  if (op.compare(">") == 0) {
    if (p > v)
      return true;
    else
      return false;
  }
  if (op.compare("<") == 0) {
    if (p < v)
      return true;
    else
      return false;
  }
  if (op.compare("=") == 0) {
    if (p == v)
      return true;
    else
      return false;
  }

  std::cerr << "Failed to compare expression." << std::endl;
  return false;
}
