#include <cstring>
#include <ctime>
#include <iostream>
#include <string>

struct Character {
  char name[50];
  int health_point;
  int armor_point;
  int damage_point;
  int pos_x;
  int pos_y;
};

char** CreateField(const int& field_size);
void DeleteField(char** array, const int& field_size);
void FillField(char** field, const int& field_size);
void CreateEnemy(char** field, const int& field_size, Character& enemy,
                 const int& enemy_number);
void CreatePlayer(char** field, const int& field_size, Character& player);
void PrintField(char** field, const int& field_size);

int main() {
  const int field_size = 20;
  char** field = CreateField(field_size);
  FillField(field, field_size);

  srand(time(nullptr));

  const int enemy_number = 5;
  Character enemies[enemy_number];
  for (int i = 0; i < enemy_number; ++i) {
    CreateEnemy(field, field_size, enemies[i], i + 1);
  }

  Character player;
  CreatePlayer(field, field_size, player);

  PrintField(field, field_size);

  DeleteField(field, field_size);
  return 0;
}

char** CreateField(const int& field_size) {
  char** array = new char*[field_size];
  for (int i = 0; i < field_size; ++i) {
    array[i] = new char[field_size];
  }
  return array;
}

void DeleteField(char** array, const int& field_size) {
  for (int i = 0; i < field_size; ++i) {
    delete[] array[i];
  }
  delete[] array;
}

void FillField(char** field, const int& field_size) {
  for (int i = 0; i < field_size; ++i) {
    for (int j = 0; j < field_size; ++j) {
      field[i][j] = '.';
    }
  }
}

void CreateEnemy(char** field, const int& field_size, Character& enemy,
                 const int& enemy_number) {
  std::string name = "Enemy #" + std::to_string(enemy_number);
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
    enemy.pos_x = rand() % field_size;
    enemy.pos_y = rand() % field_size;
    if (field[enemy.pos_y][enemy.pos_x] == '.') {
      field[enemy.pos_y][enemy.pos_x] = 'E';
      break;
    }
  }
}

void CreatePlayer(char** field, const int& field_size, Character& player) {
  std::cout << "Enter player name: ";
  std::cin >> player.name;
  std::cout << "Enter player health points: ";
  std::cin >> player.health_point;
  std::cout << "Enter player armor points: ";
  std::cin >> player.armor_point;
  std::cout << "Enter player damage points: ";
  std::cin >> player.damage_point;

  while (true) {
    player.pos_x = rand() % field_size;
    player.pos_y = rand() % field_size;
    if (field[player.pos_y][player.pos_x] == '.') {
      field[player.pos_y][player.pos_x] = 'P';
      break;
    }
  }
}

void PrintField(char** field, const int& field_size) {
  std::cout << std::endl;
  for (int i = 0; i < field_size + 2; ++i, std::cout << "# ");
  std::cout << std::endl;
  for (int i = 0; i < field_size; ++i) {
    std::cout << "# ";
    for (int j = 0; j < field_size; ++j) {
      std::cout << field[i][j] << ' ';
    }
    std::cout << '#' << std::endl;
  }
  for (int i = 0; i < field_size + 2; ++i, std::cout << "# ");
  std::cout << std::endl << std::endl;
}

// bool PlayerMove(int x, int y) {
//   char direction;
//   std::cin >> direction;
//   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//   direction = toupper(direction);

//   if (direction == 'L')
//     --x;
//   else if (direction == 'R')
//     ++x;
//   else if (direction == 'U')
//     --y;
//   else if (direction == 'D')
//     ++y;
//   else {
//     std::cout << "Unknown command" << std::endl;
//     return false;
//   }
//   return true;
// }
