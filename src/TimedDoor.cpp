// Copyright 2021 dash
#include "TimedDoor.h"
#include <iostream>
#include <string>

DoorTimerAdapter::DoorTimerAdapter(TimedDoor& door_) : door(door_) {}

TimedDoor::TimedDoor(int _t) {
    this->lock();
    this->iTimeout = _t;
    this->adapter = new DoorTimerAdapter(*this);
}

void DoorTimerAdapter::Timeout() {
    door.DoorTimeOut();
}

bool TimedDoor::isDoorOpened() {
    return opened;
}
void TimedDoor::unlock() {
    opened = true;
    Timer n;
    n.tregister(this->iTimeout, this->adapter);
}
void TimedDoor::lock() {
    opened = false;
}
void TimedDoor::DoorTimeOut() {
    std::string s = "close the door!";
    throw(s);
}
void TimedDoor::throwState() {
    std::string s1 = "the door is closed!";
    std::string s2 = "the door is opened!";
    if (!isDoorOpened()) {
        throw (s1);
    }
    else {
        throw (s2);
    }
}
void Timer::sleep(int _t) {
    time_t beg = time(nullptr);
    while (time(nullptr) - beg < _t) {
        continue;
    }
}
void Timer::tregister(int k, TimerClient* client) {
    sleep(k);
    client->Timeout();
}