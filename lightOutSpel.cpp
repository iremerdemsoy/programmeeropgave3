#include <iostream>

using namespace std;

class LightOutSpel {

    int bordHoogte = 4;
    int bordBreedte = 6;
    bool deWereld[20][20]{};
    char leesEnkelKarakter() {
        char ingelezenKarakter = cin.get();
        char hoofdletter = static_cast<char>(toupper(ingelezenKarakter)); //maakt het hoofdletter
        return hoofdletter;
    }

    void toonParametersMenu() {

    }

    void toonPuzzelMenu() {
        while (true)

    }

    void toonTekenMenu() {

    }

    void toonHuidigeBord() {
        for (int huidigeRij = bordHoogte - 1; huidigeRij >= 0; --huidigeRij) {
            cout << huidigeRij + 1 << "\t";
            for (int huidigeColomn = 0; huidigeColomn < bordBreedte; ++huidigeColomn) {
                bool deWaardeVanDeWereldVanDeHuigeCel = deWereld[huidigeRij][huidigeColomn];
                if (deWaardeVanDeWereldVanDeHuigeCel) { cout << "# "; }
                else { cout << ". "; }
            }
            cout << "\n";

        }
        cout << "\t" << "A B C D E F" << endl;


    }

    void toonHoofdmenu() {
        while (true) {
            toonHuidigeBord();
            cout << "[P]arameters p[U]zzel [T]ekenen [S]top: ";
            char gebruikerskeuze = leesEnkelKarakter();
            if (gebruikerskeuze == 'S') { break; }
            if (gebruikerskeuze == 'P') { toonParametersMenu(); }
            if (gebruikerskeuze == 'U') { toonPuzzelMenu(); }
            if (gebruikerskeuze == 'T') { toonTekenMenu(); }
        }

    }
public:
    void startSpel() {
        toonHoofdmenu();
    }
};

int main() {
    LightOutSpel spel;
    spel.startSpel();
    return 0;
}