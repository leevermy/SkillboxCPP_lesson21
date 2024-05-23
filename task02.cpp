#include <iostream>
#include <limits>
#include <string>
#include <vector>

enum RoomType { E_BEDROOM, E_KITCHEN, E_BATHROOM, E_CHILDRENS, E_LIVING_ROOM };

struct Room {
  RoomType type;
  int area;
};

struct Floor {
  int rooms_amount;
  double ceilingHeight;
  std::vector<Room> rooms;
};

struct House {
  int floors_amount;
  std::vector<Floor> floors;
  bool has_stove = false;
};

struct Building {
  std::string type;
  int area;
};

struct Section {
  int number;
  std::vector<Building> buildings;
  House house;
};

void InputData(struct Section& section);

int main() {
  std::cout << "Enter the amount of section in the village: ";
  int village_size;
  std::vector<Section> sections(village_size);

  for (auto& section : sections) {
    InputSection(section);
  }

  return 0;
}

void InputSection(struct Section& section) {
  std::cin >> section.number;

  int buildings_amount;
  std::cin >> buildings_amount;
  section.buildings.resize(buildings_amount);
  InputBuilding(section.buildings);

  for (auto& building : section.buildings) {
    if (building.type == "House") {
      InputHouse(section.house);
    }
  }
}

void InputBuilding(std::vector<Building>& buildings) {
  for (auto& building : buildings) {
    std::cin >> building.type;
    std::cin >> building.area;
  }
}

void InputHouse(struct House& house) {
  std::cin >> house.floors_amount;
  char answer;
  std::cin >> answer;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  if (answer == 'y') house.has_stove = true;

  house.floors.resize(house.floors_amount);
  InputFloor(house.floors);
}

void InputFloor(std::vector<Floor>& floors) {
  for (auto& floor : floors) {
    std::cin >> floor.rooms_amount;
    std::cin >> floor.ceilingHeight;
    floor.rooms.resize(floor.rooms_amount);
    InputRoom(floor.rooms);
  }
}

void InputRoom(std::vector<Room>& rooms) {
  for (auto& room : rooms) {
    int type;
    std::cin >> type;
    room.type = static_cast<RoomType>(type);
    std::cin >> room.area;
  }
}