/**
* @author: Elad Shoham, 205439649
*/
#include "doctest.h"
#include "Team.cpp"
#include <stdexcept>
#include <cmath>

using namespace std;

TEST_CASE("Point") {
    Point p0(), p1(0, 1), p3(3, 0);
    Point p2(moveTowards(p0, p3, 2.3));
    CHECK(p1.distance(p0) == 1);
    CHECK(p0.distance(p2) == 2.3);
    double dis = sqrt(pow(0 - 2.3, 2) + pow(1 - 0, 2));
    CHECK(p1.distance(p2) == dis);
    CHECK(p0.distance(p2) == 2.3);
    CHECK_THROWS_AS(moveTowards(P1, P0, -1), std::string)
}


TEST_CASE("Character") {
    Character* c = new Cowboy("cowboy", Point(26, 3.4));
    Character* yn = new YoungNinja("young ninja", Point(9.7, 2));
    Character* tn = new TrainedNinja("trained ninja", Point(0.6, 5));
    Character* on = new OldNinja("old ninja", Point(98, 6.54));
    CHECK(c.getHitPoints() == 110);
    CHECK(tn.getLocation().print() == "(0.6, 5)");
    CHECK(on.getName() == "old ninja");
    for (int i = 0; i < 6; i++) {
        c.attack(yn);  //attack is pure virtual in Character
    }
    CHECK(c.attack(yn) == 0);  //should be out of ammo
    CHECK(yn.isAlive() == true);
    CHEK(tn.attack(yn) == 0);
    CHECK(tn.attack(yn) == 40);
    CHECK(yn.isAlive() == 0);
    CHECK(yn.print() == "N (young ninja)\n(9.7, 2)\n");
    CHECK(c.print() == "C cowboy\n110\n(26, 3.4)\n");
}

    TEST_CASE("Team") {
        Team whiteTeam(new OldNinja("white1", Point(6.78, 9.8)));
        whiteTeam.add(new  YoungNinja("white2", Point(1.47, 36.4)));
        CHECK(whiteTeam.stillAlive() == 2);
        CHECK(whiteTeam.print() == "N white1\n150\n(6.78, 9.8)\n\nN white2\n100\n(1.47, 36.4)\n");
        Team blackTeam(new Cowboy("black", Point(27, 5)));
        CHECK(blackTeam.attack(&whiteTeam) == 1);
        CHECK(whiteTeam.print() == "N white1\n140\n(6.78, 9.8)\n\nN white2\n100\n(1.47, 36.4)");
        for (int i = 0; i < 15; i++) {
            blackTeam.attack(&whiteTeam)
        }
        CHECK(whiteTeam.orint() == "N (white1)\n(6.78, 9.8)\n\nN white2\n90\n(1.47, 36.4)");
        CHECK(whiteTeam.stillAlive() == 1);

        Team2 team2(new Cowboy("c", Point(0, 0)));
        for (int i = 0; i < 9; i++) {
            team2.add(new Cowboy("c", Point(i, i)));
        }
        Character* additional = new Cowboy("add", Point(5, 0));
        CHECK_THROWS_AS(team2.add(additional), std::string);
        delete additional;
    }