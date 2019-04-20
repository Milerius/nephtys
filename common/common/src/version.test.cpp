//
// Created by milerius on 12/04/19.
//

#include <string>
#include <doctest.h>
#include "nephtys/version.hpp"

TEST_CASE ("nephtys version is set")
{
      CHECK_FALSE(std::string(nephtys::version()).empty());
}