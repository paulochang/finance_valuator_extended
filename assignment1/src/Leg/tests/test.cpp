#define BOOST_TEST_MODULE test_leg


#include <boost/test/unit_test.hpp>
#include "Leg/FixedLeg.h"
#include "Leg/FloatingLeg.h"
#include <Leg/ZeroCurve/ZeroCouponCurve.h>

namespace utf = boost::unit_test;


BOOST_AUTO_TEST_SUITE(leg_test_suite)

    BOOST_AUTO_TEST_CASE(fixed_day_fraction, *utf::tolerance(1e-15)) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double notional = 100;
        const double rate = 5.0 / 100;
        std::vector<boost::gregorian::date> referenceDates{};
        referenceDates.push_back(boost::gregorian::from_string("2016-04-01"));
        referenceDates.push_back(boost::gregorian::from_string("2016-10-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-04-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-10-02"));
        referenceDates.push_back(boost::gregorian::from_string("2018-04-02"));

        Actual_360 actualCalc = Actual_360();

        std::map<boost::gregorian::date, double> m_mapZeroRates{};
        m_mapZeroRates[boost::gregorian::from_string("2016-10-03")] = 0.04743305323463213;
        m_mapZeroRates[boost::gregorian::from_string("2017-04-03")] = 0.05;
        m_mapZeroRates[boost::gregorian::from_string("2017-10-02")] = 0.051;
        m_mapZeroRates[boost::gregorian::from_string("2018-04-02")] = 0.052;
        ZeroCouponCurve zeroCouponCurve{m_mapZeroRates};

        FixedLeg myLeg{notional, rate, referenceDates, actualCalc, zeroCouponCurve};
        std::vector<double> calculated_values = myLeg.getDayCountFractionVector();

        double myDoubles[] = {185.0 / 360, 182.0 / 360, 182.0 / 360, 182.0 / 360};
        std::vector<double> expected_values(myDoubles, myDoubles + sizeof(myDoubles) / sizeof(double));


        //BOOST_TEST_MESSAGE(" - Calculated Value: " << calculated_values);
        //BOOST_TEST_MESSAGE(" - Expected Value: " << expected_values);
        BOOST_TEST(calculated_values == expected_values, boost::test_tools::per_element());
    }

    BOOST_AUTO_TEST_CASE(fixed_cash_flows, *utf::tolerance(1e-15)) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double notional = 100;
        const double rate = 5.0 / 100;
        std::vector<boost::gregorian::date> referenceDates{};
        referenceDates.push_back(boost::gregorian::from_string("2016-04-01"));
        referenceDates.push_back(boost::gregorian::from_string("2016-10-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-04-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-10-02"));
        referenceDates.push_back(boost::gregorian::from_string("2018-04-02"));

        Actual_360 actualCalc = Actual_360();

        std::map<boost::gregorian::date, double> m_mapZeroRates{};
        m_mapZeroRates[boost::gregorian::from_string("2016-10-03")] = 0.04743305323463213;
        m_mapZeroRates[boost::gregorian::from_string("2017-04-03")] = 0.05;
        m_mapZeroRates[boost::gregorian::from_string("2017-10-02")] = 0.051;
        m_mapZeroRates[boost::gregorian::from_string("2018-04-02")] = 0.052;
        ZeroCouponCurve zeroCouponCurve{m_mapZeroRates};

        FixedLeg myLeg{notional, rate, referenceDates, actualCalc, zeroCouponCurve};

        double myDoubles[] = {185.0 / 360, 182.0 / 360, 182.0 / 360, 182.0 / 360};
        std::vector<double> dayCountFractionVector(myDoubles, myDoubles + sizeof(myDoubles) / sizeof(double));

        std::vector<double> calculated_values = myLeg.getLegCashFlows(dayCountFractionVector);

        double myResults[] = {185.0 / 72, 182.0 / 72, 182.0 / 72, 182.0 / 72};
        std::vector<double> expected_values(myResults, myResults + sizeof(myResults) / sizeof(double));

        //BOOST_TEST_MESSAGE(" - Calculated Value: " << calculated_values);
        //BOOST_TEST_MESSAGE(" - Expected Value: " << expected_values);
        BOOST_TEST(calculated_values == expected_values, boost::test_tools::per_element());
    }

    BOOST_AUTO_TEST_CASE(fixed_discount_factor, *utf::tolerance(1e-15)) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double notional = 100;
        const double rate = 5.0 / 100;
        std::vector<boost::gregorian::date> referenceDates{};
        referenceDates.push_back(boost::gregorian::from_string("2016-04-01"));
        referenceDates.push_back(boost::gregorian::from_string("2016-10-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-04-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-10-02"));
        referenceDates.push_back(boost::gregorian::from_string("2018-04-02"));

        Actual_360 actualCalc = Actual_360();

        std::map<boost::gregorian::date, double> m_mapZeroRates{};
        m_mapZeroRates[boost::gregorian::from_string("2016-10-03")] = 0.04743305323463213;
        m_mapZeroRates[boost::gregorian::from_string("2017-04-03")] = 0.05;
        m_mapZeroRates[boost::gregorian::from_string("2017-10-02")] = 0.051;
        m_mapZeroRates[boost::gregorian::from_string("2018-04-02")] = 0.052;
        ZeroCouponCurve zeroCouponCurve{m_mapZeroRates};

        FixedLeg myLeg{notional, rate, referenceDates, actualCalc, zeroCouponCurve};

        double totalDayCountFractions[] = {185.0 / 360, 367.0 / 360, 549.0 / 360, 731.0 / 360};
        std::vector<double> totalDayCountFractionVector(totalDayCountFractions, totalDayCountFractions +
                                                                                sizeof(totalDayCountFractions) /
                                                                                sizeof(double));

        std::vector<double> calculated_values = myLeg.getDiscountFactors(totalDayCountFractionVector);

        double myResults[] = {exp(-(185.0 / 360) * (4.743305323463213 / 100)), exp(-(367.0 / 360) * (5.0 / 100)),
                              exp(-(549.0 / 360) * (5.1 / 100)), exp(-(731.0 / 360) * (5.2 / 100))};
        std::vector<double> expected_values(myResults, myResults + sizeof(myResults) / sizeof(double));

        //BOOST_TEST_MESSAGE(" - Calculated Value: " << calculated_values);
        //BOOST_TEST_MESSAGE(" - Expected Value: " << expected_values);
        BOOST_TEST(calculated_values == expected_values, boost::test_tools::per_element());
    }

    BOOST_AUTO_TEST_CASE(fixed_discounted_values) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double notional = 100;
        const double rate = 5.0 / 100;
        std::vector<boost::gregorian::date> referenceDates{};
        referenceDates.push_back(boost::gregorian::from_string("2016-04-01"));
        referenceDates.push_back(boost::gregorian::from_string("2016-10-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-04-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-10-02"));
        referenceDates.push_back(boost::gregorian::from_string("2018-04-02"));

        Actual_360 actualCalc = Actual_360();

        std::map<boost::gregorian::date, double> m_mapZeroRates{};
        m_mapZeroRates[boost::gregorian::from_string("2016-10-03")] = 0.04743305323463213;
        m_mapZeroRates[boost::gregorian::from_string("2017-04-03")] = 0.05;
        m_mapZeroRates[boost::gregorian::from_string("2017-10-02")] = 0.051;
        m_mapZeroRates[boost::gregorian::from_string("2018-04-02")] = 0.052;
        ZeroCouponCurve zeroCouponCurve{m_mapZeroRates};

        FixedLeg myLeg{notional, rate, referenceDates, actualCalc, zeroCouponCurve};

        double discountFactors[] = {exp(-(185.0 / 360) * (4.743305323463213 / 100)), exp(-(367.0 / 360) * (5.0 / 100)),
                                    exp(-(549.0 / 360) * (5.1 / 100)), exp(-(731.0 / 360) * (5.2 / 100))};
        std::vector<double> discountFactorsVector(discountFactors,
                                                  discountFactors + sizeof(discountFactors) / sizeof(double));

        double cashFlows[] = {185.0 / 72, 182.0 / 72, 182.0 / 72, 182.0 / 72};
        std::vector<double> cashFlowsVector(cashFlows, cashFlows + sizeof(cashFlows) / sizeof(double));

        double calculated_value = myLeg.getDiscountedValue(discountFactorsVector, cashFlowsVector);
        double theoretical_value = 9.5228417749383200;
        //BOOST_TEST_MESSAGE(" - Calculated Value: " << calculated_values);
        //BOOST_TEST_MESSAGE(" - Expected Value: " << expected_values);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-15));
    }

    BOOST_AUTO_TEST_CASE(fixed_price) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double notional = 100;
        const double rate = 5.0 / 100;
        std::vector<boost::gregorian::date> referenceDates{};
        referenceDates.push_back(boost::gregorian::from_string("2016-04-01"));
        referenceDates.push_back(boost::gregorian::from_string("2016-10-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-04-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-10-02"));
        referenceDates.push_back(boost::gregorian::from_string("2018-04-02"));

        Actual_360 actualCalc = Actual_360();

        std::map<boost::gregorian::date, double> m_mapZeroRates{};
        m_mapZeroRates[boost::gregorian::from_string("2016-10-03")] = 0.04743305323463213;
        m_mapZeroRates[boost::gregorian::from_string("2017-04-03")] = 0.05;
        m_mapZeroRates[boost::gregorian::from_string("2017-10-02")] = 0.051;
        m_mapZeroRates[boost::gregorian::from_string("2018-04-02")] = 0.052;
        ZeroCouponCurve zeroCouponCurve{m_mapZeroRates};

        FixedLeg myLeg{notional, rate, referenceDates, actualCalc, zeroCouponCurve};

        double calculated_value = myLeg.price();
        double theoretical_value = 9.5228417749383200;
        //BOOST_TEST_MESSAGE(" - Calculated Value: " << calculated_values);
        //BOOST_TEST_MESSAGE(" - Expected Value: " << expected_values);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-15));
    }

    BOOST_AUTO_TEST_CASE(floating_fwd_rates, *utf::tolerance(1e-15)) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double notional = 100;
        const double rate = 5.0 / 100;
        const int periodsPerYear = 2;
        std::vector<boost::gregorian::date> referenceDates{};
        referenceDates.push_back(boost::gregorian::from_string("2016-04-01"));
        referenceDates.push_back(boost::gregorian::from_string("2016-10-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-04-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-10-02"));
        referenceDates.push_back(boost::gregorian::from_string("2018-04-02"));

        Actual_360 actualCalc = Actual_360();

        std::map<boost::gregorian::date, double> m_mapZeroRates{};
        m_mapZeroRates[boost::gregorian::from_string("2016-10-03")] = 0.04743305323463213;
        m_mapZeroRates[boost::gregorian::from_string("2017-04-03")] = 0.05;
        m_mapZeroRates[boost::gregorian::from_string("2017-10-02")] = 0.051;
        m_mapZeroRates[boost::gregorian::from_string("2018-04-02")] = 0.052;
        ZeroCouponCurve zeroCouponCurve{m_mapZeroRates};

        FloatingLeg myLeg{notional, rate, referenceDates, actualCalc, zeroCouponCurve, periodsPerYear};
        double totalDayCountFractions[] = {185.0 / 360, 367.0 / 360, 549.0 / 360, 731.0 / 360};
        std::vector<double> totalDayCountFractionVector(totalDayCountFractions, totalDayCountFractions +
                                                                                sizeof(totalDayCountFractions) /
                                                                                sizeof(double));

        std::vector<double> calculated_values = myLeg.getForwardRatesVector(totalDayCountFractionVector);
        double myResults[] = {0.04743305323463213, (0.05 * 367 - 0.04743305323463213 * 185) / 182,
                              (0.051 * 549 - 0.05 * 367) / 182,
                              (0.052 * 731 - 0.051 * 549) / 182};
        std::vector<double> expected_values(myResults, myResults + sizeof(myResults) / sizeof(double));

        BOOST_TEST(calculated_values == expected_values, boost::test_tools::per_element());
    }

    BOOST_AUTO_TEST_CASE(floating_discrete_rates, *utf::tolerance(1e-12)) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double notional = 100;
        const double rate = 5.0 / 100;
        const int periodsPerYear = 2;
        std::vector<boost::gregorian::date> referenceDates{};
        referenceDates.push_back(boost::gregorian::from_string("2016-04-01"));
        referenceDates.push_back(boost::gregorian::from_string("2016-10-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-04-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-10-02"));
        referenceDates.push_back(boost::gregorian::from_string("2018-04-02"));

        Actual_360 actualCalc = Actual_360();

        std::map<boost::gregorian::date, double> m_mapZeroRates{};
        m_mapZeroRates[boost::gregorian::from_string("2016-10-03")] = 04743305323463213;
        m_mapZeroRates[boost::gregorian::from_string("2017-04-03")] = 0.05;
        m_mapZeroRates[boost::gregorian::from_string("2017-10-02")] = 0.051;
        m_mapZeroRates[boost::gregorian::from_string("2018-04-02")] = 0.052;
        ZeroCouponCurve zeroCouponCurve{m_mapZeroRates};

        FloatingLeg myLeg{notional, rate, referenceDates, actualCalc, zeroCouponCurve, periodsPerYear};
        double forwardRates[] = {0.04743305323463213, (0.05 * 367 - 0.04743305323463213 * 185) / 182,
                                 (0.051 * 549 - 0.05 * 367) / 182,
                                 (0.052 * 731 - 0.051 * 549) / 182};
        std::vector<double> forwardRatesVector(forwardRates, forwardRates +
                                                             sizeof(forwardRates) /
                                                             sizeof(double));

        std::vector<double> calculated_values = myLeg.getDiscreteFwdRatesVector(forwardRatesVector);
        double myResults[] = {4.80 / 100, 5.33072997367 / 100, 5.37254207620 / 100, 5.57801733879 / 100};
        std::vector<double> expected_values(myResults, myResults + sizeof(myResults) / sizeof(double));

        BOOST_TEST(calculated_values == expected_values, boost::test_tools::per_element());
    }

    BOOST_AUTO_TEST_CASE(floating_cash_flows, *utf::tolerance(1e-13)) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double notional = 100;
        const double rate = 5.0 / 100;
        const int periodsPerYear = 2;
        std::vector<boost::gregorian::date> referenceDates{};
        referenceDates.push_back(boost::gregorian::from_string("2016-04-01"));
        referenceDates.push_back(boost::gregorian::from_string("2016-10-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-04-03"));
        referenceDates.push_back(boost::gregorian::from_string("2017-10-02"));
        referenceDates.push_back(boost::gregorian::from_string("2018-04-02"));

        Actual_360 actualCalc = Actual_360();

        std::map<boost::gregorian::date, double> m_mapZeroRates{};
        m_mapZeroRates[boost::gregorian::from_string("2016-10-03")] = 0.04743305323463213;
        m_mapZeroRates[boost::gregorian::from_string("2017-04-03")] = 0.05;
        m_mapZeroRates[boost::gregorian::from_string("2017-10-02")] = 0.051;
        m_mapZeroRates[boost::gregorian::from_string("2018-04-02")] = 0.052;
        ZeroCouponCurve zeroCouponCurve{m_mapZeroRates};

        FloatingLeg myLeg{notional, rate, referenceDates, actualCalc, zeroCouponCurve, periodsPerYear};

        double myDoubles[] = {185.0 / 360, 182.0 / 360, 182.0 / 360, 182.0 / 360};
        std::vector<double> dayCountFractionVector(myDoubles, myDoubles + sizeof(myDoubles) / sizeof(double));

        std::vector<double> calculated_values = myLeg.getLegCashFlows(dayCountFractionVector);

        double myResults[] = {2.4666666666667, 2.6949801533559, 2.7161184940802, 2.8199976546091};
        std::vector<double> expected_values(myResults, myResults + sizeof(myResults) / sizeof(double));

        //BOOST_TEST_MESSAGE(" - Calculated Value: " << calculated_values);
        //BOOST_TEST_MESSAGE(" - Expected Value: " << expected_values);
        BOOST_TEST(calculated_values == expected_values, boost::test_tools::per_element());
    }


BOOST_AUTO_TEST_SUITE_END()
