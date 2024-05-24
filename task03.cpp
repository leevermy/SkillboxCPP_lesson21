#include <iostream>
#include <cmath>
#include <string>

struct Vector2D {
    double x = 0;
    double y = 0;
};

Vector2D add(const Vector2D& v1, const Vector2D& v2) {
    return {v1.x + v2.x, v1.y + v2.y};
}

Vector2D subtract(const Vector2D& v1, const Vector2D& v2) {
    return {v1.x - v2.x, v1.y - v2.y};
}

Vector2D scale(const Vector2D& v, double scalar) {
    return {v.x * scalar, v.y * scalar};
}

double length(const Vector2D& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

Vector2D normalize(const Vector2D& v) {
    double len = length(v);
    if (len == 0) return Vector2D();
    return {v.x / len, v.y / len};
}

void printVector(const Vector2D& v) {
    std::cout << "(" << v.x << ", " << v.y << ")" << std::endl;
}

int main() {
    std::string operation;
    std::cout << "Enter the operation (add, subtract, scale, length, normalize): ";
    std::cin >> operation;

    if (operation == "add" || operation == "subtract") {
        Vector2D v1, v2;
        std::cout << "Enter the first vector (x y): ";
        std::cin >> v1.x >> v1.y;
        std::cout << "Enter the second vector (x y): ";
        std::cin >> v2.x >> v2.y;

        if (operation == "add") {
            Vector2D result = add(v1, v2);
            printVector(result);
        } else if (operation == "subtract") {
            Vector2D result = subtract(v1, v2);
            printVector(result);
        }
    } else if (operation == "scale") {
        Vector2D v;
        double scalar;
        std::cout << "Enter the vector (x y): ";
        std::cin >> v.x >> v.y;
        std::cout << "Enter the scalar value: ";
        std::cin >> scalar;

        Vector2D result = scale(v, scalar);
        printVector(result);
    } else if (operation == "length") {
        Vector2D v;
        std::cout << "Enter the vector (x y): ";
        std::cin >> v.x >> v.y;

        double result = length(v);
        std::cout << "Length: " << result << std::endl;
    } else if (operation == "normalize") {
        Vector2D v;
        std::cout << "Enter the vector (x y): ";
        std::cin >> v.x >> v.y;

        Vector2D result = normalize(v);
        printVector(result);
    } else {
        std::cerr << "Unknown operation" << std::endl;
    }

    return 0;
}

