#include "MessageType.h"
#include <algorithm>
#include <cctype>
#include <istream>
#include <ostream>


namespace messaging {
namespace {
  inline void TrimInPlace(std::string& s) {
  auto not_space = [](unsigned char ch) { return !std::isspace(ch); };
  auto it_begin = std::find_if(s.begin(), s.end(), not_space);
  auto it_end = std::find_if(s.rbegin(), s.rend(), not_space).base();
  if (it_begin >= it_end) { s.clear(); return; }
  s.assign(it_begin, it_end);
  }


  inline std::string ToLowerCopy(std::string_view sv) {
  std::string out(sv.begin(), sv.end());
  for (char& ch : out) {
  ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
  }
  return out;
  }
} // namespace


  constexpr std::string ToString(MessageType type) noexcept {
  switch (type) {
  case MessageType::System: return "system";
  case MessageType::Server: return "server";
  case MessageType::Session: return "session";
  default: return "";
  }
  }


  bool FromString(std::string_view text, MessageType& out) noexcept {
  std::string work = ToLowerCopy(text);
  TrimInPlace(work);
  
  if (work == "system") { out = MessageType::System; return true; }
  if (work == "server") { out = MessageType::Server; return true; }
  if (work == "session") { out = MessageType::Session; return true; }
  return false;
  }


  std::ostream& operator<<(std::ostream& os, MessageType type) {
  os << ToString(type);
  return os;
  }
  
  std::istream& operator>>(std::istream& is, MessageType& type) {
  std::string token;
  is >> token;
  if (!is) return is;


  MessageType tmp{};
  if (FromString(token, tmp)) {
  type = tmp;
  } else {
  is.setstate(std::ios::failbit);
  }
  return is;
  }

} // namespace messaging
