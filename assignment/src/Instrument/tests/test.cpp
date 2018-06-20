#define BOOST_TEST_MODULE test_instrument

#include <boost/test/unit_test.hpp>
#include <Leg/FloatingLeg.h>
#include <Instrument/Asset.h>
#include "Instrument/Bond.h"
#include "Instrument/Swap.h"

BOOST_AUTO_TEST_SUITE(instrument_test_suite)

    BOOST_AUTO_TEST_CASE(bond_price) {
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
        Bond myBond{myLeg};

        double calculated_value = myBond.price();
        double theoretical_value = 9.5228417749383200;
        //BOOST_TEST_MESSAGE(" - Calculated Value: " << calculated_values);
        //BOOST_TEST_MESSAGE(" - Expected Value: " << expected_values);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-15));
    }

    BOOST_AUTO_TEST_CASE(swap_price) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");

        const double notional = 100000000;
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

        FixedLeg payingLeg{notional, rate, referenceDates, actualCalc, zeroCouponCurve};
        FloatingLeg receivingLeg{notional, referenceDates, actualCalc, zeroCouponCurve, periodsPerYear};

        Swap mySwap{receivingLeg, payingLeg};

        double calculated_value = mySwap.price();
        double theoretical_value = 495775.94;
        //BOOST_TEST_MESSAGE(" - Calculated Value: " << calculated_values);
        //BOOST_TEST_MESSAGE(" - Expected Value: " << expected_values);
        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-2));
    }

    BOOST_AUTO_TEST_CASE(asset_getVolatility) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");


        const double spot_price = 50.0;
        double volatility = 62.0 / 100;

        Asset underlyingAsset{spot_price, volatility};

        double calculated_value = underlyingAsset.getVolatility();
        double theoretical_value = 0.62;

        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-2));
    }

    BOOST_AUTO_TEST_CASE(asset_getPrice) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");


        const double spot_price = 50.0;
        double volatility = 62.0 / 100;

        Asset underlyingAsset{spot_price, volatility};

        double calculated_value = underlyingAsset.price();
        double theoretical_value = 50.0;

        BOOST_TEST(theoretical_value == calculated_value, boost::test_tools::tolerance(1e-2));
    }

BOOST_AUTO_TEST_SUITE_END()
