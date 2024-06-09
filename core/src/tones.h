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


enum Tone {
    C3, Des3, D3, Es3, E3, F3, Ges3, G3, As3, A3, B3, H3,
    C4, Des4, D4, Es4, E4, F4, Ges4, G4, As4, A4, B4, H4,
    C5, Des5, D5, Es5, E5, F5, Ges5, G5, As5, A5, B5, H5, Error
}

class ToneEncoder {
    public:
    ToneEncoder() {}

    std::string encodeToTone(const FingerEncoder::Finger& finger, Octa octa) {
        if (finger.l1 && finger.l2 && finger.l3 && finger.l4 &&             finger.r2 && finger.r3 && finger.r4 &&           finger.r5_3) {
            return C3;
        } else if (finger.l1 && finger.l2 && finger.l3 && finger.l4 &&             finger.r2 && finger.r3 && finger.r4 &&           finger.r5_2 && !finger.r5_3) {
            return Des3;
        } else if (finger.l1 && finger.l2 && finger.l3 && finger.l4 &&             finger.r2 && finger.r3 && finger.r4 && !finger.r5_1 && !finger.r5_2 && !finger.r5_3) {
            if (octa == THREE) {
                return D3;
            } else {
                return D4;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && finger.l4 &&             finger.r2 && finger.r3 && finger.r4 && finger.r5_1) {
            if (octa == THREE) {
                return Es3;
            } else {
                return Es4;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && finger.l4 &&             finger.r2 && finger.r3 && !finger.r4) {
            if (octa == THREE) {
                return E3;
            } else {
                return E4;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && finger.l4 &&             finger.r2 && !finger.r3 && !finger.r4) {
            if (octa == THREE) {
                return F3;
            } else {
                return F4;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && finger.l4 && !finger.l5 && !finger.r2 &&               !finger.r4) {
            if (octa == THREE) {
                return Ges3;
            } else {
                return Ges4;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && finger.l4 && !finger.l5 && !finger.r2 && !finger.r3 && !finger.r4) {
            if (octa == THREE || octa == T_F) {
                return G3;
            } else {
                return G4;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && finger.l4 && !finger.l5) {
            if (octa == THREE || octa == T_F) {
                return As3;
            } else {
                return As4;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && !finger.l4 && !finger.l5) {
            if (octa == THREE || octa == T_F) {
                return A3;
            } else {
                return A4;
            }
        } else if (finger.l1 && finger.l2 && !finger.l3 && !finger.l4 && !finger.l5 && finger.r5_1) {
            if (octa == THREE || octa == T_F) {
                return B3;
            } else {
                return B4;
            }
        } else if (finger.l1 && finger.l2 && !finger.l3 && !finger.l4 && !finger.l5 && finger.r5_2) {
            if (octa == THREE || octa == T_F) {
                return H3;
            } else {
                return H4;
            }
        } else if (!finger.l1 && finger.l2 && !finger.l3 && !finger.l4 && !finger.l5 && !finger.r2 && !finger.r3 && !finger.r4 && finger.r5_1) {
            if (octa == THREE || octa == T_F) {
                return C4;
            } else {
                return C5;
            }
        } else if (!finger,l1 && !finger.l2 && !finger.l3 && !finger.l4 && !finger.l5 && !finger.r2 && !finger.r3 && !finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return Des4;
            } else {
                return Error;
            }
        } else if (finger.l1 && !finger.l2 && finger.l3 && finger.l4 && !finger.l5) {
            if (octa == T_F || octa == FOUR) {
                return D5;
            } else {
                return Error;
            }
        } else if (finger.l1               && finger.l3 && finger.l4 && fonger.l5 && finger.r2 && finger.r3 && finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return Es5;
            } else {
                return Error;
            }
        } else if (finger.l1 && finger.l2 && finger.l3 && !finger.l4 && !finger.l5 && finger.r2 && finger.r3 && !finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return E5;
            } else {
                return Error;
            }
        } else if (finger.l1 && finger.l2 && !finger.l3 && finger.l4 &&               finger.r2              && !finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return F5;
            } else {
                return Error;
            }
        } else if (finger.l1 && finger.l2 && !finger.l3 && finger.l4 &&               !finger.r2             && finger,r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return Ges5;
            } else {
                return Error;
            }
        } else if (!finger.l1 && finger.l2 && finger.l3 && finger.l4 &&               !finger.r2 && !finger.r3 && !finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return G5;
            } else {
                return Error;
            }             
        } else if (!finger.l1 && !finger.l2 && finger.l3 && finger.l4 && finger.l5  && !finger.r2 && !finger.r3 && !finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return As5;
            } else {
                return Error;
            }
        } else if (finger.l1 && !finger.l2 && finger.l3 && !finger.l4 &&           && finger.r2 && !finger.r3 && !finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return A5;
            } else {
                return Error;
            }
        } else if (finger.l1 && !finger.l2 && !finger.l3 && !finger.l4 &&           && finger.r2 && !finger.r3 && !finger.r4 && finger.r5_1) {
            if (octa == T_F || octa == FOUR) {
                return B5;
            } else {
                return Error;
            }
        } else if (finger.l1 && finger.l2 && !finger.l3 && finger.l4 &&           && !finger.r2 && !finger.r3 && !finger.r4) {
            if (octa == T_F || octa == FOUR) {
                return H5;
            } else {
                return Error;
            }
        } else {
            return Error;
        }
    }
};
