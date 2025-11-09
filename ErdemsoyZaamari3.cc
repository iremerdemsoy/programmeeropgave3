//In dit programma kan de gebruiker het spel LightsOut spelen via een
//menu-systeem. De gebruiker kan kiezen uit een aantal mogelijkheden.
//Er zijn 3 submenus die weer leiden naar enkele nieuwe opties.
//Gebruikte compiler: Apple clang version 17.0.0 (clang -1700.0.13.5)
//Target: arm64-apple-darwin24.6.0
//Thread model: posix
//Makers: Irem Erdemsoy, Anass Zaamari
//Datum: 10 november 2025

#include <iostream>
#include<ctime>
using namespace std;

class LightOutSpel {
    int bordHoogte = 5;
    int bordBreedte = 5;
    int LampPercentage = 25;
    int cursorRij = 2;
    int cursorKolom = 2;
    bool cursorStatus = false;
    bool deWereld[20][20]{};
    bool oplossing[20][20]{};
    bool isTorus = false;
    int totaalAantalZetten;
    char cursorUit = 'o';
    char cursorAan = '*';
    char lampUit = '.';
    char lampAan = '#';
    char leesEnkelKarakter() {
        char ingelezenKarakter;
        do {
            ingelezenKarakter = toupper(cin.get());
        } while (ingelezenKarakter == '\n');
        return ingelezenKarakter;
    }//leesEnkelKarakter

    long randomgetal (int min = 0, int max = 9) {
        static bool first = true;
        if (first) {
            srand(time(nullptr));
            first = false;
        }
        return min + (rand() % (max - min + 1));
    }
    //info
    void infoblokje() {
        cout << "Infoblokje" << endl;
        cout << "Makers: Irem Erdemsoy, Anass Zaamari" << endl;
        cout << "Jaar van afkomst: 2007" << endl;
        cout << "studierichting: Informatica" << endl;
        cout << "studentennummer: s4900561, s4938224" << endl;
        cout << "Derde programmeeropgave" << endl;
        cout << "De gebruiker wordt in staat gesteld 'Lights out' te spelen" << endl;
        cout << "via een menu-systeem. De gebruiker kan kiezen uit 3 submenus," << endl;
        cout << "waarin er weer enkele opties zijn." << endl;
        cout << "datum: 10 november 2025" << endl;
    }
// functie toont het parameter menu
    void toonParametersMenu(){
        while (true) {
            toonHuidigeBord();
            cout << "[T]erug [H]oogte [B]reedte [P]ercentage [K]arakters t[O]rus p[E]n: ";
            char gebruikerskeuze = leesEnkelKarakter();

            if (gebruikerskeuze == 'T') break;
            if (gebruikerskeuze == 'H') PasHoogteAan();
            if (gebruikerskeuze == 'B') PasBreedteAan();
            if (gebruikerskeuze == 'P') PasPercentageAan();
            if (gebruikerskeuze == 'K') PasKarakterAan();
            if (gebruikerskeuze == 'O') PasTorusAan();
            if (gebruikerskeuze == 'E') PasPenAan();
        }
    }//toonParametersMenu
// functie past hoogte aan
    void PasHoogteAan(){
        cout << "Nieuwe hoogte (1-20): ";
        int nieuweHoogte = leesGetalMetMaximum(20);
        bordHoogte = nieuweHoogte;
    }//PasHoogteAan
    // functie past breedte aan
    void PasBreedteAan(){
        cout << "Nieuwe breedte (1-20): ";
        int nieuweBreedte = leesGetalMetMaximum(20);
        bordBreedte = nieuweBreedte;
    }//PasBreedteAan
    // functie past percentage aan
    void PasPercentageAan(){
        cout << "Percentage is nu " << LampPercentage << "%" << endl;
        cout << "Nieuwe percentage (1-100): ";
        int nieuwePercentage = leesGetalMetMaximum(100);
        LampPercentage = nieuwePercentage;
    }//PasPercentageAan
    void PasKarakterAan(){//Switch de lampen
        char oudKarakter = lampAan;
        lampAan = lampUit;
        lampUit = oudKarakter;
    }//PasKarakterAan
    void PasTorusAan(){
        cout << "Torus is nu " << (isTorus ? "aan" : "uit") << endl;
        cout << "Torus aan? [J/N]" << endl;
        char Antwoord = leesEnkelKarakter();
        if (Antwoord == 'J')
            isTorus = true;
        if (Antwoord == 'N')
            isTorus = false;
    }//PasTorusAan
    void PasPenAan(){
        cout << "Wil je de cursor aanzetten? [J/N]" << endl;
        char Antwoord = leesEnkelKarakter();
        if (Antwoord == 'J')
            cursorStatus = true;
        if (Antwoord == 'N')
            cursorStatus = false;
    }//PasPenAan

