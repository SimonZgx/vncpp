//
// Created by admin on 2021/1/16.
//

#include "event_engine/event_engine.h"

#include <iostream>

event_engine::EventEngine::EventEngine() {
    std::cout << "Constructor!!" << std::endl;
}

void event_engine::EventEngine::Start() {

    while (active_) {

    }
}

void event_engine::EventEngine::Stop() {
    active_ = false;
}
