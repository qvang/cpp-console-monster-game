#include "random.h"
#include <algorithm>
#include <iostream>
#include <string_view>

class Creature {
public:
  Creature(std::string_view name, char symbol, int health, int dmg, int gold)
      : m_name{name}, m_symbol{symbol}, m_health{health}, m_dmg{dmg},
        m_gold{gold} {}

  std::string_view name() { return m_name; }
  char symbol() { return m_symbol; }
  int health() { return m_health; }
  int dmg() { return m_dmg; }
  int gold() { return m_gold; }

  void reduceHealth(int health) { m_health -= health; }

  bool isDead() { return m_health <= 0; }

  void addGold(int gold) { m_gold += gold; }

protected:
  std::string m_name{};
  char m_symbol{};
  int m_health{};
  int m_dmg{};
  int m_gold{};
};

class Player : public Creature {
public:
  Player(std::string_view name, char symbol = '@', int health = 10, int dmg = 1,
         int gold = 0)
      : Creature{name, symbol, health, dmg, gold} {}

  void levelUp() {
    m_level++;
    m_dmg++;
  }

  int level() { return m_level; }

  bool hasWon() { return m_level == 20; }

private:
  int m_level{1};
};

class Monster : public Creature {
public:
  enum Type {
    dragon,
    orc,
    slime,
    max_types,
  };

  Monster(Type type) : Creature{monsterData[type]} {}

  static Monster getRandomMonster() {

    return Monster{static_cast<Type>(Random::get(0, max_types - 1))};
  }

private:
  static inline Creature monsterData[]{
      Creature{"dragon", 'D', 20, 4, 100},
      Creature{"orc", 'o', 4, 2, 25},
      Creature{"slime", 's', 1, 1, 10},
  };

  static_assert(max_types == std::ssize(monsterData));
};

int main() {

  for (int i{0}; i < 10; ++i) {
    Monster m{Monster::getRandomMonster()};
    std::cout << "A " << m.name() << " (" << m.symbol() << ") was created.\n";
  }

  return 0;
}