    void wisselLampEnBurenOm(int rij, int kolom) {
        toggle (rij, kolom);
        toggle(rij - 1, kolom);
        toggle(rij + 1, kolom);
        toggle(rij, kolom - 1);
        toggle(rij, kolom + 1);

    }//wisselLampEnBurenOm

    void toggle (int rij, int kolom){
        if(isTorus){
            int torusRij = (rij + bordHoogte) % bordHoogte;
            int torusKolom = (kolom + bordBreedte) % bordBreedte;
            deWereld[torusRij][torusKolom] = !deWereld[torusRij][torusKolom];
        }
        else{
            if (rij < 0 || rij >= bordHoogte || kolom < 0 || kolom >= bordBreedte) return;
            deWereld[rij][kolom] = !deWereld[rij][kolom];

        }
    }//toggle

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

    }//pasVolgStrategietoe

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
    }//PasLosStrategieToe

    void PasSpeelStrategieToe() {
        for (int huidigeRij = 0; huidigeRij < bordHoogte; ++huidigeRij) {
            for (int huidigeKolom = 0; huidigeKolom < bordBreedte; ++huidigeKolom) {
                if (oplossing[huidigeRij][huidigeKolom]) {
                    wisselLampEnBurenOm(huidigeRij, huidigeKolom);
                    toonHuidigeBord();
                }
            }
        }
    }//PasSpeelStrategieToe

    int leesGetalMetMaximum(int maximumToegestaneWaarde) {
        string verzameldeCijfers;
        char ingelezenKarakter;

        if (cin.peek() == '\n'){
            cin.get();
        }

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
    }//leesGetalMetMaximum

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

    }//PasZetToe

    void toonPuzzelMenu() {
        while (true) {
            toonHuidigeBord();
            cout << "[T]erug [V]olg [L]os 5x5 [S]peel oplossing [Z]et doen: ";
            char gebruikerskeuze = leesEnkelKarakter();

            if (gebruikerskeuze == 'T') break;
            if (gebruikerskeuze == 'V') pasVolgStrategietoe();
            if (gebruikerskeuze == 'L') PasLosStrategieToe();
            if (gebruikerskeuze == 'S') PasSpeelStrategieToe();
            if (gebruikerskeuze == 'Z') PasZetToe();

        }

    }//toonPuzzelMenu

    void toonTekenMenu() {
        while (true) {
            toonHuidigeBord();
            cout << "[T]erug [S]choon [R]andom t[O]ggle [G]enereer: ";
            char gebruikerskeuze = leesEnkelKarakter();

            if (gebruikerskeuze == 'T') break;
            if (gebruikerskeuze == 'S') MaakSchoon();
            if (gebruikerskeuze == 'R') DoeRandomLampen();
            if (gebruikerskeuze == 'O') ToggleLampen();
            if (gebruikerskeuze == 'G') GenereerMoeilijk();
        }
    }//toonTekenMenu

    void MaakSchoon(){
        for(int rij = 0; rij < bordHoogte; rij++){
            for(int kolom = 0; kolom < bordBreedte; kolom++){
                deWereld[rij][kolom] = false;
            }
        }
        for(int rij = 0; rij < bordHoogte; rij++){
            for(int kolom = 0; kolom < bordBreedte; kolom++){
                oplossing[rij][kolom] = false;
            }
        }
    }//MaakSchoon

    void DoeRandomLampen(){
        MaakSchoon();
        int HoeveelheidLampen = bordHoogte * bordBreedte;
        int AanTeZettenLampen = (HoeveelheidLampen * LampPercentage) / 100;
        int geplaatsteLampen = 0;

        cout << AanTeZettenLampen << " lampen aan zetten." << endl;

        while (geplaatsteLampen < AanTeZettenLampen) {
            int randomRij = randomgetal() % bordHoogte;
            int randomKolom = randomgetal() % bordBreedte;

            if (!deWereld[randomRij][randomKolom]) {
                deWereld[randomRij][randomKolom] = true;
                geplaatsteLampen++;
            }
        }

    }//DoeRandomLampen

    void ToggleLampen() {
        cursorRij = bordHoogte / 2;
        cursorKolom = bordBreedte / 2;
        int previouscursorStatus;

        if (cursorStatus){
            previouscursorStatus = 1;
        }
        else{
            cursorStatus = true;
            previouscursorStatus = 0; //onthouden wat de vorige status was
        }

        while(true) {
            for(int rij = bordHoogte - 1; rij >= 0; --rij) {
                cout << rij + 1 << "\t";
                for(int kolom = 0; kolom < bordBreedte; ++kolom) {
                    if(rij == cursorRij && kolom == cursorKolom) {
                        cout << (deWereld[rij][kolom] ? cursorAan : cursorUit) << " ";
                        //cursor laten zien
                    }
                    else {
                        cout << (deWereld[rij][kolom] ? lampAan : lampUit) << " ";
                        //normale lamp laten zien
                    }
                }
                cout << "\n";
            }
            cout << "\t";
            for(int kolom = 0; kolom < bordBreedte; ++kolom) {
                cout << char('A' + kolom) << " ";
            }
            cout << endl;
            cout << "Gebruik W/A/S/D om te bewegen, spatie om te togglen, T om terug te gaan: ";

            char gebruikerskeuze = leesEnkelKarakter();
            if (gebruikerskeuze == 'W' && cursorRij < bordHoogte - 1) cursorRij++;
            if (gebruikerskeuze == 'S' && cursorRij > 0) cursorRij--;
            if (gebruikerskeuze == 'A' && cursorKolom > 0) cursorKolom--;
            if (gebruikerskeuze == 'D' && cursorKolom < bordBreedte - 1) cursorKolom++;
            if (gebruikerskeuze == ' ') toggle(cursorRij, cursorKolom);
            if (gebruikerskeuze == 'T'){
                if (previouscursorStatus == 0)
                    cursorStatus = false; //vorige status terugzetten
                break;
            }
        }
    }

    void GenereerMoeilijk() {
        MaakSchoon();  // Begin met alle lampen uit

        cout << "Geef moeilijkheidsgraad (aantal zetten): ";
        int moeilijkheidsgraad = leesGetalMetMaximum(bordHoogte * bordBreedte);
        int geplaatsteZetten = 0;

        while (geplaatsteZetten < moeilijkheidsgraad) {
            int randomRij = randomgetal(0, bordHoogte - 1);
            int randomKolom = randomgetal(0, bordBreedte - 1);

            if (!oplossing[randomRij][randomKolom]) { //checken of er al een zet is geplaatst op dat vakje
                oplossing[randomRij][randomKolom] = true;//oplossing bijwerken
                wisselLampEnBurenOm(randomRij, randomKolom);//zet toepassen op echte bord
                geplaatsteZetten++;
            }
        }
    }

    void toonHuidigeBord() {
        if(cursorStatus){
            for(int rij = bordHoogte - 1; rij >= 0; --rij) {
                cout << rij + 1 << "\t";
                for(int kolom = 0; kolom < bordBreedte; ++kolom) {
                    if(rij == cursorRij && kolom == cursorKolom) {
                        cout << (deWereld[rij][kolom] ? cursorAan : cursorUit) << " ";
                        //cursor laten zien
                    } else {
                        cout << (deWereld[rij][kolom] ? lampAan : lampUit) << " ";
                        //normale lamp laten zien
                    }
                }
                cout << "\n";
            }
            cout << "\t";
            for(int kolom = 0; kolom < bordBreedte; ++kolom) {
                cout << char('A' + kolom) << " ";
            }
            cout << endl;

        }
        else{
            for (int huidigeRij = bordHoogte - 1; huidigeRij >= 0; --huidigeRij) {
                cout << huidigeRij + 1 << "\t";
                for (int huidigeColomn = 0; huidigeColomn < bordBreedte; ++huidigeColomn) {
                    bool deWaardeVanDeWereldVanDeHuigeCel = deWereld[huidigeRij][huidigeColomn];
                    if (deWaardeVanDeWereldVanDeHuigeCel) { cout << lampAan <<" "; }
                    else { cout << lampUit << " "; }
                }
                cout << "\n";

            }
            cout << "\t";
            for (int kolom = 0; kolom < bordBreedte; ++kolom) {
                cout << char('A' + kolom) << " ";
            }
            cout << endl;
        }

    }//toonHuidigeBord

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

    }//toonHoofdmenu
public:
    void startSpel() {
        infoblokje();
        toonHoofdmenu();
    }
};

int main() {
    LightOutSpel spel;
    spel.startSpel();
    return 0;
}//main