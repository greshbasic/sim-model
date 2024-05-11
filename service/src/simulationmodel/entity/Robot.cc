#include "Robot.h"
#include "BeelineStrategy.h"
#include "Package.h"

#include "SimulationModel.h"

Robot::Robot(const JsonObject& obj) : IEntity(obj) {
    original_position = this->getPosition();
    float current_x = original_position.x;
    float current_y = original_position.y;
    float current_z = original_position.z;
    int random_x = static_cast<int>(rand()) % 301 + 100;
    int plus_or_minus_x = static_cast<int>(rand()) % 2;
    if (plus_or_minus_x == 1) {
        current_x += random_x;
    } else {
        current_x -= random_x;
    }

    int random_z = static_cast<int>(rand()) % 301 + 100;
    int plus_or_minus_z = static_cast<int>(rand()) % 2;
    if (plus_or_minus_z == 1) {
        current_z += random_z;
    } else {
        current_z -= random_z;
    }

    this->setPosition(Vector3(current_x, current_y, current_z));
}

void Robot::update(double dt) {
    // elsewhere set it so robot spawns at a random location
    // then once it gets a notification about its package being
    // delivered, it will move to the package's location

    if (package && canPickUpPackage) {
        Vector3 packagePos = package->getPosition();
        double to_pack = position.dist(packagePos);
        if (to_pack < 5) {
            receive(package);
            canPickUpPackage = false;
            model->pirates_can_steal = false;
            package->canBeStolen = false;
        }
        if (!movement) {
            Vector3 packagePosition = package->getPosition();
            movement = new BeelineStrategy(position, packagePosition);
        } else {
            movement->move(this, dt);
        }
    }
}

void Robot::receive(Package* p) { package = p; }
