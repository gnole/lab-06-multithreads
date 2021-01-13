
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <mutex>
#include <boost/regex.hpp>
#include <boost/log/trivial.hpp>
#include <vector>
#include <hash_data.h>
#include <nlohmann/json.hpp>

class HashResearcher {
  unsigned int numberOfThreads;
  nlohmann::json jsonData;
  std::mutex sync;
  void one_process();
  boost::regex hash_format;
 public:
  void start_research();
  explicit HashResearcher(unsigned int& n,
                          const boost::regex& hm)
      : numberOfThreads(n), hash_format(hm) {};
};

#endif // INCLUDE_HEADER_HPP_
