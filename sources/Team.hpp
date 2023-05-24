#pragma once
/**
* @author: Elad Shoham, 205439649
*/

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "Character.hpp"

using namespace std;
using namespace ariel;

namespace ariel {

    /*
    * order of going thru: by distance from leader (instead of ninjas and then cowboys)
    */
    class Team {
    private:
        vector<Character*> members;
        Character* leader;

        // rearrange the members by distsnce to leader
        void rearrange();

        // If the old leader is dead.
        // return 1 if found a new leader, 0 if all members are dead
        int findNewLeader();
    public:
        Team(Character* lead) : leader(lead) {
            try {
                leader->assighnToATeam();
            } catch (const runtime_error& err) {
                throw err;
            }
            members.push_back(lead);
        }

        Team(const Team& other) = delete;
        Team(Team&&) = delete;
        Team& operator=(const Team&) = delete;
        Team& operator=(Team&&) = delete;

        virtual ~Team() {
            for (auto it = members.begin(); it != members.end(); it++) {
                delete *it;
            }
        }

        virtual void add(Character* newM);

        // return the number of members in the other team that is still alive after the attack
        virtual int attack(Team* other);

        string print() const;

        int stillAlive() const;
        Character* getLeader() {return leader;}  // get Leader

        Character* findCloses(const Character* other) const;

        vector<Character*>& getMembers() {return members;}

    protected:
        void setLeader(Character* newL) {
            if (find(members.begin(), members.end(), newL) == members.end()) {
                throw string(newL->getName() + " is not in the team\n");
            }
            leader = newL;
        }
        //int getNOM() const {return static_cast<int>(members.size());} // get Num Of Members
    };



    class Team2 : public Team {
    public:
        Team2(Character* leader) : Team(leader) {};
        Team2(const Team2&) = delete;
        Team2(Team2&&) = delete;
        Team2& operator=(const Team2) = delete;
        Team2 operator=(Team2&&) = delete;

        ~Team2() override {
            /*for (auto it = getMembers().begin(); it != getMembers().end(); it++) {
                delete *it;
            }*/
        }

        void add(Character* newM) override;
        int attack(Team* other) override;
    };

    
    /*
    * select victom: the one with less lives (on the other team)
    */
    class SmartTeam : public Team {
    public:
        SmartTeam(Character* leader) : Team(leader) {}
        SmartTeam(const SmartTeam&) = delete;
        SmartTeam(SmartTeam&&) = delete;
        SmartTeam& operator=(const SmartTeam) = delete;
        SmartTeam operator=(SmartTeam&&) = delete;

        ~SmartTeam() override {}

        int attack(Team* other) override;
    private:
        Character* findVictom(Team* other) const;

    };
    
}