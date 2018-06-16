//
// Created by Paulo Chang on 5/1/18.
//

#ifndef SQF_BOND_H
#define SQF_BOND_H

#include "Leg/FixedLeg.h"
#include "Instrument.h"

class Bond : public Instrument {
public:
    Leg &theReceiver;

    double price() const override;

    Bond(Leg &Receiver) : Instrument(),
                          theReceiver{Receiver} {}
};

#endif //SQF_BOND_H
