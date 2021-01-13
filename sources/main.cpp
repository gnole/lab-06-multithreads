#include <iostream>
#include <thread>
#include <cstring>
#include <csignal>
#include <hash-analyzer.hpp>
#include <boost/regex.hpp>

#include <boost/log/sinks.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/program_options.hpp>

void signalHandler(int) {
  std::cout << "Stop the program" << std::endl;
  exit(2);
}

void init() {
  auto sinkFile = boost::log::add_file_log(
      boost::log::keywords::file_name = "research_%5N.log",
      boost::log::keywords::rotation_size = 5 * 1024 * 1024,
      boost::log::keywords::format = "[%TimeStamp%]: %Message%");
  sinkFile->set_filter(
      boost::log::trivial::severity >= boost::log::trivial::trace);
  auto sinkConsole = boost::log::add_console_log(
      std::cout,
      boost::log::keywords::format = "[%TimeStamp%]: %Message%");
  sinkConsole->set_filter(
      boost::log::trivial::severity >= boost::log::trivial::info);
  boost::log::add_common_attributes();
  signal(SIGINT, signalHandler);
}

int main(int argc, char* argv[]) {
  init();
  std::srand(time(nullptr));
  unsigned int threads_number;
  try {
    if (argc == 2)
      threads_number = atoi(argv[1]);
    else
      threads_number = std::thread::hardware_concurrency();
    HashResearcher hashResearcher(threads_number,
                                  boost::regex("^([a-z]|[A-Z]|[0-9]){60}0000$"));
    hashResearcher.start_research();
  }
  catch (std::exception& ex) {
    std::cerr << ex.what();
  }
}