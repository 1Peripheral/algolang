#include "../include/logger.h"

Logger::Logger() {}

void Logger::log(const std::string msg) {
   std::cout << "[LOG] " << msg << std::endl;
}

void Logger::info(const std::string msg) {
   std::cout << "[INFO] " << msg << std::endl;
}

void Logger::debug(const std::string msg) {
   std::cout << GREEN << "[DEBUG] " << msg << RESET << std::endl;
}

void Logger::warning(const std::string msg) {
   std::cout << YELLOW << "[WARNING] " << msg << RESET << std::endl;
}

void Logger::error(const std::string msg) {
   std::cerr << RED << "[ERROR] " << msg << RESET << std::endl;
}

void Logger::panic(const std::string msg) {
   std::cerr << RED << "[ERROR] " << msg << RESET << std::endl;
   exit(1);
}
