//
//  Sudoku.hpp
//  Sudoku
//
//  Created by Milan Lazarevic on 16.12.23..
//

#ifndef Sudoku_hpp
#define Sudoku_hpp

#include <iostream>

class Sudoku {
public:
    /**
     * @brief Konstruktor za Sudoku klasu.
     *
     * Inicijalizuje instancu Sudoku klase postavljajući potrebne vrednosti, uključujući postavljanje generatora slučajnih brojeva na osnovu trenutnog vremena.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    Sudoku();
    /**
     * @brief Konstruktor za Sudoku klasu koji prima početnu postavku.
     *
     * Inicijalizuje instancu Sudoku klase koristeći početnu postavku koja se prosleđuje.
     *
     * @param initialBoard Početna postavka Sudoku table predstavljena kao matrica celih brojeva dimenzija SIZE x SIZE.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    Sudoku(const int initialBoard[9][9]);
    /**
     * @brief Konstruktor kopije za Sudoku klasu.
     *
     * Kopira vrednosti iz druge instance Sudoku klase u trenutnu instancu.
     *
     * @param other Referenca na drugu instancu Sudoku klase koja se kopira.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    Sudoku(const Sudoku& other);
    /**
     * @brief Destruktor za Sudoku klasu.
     *
     * Oslobađa resurse vezane za instancu Sudoku klase. U ovom slučaju, nema dodatnih resursa koji bi zahtevali ručno oslobađanje.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    ~Sudoku();
    
    /**
     * @brief Operator dodele za Sudoku klasu.
     *
     * Ova funkcija omogućava dodelu vrednosti jedne instance Sudoku klase drugoj korišćenjem semantičkog pomeranja (move semantics).
     *
     * @param newBoard R-value referenca na matricu celih brojeva dimenzija SIZE x SIZE koja se dodeljuje trenutnoj instanci.
     * @return Referenca na trenutnu instancu Sudoku klase nakon dodele.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    Sudoku& operator=(int (&&newBoard)[9][9]);
    
    /**
     * @brief Proverava validnost generisane Sudoku table.
     *
     * Ova funkcija vrši proveru validnosti generisane Sudoku table. Prvo se vrši provera redova i kolona da li postoje duplikati.
     * Zatim se vrši provera unutar svakog podkvadrata 3x3. Ukoliko postoji bilo koji red, kolona ili podkvadrat sa više od 6 popunjenih
     * polja, ili ako postoji duplikat u nekom redu, koloni ili podkvadratu, funkcija vraća false. U suprotnom, vraća true.
     *
     * @return True ako je generisana tabla validna, False inače.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    bool checkGeneratedBoard() const;
    /**
     * @brief Proverava validnost rešenja Sudoku table.
     *
     * Ova funkcija proverava validnost rešenja Sudoku table. Prvo se vrši provera da li je tabla u potpunosti popunjena.
     * Zatim se vrši provera duplikata u redovima, kolonama i podkvadratima 3x3. Nakon provere, funkcija ažurira statistiku o postavljenim
     * i netačno postavljenim brojevima, kao i broj odigranih igara. Na kraju, ukoliko postoji bilo koji netačno postavljen broj,
     * funkcija vraća false, u suprotnom vraća true.
     *
     * @return True ako je rešenje validno, False inače.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    bool checkValidity();
    /**
     * @brief Generiše Sudoku tablu.
     *
     * Ova funkcija inicijalizuje proces generisanja Sudoku table. Prvo postavlja generator slučajnih brojeva na osnovu trenutnog vremena,
     * zatim resetuje statistiku i briše prethodno stanje table. Nakon toga, poziva funkciju za generisanje Sudoku table rekurzivno.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    void generateBoard();
    /**
     * @brief Proverava da li je Sudoku igra rešena.
     *
     * Proverava da li su sva polja popunjena u Sudoku tabeli, čime se utvrđuje da li je trenutna konfiguracija ispravno rešenje.
     *
     * @return True ako je Sudoku igra rešena, False inače.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    bool isSolved() const;
    /**
     * @brief Rekurzivno rešava Sudoku tablu.
     *
     * Ova funkcija rekurzivno rešava Sudoku tablu pomoću backtracking algoritma. Prvo pronalazi prvo prazno polje u tabeli.
     * Zatim, za svaki broj od 1 do SIZE, proverava da li se taj broj može postaviti na trenutno prazno polje. Ako može, postavlja
     * ga na to mesto, poziva sebe rekurzivno, i ako rekurzivni poziv uspešno reši preostali deo table, funkcija vraća true.
     * U suprotnom, vraća se unazad (backtracks) i pokušava sa sledećim brojem. Ako nijedan broj ne može da se postavi na trenutno
     * prazno polje, funkcija vraća false.
     *
     * @return True ako je tabla uspešno rešena, False inače.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    bool solveRecursive();
    
    /**
     * @brief Ispisuje trenutno stanje Sudoku table na konzolu.
     *
     * Ova funkcija prolazi kroz sve redove i kolone Sudoku table i ispisuje ih na konzolu. Prazna polja se prikazuju kao prazni karakteri,
     * dok se popunjena polja ispisuju sa njihovim vrednostima. Takođe, funkcija dodaje horizontalne i vertikalne linije između podkvadrata
     * kako bi poboljšala preglednost table.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    void printBoard() const;
    /**
     * @brief Ispisuje statistike igre na konzolu.
     *
     * Ova funkcija ispisuje statistike igre na konzolu, uključujući broj partije, broj tačno postavljenih brojeva
     * i broj netačno postavljenih brojeva.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    void printStatistics() const;
    
    /**
     * @brief Getter metoda za dobijanje vrednosti na određenom mestu u Sudoku tabeli.
     *
     * Ova funkcija omogućava pristup vrednosti na određenom mestu u Sudoku tabeli.
     *
     * @param row Redni indeks vrste u tabeli.
     * @param col Indeks kolone u tabeli.
     * @return Vrednost na datom mestu u tabeli.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    int getValue(int row, int col) const;
    /**
     * @brief Setter metoda za postavljanje vrednosti na određenom mestu u Sudoku tabeli.
     *
     * Ova funkcija omogućava postavljanje vrednosti na određenom mestu u Sudoku tabeli.
     *
     * @param row Redni indeks vrste u tabeli.
     * @param col Indeks kolone u tabeli.
     * @param value Nova vrednost koja se postavlja na datom mestu u tabeli.
     *
     *  Created by Milan Lazarevic on 27.12.2023.
     */
    void setValue(int row, int col, int value);
    
