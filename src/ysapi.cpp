
#include <sstream>

#include "ysapi.hpp"

ysapi::ysapi(const std::string url) {
  base_url = url;
}

Json::Value ysapi::list() {
  return get_data(base_url + "/exoplanets/list");
}

Json::Value ysapi::id(const std::string pl_id) {
  return get_data(base_url + "/exoplanets/id/" + pl_id);
}

std::size_t ysapi::write_callback(const char *in, std::size_t size, std::size_t num, void *out) {
  std::string data(in, (std::size_t) size * num);
  *((std::stringstream*) out) << data;
  return size * num;  
}

Json::Value ysapi::get_data(const std::string url) {
  CURL *curl;
  CURLcode res;
  std::stringstream readBuffer;
  std::string errs;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    Json::Value root;
    Json::CharReaderBuilder reader;

    Json::parseFromStream(reader, readBuffer, &root, &errs);

    return root;
  }

  return Json::objectValue;
}
