//
// Created by Paulo Chang on 6/19/18.
//

#ifndef SQF_ASSET_H
#define SQF_ASSET_H

#include "Instrument/Instrument.h"

class Asset : public Instrument {
protected:
    double m_spot_price;
    double m_volatility;

public:

    Asset(double spot_price, double volatility);

    double price() const override;

    double getVolatility() const;

};


#endif //SQF_ASSET_H
