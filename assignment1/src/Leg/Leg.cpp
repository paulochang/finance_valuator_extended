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
                m_zeroCouponCurve.getRateFromDate(m_payingDates.at(i)),
                totalDayCountFractionVector.at(i - 1)));
    }

    return discountFactors;
}

const double
Leg::getDiscountedValue(std::vector<double> &legDiscountFactors,
                        std::vector<double> &legCashFlows) const {
    double totalDiscountedValue = 0.0;

    for (unsigned int i = 0; i < legDiscountFactors.size(); ++i) {
        totalDiscountedValue += legCashFlows.at(i) * legDiscountFactors.at(i);
    }
    return totalDiscountedValue;
}

const double Leg::price() {

    // TESTED
    //Generate day count fraction vector
    std::vector<double> dayCountFractionVector{getDayCountFractionVector()};

    // TESTED
    //Calculate the legCashFlows
    std::vector<double> legCashFlows{getLegCashFlows(dayCountFractionVector)};

    std::vector<double> totalDayCountFractionVector{getTotalDayCountFractionVector(dayCountFractionVector)};

    //Calculate discount factors
    std::vector<double> legDiscountFactors{getDiscountFactors(totalDayCountFractionVector)};

    //Sum up discounted cashflows
    double totalDiscountedValue = getDiscountedValue(legDiscountFactors, legCashFlows);

    return totalDiscountedValue;
}