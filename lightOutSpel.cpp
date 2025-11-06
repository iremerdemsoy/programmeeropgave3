#include <iostream>

using namespace std;

class LightOutSpel {

    int bordHoogte = 4;
    int bordBreedte = 6;
    bool deWereld[20][20]{};
    char leesEnkelKarakter() {
        char ingelezenKarakter;
        do {
            ingelezenKarakter = toupper(cin.get());
        } while (ingelezenKarakter == '\n' && (ingelezenKarakter >= 'A' || ingelezenKarakter <= 'Z'));
        return ingelezenKarakter;
    }

    void toonParametersMenu() {

    }

    void wisselLampEnBurenOm(int rij, int kolom) {
        if (rij < 0 || rij >= bordHoogte || kolom < 0 || kolom >= bordBreedte) return;
        toggle (rij, kolom);
        toggle(rij - 1, kolom);
        toggle(rij + 1, kolom);
        toggle(rij, kolom - 1);
        toggle(rij, kolom + 1);

    }

    void toggle (int rij, int kolom){
        if (rij < 0 || rij >= bordHoogte || kolom < 0 || kolom >= bordBreedte) return;
        deWereld[rij][kolom] = !deWereld[rij][kolom];
    }

    void pasVolgStrategietoe() {
        for (int huidigeRij = bordHoogte - 1; huidigeRij > 0; --huidigeRij){
            for (int huidigeKolom = 0; huidigeKolom < bordBreedte; huidigeKolom++){
                if (deWereld[huidigeRij][huidigeKolom] == true) {
                    int onderDeHuidigeRij = huidigeRij - 1;
                    wisselLampEnBurenOm(onderDeHuidigeRij, huidigeKolom);
                    toonHuidigeBord();
                }
            }
        }

    }

    void PasLosStrategieToe() {

    }

    void PasSpeelStrategieToe() {

    }

    void PasZetStrategieToe() {

    }

    void toonPuzzelMenu() {
        while (true) {
            toonHuidigeBord();
            cout << "[T]erug [V]olg [L]os 5x5 [S]peel oplossing [Z]et doen: \n";
            char gebruikerskeuze = leesEnkelKarakter();

            if (gebruikerskeuze == 'T') break;
            if (gebruikerskeuze == 'V') pasVolgStrategietoe();
            if (gebruikerskeuze == 'L') PasLosStrategieToe();
            if (gebruikerskeuze == 'S') PasSpeelStrategieToe();
            if (gebruikerskeuze == 'Z') PasZetStrategieToe();

        }

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