#define BOOST_TEST_MODULE test_utils

#include <boost/test/unit_test.hpp>
#include <Utils/utils.h>

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


BOOST_AUTO_TEST_SUITE_END()
