#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string step(std::string state, int value) {
    if (value == 50) {
        return "dispense";
    }
    if (!(value == 10 || value == 20 || value == 50)) {
        std::cout << "Invalid input.\n";
        return state;
    }

    switch (std::stoi(state)) {
        case 0:
            switch (value) {
                case 10:
                    state = "10";
                    break;
                case 20:
                    state = "20";
                    break;
            }
            break;
        case 10:
            switch (value) {
                case 10:
                    state = "20";
                    break;
                case 20:
                    state = "30";
                    break;
            }
            break;
        case 20:
            switch (value) {
                case 10:
                    state = "30";
                    break;
                case 20:
                    state = "40";
                    break;
            }
            break;
        case 30:
            switch (value) {
                case 10:
                    state = "40";
                    break;
                case 20:
                    state = "dispense";
                    break;
            }
            break;
        case 40:
            switch (value) {
                default:
                    state = "dispense";
                    break;
            }
            break;
        default:
            std::cout << "Invalid input.\n";
            break;
    }
    return state;
}

std::string stepExtended(std::string state, int value) {
    if (!(value == 1 || value == 2 || value == 3 || value == 10 ||
          value == 20 || value == 50)) {
        std::cout << "Invalid input.\n";
        return state;
    }
    switch (std::stoi(state)) {
        case 0:
            switch (value) {
                case 1:
                    state = "1";
                    break;
                case 2:
                    state = "2";
                    break;
                case 3:
                    state = "3";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 1:
            switch (value) {
                case 10:
                    state = "110";
                    break;
                case 20:
                    state = "120";
                    break;
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 2:
            switch (value) {
                case 10:
                    state = "210";
                    break;
                case 20:
                    state = "220";
                    break;
                case 50:
                    state = "250";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 3:
            switch (value) {
                case 10:
                    state = "310";
                    break;
                case 20:
                    state = "320";
                    break;
                case 50:
                    state = "350";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 110:
            switch (value) {
                case 10:
                    state = "120";
                    break;
                case 20:
                    state = "130";
                    break;
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 120:
            switch (value) {
                case 10:
                    state = "130";
                    break;
                case 20:
                    state = "140";
                    break;
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 130:
            switch (value) {
                case 10:
                    state = "110";
                    break;
                case 20:
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 140:
            switch (value) {
                case 10:
                case 20:
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 210:
            switch (value) {
                case 10:
                    state = "220";
                    break;
                case 20:
                    state = "230";
                    break;
                case 50:
                    state = "260";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 220:
            switch (value) {
                case 10:
                    state = "230";
                    break;
                case 20:
                    state = "240";
                    break;
                case 50:
                    state = "270";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 230:
            switch (value) {
                case 10:
                    state = "240";
                    break;
                case 20:
                    state = "250";
                    break;
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 240:
            switch (value) {
                case 10:
                    state = "250";
                    break;
                case 20:
                    state = "260";
                    break;
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 250:
            switch (value) {
                case 10:
                    state = "260";
                    break;
                case 20:
                    state = "270";
                    break;
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 260:
            switch (value) {
                case 10:
                    state = "270";
                    break;
                case 20:
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 270:
            switch (value) {
                case 10:
                case 20:
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 310:
            switch (value) {
                case 10:
                    state = "320";
                    break;
                case 20:
                    state = "330";
                    break;
                case 50:
                    state = "360";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 320:
            switch (value) {
                case 10:
                    state = "330";
                    break;
                case 20:
                    state = "340";
                    break;
                case 50:
                    state = "370";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 330:
            switch (value) {
                case 10:
                    state = "340";
                    break;
                case 20:
                    state = "350";
                    break;
                case 50:
                    state = "380";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 340:
            switch (value) {
                case 10:
                    state = "350";
                    break;
                case 20:
                    state = "360";
                    break;
                case 50:
                    state = "390";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 350:
            switch (value) {
                case 10:
                    state = "360";
                    break;
                case 20:
                    state = "370";
                    break;
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 360:
            switch (value) {
                case 10:
                    state = "370";
                    break;
                case 20:
                    state = "380";
                    break;
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 370:
            switch (value) {
                case 10:
                    state = "380";
                    break;
                case 20:
                    state = "390";
                    break;
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 380:
            switch (value) {
                case 10:
                    state = "390";
                    break;
                case 20:
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        case 390:
            switch (value) {
                case 10:
                case 20:
                case 50:
                    state = "dispense";
                    break;
                default:
                    std::cout << "Invalid input.\n";
                    break;
            }
            break;
        default:
            std::cout << "Invalid state.\n";
            break;
    }
    return state;
}

int main(int argc, char* argv[]) {
    std::string state = "0";
    bool extendedMode = false;

    if (argc == 2) {
        extendedMode = true;
    }

    while (true) {
        int value = 0;
        std::string input;
        if (state == "0" && extendedMode) {
            std::cout << "Current state: " << state
                      << ". Please select a drink (1, 2, 3): ";
        } else {
            std::cout << "Current state: " << state
                      << ". Please input a coin (10, 20, 50): ";
        }
        std::getline(std::cin, input);
        std::stringstream(input) >> value;

        state = extendedMode ? stepExtended(state, value) : step(state, value);
        std::cout << "state = " << state << std::endl;

        if (state == "dispense") {
            std::cout << "Here is your drink. Goodbye!\n\n";
            state = "0";
        }
    }
}
