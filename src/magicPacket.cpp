#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>

namespace {
  class handleSocket {
    public:
      explicit handleSocket(int socketDesc) : _socketDesc(socketDesc) {
        if (_socketDesc < 0) throw std::runtime_error("Не получилось открыть сокет!");
      }

      handleSocket(const handleSocket&) = delete;
      handleSocket& operator=(const handleSocket&) = delete;

      int getSocketDesc() {
        return _socketDesc;
      }

      ~handleSocket() {
        close(_socketDesc);
      }

    private:
      const int _socketDesc;
  };

  unsigned intFromHexString(const std::string& string) {
    unsigned hex = 0;

    for (size_t i = 0; i < string.length(); i++) {
      hex <<= 4;
      if (isdigit(string[i])) {
        hex |= string[i] - '0';
      } else if (string[i] >= 'a' && string[i] <= 'f') {
        hex |= string[i] - 'a' + 10;
      } else if (string[i] >= 'A' && string[i] <= 'F') {
        hex |= string[i] - 'A' + 10;
      } else {
        throw std::runtime_error("Не получилось спарсить hex!");
      }
    }

    return hex;
  }

  std::string hexStringToByteString(const std::string& hardwareAddr) {
    std::string ethernetAddr;

    for (size_t i = 0; i < hardwareAddr.length(); i++) {
      unsigned hex = intFromHexString(hardwareAddr.substr(i, 2));
      i += 2;

      ethernetAddr += static_cast<char>(hex & 0xFF);

      if (hardwareAddr[i] == ':') {
        ++i;
      }
    }

    return ethernetAddr;
  }

  void test() {
    std::string hardwareAddr = "18:C0:4D:0B:60:4A";
    std::string test = hexStringToByteString(hardwareAddr);
    std::cout << test << std::endl;
  }
}

int main() {
  test();
  return 0;
}
