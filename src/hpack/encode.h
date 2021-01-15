#include <stdint.h>
#include <string>
#include <map>

namespace hpack {

std::string encode_uint16(int I, uint8_t mask);

// Pseudo headers and Normal headers should not be mixed in the Map
std::string encode_headers(const std::map<std::string, std::string> &headers);
std::string encode_headers(int status, const std::map<std::string, std::string> &headers);

}  // namespace hpack
