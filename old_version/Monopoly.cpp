//il programma non include interfaccia grafica
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> //mi serve per generare i numeri pseudo casuali
#include <ctime> //mi serve per usare l'ora attuale come seme dei numeri pseudo casuali.
using namespace std;

// Classe che rappresenta giocatore
class Giocatore {
public:
    string nome;
    string pedina;
    int posizione;
    int saldo;
    int turniPrigione;

    // Costruttore (lista di inizializzazione dei membri)
    Giocatore(string nomeGiocatore, string pedinaGiocatore) : nome(nomeGiocatore), pedina(pedinaGiocatore), posizione(0), saldo(1500), turniPrigione(0) {}
};

// Classe che rappresenta una proprieta' nel tabellone
class Proprieta {
public:
    string nome;
    int costo;
    int affitto;
    string colore;
    int caseCostruite;
    bool haAlbergo; //bool vero o falso
    Giocatore* proprietario;

    Proprieta(string nomeProprieta, int costoProprieta, int affittoProprieta, string coloreProprieta)
        : nome(nomeProprieta), costo(costoProprieta), affitto(affittoProprieta), colore(coloreProprieta), caseCostruite(0), haAlbergo(false), proprietario(NULL) {}
};


// Classe che rappresenta il tabellone
class Tabellone {
public:
    vector<Proprieta> proprieta; // Vettore di proprieta' nel tabellone

    // Costruttore
    Tabellone() {
    proprieta.push_back(Proprieta("Via", 0, 0, ""));
        proprieta.push_back(Proprieta("Vicolo Corto", 60, 2, "Marrone"));
        proprieta.push_back(Proprieta("Probabilita'", 0, 0, ""));
        proprieta.push_back(Proprieta("Vicolo Stretto", 60, 4, "Marrone"));
        proprieta.push_back(Proprieta("Tassa Patrimoniale", 200, 0, ""));
        proprieta.push_back(Proprieta("Stazione Sud", 200, 25, "Stazione"));
        proprieta.push_back(Proprieta("Bastioni Gran Sasso", 100, 6, "Azzurro"));
        proprieta.push_back(Proprieta("Imprevisti", 0, 0, ""));
        proprieta.push_back(Proprieta("Viale Monterosa", 100, 6, "Azzurro"));
        proprieta.push_back(Proprieta("Viale Vesuvio", 120, 8, "Azzurro"));
        proprieta.push_back(Proprieta("Prigione", 0, 0, ""));
        proprieta.push_back(Proprieta("Via Accademia", 140, 10, "Rosa"));
        proprieta.push_back(Proprieta("Societa' Elettrica", 150, 0, "Servizi"));
        proprieta.push_back(Proprieta("Corso Ateneo", 140, 10, "Rosa"));
        proprieta.push_back(Proprieta("Piazza Universita'", 160, 12, "Rosa"));
        proprieta.push_back(Proprieta("Stazione Ovest", 200, 25, "Stazione"));
        proprieta.push_back(Proprieta("Via Verdi", 180, 14, "Arancione"));
        proprieta.push_back(Proprieta("Probabilita'", 0, 0, ""));
        proprieta.push_back(Proprieta("Corso Raffaello", 180, 14, "Arancione"));
        proprieta.push_back(Proprieta("Piazza Dante", 200, 16, "Arancione"));
        proprieta.push_back(Proprieta("Parcheggio Gratuito", 0, 0, ""));
        proprieta.push_back(Proprieta("Via Marco Polo", 220, 18, "Rosso"));
        proprieta.push_back(Proprieta("Imprevisti", 0, 0, ""));
        proprieta.push_back(Proprieta("Corso Magellano", 220, 18, "Rosso"));
        proprieta.push_back(Proprieta("Largo Colombo", 240, 20, "Rosso"));
        proprieta.push_back(Proprieta("Stazione Nord", 200, 25, "Stazione"));
        proprieta.push_back(Proprieta("Viale Costantino", 260, 22, "Giallo"));
        proprieta.push_back(Proprieta("Viale Traiano", 260, 22, "Giallo"));
        proprieta.push_back(Proprieta("Societa' Acqua Potabile", 150, 0, "Servizi"));
        proprieta.push_back(Proprieta("Piazza Giulio Cesare", 280, 24, "Giallo"));
        proprieta.push_back(Proprieta("Vai in Prigione", 0, 0, ""));
        proprieta.push_back(Proprieta("Via Roma", 300, 26, "Verde"));
        proprieta.push_back(Proprieta("Corso Impero", 300, 26, "Verde"));
        proprieta.push_back(Proprieta("Probabilita'", 0, 0, ""));
        proprieta.push_back(Proprieta("Largo Augusto", 320, 28, "Verde"));
        proprieta.push_back(Proprieta("Stazione Est", 200, 25, "Stazione"));
        proprieta.push_back(Proprieta("Imprevisti", 0, 0, ""));
        proprieta.push_back(Proprieta("Viale dei Giardini", 350, 35, "Blu"));
        proprieta.push_back(Proprieta("Parco della Vittoria", 400, 50, "Blu"));
    }

