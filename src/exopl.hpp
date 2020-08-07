
#include <string>
#include "ysapi.hpp"

namespace exopl {
  void op_list(ysapi api);
  void op_filter(ysapi api, std::string expr);
  void op_select(ysapi api, std::string expr);
  void op_as_txt(ysapi api);
  void op_as_csv(ysapi api);
}
