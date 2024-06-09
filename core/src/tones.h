#include <string>
#include <iostream>

class FingerEncoder {
    public:
    struct Finger {
        bool l1;
        bool l2;
        bool l3;
        bool l4;
        bool l5;
        bool r2;
        bool r3;
        bool r4;
        bool r5_1;
        bool r5_2;
        bool r5_3;
    };

    FingerEncoder() {}

    Finger encode(const String& input) {
        if (input.length() != 16) {
            throw std::invalid_argument("Input must be exactly 16 characters long.");
        }
        Finger finger = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        input[1] == '1' ? finger.l1 = true : finger.l1 = false;
        input[3] == '1' ? finger.l2 = true : finger.l2 = false;
        input[2] == '1' ? finger.l3 = true : finger.l3 = false;
        input[0] == '1' ? finger.l4 = true : finger.l4 = false;
        input[10] == '0' ? finger.l5 = true : finger.l5 = false;
        input[9] == '1' ? finger.r2 = true : finger.r2 = false;
        input[15] == '1' ? finger.r3 = true : finger.r3 = false;
        input[14] == '1' ? finger.r4 = true : finger.r4 = false;
        input[13] == '0' ? finger.r5_1 = true : finger.r5_1 = false;
        input[12] == '1' ? finger.r5_2 = true : finger.r5_2 = false;
        input[11] == '0' ? finger.r5_3 = true : finger.r5_3 = false;

        return finger;
    }
};

enum Doremi {
    B, H, C, Des, D, Es, E, F, Ges, G, As, A
};

class ToneEncoder {
    public:
    ToneEncoder() {}

    std::string encodeToDoremi(const FingerEncoder::Finger& finger) {
        if (finger.l1) {
            return "B";
        }
        return "A";
    }
};