    // Metodo per visualizzare il tabellone con le posizioni dei giocatori in questa formattazione: [Casella, Pedina, Pedina, ecc...]
    void visualizza(const vector<Giocatore>& giocatori) const { //const per assicurarmi di non cambiare i valori che uso
        for (size_t i = 0; i < proprieta.size(); ++i) {
            cout << "[" << proprieta[i].nome;
            for (size_t j = 0; j < giocatori.size(); ++j)
                if (giocatori[j].posizione == i)
                    cout << ", " << giocatori[j].pedina; 
            cout << "] ";
        }
        cout << endl;
    }
};
//funzione check per vedere se posso costruire case
bool possiedeTutteLeProprietaDiColore(Giocatore& giocatore, const string& colore, const Tabellone& tabellone) {
    for (size_t i = 0; i < tabellone.proprieta.size(); ++i) {
        if (tabellone.proprieta[i].colore == colore && tabellone.proprieta[i].proprietario != &giocatore) { 	//vede se di tutte le caselle di quel colore ce n'è una che non possieda, in questo caso restituisce false
            return false;
        }
    }
    return true;
}
//funzione per costruire casa o albergo, max 4 case, max 1 albergo
void costruisciCasaOAlbergo(Giocatore& giocatore, Proprieta& proprieta, const Tabellone& tabellone) {
    if (proprieta.proprietario == &giocatore && possiedeTutteLeProprietaDiColore(giocatore, proprieta.colore, tabellone)) {
        if (proprieta.caseCostruite < 4) { //se ha meno di 4 case esegue questo
            proprieta.caseCostruite++;
            giocatore.saldo -= 50; // Costo di una casa
            cout << giocatore.nome << " ha costruito una casa su " << proprieta.nome << endl;
        } else if (!proprieta.haAlbergo) { //se ha quattro case ma nessun albergo questo
            proprieta.haAlbergo = true;
            giocatore.saldo -= 200; // Costo di un albergo
            cout << giocatore.nome << " ha costruito un albergo su " << proprieta.nome << endl;
        } else { //se ha un albergo questo
            cout << "Non puoi costruire più di un albergo su " << proprieta.nome << endl;
        }
    } else {
        cout << "Non possiedi tutte le proprietà di questo colore o non sei il proprietario di " << proprieta.nome << endl;
    }
}

// Funzione che consente di spostare un giocatore con un dado, e se supera l'ultima casella torna alla prima e ottiene 100 dollari
void spostaGiocatore(Giocatore& giocatore, int dado, const Tabellone& tabellone) {
    int nuovaPosizione = giocatore.posizione + dado;
    if (nuovaPosizione >= tabellone.proprieta.size()) {
        cout << giocatore.nome << " ha raccolto $100 passando dal Via." << endl;
        giocatore.saldo += 100;
        cout << giocatore.nome << " ora ha $" << giocatore.saldo << " rimanenti." << endl;
        nuovaPosizione %= tabellone.proprieta.size();
    }
    giocatore.posizione = nuovaPosizione;
}

// Funzione per permettere al giocatore di comprare la proprieta'
void compraProprieta(Giocatore& giocatore, Proprieta& proprieta) {
    if (proprieta.proprietario == NULL && giocatore.saldo >= proprieta.costo) { //controlla se e' posseduta o costa troppo
        giocatore.saldo -= proprieta.costo;
        proprieta.proprietario = &giocatore;
        cout << giocatore.nome << " ha comprato " << proprieta.nome << " per $" << proprieta.costo << endl;
        cout << giocatore.nome << " ora ha $" << giocatore.saldo << " rimanenti." << endl;
    } else {
        cout << "Non puo' comprare " << proprieta.nome << endl;
    }
}

