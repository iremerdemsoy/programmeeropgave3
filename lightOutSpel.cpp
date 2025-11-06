#include <iostream>

using namespace std;

class LightOutSpel {

    int bordHoogte = 5;
    int bordBreedte = 5;
    bool deWereld[20][20]{};
    bool oplossing[20][20]{};
    int totaalAantalZetten;
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
        if (bordHoogte != 5 || bordBreedte != 5) {
            cout << "Alleen mogelijk op een 5x5 bord!\n";
            return;
        }
        pasVolgStrategietoe();
        for (int huidigeKolom = 0; huidigeKolom < bordBreedte; ++huidigeKolom) {
            if (deWereld[0][huidigeKolom]) {
                wisselLampEnBurenOm(1, huidigeKolom);
                toonHuidigeBord();
            }
        }
        pasVolgStrategietoe();
    }

    void PasSpeelStrategieToe() {
        for (int huidigeRij = 0; huidigeRij < bordHoogte; ++huidigeRij) {
            for (int huidigeKolom = 0; huidigeKolom < bordBreedte; ++huidigeKolom) {
                if (oplossing[huidigeRij][huidigeKolom]) {
                    wisselLampEnBurenOm(huidigeRij, huidigeKolom);
                    toonHuidigeBord();
                }
            }
        }
    }

    int leesGetalMetMaximum(int maximumToegestaneWaarde) {
        string verzameldeCijfers;
        char ingelezenKarakter;

        while ((ingelezenKarakter = cin.get()) != '\n') {
            if (ingelezenKarakter >= '0' && ingelezenKarakter <= '9') {
                verzameldeCijfers += ingelezenKarakter;
            }
        }

        int resultaatGetal = 0;
        for (char cijferKarakter : verzameldeCijfers) {
            resultaatGetal = resultaatGetal * 10 + (cijferKarakter - '0');
            if (resultaatGetal > maximumToegestaneWaarde) {
                resultaatGetal = maximumToegestaneWaarde;
            }
        }
        return resultaatGetal > 0 ? resultaatGetal : 1;
    }

    void PasZetToe() {
            cout << "Positie (bijv. A1): ";
            char ingevoerdeKolomLetter = leesEnkelKarakter();
            int ingevoerdeRijNummer = leesGetalMetMaximum(bordHoogte) - 1;
            int berekendeKolomIndex = ingevoerdeKolomLetter - 'A';

            if (ingevoerdeRijNummer >= 0 && ingevoerdeRijNummer < bordHoogte &&
                berekendeKolomIndex >= 0 && berekendeKolomIndex < bordBreedte) {
                wisselLampEnBurenOm(ingevoerdeRijNummer, berekendeKolomIndex);
            } else {
                cout << "Ongeldige positie!\n";
            }

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
            if (gebruikerskeuze == 'Z') PasZetToe();

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