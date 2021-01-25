#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


// Struktury a jejich vektory použité pro ukládání dat intepretů
struct alba {
    string nazevAlba;
    int pocetPisni;
    vector<string> pisen;
};

struct interpret {
    string jmeno;
    int pocetAlb;
    vector<alba> album;
};

// Hlavní vektor obsahující struktury všech interpretů
vector<interpret> interpreti;

int pocetIntepretu = interpreti.size();


// Deklarace veškerých funkcí, které se nacházejí pod hlavní funkcí main pro správnou funkcionalitu programu
void chybovaHlaska();
void pridatInterpreta();
void ulozitDoSouboru();
void nacteniZeSouboru();
void vytvoritPlaylist();
int zavrit();
void mainMenu();


// funkce pro start aplikace
int main() {
    cout << "Aplikace pro spravu hudebni sbirky" << endl;
    // Zavolá funkci hlavního menu
    mainMenu();
}


// Funkce vypisující chybovou hlásku po zadaní špatného vstupu
void chybovaHlaska() {
    cout << "Zadan neplatny vstup, zopakujte prosim znovu celou akci." << endl;
    cin.clear();
    cin.ignore(256,'\n');
    // Znovu se zavolá hlavní menu pomocí rekurze
}


// Funkce, která přidá data o intepretovi do jeho vlastní struktury ve vektoru intepreti
void pridatInterpreta() {
    cout << "Pridani interpreta" << endl;
    cout << "Zadejte jmeno noveho interpreta" << endl;
    string jmenoInterpreta;
    cin.clear();
    cin.sync();
    getline(cin, jmenoInterpreta);
    cout << "Kolik budete zadavat alb?" << endl;
    int jePocetPisniInt;
    int jePocetAlbInt;
    // Vektor pro počet písní jednotlivých alb, jelikož každé album může mít jiný počet zadávaných písní
    cin >> jePocetAlbInt;
    // Pokud se zadá špatný vstup
    if(cin.fail()) {
        // Vypíše se chybová hláška, input se vyčistí a uživatel bude muset znovu zadat požadovanou akci
        chybovaHlaska();
        pridatInterpreta();
    }
        // Jinak se pokračuje a začnou se zapisovat data podle vstupu uživatele
    else {
        // Vytvoří se struktura ve vektoru interpreti
        interpreti.push_back(interpret());
        pocetIntepretu = interpreti.size();
        interpreti[pocetIntepretu - 1].pocetAlb = jePocetAlbInt;
        // Do této struktury se postupně ukládají data jako název intepreta, jeho alba a jednotlivé písně v každém albumu
        interpreti[pocetIntepretu - 1].jmeno = jmenoInterpreta;
        // Pro každé album
        for(int i = 1; i <= interpreti[pocetIntepretu - 1].pocetAlb; i++) {
            cout << "Zadejte nazev " << i << ". alba:" << endl;
            string nazevAlba;
            cin.clear();
            cin.sync();
            getline(cin, nazevAlba);
            // Pro aktuálně tvořeného interpreta se přidá album a přiřadí se mu jméno zadané uživatelem
            interpreti[pocetIntepretu - 1].album.push_back(alba());
            interpreti[pocetIntepretu - 1].album[i - 1].nazevAlba = nazevAlba;
            cout << "Kolik je v albu pisni?" << endl;
            cin >> jePocetPisniInt;
            if(cin.fail()) {
                chybovaHlaska();
                pridatInterpreta();
            }
            else {
                // Pro každou píseň v albumu
                interpreti[pocetIntepretu - 1].album[i - 1].pocetPisni = jePocetPisniInt;
                for(int j = 1; j <= interpreti[pocetIntepretu - 1].album[i - 1].pocetPisni; j++) {
                    cout << "Zadejte nazev " << j << ". pisne:" << endl;
                    string nazevPisne;
                    cin.clear();
                    cin.sync();
                    getline(cin, nazevPisne);
                    // Pro každou píseň se vytvoří název v albu svého interpreta
                    interpreti[pocetIntepretu - 1].album[i - 1].pisen.push_back(nazevPisne);
                }
            }
        }
        // Výpis všech aktuálních informací
            for(int ip = 0; ip < pocetIntepretu; ip++) {
                cout << "Interpret: " << interpreti[ip].jmeno << endl;
                for (int g = 1; g <= interpreti[ip].pocetAlb; g++) {
                    cout << "Nazev alba: " << interpreti[ip].album[g - 1].nazevAlba << endl;
                    for(int k = 1; k <= interpreti[ip].album[g - 1].pocetPisni; k++) {
                        cout << k << ". pisen: " << interpreti[ip].album[g - 1].pisen[k - 1] << endl;
                    }
                }
            }
            // Smaže počet zadávaných písní pro jednotlivá alba kvůli opětovnému použití při chodu programu
        // Po stisknutí klávesy návrat do hlavního menu
        cout << "Pokracujte stisknutim klavesy enter..." << endl;
        cin.get();
        mainMenu();

    }
}

