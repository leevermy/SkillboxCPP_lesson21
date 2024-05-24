#include <iostream>
#include <string>
#include <ctime>


struct Character {
    std::string name;
    int health_point;
    int armor_point;
    int damage_point;
};

char* MakeField();

int main() {
    const int field_size = 20;
    char field[field_size][field_size];

    MakeField();

    char player = 'P';
    char enemy = 'E';
    char empty_place = '.';

    //действия игрока
    PrintField(field, field_size);
}

MakeField() {
    srand(time(nullptr));
    Character enemies[5];
    for (int i = 0; i < 5; ++i) {
        enemies[i].name = "Enemy #" + std::to_string(i);
        enemies[i].health_point = rand() % 101 + 50;
        enemies[i].armor_point = rand() % 51;
        enemies[i].damage_point = rand() % 16 + 15;
    }

    Character player;
    std::cin >> player.name;
    std::cin >> player.health_point;
    std::cin >> player.armor_point;
    std::cin >> player.damage_point;

    // разместить на поле
}

bool PlayerMove(int x, int y) {
    char direction;
    std::cin >> direction;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    direction = toupper(direction);

    //L, R, U, D
    if (direction == 'L') --x;
    else if (direction == 'R') ++x;
    else if (direction == 'U') --y;
    else if (direction == 'D') ++y;
    else {
        std::cout << "Unknown command" << std::endl;
        return false;
    }
    return true;
}

void EnemiesMove(Character enemies[], int size) {

}