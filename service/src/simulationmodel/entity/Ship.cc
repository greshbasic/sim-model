#define _USE_MATH_DEFINES
#include "Ship.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"

Ship::Ship(const JsonObject& obj) : IEntity(obj) {
    // location TBD
    this->position = Vector3(515, 320, -228.623);
}

Ship::~Ship() {}

void Ship::update(double dt) {}
