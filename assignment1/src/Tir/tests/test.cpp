#define BOOST_TEST_MODULE test_tir

#include <boost/test/unit_test.hpp>
#include <Tir/Tir.h>

BOOST_AUTO_TEST_SUITE(tir_test_suite)

    BOOST_AUTO_TEST_CASE(actual_count) {
        BOOST_TEST_MESSAGE("using tolerances within checks.");
				
				
			  const double notional = 95.92;
				const std::vector<double> CashFlows = {5.0, 5.8, 6.4, 6.8};
				const int sPeriods = 2;
			  const double tPPeriods = 2.0;
				const int mPeriod = 1;
				
				Bono_TIR bond = Bono_TIR();
        
				double expected_values = 3.61;
				double calculated_values = bond(notional, CashFlows, sPeriods, tPPeriods, mPeriod);
        

        BOOST_TEST_MESSAGE(" - Calculated Value: " << calculated_values);
        BOOST_TEST_MESSAGE(" - Expected Value: " << expected_values);
        BOOST_TEST_MESSAGE(" - Diff " << calculated_values - expected_values);
        BOOST_TEST(expected_values == calculated_values, boost::test_tools::tolerance(1e-15));
    }

BOOST_AUTO_TEST_SUITE_END()
