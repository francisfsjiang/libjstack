#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/bind/bind.hpp>

#include "crypto/md5.hpp"

using namespace boost::unit_test;
BOOST_AUTO_TEST_SUITE(MD5)
    BOOST_AUTO_TEST_CASE(testPlus) {

        auto bytes = libjstack::string_to_bytes("123");
        auto result = libjstack::crypto::md5(bytes);
        auto hex = libjstack::bytes_to_hex_string(result);

        BOOST_CHECK_EQUAL(hex, "202CB962AC59075B964B07152D234B70");
    }
    BOOST_AUTO_TEST_CASE(testPlus2) {

        auto bytes = libjstack::string_to_bytes(" ");
        auto result = libjstack::crypto::md5(bytes);
        auto hex = libjstack::bytes_to_hex_string(result);

        BOOST_CHECK_EQUAL(hex, "7215EE9C7D9DC229D2921A40E899EC5F");
    }
BOOST_AUTO_TEST_SUITE_END()