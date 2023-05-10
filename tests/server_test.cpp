#include "../src/core/errors.hpp"
#include "../src/core/server/server.hpp"
#include <boost/asio.hpp>
#include <gtest/gtest.h>

#define BOOST_TEST_DYN_LINK

config_data config_file_info = {80, "127.0.0.1"};

bool check_if_port_is_being_used(int port) {
  using namespace boost::asio;
  using ip::tcp;

  io_service svc;
  tcp::acceptor a(svc);

  boost::system::error_code ec;
  a.open(tcp::v4(), ec) || a.bind({tcp::v4(), (unsigned int)port}, ec);

  return ec == error::address_in_use;
}

TEST(Server, ThePortIsBeingUsed) {
  int err = handle_multiple_connections(&config_file_info);

  EXPECT_EQ(err, NO_ERROR_EXIT)
      << "\033[31mAn error has occurred when setting up the server. Err: "
      << err << "\033[0m\n";

  EXPECT_TRUE(check_if_port_is_being_used(config_file_info.port))
      << "\033[31mThe server isn't running on port " << config_file_info.port
      << ".\033[0m\n";
}