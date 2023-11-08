#include <string>


class Enemy {
public:
    Enemy(int hp, int speed, std::string type)
        : hp_(hp), speed_(speed), type_(type) {}

    ~Enemy() {}

    void Move(); //use the speed_ variable to advance the position of the enemy, keep it void for now
    
    int hp();
    
    int speed();
    
    int poisonStatus();

    int slowedStatus();

    std::string type();
    
    void takeDamage(int damage); //decreases the hp_ variable and if hp reaches 0 than the enemy is automatically destroyed

    void applyPoison(int duration);

    void poisonDamage();

    void applySlowed(int duration);

    void slowedDamage();
private:
    int hp_;
    int speed_;
    std::string type_;
    int poison_; //If poison is larger than 0 that means that the enemy is poisoned
    // the length of time that the enemy is poisoned for depends on how large the poison
    //value is as the number decreases incrimently until 0
    int slowed_; 
    //state member needs to be implemented
};