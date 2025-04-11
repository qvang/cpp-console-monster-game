#include <iostream>
#include <string_view>

class Creature {
private:
  std::string m_name{};
  char m_symbol{};
  int m_health{};
  int m_dmg{};
  int m_gold{};

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
};

int main() {
  Creature o{"orc", 'o', 4, 2, 10};

  o.addGold(5);
  o.reduceHealth(1);
  std::cout << "The " << o.name() << " has " << o.health()
            << " health and is carrying " << o.gold() << " gold.\n";

  return 0;
}
