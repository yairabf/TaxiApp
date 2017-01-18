
#include "InfoForTripThread.h"

InfoForTripThread::InfoForTripThread(TaxiStation* ts, TripInfo *t):taxiStation(ts), tripInfo(t) {}

TaxiStation *InfoForTripThread::getTaxiStation() const {
    return taxiStation;
}

TripInfo *InfoForTripThread::getTripInfo() const {
    return tripInfo;
}
