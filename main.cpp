#include "budget.h"
#include "test_runner.h"
#include <iostream>
#include <iomanip>

int main() {
  //
  BudgetManager b(std::cin);
  auto res = b.Process();
  std::cout.precision(25);
  for (const auto& elem : res) {
    std::cout << elem << std::endl;
  }
  return 0;
}