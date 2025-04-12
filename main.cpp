#include "random.h"
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

std::string getUserInput() {
  std::cout << "Enter your name: ";
  std::string name;
  std::cin >> name;
  return name;
}

void attackPlayer(Monster &m, Player &p) {

  m.reduceHealth(p.dmg());
  std::cout << "You hit the " << m.name() << " for " << p.dmg() << " damage.\n";

  if (m.isDead()) {

    std::cout << "You killed the " << m.name() << ".\n";

    p.levelUp();
    std::cout << "You are now level " << p.level() << ".\n";

    p.addGold(m.gold());
    std::cout << "You found " << m.gold() << " gold.\n";
  }
}
void attackMonster(Monster &m, Player &p) {

  p.reduceHealth(m.dmg());
  std::cout << "The " << m.name() << " has hit you for " << m.dmg() << ".\n";
}

void fightMonster(Player &p) {

  Monster m{Monster::getRandomMonster()};

  std::cout << "You have encountered a " << m.name() << " (" << m.symbol()
            << ").\n";

  while (true) {
    if (m.isDead() || p.isDead() || p.hasWon())
      break;

    std::cout << "(R)un or (F)ight: ";
    char input{};
    std::cin >> input;

    if (input == 'f') {
      attackPlayer(m, p);
      attackMonster(m, p);
    }

    if (input == 'r') {
      bool success = static_cast<bool>(Random::get(0, 1));
      if (success) {
        std::cout << "You successfully fled.\n";
        break;
      } else {
        std::cout << "You failed to flee.\n";
        attackMonster(m, p);
      }
    }
  }
}

int main() {

  // Init player
  Player player{getUserInput()};
  std::cout << "Welcome, " << player.name() << '\n';

  while (true) {
    if (player.isDead()) {
      std::cout << "You died at level " << player.level() << " and with "
                << player.gold() << " gold.\n";
      break;
    }

    fightMonster(player);
  }

  return 0;
}
