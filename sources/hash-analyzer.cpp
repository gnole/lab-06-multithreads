#include <hash-analyzer.hpp>
#include <vector>
#include <thread>
#include <../third-party/PicoSHA2/picosha2.h>
#include <mutex>
#include <iostream>
#include <boost/log/trivial.hpp>
#include <hash_data.h>
#include <nlohmann/json.hpp>
#include <chrono>

using nlohmann::json;

void to_json(json& json_, const Data& jData) {
  json_ = {{"time", jData.timeStamp},
           {"hash", jData.hash},
           {"data", jData.argument}};
}

[[noreturn]] void HashResearcher::one_process() {
  while (true) {
    const std::string random_data = std::to_string(rand());
    const std::string hash =
        picosha2::hash256_hex_string(random_data);
    if (boost::regex_match(hash, hash_format)) {
      sync.lock();
      Data oneHashData(hash, random_data, 1);
      jsonData.push_back(oneHashData);
      BOOST_LOG_TRIVIAL(info) << "Thread id: " << std::this_thread::get_id();
      BOOST_LOG_TRIVIAL(info) << "Successful match: " << hash;
      BOOST_LOG_TRIVIAL(info) << "With data: " << random_data << std::endl;
      BOOST_LOG_TRIVIAL(info) << "In time: " <<
          std::chrono::system_clock::now().time_since_epoch().count();
      BOOST_LOG_TRIVIAL(info) << std::endl;
      sync.unlock();
    }
  }
}

void HashResearcher::start_research() {
  std::vector<std::thread> threads;
  threads.reserve(numberOfThreads);
  unsigned int startedThreads(0);
  while (startedThreads < numberOfThreads) {
    threads.emplace_back(&HashResearcher::one_process, this);
    startedThreads++;
  }
  for (std::thread& th : threads) {
    th.join();
  }
}
