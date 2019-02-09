#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <cassert>
#include <string>
#include <yal/manager.hpp>

class sink_mock : public yalog::sink {
 public:
  MOCK_METHOD1(print, void(const yalog::log_message&));
};

MATCHER_P(IsASCIIMessage, n, "") {
  std::string msg;
  std::transform(arg.message.begin(), arg.message.end(), std::back_inserter(msg),
                 [](uint8_t c) { return static_cast<char>(c); });
  return msg == n;
}

MATCHER_P(IsU8Message, n, "") {
  std::string msg;
  std::transform(arg.message.begin(), arg.message.end(), std::back_inserter(msg),
                 [](uint8_t c) { return static_cast<char>(c); });
  return msg == n;
}

MATCHER_P(IsU16Message, n, "") {
  std::u16string msg;
  assert(arg.message.size() % 2 == 0);
  for (std::size_t i = 0; i < arg.message.size(); i += 2) {
    char16_t out;
    out = arg.message[i] << 8;
    out |= arg.message[i + 1];
    msg.push_back(out);
  }
  return msg == n;
}

MATCHER_P(IsU32Message, n, "") {
  std::u32string msg;
  assert(arg.message.size() % 4 == 0);
  for (std::size_t i = 0; i < arg.message.size(); i += 4) {
    char32_t out;
    out = arg.message[i] << 24;
    out |= arg.message[i + 1] << 16;
    out |= arg.message[i + 2] << 8;
    out |= arg.message[i + 3];
    msg.push_back(out);
  }
  return msg == n;
}

MATCHER_P(IsWidecharMessage, n, "") {
  std::wstring msg;
#if defined(_WIN32) || defined(_WIN64)
  assert(arg.message.size() % 2 == 0);
  for (std::size_t i = 0; i < arg.message.size(); i += 2) {
    wchar_t out;
    out = arg.message[i] << 8;
    out |= arg.message[i + 1];
    msg.push_back(out);
  }
#else
  assert(arg.message.size() % 4 == 0);
  for (std::size_t i = 0; i < arg.message.size(); i += 4) {
    wchar_t out;
    out = arg.message[i] << 24;
    out |= arg.message[i + 1] << 16;
    out |= arg.message[i + 2] << 8;
    out |= arg.message[i + 3];
  }
#endif
  return msg == n;
}

TEST(Logger, LogLevelUsage) {
  using namespace std::chrono_literals;
  auto mock_obj = std::make_unique<testing::StrictMock<sink_mock>> ();
  testing::StrictMock<sink_mock>* hack = mock_obj.get();
  {
    yalog::yal_manager manager{};
    manager.add_new_logger("mock", std::move(mock_obj), yalog::log_level::WARNING);
    EXPECT_CALL(*hack, print(testing::_)).Times(2);
    manager("mock").debug() << "Hello";
    manager("mock").warn() << "Hello";
    manager("mock").error() << "Hello";
  }
  EXPECT_TRUE(::testing::Mock::VerifyAndClear(hack));
}

