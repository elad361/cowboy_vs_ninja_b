/**
* @author: Elad Shoham, 205439649
*/

#include "Team.hpp"

using namespace std;
using namespace ariel;

namespace ariel {
    void Team::add(Character* newM) {
        if (find(members.begin(), members.end(), newM) != members.end()) {
            throw runtime_error(newM->getName() + " is already in this team");
        }

        if (members.size() >= 10) {
            throw runtime_error("Team is full");
        }

        try {
            newM->assighnToATeam();
        } catch ( const runtime_error& err) {
            throw err;
        }

        double newDis = newM->distance(leader);
        auto it = members.begin() + 1;
        while (it != members.end()) {
            if ((*it)->distance(leader) > newDis) break;
            it++;
        }

        members.insert(it, newM);
    }

    string Team::print() const {
        string str = "";
        for (auto it = members.begin(); it != members.end(); it++) {
            str += (*it)->print();
            cout << "\n";
            str += "\n";
        }
        return str;
    }


    int Team::stillAlive() const {
        int counter = 0;
        for (auto it = members.begin(); it != members.end(); it++) {
            if ((*it)->isAlive()) counter++;
        }
        return counter;
    }

    Character* Team::findCloses(const Character* other) const {
        if (!stillAlive()) return nullptr;

        Character* closes/* = leader*/;
        auto it = members.begin();
        while (!(*it)->isAlive()) it++;
        closes = *it;
        for (; it != members.end(); it++) {
            if (((*it)->distance(other) < closes->distance(other)) && (*it)->isAlive()) {
                closes = *it;
            }
        }
        return closes;
    }


    void Team::rearrange() {
        // Let the build sort function sort the members by distance from the leader
        // With a lambda function as a custom comparator
        sort(members.begin(), members.end(),
            [this] (Character* a, Character* b) {return a->distance(this->leader) < b->distance(this->leader);});
    }

    int Team::findNewLeader() {
        Character* newLeader = findCloses(leader);

        if (newLeader == nullptr) return 0;

        rearrange();
        return 1;
    }

    int Team::attack(Team* other) {
        if (other == nullptr) {
            throw invalid_argument("given a null pointer");
        }

        if (!stillAlive()) throw runtime_error("No alive Character in this team");
        if (!(other->stillAlive())) throw runtime_error("No alive Character in other team");

        if (!leader->isAlive()) {
            findNewLeader();
        }

        Character* enemy = other->findCloses(leader);
        if (enemy == nullptr) return 0;

        for (auto it = members.begin(); it != members.end(); it++) {
            (*it)->attack(enemy);
            if (!enemy->isAlive()) {
                enemy = other->findCloses(leader);

                if (enemy == nullptr) break;
            }
        }

        return other ->stillAlive();
    }

    int Team2::attack(Team* other) {
        if (other == nullptr) {
            throw invalid_argument("given a null pointer");
        }

        if (!stillAlive()) throw runtime_error("No alive Character in this team");
        if (!(other->stillAlive())) throw runtime_error("No alive Character in other team");

        if (!(getLeader()->isAlive())) {
            setLeader(findCloses(getLeader()));
        }

        Character* enemy = other->findCloses(getLeader());
        if (enemy == nullptr) return 0;
        vector<Character*>& memb = getMembers();
        for (auto it = memb.begin(); it != memb.end(); it++) {
            (*it)->attack(enemy);
            if (!enemy->isAlive()) {
                enemy = other->findCloses(getLeader());

                if (enemy == nullptr) break;
            }
        }
        return other->stillAlive();
    }

    void Team2::add(Character* newM) {
        vector<Character*>& memb = getMembers();
        if ((std::find(memb.begin(), memb.end(), newM) != memb.end())) {
            throw runtime_error(newM->getName() + " is already in this team");
        }

        if (memb.size() >= 10) {
            throw runtime_error("Team is full");
        }

        try {
            newM->assighnToATeam();
        }
        catch (const runtime_error& err){
            throw err;
        }
        memb.push_back(newM);
    }
}

Character* SmartTeam::findVictom(Team* other) const {
    if (other->stillAlive() == 0) {
        return nullptr;
    }

    vector<Character*> otherMembers = other->getMembers();
    auto it = otherMembers.begin();

    while (!((*it)->isAlive())) {
        it++;
    }

    Character* victom = *it;
    while (it != otherMembers.end()) {
        if ((*it)->isAlive() && (*it)->getHitPoints() < victom->getHitPoints()) {
            victom = *it;
        }
        it++;
    }
    return victom;
}

int SmartTeam::attack(Team* other) {
    if (other == nullptr) {
            throw invalid_argument("given a null pointer");
    }

    if (!stillAlive()) throw runtime_error("No alive Character in this team");
    if (!(other->stillAlive())) throw runtime_error("No alive Character in other team");

    if (!(getLeader()->isAlive())) {
        setLeader(findCloses(getLeader()));
    }

    Character* enemy = findVictom(other);

    for (auto it = getMembers().begin(); it != getMembers().end(); it++) {
        (*it)->attack(enemy);
        if (!enemy->isAlive()) {
            enemy = findVictom(other);
            if (enemy == nullptr) {
                break;
            }
        }
    }
    return other->stillAlive();
}