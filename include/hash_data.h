#ifndef HASH_ANALYZER_PRJ_HASH_DATA_H
#define HASH_ANALYZER_PRJ_HASH_DATA_H

#include <iostream>

struct Data {
  std::string hash;
  std::string argument;
  std::size_t timeStamp;
  Data(const std::string& s1,
       const std::string& s2,
       const std::size_t& thId) : hash(s1),
                           argument(s2),
                           timeStamp(thId) {};
};

#endif  // HASH_ANALYZER_PRJ_HASH_DATA_H