// Funzione per far pagare al giocatore l'affitto al proprietario della proprietà su cui atterra.
void pagaAffitto(Giocatore& giocatore, Proprieta& proprieta, const Tabellone& tabellone) {
    if (proprieta.proprietario != NULL && proprieta.proprietario != &giocatore) {
        int affittoDaPagare = proprieta.affitto;
        if (proprieta.colore == "Stazione") {
            int numeroStazioni = 0;
            for (size_t i = 0; i < tabellone.proprieta.size(); ++i) {
                if (tabellone.proprieta[i].colore == "Stazione" && tabellone.proprieta[i].proprietario == proprieta.proprietario) {
                    numeroStazioni++;
                }
            }
            affittoDaPagare *= numeroStazioni; // Moltiplica l'affitto base per il numero di stazioni possedute
        }
        if (proprieta.caseCostruite > 0) {
            affittoDaPagare *= (proprieta.caseCostruite + 1); // Moltiplica l'affitto base per il numero di case + 1
        }
        if (proprieta.haAlbergo) {
            affittoDaPagare *= 2; // Raddoppia l'affitto se c'è un albergo
        }
        giocatore.saldo -= affittoDaPagare;
        proprieta.proprietario->saldo += affittoDaPagare;
        cout << giocatore.nome << " ha pagato $" << affittoDaPagare << " di affitto a " << proprieta.proprietario->nome << endl;
        cout << giocatore.nome << " ora ha $" << giocatore.saldo << " rimanenti." << endl;
        cout << proprieta.proprietario->nome << " ora ha $" << proprieta.proprietario->saldo << " rimanenti." << endl;
    }
}





// Funzione per pescare una carta casuale e applicare il suo effetto al giocatore.
void pescaCartaProbabilita(Giocatore& giocatore) {
    int carta = rand() % 5; //% e' l'operatore modulo, restituisce il resto
    switch (carta) {
        case 0:
            cout << "Probabilita': Avanza al Via (Raccogli $100)" << endl;
            giocatore.posizione = 0;
            giocatore.saldo += 100;
            break;
        case 1:
            cout << "Probabilita': Paga $50" << endl;
            giocatore.saldo -= 50;
            break;
        case 2:
            cout << "Probabilita': Raccogli $50" << endl;
            giocatore.saldo += 50;
            break;
        case 3:
            cout << "Probabilita': Paga $100" << endl;
            giocatore.saldo -= 100;
            break;
        case 4:
            cout << "Probabilita': Vai in prigione!" << endl;
            giocatore.posizione = 10; //pos prigione
            giocatore.turniPrigione = 3;
            break;
    }
    cout << giocatore.nome << " ora ha $" << giocatore.saldo << " rimanenti." << endl;
}

// Funzione per gestire turno giocatore
void turnoGiocatore(Giocatore& giocatore, Tabellone& tabellone, vector<Giocatore>& giocatori) {
    // Check prigione
    if (giocatore.turniPrigione > 0) {
        cout << giocatore.nome << " e' in prigione per altri " << giocatore.turniPrigione << " turno(i)." << endl;
        cout << "Vuoi pagare $50 per uscire di prigione? (s/n): ";
        char scelta;
        cin >> scelta;
        if (scelta == 's' || scelta == 'S') {
            giocatore.saldo -= 50;
            giocatore.turniPrigione = 0;
            cout << giocatore.nome << " ha pagato $50 per uscire di prigione." << endl;
        } else {
            giocatore.turniPrigione--;
            return;
        }
    }

    // Turno del giocatore per lanciare i dadi e muoversi
    cout << "Turno di " << giocatore.nome << ". Saldo attuale: $" << giocatore.saldo << endl;
    cout << "Premi Invio per tirare i dadi...";
    cin.ignore(100, '\n');
    cin.get();
    int dado1 = rand() % 6 + 1;
	int dado2 = rand() % 6 + 1;
	int dado = dado1 + dado2;
	cout << giocatore.nome << " ha tirato " << dado1 << " e " << dado2 << " per un totale di " << dado << endl;
    spostaGiocatore(giocatore, dado, tabellone);

    // Determina dove e' arrivato il giocatore
    Proprieta& proprietaAtterrata = tabellone.proprieta[giocatore.posizione];
    cout << giocatore.nome << " e' atterrato su " << proprietaAtterrata.nome << endl;

    // Gestire l'azione in base al tipo di proprietà
if (proprietaAtterrata.nome == "Probabilita'") {
        pescaCartaProbabilita(giocatore);
    } else if (proprietaAtterrata.nome == "Vai in Prigione") {
        cout << giocatore.nome << " e' stato mandato in prigione per 3 turni." << endl;
        giocatore.posizione = 10; //pos prigione
        giocatore.turniPrigione = 3;
} else if (proprietaAtterrata.nome == "Via") {
} else if (proprietaAtterrata.nome == "Prigione") {
} else if (proprietaAtterrata.nome == "Parcheggio Gratuito") {
    cout << giocatore.nome << " si riposa nel Parcheggio Gratuito." << endl;
} else if (proprietaAtterrata.nome == "Tassa Patrimoniale") {
    cout << giocatore.nome << " deve pagare la Tassa Patrimoniale di $200." << endl;
    giocatore.saldo -= 200;
} else if (proprietaAtterrata.nome == "Imprevisti") {
    pescaCartaProbabilita(giocatore);
} else if (proprietaAtterrata.proprietario == NULL && giocatore.saldo >= proprietaAtterrata.costo) {
        char scelta;
        do {
            cout << "Vuoi comprare " << proprietaAtterrata.nome << " per $" << proprietaAtterrata.costo << "? (s/n): ";
            cin >> scelta;
        } while (scelta != 's' && scelta != 'n' && scelta != 'S' && scelta != 'N');
        if (scelta == 's' || scelta == 'S') {
                    compraProprieta(giocatore, proprietaAtterrata);
        } else {
            cout << giocatore.nome << " ha scelto di non comprare " << proprietaAtterrata.nome << endl;
        }
    } else if (proprietaAtterrata.proprietario != NULL) {
        pagaAffitto(giocatore, proprietaAtterrata, tabellone);
    } else {
        cout << giocatore.nome << " non ha abbastanza soldi per comprare " << proprietaAtterrata.nome << endl;
    }

//opzione per costruire case o alberghi dove è permesso

    if (proprietaAtterrata.colore!="Stazione"&& proprietaAtterrata.colore!="" && proprietaAtterrata.colore!="Servizi" &&proprietaAtterrata.proprietario == &giocatore && possiedeTutteLeProprietaDiColore(giocatore, proprietaAtterrata.colore, tabellone)) {
        char scelta;
        do {
            cout << "Vuoi costruire una casa o un albergo su " << proprietaAtterrata.nome << "? (s/n): ";
            cin >> scelta;
        } while (scelta != 's' && scelta != 'n' && scelta != 'S' && scelta != 'N');
        if (scelta == 's' || scelta == 'S') {
            costruisciCasaOAlbergo(giocatore, proprietaAtterrata, tabellone);
        }
    }

    // Visualizzare il tabellone con le posizioni dei giocatori
    cin.ignore(100, '\n');
    tabellone.visualizza(giocatori);
}

