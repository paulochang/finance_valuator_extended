#define BOOST_TEST_MODULE test_utils

#include <boost/test/unit_test.hpp>
#include <Utils/utils.h>
#include <Utils/bshelper.h>

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(utils_boost)

    BOOST_AUTO_TEST_CASE(annual_cap1) {
        BOOST_TEST_MESSAGE("Testing annual_cap1");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double amount = 100;
        double annual_rate = 10.0 / 100;
        int number_of_years = 2;
        double theoretical_value = 121; // (100*(1.1)^2)

        auto calculated_value = annual_capitalization(amount, annual_rate, number_of_years);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known_capitalization: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-15));
    }

    BOOST_AUTO_TEST_CASE(annual_discount1) {
        BOOST_TEST_MESSAGE("Testing annual_discount1");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double amount = 121;
        double annual_rate = 10.0 / 100;
        int number_of_years = 2;
        double theoretical_value = 100; // (121/(1.1)^2)

        auto calculated_value = discount_annually(amount, annual_rate, number_of_years);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known discounted_value: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-15));
    }

    BOOST_AUTO_TEST_CASE(period_cap1) {
        BOOST_TEST_MESSAGE("Testing period_cap1");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double amount = 100;
        double annual_rate = 10.0 / 100;
        int periods_per_year = 2;
        int number_of_years = 1;
        double theoretical_value = 110.25; // (100*(1.05)^2)

        auto calculated_value = period_capitalization(amount, annual_rate, periods_per_year, number_of_years);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known_capitalization: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-15));
    }

    BOOST_AUTO_TEST_CASE(period_discount1) {
        BOOST_TEST_MESSAGE("Testing period_discount1");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double amount = 110.25;
        double annual_rate = 10.0 / 100;
        int periods_per_year = 2;
        int number_of_years = 1;
        double theoretical_value = 100; // (110.25/(1.05)^2)

        auto calculated_value = discount_by_periods(amount, annual_rate, periods_per_year, number_of_years);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known discounted_value: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-15));
    }

    BOOST_AUTO_TEST_CASE(continuous_cap1) {
        BOOST_TEST_MESSAGE("Testing continuous_cap1");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double amount = 100;
        double annual_rate = 10.0 / 100;
        int number_of_years = 2;
        double theoretical_value = 122.140275816; // 100 * e^(0.10*2) rounded to second

        auto calculated_value = continuous_capitalization(amount, annual_rate, number_of_years);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known_capitalization: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-8));
    }

    BOOST_AUTO_TEST_CASE(continuous_discount1) {
        BOOST_TEST_MESSAGE("Testing continuous_discount1");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double amount = 122.140275816;
        double annual_rate = 10.0 / 100;
        int number_of_years = 2;
        double theoretical_value = 100; // 122.140275816 / e^(0.10*2) rounded to second

        auto calculated_value = discount_continuously(amount, annual_rate, number_of_years);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known discounted_value: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-8));
    }

    BOOST_AUTO_TEST_CASE(fwd_rate1) {
        BOOST_TEST_MESSAGE("Testing fwd_rate1");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double zero_coupon_total = 0.04;
        int years_total = 2;

        double zero_coupon_partial = 0.03;
        int years_partial = 1;

        double theoretical_value = 0.05; // (100*(1.1)^2) rounded to second

        auto calculated_value = forward_rate(zero_coupon_total, years_total, zero_coupon_partial, years_partial);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known_fwd_rate: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-15));
    }

    BOOST_AUTO_TEST_CASE(annual_to_cont1) {
        BOOST_TEST_MESSAGE("Testing annual_to_cont1");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double annual_rate = 0.12;

        double theoretical_value = 0.1133286853; // ln(1.12)

        auto calculated_value = annual_to_continuous_rate(1, annual_rate);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known_fwd_rate: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-10));
    }

    BOOST_AUTO_TEST_CASE(cont_to_annual) {
        BOOST_TEST_MESSAGE("Testing cont_to_annual");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double continuous_rate = 0.11332868531; //(e^0.1)-1

        double theoretical_value = 0.12; // (e^0.1)-1

        auto calculated_value = continuous_to_annual_rate(1, continuous_rate);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known_fwd_rate: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-9));
    }

    BOOST_AUTO_TEST_CASE(total_day_count, *utf::tolerance(0.0001)) {
        BOOST_TEST_MESSAGE("Testing cont_to_annual");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double myDoubles[] = {185.0 / 360, 182.0 / 360, 182.0 / 360, 182.0 / 360};
        std::vector<double> dayCountFractionVector(myDoubles, myDoubles + sizeof(myDoubles) / sizeof(double));

        std::vector<double> calculated_values = getTotalDayCountFractionVector(dayCountFractionVector);

        double myResults[] = {0.513888888889, 1.019444444444, 1.525000000000, 2.030555555556};
        std::vector<double> expected_values(myResults, myResults + sizeof(myResults) / sizeof(double));

        BOOST_TEST(calculated_values == expected_values, boost::test_tools::per_element());

    }

    BOOST_AUTO_TEST_CASE(black_scholes_d1) {
        BOOST_TEST_MESSAGE("Testing black_scholes_d1");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double asset_price = 50.0;
        double strike = 50.0;
        double rate = 3.66 / 100;
        double volatility = 62.0 / 100;
        double time_to_maturity = 5.0;

        double theoretical_value = 0.8251812; // (e^0.1)-1

        auto calculated_value = getD1(asset_price, strike, rate, volatility, time_to_maturity);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known_d1_value: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-7));
    }

    BOOST_AUTO_TEST_CASE(black_scholes_d2) {
        BOOST_TEST_MESSAGE("Testing black_scholes_d2");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double asset_price = 50.0;
        double strike = 50.0;
        double rate = 3.66 / 100;
        double volatility = 62.0 / 100;
        double time_to_maturity = 5.0;

        double theoretical_value = -0.5611809; // (e^0.1)-1

        auto calculated_value = getD2(asset_price, strike, rate, volatility, time_to_maturity);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known_d2_value: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-7));
    }

    BOOST_AUTO_TEST_CASE(black_scholes_weightAsset) {
        BOOST_TEST_MESSAGE("Testing black_scholes_weightAsset");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double asset_price = 50.0;
        double option_d1 = 0.8251812; //pre-calculated value

        double theoretical_value = 39.7682821; // (e^0.1)-1

        auto calculated_value = weightAsset(asset_price, option_d1);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known_asset_contribution: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-7));
    }

    BOOST_AUTO_TEST_CASE(black_scholes_weightStrike) {
        BOOST_TEST_MESSAGE("Testing black_scholes_weightStrike");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double strike = 50.0;
        double rate = 3.66 / 100;
        double time_to_maturity = 5.0;
        double option_d2 = -0.5611809; //pre-calculated value

        double theoretical_value = 11.9642594; // (e^0.1)-1

        auto calculated_value = weightStrike(strike, option_d2, rate, time_to_maturity);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known_asset_contribution: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-7));
    }

    BOOST_AUTO_TEST_CASE(black_scholes_evaluateCall) {
        BOOST_TEST_MESSAGE("Testing black_scholes_evaluateCall");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double option_strike = 50.0;
        double time_to_maturity = 5.0;
        double rate = 3.66 / 100;
        double volatility = 62.0 / 100;
        double asset_price = 50.0;

        double theoretical_value = 27.804023; // (e^0.1)-1

        auto calculated_value = evaluateCall(option_strike, time_to_maturity, rate, volatility, asset_price);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known_asset_contribution: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-6));
    }

    BOOST_AUTO_TEST_CASE(black_scholes_evaluatePut) {
        BOOST_TEST_MESSAGE("Testing black_scholes_evaluatePut");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double option_strike = 50.0;
        double time_to_maturity = 5.0;
        double rate = 3.66 / 100;
        double volatility = 62.0 / 100;
        double asset_price = 50.0;

        double theoretical_value = 19.442431; // (e^0.1)-1

        auto calculated_value = evaluatePut(option_strike, time_to_maturity, rate, volatility, asset_price);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known_asset_contribution: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-6));
    }

    BOOST_AUTO_TEST_CASE(black_scholes_blackScholesCall) {
        BOOST_TEST_MESSAGE("Testing black_scholes_blackScholesCall");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double option_strike = 50.0;
        double time_to_maturity = 5.0;
        double rate = 3.66 / 100;
        double volatility = 62.0 / 100;
        double asset_price = 50.0;


        double theoretical_value = 27.804023; // (e^0.1)-1

        auto calculated_value = blackScholes(call, option_strike, time_to_maturity, rate, volatility, asset_price);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known_asset_contribution: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-6));
    }

    BOOST_AUTO_TEST_CASE(black_scholes_blackScholesPut) {
        BOOST_TEST_MESSAGE("Testing black_scholes_blackScholesPut");
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        double option_strike = 50.0;
        double time_to_maturity = 5.0;
        double rate = 3.66 / 100;
        double volatility = 62.0 / 100;
        double asset_price = 50.0;


        double theoretical_value = 19.442431; // (e^0.1)-1

        auto calculated_value = blackScholes(put, option_strike, time_to_maturity, rate, volatility, asset_price);

        BOOST_TEST_MESSAGE(" - calculated_value: " << calculated_value);
        BOOST_TEST_MESSAGE(" - known_asset_contribution: " << theoretical_value);
        BOOST_TEST_MESSAGE(" - diff " << calculated_value - theoretical_value);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-6));
    }

BOOST_AUTO_TEST_SUITE_END()
