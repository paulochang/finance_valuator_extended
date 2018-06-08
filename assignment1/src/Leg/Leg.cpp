#include "Leg.h"

Leg::~Leg() = default;

const std::vector<double> Leg::getDayCountFractionVector() const {
    std::vector<double> dayCountFractionVector{};
    dayCountFractionVector.reserve(m_payingDates.size() - 1);

    for (unsigned int i = 1; i < m_payingDates.size(); i++) {
        double dayCountFraction = m_dayCalculator.getDayRatio(m_payingDates.at(i - 1), m_payingDates.at(i));
        dayCountFractionVector.emplace_back(dayCountFraction);
    }

    return dayCountFractionVector;
}

const std::vector<double> Leg::getDiscountFactors(std::vector<double> totalDayCountFractionVector) const {
    std::vector<double> discountFactors{};
    discountFactors.reserve(totalDayCountFractionVector.size());
    for (unsigned int i = 1; i <= totalDayCountFractionVector.size(); ++i) {
        discountFactors.emplace_back(continuous_discount_factor(
                m_zeroCouponCurve.getRateFromDateString(m_payingDates.at(i)),
                totalDayCountFractionVector.at(i - 1)));
    }

    return discountFactors;
}

const double
Leg::getDiscountedValue(std::vector<double> &dayCountFractionVector, std::vector<double> &legDiscountFactors,
                        std::vector<double> &legCashFlows) const {
    double totalDiscountedValue = 0.0;
    double currentPeriodFraction = 0.0;

    for (unsigned int i = 0; i < dayCountFractionVector.size(); ++i) {
        currentPeriodFraction += dayCountFractionVector.at(i);
        totalDiscountedValue += discount_continuously(legCashFlows.at(i), legDiscountFactors.at(i),
                                                      currentPeriodFraction);
    }
    return totalDiscountedValue;
}