int main() {
    srand(time(0)); // Inserisce il generatore di numeri casuali (il seme e' l'ora attuale)

    // Lista di pedine disponibili
    vector<string> pedineDisponibili;
    pedineDisponibili.push_back("Auto");
    pedineDisponibili.push_back("Cappello");
    pedineDisponibili.push_back("Scarpa");
    pedineDisponibili.push_back("Cane");
    pedineDisponibili.push_back("Carriola");
    pedineDisponibili.push_back("Battello");
    pedineDisponibili.push_back("Ferro da stiro");
    pedineDisponibili.push_back("Scarpa");

    // Ottenere il numero di giocatori con ciclo do while
    int numGiocatori;
    do {
        cout << "Inserisci il numero di giocatori (max 8): ";
        cin >> numGiocatori;
        if(numGiocatori < 2 || numGiocatori > 8)
            cout<<"Numero di giocatori non accettabile"<<endl;
    } while (numGiocatori < 2 || numGiocatori > 8);

    // Crea giocatori
    vector<Giocatore> giocatori;
    for (int i = 0; i < numGiocatori; ++i) {
        string nomeGiocatore;
        cout << "Inserisci il nome per il giocatore " << (i + 1) << ": ";
        cin >> nomeGiocatore;

        // Mostra le pedine disponibili
        cout << "Scegli una pedina tra le seguenti: ";
        for (size_t j = 0; j < pedineDisponibili.size(); ++j) {
            cout << j + 1 << ". " << pedineDisponibili[j] << " ";
        }
        cout << endl;

        // Seleziona la pedina
        int sceltaPedina;
        cin >> sceltaPedina;
        string pedinaScelta = pedineDisponibili[sceltaPedina - 1];

        // Rimuovi la pedina scelta dalla lista delle pedine disponibili
        pedineDisponibili.erase(pedineDisponibili.begin() + sceltaPedina - 1);

		//aggiunge il giocatore
        giocatori.push_back(Giocatore(nomeGiocatore, pedinaScelta));
    }

    // Inizializza il tabellone
    Tabellone tabellone;

    // Loop di gioco
    bool giocoInCorso = true;
    while (giocoInCorso) {
        for (size_t i = 0; i < giocatori.size(); ++i) {
            turnoGiocatore(giocatori[i], tabellone, giocatori);

            // Rimuovi i giocatori in bancarotta
            if (giocatori[i].saldo <= 0) {
                cout << giocatori[i].nome << " e' in bancarotta ed e' stato eliminato dal gioco." << endl;
                giocatori.erase(giocatori.begin() + i); //cancello l'elemento dal vettore
                --i; // Decrementa l'indice per evitare di saltare il prossimo giocatore
            }
        }

        // Check fine
        if (giocatori.size() <= 1) {
            giocoInCorso = false;
        }
    }

    // Determina il vincitore
    if (giocatori.size() == 1) {
        cout << "Gioco finito! Il vincitore e' " << giocatori[0].nome << " con $" << giocatori[0].saldo << " rimanenti." << endl;
    } else {
        cout << "Gioco finito! Nessun vincitore." << endl;
    }

    return 0;
}
