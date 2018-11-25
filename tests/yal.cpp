#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <yal/yal_manager.hpp>

class sink_mock : public yalog::sink {
 public:
  MOCK_METHOD1(print, void(const yalog::log_message&));
};

TEST(Logger, LogLevelUsage) {
  using namespace std::chrono_literals;

  sink_mock mock_obj{};
  {
    yalog::yal_manager manager{};
    manager.add_new_logger("mock", mock_obj, yalog::log_level::WARNING);
    EXPECT_CALL(mock_obj, print(testing::_)).Times(2);
    manager("mock").debug() << "Hello";
    manager("mock").warn() << "Hello";
    manager("mock").error() << "Hello";
  }
}

MATCHER_P(IsAnsiiMessage, n, "") {
  std::string msg;
  std::transform(arg.message.begin(), arg.message.end(), std::back_inserter(msg), [](uint8_t c) { return static_cast<char>(c); });
  return msg == n;
}

TEST(Logger, ANSIIStreamInterface) {
  yalog::yal_manager manager{};
  sink_mock mock_obj{};
  manager.add_new_logger("mock", mock_obj, yalog::log_level::DEBUG);
  manager.set_default_logger("mock");
  EXPECT_CALL(mock_obj, print(IsAnsiiMessage("Hello1\n")));
  manager().debug().println("Hello1");
  EXPECT_CALL(mock_obj, print(IsAnsiiMessage("Hello2\n")));
  manager().warn().println("Hello2");
  EXPECT_CALL(mock_obj, print(IsAnsiiMessage("Hello3\n")));
  manager().error().println("Hello3");

  EXPECT_CALL(mock_obj, print(IsAnsiiMessage("Hello4\n")));
  manager().debug().print("Hello4\n");
  EXPECT_CALL(mock_obj, print(IsAnsiiMessage("Hello5\n")));
  manager().warn().print("Hello5\n");
  EXPECT_CALL(mock_obj, print(IsAnsiiMessage("Hello6\n")));
  manager().error().print("Hello6\n");

  EXPECT_CALL(mock_obj, print(IsAnsiiMessage("Hello7\n")));
  manager().debug() << "Hello7\n";
  EXPECT_CALL(mock_obj, print(IsAnsiiMessage("Hello8\n")));
  manager().warn() << "Hello8\n";
  EXPECT_CALL(mock_obj, print(IsAnsiiMessage("Hello9\n")));
  manager().error() << "Hello9\n";
  manager.flush();
}

TEST(Logger, U8StreamInterface) {
  yalog::yal_manager manager{};
  sink_mock mock_obj{};
  manager.add_new_logger("mock", mock_obj, yalog::log_level::DEBUG);
  manager.set_default_logger("mock");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello1\n")));
  manager().debug().println("Hello1");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello2\n")));
  manager().warn().println("Hello2");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello3\n")));
  manager().error().println("Hello3");

  EXPECT_CALL(mock_obj, print(IsMessage("Hello4\n")));
  manager().debug().print("Hello4\n");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello5\n")));
  manager().warn().print("Hello5\n");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello6\n")));
  manager().error().print("Hello6\n");

  EXPECT_CALL(mock_obj, print(IsMessage("Hello7\n")));
  manager().debug() << "Hello7\n";
  EXPECT_CALL(mock_obj, print(IsMessage("Hello8\n")));
  manager().warn() << "Hello8\n";
  EXPECT_CALL(mock_obj, print(IsMessage("Hello9\n")));
  manager().error() << "Hello9\n";
  manager.flush();
}

TEST(Logger, U16StreamInterface) {
  yalog::yal_manager manager{};
  sink_mock mock_obj{};
  manager.add_new_logger("mock", mock_obj, yalog::log_level::DEBUG);
  manager.set_default_logger("mock");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello1\n")));
  manager().debug().println("Hello1");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello2\n")));
  manager().warn().println("Hello2");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello3\n")));
  manager().error().println("Hello3");

  EXPECT_CALL(mock_obj, print(IsMessage("Hello4\n")));
  manager().debug().print("Hello4\n");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello5\n")));
  manager().warn().print("Hello5\n");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello6\n")));
  manager().error().print("Hello6\n");

  EXPECT_CALL(mock_obj, print(IsMessage("Hello7\n")));
  manager().debug() << "Hello7\n";
  EXPECT_CALL(mock_obj, print(IsMessage("Hello8\n")));
  manager().warn() << "Hello8\n";
  EXPECT_CALL(mock_obj, print(IsMessage("Hello9\n")));
  manager().error() << "Hello9\n";
  manager.flush();
}

TEST(Logger, U32Interface) {
  yalog::yal_manager manager{};
  sink_mock mock_obj{};
  manager.add_new_logger("mock", mock_obj, yalog::log_level::DEBUG);
  manager.set_default_logger("mock");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello1\n")));
  manager().debug().println("Hello1");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello2\n")));
  manager().warn().println("Hello2");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello3\n")));
  manager().error().println("Hello3");

  EXPECT_CALL(mock_obj, print(IsMessage("Hello4\n")));
  manager().debug().print("Hello4\n");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello5\n")));
  manager().warn().print("Hello5\n");
  EXPECT_CALL(mock_obj, print(IsMessage("Hello6\n")));
  manager().error().print("Hello6\n");

  EXPECT_CALL(mock_obj, print(IsMessage("Hello7\n")));
  manager().debug() << "Hello7\n";
  EXPECT_CALL(mock_obj, print(IsMessage("Hello8\n")));
  manager().warn() << "Hello8\n";
  EXPECT_CALL(mock_obj, print(IsMessage("Hello9\n")));
  manager().error() << "Hello9\n";
  manager.flush();
}

TEST(Logger, OrderedMessages) {
  using namespace std::chrono_literals;
  yalog::yal_manager manager{};
  sink_mock mock_obj{};
  manager.add_new_logger("mock", mock_obj, yalog::log_level::DEBUG);
  {
    testing::InSequence dummy;
    EXPECT_CALL(mock_obj, print(IsMessage("1\n")));
    manager("mock").debug().println("1");
    EXPECT_CALL(mock_obj, print(IsMessage("2\n")));
    manager("mock").warn().println("2");
    EXPECT_CALL(mock_obj, print(IsMessage("3\n")));
    manager("mock").error().println("3");
    manager.flush("mock");
  }
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  testing::InitGoogleMock(&argc, argv);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}