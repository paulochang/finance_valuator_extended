#define BOOST_TEST_MODULE test_optionsInstances

#include <boost/test/unit_test.hpp>
#include <OptionInstances/CallOption.h>
#include <OptionInstances/PutOption.h>

BOOST_AUTO_TEST_SUITE(optionInstances_test_suite)

    BOOST_AUTO_TEST_CASE(option_getTimeToMaturity) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double strike = 50.0;
        const double rate = 3.66 / 100;
        const boost::gregorian::date startDate = boost::gregorian::from_simple_string("2013-01-01");
        const boost::gregorian::date endDate = boost::gregorian::from_simple_string("2016-01-01");
        Actual_365 dayCountCalculator = Actual_365();

        const double spot_price = 50.0;
        double volatility = 62.0 / 100;

        Asset underlyingAsset{spot_price, volatility};

        CallOption my_option{strike, rate, startDate, endDate, dayCountCalculator, underlyingAsset};
        double theoretical_value = 3.0;
        double calculated_value = my_option.getTimeToMaturity();

        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-2));

    }

    BOOST_AUTO_TEST_CASE(call_getReceiving) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double strike = 50.0;
        const double rate = 3.66 / 100;
        const boost::gregorian::date startDate = boost::gregorian::from_simple_string("2013-01-01");
        const boost::gregorian::date endDate = boost::gregorian::from_simple_string("2016-01-01");
        Actual_365 dayCountCalculator = Actual_365();

        const double spot_price = 50.0;
        double volatility = 62.0 / 100;

        Asset underlyingAsset{spot_price, volatility};

        CallOption my_option{strike, rate, startDate, endDate, dayCountCalculator, underlyingAsset};
        double theoretical_value = 36.93239658;
        double calculated_value = my_option.getReceiving();

        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-8));

    }

    BOOST_AUTO_TEST_CASE(call_getPaying) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double strike = 50.0;
        const double rate = 3.66 / 100;
        const boost::gregorian::date startDate = boost::gregorian::from_simple_string("2013-01-01");
        const boost::gregorian::date endDate = boost::gregorian::from_simple_string("2016-01-01");
        Actual_365 dayCountCalculator = Actual_365();

        const double spot_price = 50.0;
        double volatility = 62.0 / 100;

        Asset underlyingAsset{spot_price, volatility};

        CallOption my_option{strike, rate, startDate, endDate, dayCountCalculator, underlyingAsset};
        double theoretical_value = 14.86907831;
        double calculated_value = my_option.getPaying();

        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-8));

    }

    BOOST_AUTO_TEST_CASE(call_price) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double strike = 50.0;
        const double rate = 3.66 / 100;
        const boost::gregorian::date startDate = boost::gregorian::from_simple_string("2013-01-01");
        const boost::gregorian::date endDate = boost::gregorian::from_simple_string("2016-01-01");
        Actual_365 dayCountCalculator = Actual_365();

        const double spot_price = 50.0;
        double volatility = 62.0 / 100;

        Asset underlyingAsset{spot_price, volatility};

        CallOption my_option{strike, rate, startDate, endDate, dayCountCalculator, underlyingAsset};
        double theoretical_value = 22.06331827;
        double calculated_value = my_option.price();

        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-8));

    }

    BOOST_AUTO_TEST_CASE(put_getReceiving) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double strike = 50.0;
        const double rate = 3.66 / 100;
        const boost::gregorian::date startDate = boost::gregorian::from_simple_string("2013-01-01");
        const boost::gregorian::date endDate = boost::gregorian::from_simple_string("2016-01-01");
        Actual_365 dayCountCalculator = Actual_365();

        const double spot_price = 50.0;
        double volatility = 62.0 / 100;

        Asset underlyingAsset{spot_price, volatility};

        PutOption my_option{strike, rate, startDate, endDate, dayCountCalculator, underlyingAsset};
        double theoretical_value = 29.93158769;
        double calculated_value = my_option.getReceiving();

        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-8));

    }

    BOOST_AUTO_TEST_CASE(put_getPaying) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double strike = 50.0;
        const double rate = 3.66 / 100;
        const boost::gregorian::date startDate = boost::gregorian::from_simple_string("2013-01-01");
        const boost::gregorian::date endDate = boost::gregorian::from_simple_string("2016-01-01");
        Actual_365 dayCountCalculator = Actual_365();

        const double spot_price = 50.0;
        double volatility = 62.0 / 100;

        Asset underlyingAsset{spot_price, volatility};

        PutOption my_option{strike, rate, startDate, endDate, dayCountCalculator, underlyingAsset};
        double theoretical_value = 13.06760342;
        double calculated_value = my_option.getPaying();

        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-8));

    }

    BOOST_AUTO_TEST_CASE(put_price) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double strike = 50.0;
        const double rate = 3.66 / 100;
        const boost::gregorian::date startDate = boost::gregorian::from_simple_string("2013-01-01");
        const boost::gregorian::date endDate = boost::gregorian::from_simple_string("2016-01-01");
        Actual_365 dayCountCalculator = Actual_365();

        const double spot_price = 50.0;
        double volatility = 62.0 / 100;

        Asset underlyingAsset{spot_price, volatility};

        PutOption my_option{strike, rate, startDate, endDate, dayCountCalculator, underlyingAsset};
        double theoretical_value = 16.86398427;
        double calculated_value = my_option.price();

        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-8));

    }

BOOST_AUTO_TEST_SUITE_END()
