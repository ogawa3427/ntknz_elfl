#include <string>
#include <iostream>
#include <notes.h>

enum Octa {
    THREE, FOUR, T_F
};

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
        input[11] == '1' ? finger.r5_3 = true : finger.r5_3 = false;

        return finger;
    }
};


enum Tone {
    C3, Des3, D3, Es3, E3, F3, Ges3, G3_, As3, A3, B3, H3,
    C4, Des4, D4, Es4, E4, F4, Ges4, G4_, As4, A4, B4, H4,
    C5, Des5, D5, Es5, E5, F5, Ges5, G5_, As5, A5, B5, H5, Error
};

std::string toneToString(Tone tone) {
    switch (tone) {
        case C3: return "C3";
        case Des3: return "Des3";
        case D3: return "D3";
        case Es3: return "Es3";
        case E3: return "E3";
        case F3: return "F3";
        case Ges3: return "Ges3";
        case G3_: return "G3_";
        case As3: return "As3";
        case A3: return "A3";
        case B3: return "B3";
        case H3: return "H3";
        case C4: return "C4";
        case Des4: return "Des4";
        case D4: return "D4";
        case Es4: return "Es4";
        case E4: return "E4";
        case F4: return "F4";
        case Ges4: return "Ges4";
        case G4_: return "G4_";
        case As4: return "As4";
        case A4: return "A4";
        case B4: return "B4";
        case H4: return "H4";
        case C5: return "C5";
        case Des5: return "Des5";
        case D5: return "D5";
        case Es5: return "Es5";
        case E5: return "E5";
        case F5: return "F5";
        case Ges5: return "Ges5";
        case G5_: return "G5_";
        case As5: return "As5";
        case A5: return "A5";
        case B5: return "B5";
        case H5: return "H5";
        case Error: return "Error";
        default: return "Error";
    }
}

class ToneEncoder {
    public:
    ToneEncoder() {}

    int encodeToTone(const FingerEncoder::Finger& finger, Octa octa) {
        if (finger.l1 && finger.l2 && finger.l3 && finger.l4 &&             finger.r2 && finger.r3 && finger.r4 &&           finger.r5_3) {
            return NOTE_C3;
        } else if (finger.l1 && finger.l2 && finger.l3 && finger.l4 &&             finger.r2 && finger.r3 && finger.r4 &&           finger.r5_2 && !finger.r5_3) {
            return NOTE_CS3;
        } else if (             finger.l2 && finger.l3 && finger.l4 &&             finger.r2 && finger.r3 && finger.r4 && !finger.r5_1 && !finger.r5_2 && !finger.r5_3) {
            if (octa == THREE) {
                return NOTE_D3;
            } else {
                return NOTE_D4;
            }
        } else if (             finger.l1 && finger.l3 && finger.l4 &&             finger.r2 && finger.r3 && finger.r4 && finger.r5_1) {
            if (octa == THREE) {
                return NOTE_DS3;
            } else {
                return NOTE_DS4;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && finger.l4 &&             finger.r2 && finger.r3 && !finger.r4) {
            if (octa == THREE) {
                return NOTE_E3;
            } else {
                return NOTE_E4;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && finger.l4 &&             finger.r2 && !finger.r3 && !finger.r4) {
            if (octa == THREE) {
                return NOTE_F3;
            } else {
                return NOTE_F4;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && finger.l4 && !finger.l5 && !finger.r2 && finger.r3 && !finger.r4) {
            if (octa == THREE) {
                return NOTE_FS3;
            } else {
                return NOTE_FS4;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && finger.l4 && !finger.l5 && !finger.r2 && !finger.r3 && !finger.r4) {
            if (octa == THREE || octa == T_F) {
                return NOTE_G3;
            } else {
                return NOTE_G4;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && finger.l4 && finger.l5 && !finger.r2 && !finger.r3 && !finger.r4) {
            if (octa == THREE || octa == T_F) {
                return NOTE_GS3;
            } else {
                return NOTE_GS4;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && !finger.l4 && !finger.l5 && !finger.r2) {
            if (octa == THREE || octa == T_F) {
                return NOTE_A3;
            } else {
                return NOTE_A4;
            }
        } else if (finger.l1 && finger.l2 && !finger.l4 && !finger.l5 && finger.r2 && finger.r5_1) {
            if (octa == THREE || octa == T_F) {
                return NOTE_AS3;
            } else {
                return NOTE_AS4;
            }
        } else if (finger.l1 && finger.l2 && !finger.l3 && !finger.l4 && !finger.l5 && !finger.r5_2) {
            if (octa == THREE || octa == T_F) {
                return NOTE_B3;
            } else {
                return NOTE_B4;
            }
        } else if (!finger.l1 && finger.l2 && !finger.l3 && !finger.l4 && !finger.l5 && !finger.r2 && !finger.r3 && !finger.r4 && finger.r5_1) {
            if (octa == THREE || octa == T_F) {
                return NOTE_C4;
            } else {
                return NOTE_C5;
            }
        } else if (!finger.l1 && !finger.l2 && !finger.l3 && !finger.l4 && !finger.l5 && !finger.r2 && !finger.r3 && !finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return NOTE_CS4;
            } else {
                return NOTE_CS5;
            }
        } else if (finger.l1 && !finger.l2 && finger.l3 && finger.l4 && !finger.l5) {
            if (octa == T_F || octa == FOUR) {
                return NOTE_D5;
            } else {
                return -1;
            }
        } else if (finger.l1               && finger.l3 && finger.l4 && finger.l5 && finger.r2 && finger.r3 && finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return NOTE_DS5;
            } else {
                return -1;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && !finger.l4 && !finger.l5 && finger.r2 && finger.r3 && !finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return NOTE_E5;
            } else {
                return -1;
            }
        } else if (finger.l1 && finger.l2 && !finger.l3 && finger.l4 &&               finger.r2              && !finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return NOTE_F5;
            } else {
                return -1;
            }
        } else if (finger.l1 && finger.l2 && !finger.l3 && finger.l4 &&               !finger.r2             && finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return NOTE_FS5;
            } else {
                return -1;
            }
        } else if (!finger.l1 && finger.l2 && finger.l3 && finger.l4 &&               !finger.r2 && !finger.r3 && !finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return NOTE_G5;
            } else {
                return -1;
            }             
        } else if (!finger.l1 && !finger.l2 && finger.l3 && finger.l4 && finger.l5  && !finger.r2 && !finger.r3 && !finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return NOTE_GS5;
            } else {
                return -1;
            }
        } else if (finger.l1 && !finger.l2 && finger.l3 && !finger.l4 &&              finger.r2 && !finger.r3 && !finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return NOTE_A5;
            } else {
                return -1;
            }
        } else if (finger.l1 && !finger.l2 && !finger.l3 && !finger.l4 &&              finger.r2 && !finger.r3 && !finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return NOTE_AS5;
            } else {
                return -1;
            }
        } else if (finger.l1 && finger.l2 && !finger.l3 && finger.l4 &&              !finger.r2 && !finger.r3 && !finger.r4) {
            if (octa == T_F || octa == FOUR) {
                return NOTE_B5;
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    }
};
