#include <algorithm>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Character {
  char name[50];
  int health_point;
  int armor_point;
  int damage_point;
  int pos_x;
  int pos_y;
};

void InitializeMap(vector<vector<char>>& map, const int& size);
void CreateEnemies(vector<vector<char>>& map, vector<Character>& enemies);
void CreatePlayer(vector<vector<char>>& map, Character& player);
void PrintMap(const vector<vector<char>>& map, const int& size);
void PlaceCharacter(vector<vector<char>>& map, const Character& character, const char symbol);
void InputFromUser(string& command);
bool IsActionCommand(const string& command);
void LoadGame(Character& player, vector<Character>& enemies);
void SaveGame(const Character& player, const vector<Character>& enemies);
void AttackCharacter(Character& attacker, Character& defender);
bool IsCharacterDead(const Character& character);
bool GameOver(const Character& player, const vector<Character>& enemies);
void PlayerAction(Character& player, vector<Character>& enemies, vector<vector<char>>& map, const string& command);
void EnemyAction(Character& enemy, Character& player, vector<vector<char>>& map, const string& command);
bool IsDead(const Character& character);

int main() {
  srand(static_cast<unsigned int>(time(0)));

  const int map_size = 10;
  vector<vector<char>> map;
  InitializeMap(map, map_size);

  Character player;
  CreatePlayer(map, player);

  int enemies_amount = 5;
  vector<Character> enemies(enemies_amount);
  CreateEnemies(map, enemies);

  bool is_player_move = true;

  while (true) {
    InitializeMap(map, map_size);
    PlaceCharacter(map, player, 'P');
    for (const auto& enemy : enemies) {
      if (!IsDead(enemy)) {
        PlaceCharacter(map, enemy, 'E');
      }
    }

    PrintMap(map, map_size);

    if (is_player_move) {
        cout << "\nYour turn to action" << endl;
        string command;
        InputFromUser(command);

        if (IsActionCommand(command)) {
            PlayerAction(player, enemies, map, command);
        } else {
            if (command == "SAVE") {
                SaveGame(player, enemies);
            } else if (command == "LOAD") {
                LoadGame(player, enemies);
                continue;
            }
        }
        is_player_move = !is_player_move;

    } else {
        cout << "\nEnemies turn to action" << endl;
        for (auto& enemy : enemies) {
            if (!IsDead(enemy)) {
                string command(1, "WSAD"[rand() % 4]);
                EnemyAction(enemy, player, map, command);
            }
        }
        is_player_move = !is_player_move;
    }

    if (GameOver(player, enemies)) {
      break;
    }
    
    //map.clear();
  }
  return 0;
}




void InitializeMap(vector<vector<char>>& map, const int& size) {
  map.assign(size, vector<char>(size, '.'));
}

void CreateEnemies(vector<vector<char>>& map, vector<Character>& enemies) {
    int i = 1;
    for (auto& enemy : enemies) {
        std::string name = "Enemy #" + std::to_string(i);
        if (name.length() >= sizeof(enemy.name)) {
            std::cerr << "Name is too long!" << std::endl;
            return;
        }
        strncpy(enemy.name, name.c_str(), name.length());
        enemy.name[name.length()] = '\0';
        enemy.health_point = rand() % 101 + 50;
        enemy.armor_point = rand() % 51;
        enemy.damage_point = rand() % 16 + 15;

        while (true) {
            enemy.pos_x = rand() % map.size();
            enemy.pos_y = rand() % map.size();
            if (map[enemy.pos_y][enemy.pos_x] == '.') {
                map[enemy.pos_y][enemy.pos_x] = 'E';
                break;
            }
        }
        ++i;
    }
}

void CreatePlayer(vector<vector<char>>& map, Character& player) {
  std::cout << "Enter player name: ";
  std::cin >> player.name;
  std::cout << "Enter player health points: ";
  std::cin >> player.health_point;
  std::cout << "Enter player armor points: ";
  std::cin >> player.armor_point;
  std::cout << "Enter player damage points: ";
  std::cin >> player.damage_point;

  while (true) {
    player.pos_x = rand() % map.size();
    player.pos_y = rand() % map.size();
    if (map[player.pos_y][player.pos_x] == '.') {
        map[player.pos_y][player.pos_x] = 'P';
        break;
    }
  }
}

void PrintMap(const vector<vector<char>>& map, const int& size) {
  for (int i = 0; i < size + 1; ++i) {
    cout << "# ";
  }
  cout << "#" << endl;

  for (const auto& row : map) {
    cout << "#";
    for (const auto& col : row) {
      cout << ' ' << col;
    }
    cout << " #" << endl;
  }

  for (int i = 0; i < size + 1; ++i) {
    cout << "# ";
  }
  cout << "#\n" << endl;
}

