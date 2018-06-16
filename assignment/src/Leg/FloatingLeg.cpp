#include "FloatingLeg.h"

/**
 * Implementacion de la clase 'FloatingLeg' que representa los pagos flotantes
 * Para calcular los flujos de caja se necesitan saber los periodos de pago, para calcular las fracciones de anyo
 * El interes esta acordado previamente y se supone que es en la duracion de los periodos de pago,
 * las clases superiores se ocuparan de calcularlo.
 */


std::vector<double> FloatingLeg::getLegCashFlows(std::vector<double> dayCountFractionVector) {
    std::vector<double> legCashFlows{};
    std::vector<double> totalDayCountFractionVector{getTotalDayCountFractionVector(dayCountFractionVector)};
    std::vector<double> forwardRatesVector{getForwardRatesVector(totalDayCountFractionVector)};
    std::vector<double> discreteFwdRatesVector{getDiscreteFwdRatesVector(forwardRatesVector)};
    legCashFlows.reserve(dayCountFractionVector.size());

    for (int j = 0; j < dayCountFractionVector.size(); ++j) {
        legCashFlows.emplace_back(discreteFwdRatesVector.at(j) * dayCountFractionVector.at(j) * m_notional);
    }

    return legCashFlows;
}

std::vector<double> FloatingLeg::getForwardRatesVector(std::vector<double> totalDayCountFractionVector) {

    std::vector<double> forwardRatesVector{};
    forwardRatesVector.reserve(m_payingDates.size() - 1);
    double pastTotalDayCountFraction = 0;

    for (unsigned int i = 1; i < m_payingDates.size(); i++) {
        double currentRate = m_zeroCouponCurve.getRateFromDate(m_payingDates.at(i));
        double currentTotalDayCountFraction = totalDayCountFractionVector.at(i - 1);
        double pastRate = m_zeroCouponCurve.getRateFromDate(m_payingDates.at(i - 1));
        pastRate = isnan(pastRate) ? 0 : pastRate;

        double currentFwdRate =
                (currentRate * currentTotalDayCountFraction -
                 pastRate * pastTotalDayCountFraction)
                / (currentTotalDayCountFraction - pastTotalDayCountFraction);
        forwardRatesVector.emplace_back(currentFwdRate);
        pastTotalDayCountFraction = currentTotalDayCountFraction;
    }

    return forwardRatesVector;
}

std::vector<double> FloatingLeg::getDiscreteFwdRatesVector(std::vector<double> forwardRatesVector) {
    std::vector<double> discreteFwdRatesVector{};
    discreteFwdRatesVector.reserve(forwardRatesVector.size());
    for (auto rate : forwardRatesVector) {
        discreteFwdRatesVector.emplace_back(continuous_to_annual_rate(periodsPerYear, rate));
    }
    return discreteFwdRatesVector;
}