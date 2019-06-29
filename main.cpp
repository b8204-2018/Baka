#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;


class MagicCreatures {
private:
    int HP;
    int Damage;
public:
    MagicCreatures() {}

    void Attack(MagicCreatures &target) {
        target.changeHP(getDemage());
    }

    void SetHP(int a) {
        HP = a;
    }

    int getHP() {
        return HP;
    }

    void setDamage(int d) {
        Damage = d;
    }

    int getDemage() {
        return Damage;
    }

    void changeHP(int emount) {
        HP -= emount;
        //this->HP = HP - emount;
        //return HP;
    }
};

class SoulGem {
private:
    short SoulGemScore;
public:
    SoulGem() {}

    SoulGem(short score) {
        SoulGemScore = score;
    }

    int getSoulGemScore() {
        return SoulGemScore;
    }

    int setSoulGemScore(short s) {
        SoulGemScore = s;
    }

    bool isSoulGemOk() {
        if (SoulGemScore >= 3) {
            return true;
        } else {
            return false;
        }
    }

    void WasteSoulGemScore(short emount) {
        SoulGemScore -= emount;
    }
};

class magicGirls : public MagicCreatures {
public:
    SoulGem soulGem;

    magicGirls() {
        this->soulGem = soulGem;
    }


};

class Pink : public magicGirls {
public:

    Pink(int HP, int Damage, short SoulGemScore) {
        this->SetHP(HP);
        this->setDamage(Damage);
        this->pinkSoulGeme.setSoulGemScore(SoulGemScore);
    }

    SoulGem pinkSoulGeme = SoulGem(pinkSoulGeme.getSoulGemScore());

    void SuperAttack(MagicCreatures &targett) {
        targett.changeHP(getDemage() * 3);
    };
};

class Blue : public magicGirls {
public:

    Blue(int HP, int Damage, short SoulGemScore) {
        this->SetHP(HP);
        this->setDamage(Damage);
        this->blueSoulGeme.setSoulGemScore(SoulGemScore);
    }

    SoulGem blueSoulGeme = SoulGem(blueSoulGeme.getSoulGemScore());

    void Heal(magicGirls &target) {
        target.changeHP(-(getHP() * 0.5));
    };
};

class Purple : public magicGirls {
public:

    Purple(int HP, int Damage, short SoulGemScore) {
        this->SetHP(HP);
        this->setDamage(Damage);
        this->purpleSoulGeme.setSoulGemScore(SoulGemScore);
    }

    SoulGem purpleSoulGeme = SoulGem(purpleSoulGeme.getSoulGemScore());

    bool StopTime() {
        return true;
    };
};

class Witch : public MagicCreatures {
public:
    Witch(int HP, int Damage) {
        this->SetHP(HP);
        this->setDamage(Damage);
    }

    int AttackOnArea() {
        return 123;
    }
};

int main() {
    Witch witch(200, 30);
    Purple purple(60, 10, 3);
    Blue blue(80, 30, 6);
    Pink pink(100, 20, 6);
    cout << "blue: " << blue.getHP() << endl;
    cout << "pink: " << pink.getHP() << endl;
    cout << "purple: " << purple.getHP() << endl;
    cout << "witch: " << witch.getHP() << endl;
    vector<magicGirls> magic;
    magic.push_back(purple);
    magic.push_back(pink);
    magic.push_back(blue);
    while ((witch.getHP() > 0) && ((pink.getHP() > 0) || (blue.getHP() > 0) || (purple.getHP() > 0))) {
        bool time_stoped;
        int x, y, z;
        cout << "input 1 for attack" << endl;
        cout << "input 2 for superattack" << endl;
        cin >> x;
        switch (x) {
            case 1: {
                pink.Attack(witch);
                break;
            }
            case 2: {
                if (pink.pinkSoulGeme.isSoulGemOk()) {
                    pink.SuperAttack(witch);
                    pink.pinkSoulGeme.WasteSoulGemScore(3);
                } else {
                    cout << "too weak!" << endl;
                }
                break;
            }
            default:
                cout << "neverno" << endl;
                break;
        }
        cout << "input 1 for attack" << endl;
        cout << "input 2 for heal" << endl;
        cin >> y;
        switch (y) {
            case 1: {
                blue.Attack(witch);
                break;
            }
            case 2: {
                if (blue.blueSoulGeme.isSoulGemOk()) {
                    if ((pink.getHP() <= blue.getHP()) && (pink.getHP() <= purple.getHP())) {
                        blue.Heal(pink);
                    } else {
                        if (purple.getHP() <= blue.getHP()) {
                            blue.Heal(purple);
                        } else {
                            blue.Heal(blue);
                        }
                    }
                    blue.blueSoulGeme.WasteSoulGemScore(3);
                } else {
                    cout << "too weak!" << endl;
                }


                break;
            }
            default:
                cout << "neverno" << endl;
                break;

        }
        cout << "input 1 for attack" << endl;
        cout << "input 2 for stoptime" << endl;
        cin >> z;
        switch (z) {
            case 1: {
                purple.Attack(witch);
                break;
            }
            case 2: {
                if (purple.purpleSoulGeme.isSoulGemOk()) {
                    time_stoped = purple.StopTime();
                    purple.purpleSoulGeme.WasteSoulGemScore(3);
                } else {
                    cout << "too weak!" << endl;
                }

                break;
            }
            default: {
                cout << "neverno" << endl;
                break;
            }
        }

        if (!time_stoped) {
            srand(time(NULL));
            int rand = rand % 1;
            switch (rand) {
                case 1 : {

                    for (magicGirls x:magic) {
                        x.changeHP(witch.AttackOnArea());
                    }
                    break;
                }
                default: {
                    //  srand(time(NULL));
                    int random_target = rand % 3 + 1;
                    switch (random_target) {
                        case 1 : {
                            witch.Attack(blue);
                            break;
                        }
                        case 2 : {
                            witch.Attack(pink);
                            break;
                        }
                        case 3 : {
                            witch.Attack(purple);
                            break;
                        }
                        default : {
                            witch.Attack(pink);
                            break;
                        }

                    }
                }

            }
        }
        cout << "blue: " << blue.getHP() << endl;
        cout << "pink: " << pink.getHP() << endl;
        cout << "purple: " << purple.getHP() << endl;
        cout << "witch: " << witch.getHP() << endl;
        time_stoped = false;
    }
    if (witch.getHP() <= 0) { cout << "Witch is dead!" << endl; }
    if ((pink.getHP() <= 0) || (blue.getHP() <= 0) || (purple.getHP() <= 0)) {
        cout << "Magic Girls all dead!" << endl;
    }
    return 0;
}