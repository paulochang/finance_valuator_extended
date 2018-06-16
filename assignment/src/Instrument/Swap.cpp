#include "Swap.h"


double Swap::price() const {

    return theReceiver.price() - thePayer.price();

}