    static const int SIZE = 9;
    static const int SUBGRID_SIZE = SIZE / 3;
private:
    static const int EMPTY_CELL = 0;
    int board[SIZE][SIZE];
    
    // Broj unetih brojeva koji su na pravom mestu
    int correctPlacements;
    // Broj unetih brojeva koji su na pogrešnom mestu
    int incorrectPlacements;
    // Redni broj trenutne partije
    int gameCounter;
    
    /**
     * @brief Postavlja praznu vrednost na sva polja Sudoku table.
     *
     * Ova funkcija postavlja vrednost EMPTY_CELL na sva polja Sudoku table, čime se tabela vraća u početno stanje.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    void clearBoard();
    /**
     * @brief Proverava da li je potez validan u Sudoku igri.
     *
     * Proverava da li je uneseni broj (num) validan za postavljanje u određeni red (row) i kolonu (col) Sudoku table.
     * Validan potez je onaj koji ne krši pravila igre, tj. da se broj ne pojavljuje više puta u istom redu, istoj koloni ili u istom 3x3 bloku.
     *
     * @param row Red u kojem se vrši provera.
     * @param col Kolona u kojoj se vrši provera.
     * @param num Broj koji se proverava za validnost poteza.
     * @return True ako je potez validan, False inače.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    bool isValidMove(int row, int col, int num) const;
    /**
     * @brief Broji popunjena polja unutar određenog podkvadrata 3x3.
     *
     * Ova funkcija broji popunjena polja unutar određenog podkvadrata 3x3 na osnovu prosleđenih indeksa podkvadrata.
     *
     * @param subgridRow Redni indeks podkvadrata u glavnoj tabeli.
     * @param subgridCol Kolona indeks podkvadrata u glavnoj tabeli.
     * @return Broj popunjenih polja u određenom podkvadratu.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    int countFilledCellsInSubgrid(int subgridRow, int subgridCol) const;

    /**
     * @brief Rekurzivna funkcija za generisanje Sudoku table.
     *
     * Ova funkcija rekurzivno postavlja brojeve na Sudoku tabli, proveravajući validnost poteza. Pokušava postaviti brojeve od 1 do 9 na trenutno mesto,
     * premeštajući se redom po svim poljima table. Kada dođe do kraja tabele, generisanje se smatra uspešnim.
     *
     * @param row Red u kojem se vrši postavljanje broja.
     * @param col Kolona u kojoj se vrši postavljanje broja.
     * @return True ako je generisanje uspešno, False inače.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    bool generateSudoku(int row, int col);
    /**
     * @brief Uklanja brojeve iz postavke kako bi se dobila zagonetka.
     *
     * Ova funkcija uklanja određeni procenat brojeva iz generisane Sudoku table kako bi se dobila zagonetka.
     * Broj polja koji se uklanja određen je procenatom `removalPercentage`. Nakon toga, vrši se dodatna provera uklanjanjem brojeva
     * tako da svaki podkvadrat 3x3 ima najviše 6 popunjenih polja.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    void removeNumbers();
    
    /**
     * @brief Pronalazi prvo prazno polje u Sudoku tabeli.
     *
     * Ova funkcija pretražuje Sudoku tabelu red po red i kolona po kolona kako bi pronašla prvo prazno polje.
     * Ukoliko pronađe prazno polje, postavlja vrednosti argumenata 'row' i 'col' na koordinate tog polja i vraća true.
     * U suprotnom, vraća false.
     *
     * @param row Referenca na promenljivu u kojoj će se čuvati redni indeks praznog polja.
     * @param col Referenca na promenljivu u kojoj će se čuvati indeks kolone praznog polja.
     * @return True ako postoji prazno polje, False inače.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    bool findEmptyLocation(int& row, int& col) const;

    /**
     * @brief Resetuje statistike igre.
     *
     * Ova funkcija resetuje statistike igre pozivajući funkciju resetPlacements() i postavlja brojač partija na nulu.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    void resetStatistics();
    /**
     * @brief Resetuje statistike o postavljenim brojevima.
     *
     * Ova funkcija postavlja brojače ispravno postavljenih i netačno postavljenih brojeva na nulu.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    void resetPlacements();
};

#endif /* Sudoku_hpp */
