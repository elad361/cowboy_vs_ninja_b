#pragma once
/**
* @author: Elad Shoham, 205439649
*/

#include <iostream>
#include <string>
#include <cmath>
#include "Point.hpp"

// Defines for cowboy
constexpr int COWBOY_START_HIT_POINTS = 110;
constexpr int COWBOY_START_BULLETS = 6;
constexpr int RELOAD = 6;
constexpr int SHOOT_POINTS = 10;

// Defines for ninja
constexpr int YUONG_SPEED = 14;
constexpr int YOUNG_HIT_POINTS = 100;
constexpr int TRAINED_SPEED = 12;
constexpr int TRAINED_HIT_POINTS = 120;
constexpr int OLD_SPEED = 8;
constexpr int OLD_HIT_POINTS = 150;
constexpr int SLASH_POINTS = 40;

using namespace std;
using namespace ariel;

namespace ariel {
    //Describes a charcter in the game
    class Character {
    private:
        Point location;
        int hitPoints;
        std::string name;
        bool isInATeam;

    public:
        // Constructor 
        Character(string& charName, const Point& startLocation, int startPoints) : name(charName), location(startLocation),  hitPoints(startPoints), isInATeam(false) {}
        Character(string& charName, const Point& startLocation) : name(charName), location(startLocation),  hitPoints(0), isInATeam(false) {}
        Character(const Character& other) : name(other.getName()), location(other.location), hitPoints(other.hitPoints), isInATeam(false) {}
        //
        Character(Character&&) = delete;

        Character& operator=(const Character& other) {
            if (this == &other) {
                return *this;
            }

            location = other.location;
            name = other.name;
            hitPoints = other.hitPoints;
            isInATeam = other.isInATeam;
            return *this;
        }

        Character& operator=(Character&&) = delete;


        // Destractur
        virtual ~Character() {}



        //Get
        int getHitPoints() const {return hitPoints;}
        string getName() const {return name;}
        Point getLocation() const {return location;}

        // Subtract points from hitPoints
        void hit(int points) {
            if (points < 0) {
                throw invalid_argument("cannot get negetive val");
            }
            hitPoints -= points;
            if (hitPoints < 0)  {
                hitPoints = 0;
            }
        }

        //

        bool isAlive() const {return hitPoints > 0;}

        //Distance from the given Character
        double distance(const Character* other) const {return location.distance(other->location);}

        void assighnToATeam();

        /*
        * Format:
        * Name of the character (the name will start with: N for ninja, C for cowboy). if not alive the fornat will be: "N/C (name)"
        * Number of hitting points (only if hitPoints > 0)
        * Location
        */
        virtual string print() const = 0;

        virtual int attack(Character*) = 0;

    protected:
        
        // for inherating classes
        void setLocation(const Point& loc) {location = loc;}
    };


    // Describes a charcter of type cowboy
    class Cowboy : public Character{
    private:
        int bullets;
    public:
        // Constructor 
        Cowboy(string charName, const Point& startLocation) : Character(charName, startLocation, COWBOY_START_HIT_POINTS), bullets(COWBOY_START_BULLETS) {}
        Cowboy(const Cowboy& other) : Character(other), bullets(other.bullets) {}
        Cowboy(Cowboy&&) = delete;

        Cowboy& operator=(const Cowboy&) = delete;
        Cowboy operator=(Cowboy&&) = delete; 
        // Destractur
        ~Cowboy() override {}

        /*
        * Shoot other and subtract 10 points from him
        * if out of ammo, reloading gun insted of shooting
        * return 1 if shut happend, 0 otherwise
        */
        int shoot(Character* other);

        bool hasbullets() const {return bullets > 0;}

        // Reload bullets
        void reload() {
            if (!isAlive()) {
                throw runtime_error(getName() + " is dead");
            }
            bullets = RELOAD;
        }

        string print() const override ;

        int attack(Character* other) override ;
    };


    // Describes a charcter of type ninja
    class Ninja : public Character{
    private:
        int speed;

    public:
        // Constructor 
        Ninja(string& charName, int hitPoints, const Point& startLocation, int speed) : Character(charName, startLocation, hitPoints), speed(speed) {}
        Ninja(const Ninja& other) : Character(other), speed(other.speed) {}
        Ninja(Ninja&&) = delete;

        Ninja& operator=(const Ninja&) = delete;
        Ninja& operator=(Ninja&&) = delete;
        // Destructur
        ~Ninja() override {}

        /*
        * Moves speed units towards the given character
        * reutrn the distance that left between them after moved
        */
        int move(const Character* other);

        /*
        * slash another character (only if distance <= 1)
        * Return 1 if slashed, 0 if not (too far from the enemy)
        */
        int slash(Character* other) const;

        string print() const override ;

        /*
        * If alive and close enough to the enemy, will slash him and return 1
        * Otherwise will get closer to the enemy and return 0
        */
        int attack(Character* other) override ;
    };

    class YoungNinja : public Ninja {
    public:
        YoungNinja(string charName, const Point& startLocation) : Ninja(charName, YOUNG_HIT_POINTS, startLocation, YUONG_SPEED) {}
        YoungNinja(const YoungNinja& other) : Ninja(other) {}
        YoungNinja(YoungNinja&&) = delete;
        YoungNinja& operator=(const YoungNinja&) = delete;
        YoungNinja& operator=(YoungNinja&&) = delete;
        ~YoungNinja() override {}
    };

    class TrainedNinja : public Ninja {
    public:
        TrainedNinja(string charName, const Point& startLocation) : Ninja(charName, TRAINED_HIT_POINTS, startLocation, TRAINED_SPEED) {}
        TrainedNinja(const TrainedNinja& other) : Ninja(other) {}
        TrainedNinja(TrainedNinja&&) = delete;
        TrainedNinja& operator=(const TrainedNinja&) = delete;
        TrainedNinja& operator=(TrainedNinja&&) = delete;
        ~TrainedNinja() override {}
    };

    class OldNinja : public Ninja {
    public:
        OldNinja(string charName, const Point& startLocation) : Ninja(charName, OLD_HIT_POINTS, startLocation, OLD_SPEED) {}
        OldNinja(const OldNinja& other) : Ninja(other) {}
        OldNinja(OldNinja&&) = delete;
        OldNinja& operator=(const OldNinja&) = delete;
        OldNinja& operator=(OldNinja&&) = delete;
        ~OldNinja() override {}
    };
}