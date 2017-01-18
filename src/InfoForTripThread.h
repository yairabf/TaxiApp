//
// Created by hanani on 17/01/17.
//

#ifndef ADPROG1_1_INFOFORTRIP_H
#define ADPROG1_1_INFOFORTRIP_H


#include "BreadthFirstSearch.h"
#include "TaxiStation.h"

class InfoForTripThread {
private:
    TaxiStation* taxiStation;
    TripInfo* tripInfo;

public:
    /**
     * constructor
     * @param ts taxi center.
     * @param t trip info.
     * @return new InfoForTrip
     */
    InfoForTripThread(TaxiStation* ts, TripInfo* t);

    /**
     * getter.
     * @return taxi station.
     */
    TaxiStation *getTaxiStation() const;

    /**
     * getter.
     * @return trip info.
     */
    TripInfo *getTripInfo() const;

};


#endif //ADPROG1_1_INFOFORTRIP_H
