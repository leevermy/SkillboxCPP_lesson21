#include <ctime>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
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

void InitializeMap(vector<vector<char>>& map, const int& size) {
    map.resize(size, vector<char>(size, '.'));
}

void CreateEnemy(vector<vector<char>>& map, Character& enemy, int& enemy_number) {
  std::string name = "Enemy #" + std::to_string(enemy_number + 1);
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
    if (map[enemy.pos_y][enemy.pos_x] == '.') break;
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
    if (map[player.pos_y][player.pos_x] == '.') break;
  }
}

void PrintMap(const vector<vector<char>>& map, const int& size) {
    cout << endl;
    for (int i = 0; i < size + 1; ++i) {
        cout << "# ";
    }
    cout << "#" << endl;

    for (const auto & row : map) {
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

void InputFromUser(string& symbol) {
    do {
        cout << "Enter \'A\', \'D\', \'W\', \'S\' to move ";
        cout << "or \'SAVE\', \'LOAD\' to save or download: ";
        cin >> symbol;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        transform(symbol.begin(), symbol.end(), symbol.begin(), [](unsigned char ch) {
            return toupper(ch);
        });

    } while (symbol != "A" && symbol != "D" && symbol != "W" && symbol != "S" && symbol != "SAVE" && symbol != "LOAD");
    


}

bool IsMovingSymbol(const string& symbol) {
    return symbol == "A" || symbol == "D" || symbol == "W" || symbol == "S";
}

void Load();

void Save();

void MoveCharacter(vector<vector<char>>& map, Character& character, const string& symbol) {
    int map_size = map.size();
    int new_x = character.pos_x;
    int new_y = character.pos_y;

    if (symbol == "W") --new_y;
    else if (symbol == "S") ++new_y;
    else if (symbol == "A") --new_x;
    else if (symbol == "D") ++new_x;

    if (new_x >= 0 && new_x < map_size && new_y >= 0 && new_y < map_size) {
        if (map[new_y][new_x] == '.') {
            map[character.pos_y][character.pos_x] = '.';
            character.pos_x = new_x;
            character.pos_y = new_y;
        } else if (map[new_y][new_x] == 'P' || map[new_y][new_x] == 'E') {
            
        }
    }

}

void Attack() {
    player.armor_point -= enemy.damage_point;
            if (player.armor_point < 0) {
                player.health_point += player.armor_point;
                player.armor_point = 0;
            }
}


bool IsDead(const Character& character) {
    return character.health_point <= 0;
}



bool GameOver(const Character& player, const vector<Character>& enemies) {
    if (player.health_point <= 0) {
        cout << "You are defeted!" << endl;
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

int main() {
    const int map_size = 20;
    vector<vector<char>> map;
    InitializeMap(map, map_size);

    Character player;
    CreatePlayer(map, player);

    int enemies_amount = 5;
    vector<Character> enemies(enemies_amount);
    for (int i = 0; i < enemies_amount; ++i) {
        CreateEnemy(map, enemies[i], i);
    }


    while (true) {
        PlaceCharacter(map, player, 'P');
        for (const auto& enemy : enemies) {
            if (IsDead(enemy)) {
                PlaceCharacter(map, enemy, '.');
            } else {
                PlaceCharacter(map, enemy, 'E');
            }
        }

        PrintMap(map, map_size);

        string symbol;
        InputFromUser(symbol); 

        if (IsMovingSymbol(symbol)) {
            MoveCharacter(map, player, symbol);
        } else {
            if (symbol == "SAVE") {
                Save();
            } else {
                Load();
                continue;
            }
        }
        

        for (auto& enemy : enemies) {
            string symbol = string(1, "L,R,D,U"[rand() % 4]);
            MoveCharacter(map, enemy, symbol);
        }
        



        if (GameOver(player, enemies)) {
            break;
        }
    }
    return 0;
}