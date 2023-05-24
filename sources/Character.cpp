/**
* @author: Elad Shoham, 205439649
*/

#include "Character.hpp"

using namespace std;
using namespace ariel;

namespace ariel {
    void Character::assighnToATeam() {
        if (isInATeam != false) {
            throw runtime_error(name + " alreadi in the a team");
        }
        else isInATeam = true;
    }

    int Cowboy::shoot(Character* other) {
        if (other == this) {
            throw runtime_error("cannot shoot himself");
        }

        if (!isAlive()) {
            throw runtime_error(getName() + "is dead");
        }

        if (!(other->isAlive())) {
            throw runtime_error(other->getName() + "is dead");
        }

        if (bullets <= 0) {
            return 0;
        }

        other->hit(SHOOT_POINTS);
        bullets--;
        return 1;
    }

    string Cowboy::print() const {
        string str = "C";
        if (isAlive()) {
            str += " " + getName() + "\n" + to_string(getHitPoints()) + "\n";
        }
        else {
            str += " (" + getName() + ")\n";
        }
        cout << str;
        str += getLocation().print();
        return str;
    }

    int Cowboy::attack(Character* other) {
        if (other == this) {
            throw runtime_error("cannot shoot himself");
        }
        
        int success = 0;

        if (!isAlive()) {
            return success;
        }
        if (!hasbullets()) reload();
        else {
            try {
                success = shoot(other);
            } catch (const runtime_error& err) {
                throw err;
            }
        }
        return success;
    }

    int Ninja::move(const Character* other) {
        setLocation(Point::moveTowards(getLocation(), other->getLocation(), speed));
        return distance(other);
    }

    int Ninja::slash(Character* other) const {
        if (other == this) {
            throw runtime_error("cannot slash himself");
        }

        if (!isAlive()) {
            throw runtime_error(getName() + "is dead");
        }
        if (!(other->isAlive())) {
            throw runtime_error(other->getName() + "is dead");
        }

        if (distance(other) > 1) return 0;  // not close enough
        
        other->hit(SLASH_POINTS);
        return 1;
    }

    int Ninja::attack(Character* other) {
        int success = 0;

        if (!isAlive()){
            return success;
        }

        try {
            if (!slash(other)) {
                move(other);
                success = 0;
            }
            else success = 1;
        } catch (const runtime_error& err) {
            throw err;
        }
        return success;
    }

    string Ninja::print() const {
        string str = "N ";
        if (isAlive()) {
            str += getName() + "\n" + to_string(getHitPoints()) + "\n";
        }
        else {
            str += "(" + getName() + ")\n";
        }
        cout << str;
        str += getLocation().print();
        return str;
    }
}