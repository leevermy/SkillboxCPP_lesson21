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
  int floor_number;
  int rooms_amount;
  double ceilingHeight;
  std::vector<Room> rooms;
};

struct House {
  int floors_amount;
  std::vector<Floor> floors;
  bool has_stove = false;
};

struct Bath {
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
  Bath bath;
};

void InputSection(struct Section& section);
void InputBuilding(std::vector<Building>& buildings);
void InputHouse(struct House& house);
void InputBath(struct Bath& bath);
void InputFloor(std::vector<Floor>& floors);
void InputRoom(std::vector<Room>& rooms);

int main() {
  std::cout << "Enter the amount of section in the village: ";
  int village_size;
  std::cin >> village_size;
  std::vector<Section> sections(village_size);

  int i = 1;
  for (auto& section : sections) {
    std::cout << "\nEnter the data of " << i++ << " section" << std::endl;
    InputSection(section);
  }

  return 0;
}

void InputSection(struct Section& section) {
  std::cout << "Enter the section number: ";
  std::cin >> section.number;

  std::cout << "Enter the amount of building that are located on the section: ";
  int buildings_amount;
  std::cin >> buildings_amount;
  section.buildings.resize(buildings_amount);
  InputBuilding(section.buildings);

  for (auto& building : section.buildings) {
    if (building.type == "House") {
      InputHouse(section.house);
    } else if (building.type == "Bath") {
      InputBath(section.bath);
    }
  }
}

void InputBuilding(std::vector<Building>& buildings) {
  for (auto& building : buildings) {
    std::cout << "Enter building type (House, Garage, Shed, Bath): ";
    std::cin >> building.type;
    std::cout << "Enter building area: ";
    std::cin >> building.area;
  }
}

void InputHouse(struct House& house) {
  std::cout << "Enter number of floors in the house: ";
  std::cin >> house.floors_amount;

  char answer;
  std::cout << "Does the house have a stove (y/n)? ";
  std::cin >> answer;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  if (answer == 'y') house.has_stove = true;

  house.floors.resize(house.floors_amount);
  InputFloor(house.floors);
}

void InputBath(struct Bath& bath) {
  std::cout << "Does the bath have a stove (y/n)? ";
  char answer;
  std::cin >> answer;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  if (answer == 'y') bath.has_stove = true;
}

void InputFloor(std::vector<Floor>& floors) {
  for (auto& floor : floors) {
    std::cout << "Enter floor number: ";
    std::cin >> floor.floor_number;

    std::cout << "Enter number of rooms on floor: ";
    std::cin >> floor.rooms_amount;

    std::cout << "Enter ceiling height: ";
    std::cin >> floor.ceilingHeight;
    floor.rooms.resize(floor.rooms_amount);
    InputRoom(floor.rooms);
  }
}

void InputRoom(std::vector<Room>& rooms) {
  for (auto& room : rooms) {
    int type;
    std::cout << "Enter room type (0: Bedroom, 1: Kitchen, 2: Bathroom, 3: ChildrenRoom, 4: LivingRoom): ";
    std::cin >> type;
    while (true) {
      std::cin >> type;
      if (type >= 0 && type <= 4) {
        room.type = static_cast<RoomType>(type);
        break;
      } else {
        std::cout << "Invalid room type. Try again: ";
      }
    }

    std::cout << "Enter room area: ";
    std::cin >> room.area;
  }
}