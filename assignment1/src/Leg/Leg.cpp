#include "Leg.h"

Leg::~Leg() = default;

std::vector<double> Leg::getDayCountFractionVector() {
    std::vector<double> dayCountFractionVector{};
    dayCountFractionVector.reserve(m_payingDates.size()-1);

    for (unsigned int i = 1; i < m_payingDates.size(); i++) {
        double dayCountFraction = m_dayCalculator.getDayRatio(m_payingDates.at(i - 1), m_payingDates.at(i));
        dayCountFractionVector.emplace_back(dayCountFraction);
    }

    return dayCountFractionVector;
}

std::vector<double> Leg::getDiscountFactors(std::vector<double> dayCountFractionVector) {
    std::vector<double> discountFactors{};
    discountFactors.reserve(dayCountFractionVector.size());
    for (int i = 1; i <= dayCountFractionVector.size(); ++i) {
        discountFactors.emplace_back(continuous_discount_factor(
                m_zeroCouponCurve.getRateFromDateString(m_payingDates.at(i)),
                dayCountFractionVector.at(i-1)));
    }

    return discountFactors;
}

double Leg::getDiscountedValue(std::vector<double> &dayCountFractionVector, std::vector<double> &legDiscountFactors,
                               std::vector<double> &legCashFlows) {
    double totalDiscountedValue = 0.0;
    double currentPeriodFraction = 0.0;

    for (int i = 0; i < dayCountFractionVector.size(); ++i) {
        currentPeriodFraction += dayCountFractionVector.at(i);
        totalDiscountedValue += discount_continuously(legCashFlows.at(i), legDiscountFactors.at(i),
                                                      currentPeriodFraction);
    }
    return totalDiscountedValue;
}