void PlaceCharacter(vector<vector<char>>& map, const Character& character, const char symbol) {
  map[character.pos_y][character.pos_x] = symbol;
}

void InputFromUser(string& command) {
  do {
    cout << "Enter 'A', 'D', 'W', 'S' to move or 'SAVE', 'LOAD' to save or "
            "load: ";
    cin >> command;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    transform(command.begin(), command.end(), command.begin(),
              [](unsigned char ch) { return toupper(ch); });
    } while (command != "W" && command != "A" && command != "S" &&
           command != "D" && command != "SAVE" && command != "LOAD");
}

bool IsActionCommand(const string& command) {
  return command == "W" || command == "A" || command == "S" || command == "D";
}

void LoadGame(Character& player, vector<Character>& enemies) {
  filesystem::path file_path = "./save.bin";
  ifstream in_file(file_path, ios::binary);

  if (!in_file.is_open()) {
    cerr << "Failed to open file. Probably, file doesn't exist" << endl;
    return;
  }

  in_file.read(reinterpret_cast<char*>(&player), sizeof(Character));

  size_t enemies_count;
  in_file.read(reinterpret_cast<char*>(&enemies_count), sizeof(size_t));

  enemies.clear();
  enemies.resize(enemies_count);
  for (size_t i = 0; i < enemies_count; ++i) {
    in_file.read(reinterpret_cast<char*>(&enemies[i]), sizeof(Character));
  }

  in_file.close();
  cout << "The game is loaded successfully" << endl;
}

void SaveGame(const Character& player, const vector<Character>& enemies) {
  filesystem::path file_path = "./save.bin";
  ofstream out_file(file_path, ios::binary);

  if (!out_file.is_open()) {
    cerr << "Failed to open file." << endl;
    return;
  }

  out_file.write(reinterpret_cast<const char*>(&player), sizeof(Character));

  size_t enemy_count = enemies.size();
  out_file.write(reinterpret_cast<const char*>(&enemy_count),
                 sizeof(enemy_count));

  for (const auto& enemy : enemies) {
    out_file.write(reinterpret_cast<const char*>(&enemy), sizeof(Character));
  }

  out_file.close();
  cout << "The game saved successfully" << endl;
}

bool IsDead(const Character& character) { return character.health_point < 1; }

bool GameOver(const Character& player, const vector<Character>& enemies) {
  if (player.health_point <= 0) {
    cout << "You are defeated!" << endl;
    return true;
  }

  for (const auto& enemy : enemies) {
    if (enemy.health_point > 0) {
      return false;
    }
  }
  cout << "All enemies are dead! You win!" << endl;
  return true;
}

void Attack(Character& attacker, Character& defender) {
  defender.armor_point -= attacker.damage_point;
  if (defender.armor_point < 0) {
    defender.health_point += defender.armor_point;
    defender.armor_point = 0;
  }

  cout << attacker.name << " attacks " << defender.name << " for "
       << attacker.damage_point << " damage!" << endl;
}

void PlayerAction(Character& player, vector<Character>& enemies, vector<vector<char>>& map, const string& command) {
    int map_size = map.size();
    int new_x = player.pos_x;
    int new_y = player.pos_y;

    if (command == "W")
        --new_y;
    else if (command == "S")
        ++new_y;
    else if (command == "A")
        --new_x;
    else if (command == "D")
        ++new_x;

    if (new_x >= 0 && new_x < map_size && new_y >= 0 && new_y < map_size) {
        if (map[new_y][new_x] == '.') {
            map[player.pos_y][player.pos_x] = '.';
            player.pos_x = new_x;
            player.pos_y = new_y;
        } else if (map[new_y][new_x] == 'E') {
            for (auto& enemy :enemies) {
                if (enemy.pos_x == new_x && enemy.pos_y == new_y) {
                    Attack(player, enemy);
                    if (IsDead(enemy)) {
                        map[enemy.pos_y][enemy.pos_x] = '.';
                        cout << enemy.name << " is dead" << endl;
                    }
                    break;
                }
            }
        }
    }
}

void EnemyAction(Character& enemy, Character& player, vector<vector<char>>& map, const string& command) {
    int map_size = map.size();
    int new_x = enemy.pos_x;
    int new_y = enemy.pos_y;

    if (command == "W")
        --new_y;
    else if (command == "S")
        ++new_y;
    else if (command == "A")
        --new_x;
    else if (command == "D")
        ++new_x;

    if (new_x >= 0 && new_x < map_size && new_y >= 0 && new_y < map_size) {
        if (map[new_y][new_x] == '.') {
            map[enemy.pos_y][enemy.pos_x] = '.';
            enemy.pos_x = new_x;
            enemy.pos_y = new_y;
        } else if (map[new_y][new_x] == 'P') {
            Attack(enemy, player);
        }
    }
}