TEST(Logger, MultiLine) {
  yalog::yal_manager manager{};
  auto mock_obj = std::make_unique<testing::StrictMock<sink_mock>>();
  testing::StrictMock<sink_mock>* hack = mock_obj.get();

  manager.add_new_logger("mock", std::move(mock_obj), yalog::log_level::DEBUG);
  manager.set_default_logger("mock");

  EXPECT_CALL(*hack, print(IsASCIIMessage("Hi\n"))).Times(2);
  manager().debug().print("Hi\nHi\n");
  manager.flush_all();
}
TEST(Logger, WidecharStreamInterface) {
  yalog::yal_manager manager{};
  auto mock_obj = std::make_unique<testing::StrictMock<sink_mock>>();
  testing::StrictMock<sink_mock>* hack = mock_obj.get();

  manager.add_new_logger("mock", std::move(mock_obj), yalog::log_level::DEBUG);
  manager.set_default_logger("mock");

  EXPECT_CALL(*hack, print(IsWidecharMessage(L"\U0001F4A9Hello1\n"))).Times(1);
  manager().debug().println(L"\U0001F4A9Hello1");
  EXPECT_CALL(*hack, print(IsWidecharMessage(L"\U0001F4A9Hello2\n"))).Times(1);
  manager().warn().println(L"\U0001F4A9Hello2");
  EXPECT_CALL(*hack, print(IsWidecharMessage(L"\U0001F4A9Hello3\n"))).Times(1);
  manager().error().println(L"\U0001F4A9Hello3");

  EXPECT_CALL(*hack, print(IsWidecharMessage(L"\U0001F4A9Hello4\n"))).Times(1);
  manager().debug().print(L"\U0001F4A9Hello4\n");
  EXPECT_CALL(*hack, print(IsWidecharMessage(L"\U0001F4A9Hello5\n"))).Times(1);
  manager().warn().print(L"\U0001F4A9Hello5\n");
  EXPECT_CALL(*hack, print(IsWidecharMessage(L"\U0001F4A9Hello6\n"))).Times(1);
  manager().error().print(L"\U0001F4A9Hello6\n");

  EXPECT_CALL(*hack, print(IsWidecharMessage(L"\U0001F4A9Hello7\n"))).Times(1);
  manager().debug() << L"\U0001F4A9Hello7\n";
  EXPECT_CALL(*hack, print(IsWidecharMessage(L"\U0001F4A9Hello8\n"))).Times(1);
  manager().warn() << L"\U0001F4A9Hello8\n";
  EXPECT_CALL(*hack, print(IsWidecharMessage(L"\U0001F4A9Hello9\n"))).Times(1);
  manager().error() << L"\U0001F4A9Hello9\n";
  manager.flush();
  EXPECT_TRUE(::testing::Mock::VerifyAndClear(hack));
}
TEST(Logger, UTF32StreamInterface) {
  using namespace std::string_literals;
  yalog::yal_manager manager{};
  
  auto mock_obj = std::make_unique<testing::StrictMock<sink_mock>>();
  testing::StrictMock<sink_mock>* hack = mock_obj.get();


  manager.add_new_logger("mock", std::move(mock_obj), yalog::log_level::DEBUG);
  manager.set_default_logger("mock");
  EXPECT_CALL(*hack, print(IsU32Message(U"\U0001F4A9Hello1\n")));
  manager().debug().println(U"\U0001F4A9Hello1");
  EXPECT_CALL(*hack, print(IsU32Message(U"\U0001F4A9Hello2\n")));
  manager().warn().println(U"\U0001F4A9Hello2");
  EXPECT_CALL(*hack, print(IsU32Message(U"\U0001F4A9Hello3\n")));
  manager().error().println(U"\U0001F4A9Hello3");

  EXPECT_CALL(*hack, print(IsU32Message(U"\U0001F4A9Hello4\n")));
  manager().debug().print(U"\U0001F4A9Hello4\n");
  EXPECT_CALL(*hack, print(IsU32Message(U"\U0001F4A9Hello5\n")));
  manager().warn().print(U"\U0001F4A9Hello5\n");
  EXPECT_CALL(*hack, print(IsU32Message(U"\U0001F4A9Hello6\n")));
  manager().error().print(U"\U0001F4A9Hello6\n");

  EXPECT_CALL(*hack, print(IsU32Message(U"\U0001F4A9Hello7\n")));
  manager().debug() << U"\U0001F4A9Hello7\n";
  EXPECT_CALL(*hack, print(IsU32Message(U"\U0001F4A9Hello8\n")));
  manager().warn() << U"\U0001F4A9Hello8\n";
  EXPECT_CALL(*hack, print(IsU32Message(U"\U0001F4A9Hello9\n")));
  manager().error() << U"\U0001F4A9Hello9\n";
  manager.flush();
  EXPECT_TRUE(::testing::Mock::VerifyAndClear(hack));
}

TEST(Logger, UTF16StreamInterface) {
  using namespace std::string_literals;
  yalog::yal_manager manager{};
  auto mock_obj = std::make_unique<testing::StrictMock<sink_mock>>();
  testing::StrictMock<sink_mock>* hack = mock_obj.get();

  manager.add_new_logger("mock", std::move(mock_obj), yalog::log_level::DEBUG);
  manager.set_default_logger("mock");
  EXPECT_CALL(*hack, print(IsU16Message(u"\U0001F4A9Hello1\n")));
  manager().debug().println(u"\U0001F4A9Hello1");
  EXPECT_CALL(*hack, print(IsU16Message(u"\U0001F4A9Hello2\n")));
  manager().warn().println(u"\U0001F4A9Hello2");
  EXPECT_CALL(*hack, print(IsU16Message(u"\U0001F4A9Hello3\n")));
  manager().error().println(u"\U0001F4A9Hello3");

  EXPECT_CALL(*hack, print(IsU16Message(u"\U0001F4A9Hello4\n")));
  manager().debug().print(u"\U0001F4A9Hello4\n");
  EXPECT_CALL(*hack, print(IsU16Message(u"\U0001F4A9Hello5\n")));
  manager().warn().print(u"\U0001F4A9Hello5\n");
  EXPECT_CALL(*hack, print(IsU16Message(u"\U0001F4A9Hello6\n")));
  manager().error().print(u"\U0001F4A9Hello6\n");

  EXPECT_CALL(*hack, print(IsU16Message(u"\U0001F4A9Hello7\n")));
  manager().debug() << u"\U0001F4A9Hello7\n";
  EXPECT_CALL(*hack, print(IsU16Message(u"\U0001F4A9Hello8\n")));
  manager().warn() << u"\U0001F4A9Hello8\n";
  EXPECT_CALL(*hack, print(IsU16Message(u"\U0001F4A9Hello9\n")));
  manager().error() << u"\U0001F4A9Hello9\n";
  manager.flush();
  EXPECT_TRUE(::testing::Mock::VerifyAndClear(hack));
}

