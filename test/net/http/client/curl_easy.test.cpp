#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/bind/bind.hpp>

#include "net/http/client/curl_easy.hpp"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(Curl)
    BOOST_AUTO_TEST_CASE(test_curl) {
        namespace curl_easy = libjstack::net::http::curl_easy;
        auto curl = curl_easy::CurlEasy();
        auto *os = new std::ostringstream();

        curl.set_write_data((void*)os);
        curl.set_write_function([](char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t {
            *(std::ostringstream*)userdata << std::string(static_cast<char*>(ptr), size * nmemb);
            return size * nmemb;
        });

        curl.set_url("ifconfig.co");
        curl.set_useragent("curl/7.68.0");
        curl.perform();

        BOOST_CHECK_NE(os->str(), "");
        delete os;
    }
BOOST_AUTO_TEST_SUITE_END()