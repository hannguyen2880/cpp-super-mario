// Item.h
#pragma once
#include "../Actor.h"
#include "../MarioCharacter.h"

enum class ItemType {
    COIN,
    MUSHROOM,
    FIRE_FLOWER,
    STAR
};

class Item : public Actor {
protected:
    ItemType type;
    bool isCollected;
    
public:
    Item(ItemType type, float x, float y);
    virtual ~Item() = default;
    
    virtual void Update();
    virtual void OnCollect(MarioCharacter& player);
    
    bool IsCollected() const { return isCollected; }
    ItemType GetType() const { return type; }
};

// Specific item types
class Coin : public Item {
public:
    Coin(float x, float y) : Item(ItemType::COIN, x, y) {}
    
    void OnCollect(MarioCharacter& player) override {
        player.AddScore(100);
        isCollected = true;
    }
};

class PowerUp : public Item {
public:
    PowerUp(ItemType type, float x, float y) : Item(type, x, y) {}
    
    void OnCollect(MarioCharacter& player) override {
        switch(type) {
            case ItemType::MUSHROOM:
                //player.GrowBig();
                break;
            case ItemType::FIRE_FLOWER:
                //player.SetFirePower();
                break;
            case ItemType::STAR:
                //player.SetInvincible();
                break;
        }
        isCollected = true;
    }
};
