#pragma once
#include <iostream>

#define DEBUG(X) std::cout << (#X) << " -> " << (X) << std::endl

#define LOG(X) std::cout << (#X) << std::endl; (X)

#define RUN(X) std::cout << "================================" << std::endl \
  << "---- " << (#X) << " ----" << std::endl; \
  (X); \
  std::cout << "================================" << std::endl << std::endl
