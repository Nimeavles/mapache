#include "../src/utils/config_file.hpp"
#include <gtest/gtest.h>

TEST(ConfigParser, PortValue) {
  config_data data;
  // This path due to the fact that the program searchs from build/ dir
  read_json_config_file("../tests/mock/mapache_config.json", &data);

  EXPECT_EQ(data.port, 8080);
  EXPECT_EQ(data.host, "127.0.0.1");
}