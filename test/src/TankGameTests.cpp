#define BOOST_TEST_MODULE Test Libs Module

#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_obstacle) {
    float expected = 4.0;
    float result = 2.0f * 2.0f;

    BOOST_TEST(expected == result);
}
