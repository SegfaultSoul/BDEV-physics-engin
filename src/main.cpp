#include "Renderer.hpp"
#include <iostream>

int main(){
  Renderer r(640, 440, "BDEV Physics Engin");
  r.run();

  std::cout << "Process Terminated..." << "\n";
  return 0;
}
