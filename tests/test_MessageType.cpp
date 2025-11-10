#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include "MessageType.h"

using namespace messaging;

TEST(MessageTypeTest, ToStringBasics) {
EXPECT_EQ(ToString(MessageType::System), "system");
EXPECT_EQ(ToString(MessageType::Server), "server");
EXPECT_EQ(ToString(MessageType::Session), "session");
}


TEST(MessageTypeTest, FromStringBasics) {
MessageType t{};
EXPECT_TRUE(FromString("system", t)); EXPECT_EQ(t, MessageType::System);
EXPECT_TRUE(FromString("server", t)); EXPECT_EQ(t, MessageType::Server);
EXPECT_TRUE(FromString("session", t)); EXPECT_EQ(t, MessageType::Session);
}


TEST(MessageTypeTest, CaseInsensitivityAndTrim) {
MessageType t{};
EXPECT_TRUE(FromString(" SyStEm ", t)); EXPECT_EQ(t, MessageType::System);
EXPECT_TRUE(FromString("\tSERVER\n", t)); EXPECT_EQ(t, MessageType::Server);
EXPECT_TRUE(FromString(" Session ", t)); EXPECT_EQ(t, MessageType::Session);
}


TEST(MessageTypeTest, InvalidInput) {
MessageType t{};
EXPECT_FALSE(FromString("", t));
EXPECT_FALSE(FromString("unknown", t));
EXPECT_FALSE(FromString("sys tem", t));
}


TEST(MessageTypeTest, SerializeDeserializeRoundtrip) {
const std::vector<MessageType> all{ MessageType::System, MessageType::Server, MessageType::Session };
for (auto v : all) {
std::string s = Serialize(v);
MessageType parsed{};
EXPECT_TRUE(Deserialize(s, parsed));
EXPECT_EQ(parsed, v);
}
}


TEST(MessageTypeTest, StreamOperators) {
std::ostringstream oss;
oss << MessageType::System;
EXPECT_EQ(oss.str(), "system");


std::istringstream iss("server\nsession");
MessageType a{}, b{};
iss >> a >> b;
EXPECT_EQ(a, MessageType::Server);
EXPECT_EQ(b, MessageType::Session);


std::istringstream badiss("badtoken");
MessageType t{};
badiss >> t;
EXPECT_FALSE(badiss.good());
}


int main(int argc, char** argv) {
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}
