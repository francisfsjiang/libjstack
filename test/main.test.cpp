#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE LibjstackTest

#include <boost/test/unit_test.hpp>

/*
BOOST_AUTO_TEST_CASE(test1)
{
    BOOST_TEST(true);
}

bool init_unit_test()
{
    std::cout << "using custom init" << std::endl;
    return true;
}
 */

BOOST_AUTO_TEST_SUITE(Main)
    BOOST_AUTO_TEST_CASE(test_main) {
        BOOST_CHECK_EQUAL(1, 1);
    }
    BOOST_AUTO_TEST_CASE(test_main2) {
        BOOST_CHECK_EQUAL(1, 1);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE( test1 )
{
    int i = 1;
    BOOST_CHECK( i*i == 1 );
}