TEST(Logger, UTF8StreamInterface) {
  using namespace std::string_literals;
  yalog::yal_manager manager{};
  
  auto mock_obj = std::make_unique<testing::StrictMock<sink_mock>>();
  testing::StrictMock<sink_mock>* hack = mock_obj.get();


  manager.add_new_logger("mock", std::move(mock_obj), yalog::log_level::DEBUG);
  manager.set_default_logger("mock");
  EXPECT_CALL(*hack, print(IsU8Message(u8"\U0001F4A9Hello1\n")));
  manager().debug().println(u8"\U0001F4A9Hello1");
  EXPECT_CALL(*hack, print(IsU8Message(u8"\U0001F4A9Hello2\n")));
  manager().warn().println(u8"\U0001F4A9Hello2");
  EXPECT_CALL(*hack, print(IsU8Message(u8"\U0001F4A9Hello3\n")));
  manager().error().println(u8"\U0001F4A9Hello3");

  EXPECT_CALL(*hack, print(IsU8Message(u8"\U0001F4A9Hello4\n")));
  manager().debug().print(u8"\U0001F4A9Hello4\n");
  EXPECT_CALL(*hack, print(IsU8Message(u8"\U0001F4A9Hello5\n")));
  manager().warn().print(u8"\U0001F4A9Hello5\n");
  EXPECT_CALL(*hack, print(IsU8Message(u8"\U0001F4A9Hello6\n")));
  manager().error().print(u8"\U0001F4A9Hello6\n");

  EXPECT_CALL(*hack, print(IsU8Message(u8"\U0001F4A9Hello7\n")));
  manager().debug() << u8"\U0001F4A9Hello7\n";
  EXPECT_CALL(*hack, print(IsU8Message(u8"\U0001F4A9Hello8\n")));
  manager().warn() << u8"\U0001F4A9Hello8\n";
  EXPECT_CALL(*hack, print(IsU8Message(u8"\U0001F4A9Hello9\n")));
  manager().error() << u8"\U0001F4A9Hello9\n";
  manager.flush();
  EXPECT_TRUE(::testing::Mock::VerifyAndClear(hack));
}

TEST(Logger, ASCIIStreamInterface) {
  yalog::yal_manager manager{};
  auto mock_obj = std::make_unique<testing::StrictMock<sink_mock>>();
  testing::StrictMock<sink_mock>* hack = mock_obj.get();
  manager.add_new_logger("mock", std::move(mock_obj), yalog::log_level::DEBUG);
  manager.set_default_logger("mock");
  EXPECT_CALL(*hack, print(IsASCIIMessage("Hello1\n")));
  manager().debug().println("Hello1");
  EXPECT_CALL(*hack, print(IsASCIIMessage("Hello2\n")));
  manager().warn().println("Hello2");
  EXPECT_CALL(*hack, print(IsASCIIMessage("Hello3\n")));
  manager().error().println("Hello3");

  EXPECT_CALL(*hack, print(IsASCIIMessage("Hello4\n")));
  manager().debug().print("Hello4\n");
  EXPECT_CALL(*hack, print(IsASCIIMessage("Hello5\n")));
  manager().warn().print("Hello5\n");
  EXPECT_CALL(*hack, print(IsASCIIMessage("Hello6\n")));
  manager().error().print("Hello6\n");

  EXPECT_CALL(*hack, print(IsASCIIMessage("Hello7\n")));
  manager().debug() << "Hello7\n";
  EXPECT_CALL(*hack, print(IsASCIIMessage("Hello8\n")));
  manager().warn() << "Hello8\n";
  EXPECT_CALL(*hack, print(IsASCIIMessage("Hello9\n")));
  manager().error() << "Hello9\n";
  manager.flush();
  EXPECT_TRUE(::testing::Mock::VerifyAndClear(&mock_obj));
}

TEST(Logger, OrderedMessages) {
  using namespace std::chrono_literals;
  yalog::yal_manager manager{};
  auto mock_obj = std::make_unique<testing::StrictMock<sink_mock>>();
  testing::StrictMock<sink_mock>* hack = mock_obj.get();
  manager.add_new_logger("mock", std::move(mock_obj), yalog::log_level::DEBUG);
  {
    testing::InSequence dummy;
    EXPECT_CALL(*hack, print(IsASCIIMessage("1\n")));
    manager("mock").debug().println("1");
    EXPECT_CALL(*hack, print(IsASCIIMessage("2\n")));
    manager("mock").warn().println("2");
    EXPECT_CALL(*hack, print(IsASCIIMessage("3\n")));
    manager("mock").error().println("3");
    manager.flush("mock");
  }
  EXPECT_TRUE(::testing::Mock::VerifyAndClear(&mock_obj));
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  testing::InitGoogleMock(&argc, argv);
  testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
  return result;
}