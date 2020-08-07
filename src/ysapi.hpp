
#ifndef YSAPI_H
#define YSAPI_H

#include <string>
#include <curl/curl.h>
#include <json/json.h>

class ysapi {
  std::string base_url;

  public:
    ysapi(std::string url);
    Json::Value list();
    Json::Value id(const std::string pl_id);
  private:
  	static std::size_t write_callback(const char *in, std::size_t size, std::size_t num, void *out);
  	Json::Value get_data(const std::string url);
};

#endif
