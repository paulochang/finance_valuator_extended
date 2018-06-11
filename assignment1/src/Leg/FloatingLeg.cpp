#include "FloatingLeg.h"

/**
 * Implementacion de la clase 'FloatingLeg' que representa los pagos flotantes
 * Para calcular los flujos de caja se necesitan saber los periodos de pago, para calcular las fracciones de anyo
 * El interes esta acordado previamente y se supone que es en la duracion de los periodos de pago,
 * las clases superiores se ocuparan de calcularlo.
 */


//TODO: Implement actual floating cash flow
std::vector<double> FloatingLeg::getLegCashFlows(std::vector<double> dayCountFractionVector) {
    std::vector<double> legCashFlows{};
    for (int i = 0; i < dayCountFractionVector.size(); ++i) {

    }
    //for (auto currentFraction : dayCountFractionVector)
    //    legCashFlows.emplace_back(m_rate * currentFraction * m_notional);

    return legCashFlows;
}