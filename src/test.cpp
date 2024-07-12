#include "Utility.hpp"

int main() {
  Utility utility;

  const char* macAddress = "18:C0:4D:0B:60:4A";
  utility.sendMagicPacket(macAddress);
  return 0;
}