// Funkce, která uloží dosavadní seznam interpretů do souboru specifikovaného uživatelem
void ulozitDoSouboru() {
    cout << "Ulozeni zaznamu do souboru" << endl;
    cout << "Zadejte nazev souboru s priponou (.txt):" << endl;
    string nazevSouboru;
    cin >> nazevSouboru;
    // Soubor se vytvoří pro zápis v binární podobě a otevře se
    ofstream souborNaZapis;
    souborNaZapis.open(nazevSouboru, ios::binary);
    // Cykly pomocí kterých se projedou všichni interpreti a zapíšou se jejich informace
    for(int s = 0; s < pocetIntepretu; s++) {
        souborNaZapis << "Interpret: " << interpreti[s].jmeno << endl;
        for (int g = 1; g <= interpreti[s].pocetAlb; g++) {
            souborNaZapis << "Nazev alba: " << interpreti[s].album[g - 1].nazevAlba << endl;
            for(int k = 1; k <= interpreti[s].album[g - 1].pocetPisni; k++) {
                souborNaZapis << k << ". pisen: " << interpreti[s].album[g - 1].pisen[k - 1] << endl;
            }
        }
    }
    // Vypíše všechny data zapsané do souboru
    souborNaZapis.close();
    for(int ip = 0; ip < pocetIntepretu; ip++) {
        cout << "Interpret: " << interpreti[ip].jmeno << endl;
        for (int g = 1; g <= interpreti[ip].pocetAlb; g++) {
            cout << "Nazev alba: " << interpreti[ip].album[g - 1].nazevAlba << endl;
            for(int k = 1; k <= interpreti[ip].album[g - 1].pocetPisni; k++) {
                cout << k << ". pisen: " << interpreti[ip].album[g - 1].pisen[k - 1] << endl;
            }
        }
    }
    cout << "Akce provedena uspesne. Pokracujte stisknutim klavesy enter..." << endl;
    cin.get();
    mainMenu();

}

// Funkce, která zobrazí všechny informace obsažené v souboru, který uživatel specifikuje
void nacteniZeSouboru() {
    cout << "Zadejte nazev souboru, ze ktereho chcete data nacist (i s priponou):" << endl;
    string nazevSouboru;
    string text;
    cin >> nazevSouboru;
    ifstream soubor;
    soubor.open(nazevSouboru, ios::binary);
    // Pokud se soubor úspěšně otevře
    if(soubor.is_open()) {
        while(getline(soubor, text)) {
            cout << text << endl;
        }
    }
    // Pokud soubor nelze otevřít, vypíše se chybová hláška
    else cout << "Soubor nelze ovetřít." << endl;
    cout << "Pokracujte stisknutim klavesy enter..." << endl;
    cin.get();
    cin.get();
    mainMenu();
}

// Funkce vytvářející .m3u playlist s písněmi, které si uživatel vybere ze seznamu zadaných interpretů a alb v programu
void vytvoritPlaylist() {
cout << "Vyberte interpreta" << endl;
for(int i = 0; i < pocetIntepretu; i++) {
    cout << "ID: " << i << " " << interpreti[i].jmeno << endl;
}
int volbaInterpreta;
cin >> volbaInterpreta;
// Pokud uživatel zadá nepodporovaný vstup, který nemá na výběr
if(cin.fail() || (volbaInterpreta < 0 || volbaInterpreta > (pocetIntepretu - 1))) {
    chybovaHlaska();
    vytvoritPlaylist();
}
else {
    cout << "Vyberte album" << endl;
    for (int j = 0; j < interpreti[volbaInterpreta].pocetAlb; ++j) {
        cout << "ID: " << j << " " << interpreti[volbaInterpreta].album[j].nazevAlba << endl;
    }
    int volbaAlba;
    cin >> volbaAlba;
    if(cin.fail() || (volbaAlba < 0 || volbaAlba > (interpreti[volbaInterpreta].pocetAlb - 1))) {
        chybovaHlaska();
        vytvoritPlaylist();
    }
    else {
        cout << "Zadejte nazev souboru (bez pripony), do ktereho ze ulozi Vas playlist" << endl;
        string nazevSouboru;
        cin >> nazevSouboru;
        nazevSouboru = nazevSouboru + ".m3u";
        // Soubor se vytvoří, otevře, pomocí cyklu se do něj vše potřebné zapíše a následně se opět zavře
        ofstream playlist;
        playlist.open(nazevSouboru);
        for(int k = 0; k < interpreti[volbaInterpreta].album[volbaAlba].pocetPisni; k++) {
            playlist << interpreti[volbaInterpreta].album[volbaAlba].pisen[k] << ".mp3" << endl;
        }
        playlist.close();
        // Informuje uživatele o úspěšném zapsání do playlistu a po stisknutí klávesy enter navrátí uživatele do hlavního menu
        cout << "Vas playlist byl ulozen do souboru " << nazevSouboru << ". Pro spusteni premistete soubor m3u do slozky s pisnemi." << endl;
        cout << "Pokracujte stisknutim klavesy enter..." << endl;
        cin.get();
        mainMenu();
    }
}
}

// funkce pro ukončení aplikace
int zavrit() {
    //Ukončí aplikaci a uvolní místo v paměti pomocí destruktorů
    return 0;
}


// funkce hlavní menu
void mainMenu() {
    // Vypíše možnosti aplikace
    cout << "Menu\n0 - Pridat interpreta\n1 - Ulozit do souboru\n2 - Nacteni ze souboru\n3 - Vytvorit playlist (.M3U)\n4 - Zavrit\nZadejte volbu:" << endl;
    int volba;
    cin >> volba;
    // Pokud uživatel zadá něco jiného než číslo či číslo, které není na výběr
    if(cin.fail() || (volba < 0 || volba > 4)) {
        // Vypíše se chybová hláška, input se vyčistí a uživatel bude muset znovu zadat požadovanou akci
        cout << "Zadan neplatny prikaz. Napiste jej prosim znovu." << endl;
        cin.clear();
        cin.ignore(256,'\n');
        // Znovu se zavolá hlavní menu pomocí rekurze
        mainMenu();
    }
        // Pokud se vstup platný, tak se podle něj zavolá příslušná funkce
    else {
        switch(volba) {
            case 0: pridatInterpreta();
                break;
            case 1: ulozitDoSouboru();
                break;
            case 2: nacteniZeSouboru();
                break;
            case 3: vytvoritPlaylist();
                break;
            case 4: zavrit();
                break;
        }
    }
}