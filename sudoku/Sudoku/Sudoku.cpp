//
//  Sudoku.cpp
//  Sudoku
//
//  Created by Milan Lazarevic on 16.12.23..
//

#include "Sudoku.hpp"
#include <fstream>
#include <ctime>
#include <random>

/**
 * @brief Konstruktor za Sudoku klasu.
 *
 * Inicijalizuje instancu Sudoku klase postavljajući potrebne vrednosti, uključujući postavljanje generatora slučajnih brojeva na osnovu trenutnog vremena.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
Sudoku::Sudoku() {
    std::srand((unsigned)std::time(0));
    resetStatistics();
    clearBoard();
}

/**
 * @brief Konstruktor kopije za Sudoku klasu.
 *
 * Kopira vrednosti iz druge instance Sudoku klase u trenutnu instancu.
 *
 * @param other Referenca na drugu instancu Sudoku klase koja se kopira.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
Sudoku::Sudoku(const Sudoku& other) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = other.board[i][j];
        }
    }

    correctPlacements = other.correctPlacements;
    incorrectPlacements = other.incorrectPlacements;
    gameCounter = other.gameCounter;
}

/**
 * @brief Konstruktor za Sudoku klasu koji prima početnu postavku.
 *
 * Inicijalizuje instancu Sudoku klase koristeći početnu postavku koja se prosleđuje.
 *
 * @param initialBoard Početna postavka Sudoku table predstavljena kao matrica celih brojeva dimenzija SIZE x SIZE.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
Sudoku::Sudoku(const int initialBoard[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = initialBoard[i][j];
        }
    }

    resetStatistics();
}
/**
 * @brief Destruktor za Sudoku klasu.
 *
 * Oslobađa resurse vezane za instancu Sudoku klase. U ovom slučaju, nema dodatnih resursa koji bi zahtevali ručno oslobađanje.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
Sudoku::~Sudoku() {}

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
Sudoku& Sudoku::operator=(int (&&newBoard)[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = std::move(newBoard[i][j]);
        }
    }

    return *this;
}

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
bool Sudoku::isValidMove(int row, int col, int num) const {

    for (int i = 0; i < SIZE; ++i) {
        if ((board[row][i] == num && col != i) || (board[i][col] == num && row != i)) {
            return false;
        }
    }

    int startRow = row - row % SUBGRID_SIZE;
    int startCol = col - col % SUBGRID_SIZE;
    for (int i = 0; i < SUBGRID_SIZE; ++i) {
        for (int j = 0; j < SUBGRID_SIZE; ++j) {
            if (board[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

/**
 * @brief Proverava da li je Sudoku igra rešena.
 *
 * Proverava da li su sva polja popunjena u Sudoku tabeli, čime se utvrđuje da li je trenutna konfiguracija ispravno rešenje.
 *
 * @return True ako je Sudoku igra rešena, False inače.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
bool Sudoku::isSolved() const {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == EMPTY_CELL) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Generiše Sudoku tablu.
 *
 * Ova funkcija inicijalizuje proces generisanja Sudoku table. Prvo postavlja generator slučajnih brojeva na osnovu trenutnog vremena,
 * zatim resetuje statistiku i briše prethodno stanje table. Nakon toga, poziva funkciju za generisanje Sudoku table rekurzivno.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
void Sudoku::generateBoard() {
    srand(static_cast<unsigned>(time(nullptr)));
    resetPlacements();
    clearBoard();
    generateSudoku(0, 0);
    removeNumbers();
}

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
bool Sudoku::generateSudoku(int row, int col) {
    if (row == SIZE) {
        return true;
    }

    if (col == SIZE) {
        return generateSudoku(row + 1, 0);
    }

    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::shuffle(nums.begin(), nums.end(), std::default_random_engine((unsigned)std::time(0)));
    
    for (int num : nums) {
        if (isValidMove(row, col, num)) {
            board[row][col] = num;
            
            if (generateSudoku(row, col + 1)) {
                return true;
            }

            board[row][col] = EMPTY_CELL;
        }
    }

    return false;
}

/**
 * @brief Uklanja brojeve iz postavke kako bi se dobila zagonetka.
 *
 * Ova funkcija uklanja određeni procenat brojeva iz generisane Sudoku table kako bi se dobila zagonetka.
 * Broj polja koji se uklanja određen je procenatom `removalPercentage`. Nakon toga, vrši se dodatna provera uklanjanjem brojeva
 * tako da svaki podkvadrat 3x3 ima najviše 6 popunjenih polja.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
void Sudoku::removeNumbers() {
    double removalPercentage = 0.7;
    int cellsToRemove = static_cast<int>(removalPercentage * SIZE * SIZE);
    
    for (int i = 0; i < cellsToRemove; ++i) {
        int row = std::rand() % SIZE;
        int col = std::rand() % SIZE;
        
        board[row][col] = EMPTY_CELL;
    }
    
    std::cout << "\n";
    
    int subgridsCount[SIZE];
    for (int i = 0; i < SUBGRID_SIZE; ++i) {
        for (int j = 0; j < SUBGRID_SIZE; ++j) {
            subgridsCount[3 * i + j] = countFilledCellsInSubgrid(i, j);
        }
    }
    
    for (int subgridRow = 0; subgridRow < SUBGRID_SIZE; ++subgridRow) {
        for (int subgridCol = 0; subgridCol < SUBGRID_SIZE; ++subgridCol) {
            int startRow = subgridRow * SUBGRID_SIZE;
            int startCol = subgridCol * SUBGRID_SIZE;

            while (subgridsCount[3 * subgridRow + subgridCol] > 6) {
                int row = std::rand() % SUBGRID_SIZE;
                int col = std::rand() % SUBGRID_SIZE;

                if (board[startRow + row][startCol + col] != EMPTY_CELL) {
                    board[startRow + row][startCol + col] = EMPTY_CELL;
                    --subgridsCount[3 * subgridRow + subgridCol];
                }
            }
        }
    }
}

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
int Sudoku::countFilledCellsInSubgrid(int subgridRow, int subgridCol) const {
    int startRow = subgridRow * SUBGRID_SIZE;
    int startCol = subgridCol * SUBGRID_SIZE;
    int count = 0;

    for (int i = 0; i < SUBGRID_SIZE; ++i) {
        for (int j = 0; j < SUBGRID_SIZE; ++j) {
            if (board[i + startRow][j + startCol] != EMPTY_CELL) {
                ++count;
            }
        }
    }

    return count;
}

/**
 * @brief Postavlja praznu vrednost na sva polja Sudoku table.
 *
 * Ova funkcija postavlja vrednost EMPTY_CELL na sva polja Sudoku table, čime se tabela vraća u početno stanje.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
void Sudoku::clearBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = EMPTY_CELL;
        }
    }
}

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
bool Sudoku::checkValidity() {
    if (!isSolved())
        return false;
    
    resetPlacements();
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int currentNum = board[i][j];
            int incorrect = 0;

            for (int col = 0; col < SIZE; ++col) {
                if (col != j && board[i][col] == currentNum) {
                    ++incorrect;
                }
            }

            for (int row = 0; row < SIZE; ++row) {
                if (row != i && board[row][j] == currentNum) {
                    ++incorrect;
                }
            }

            int startRow = i - i % SUBGRID_SIZE;
            int startCol = j - j % SUBGRID_SIZE;
            for (int row = 0; row < SUBGRID_SIZE; ++row) {
                for (int col = 0; col < SUBGRID_SIZE; ++col) {
                    int currentRow = startRow + row;
                    int currentCol = startCol + col;
                    if (currentRow != i && currentCol != j && board[currentRow][currentCol] == currentNum) {
                        ++incorrect;
                    }
                }
            }
            
            if (incorrect > 0)
                incorrectPlacements++;
            else
                correctPlacements++;
        }
    }

    ++gameCounter;
    
    if (incorrectPlacements > 0)
        return false;
    
    return true;
}

/**
 * @brief Ispisuje trenutno stanje Sudoku table na konzolu.
 *
 * Ova funkcija prolazi kroz sve redove i kolone Sudoku table i ispisuje ih na konzolu. Prazna polja se prikazuju kao prazni karakteri,
 * dok se popunjena polja ispisuju sa njihovim vrednostima. Takođe, funkcija dodaje horizontalne i vertikalne linije između podkvadrata
 * kako bi poboljšala preglednost table.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
void Sudoku::printBoard() const {
    for (int i = 0; i < SIZE; ++i) {
        if (i % SUBGRID_SIZE == 0 && i != 0) {
            std::cout << "---------------------\n";
        }

        for (int j = 0; j < SIZE; ++j) {
            if (j % SUBGRID_SIZE == 0 && j != 0) {
                std::cout << "| ";
            }

            if (board[i][j] == EMPTY_CELL)
                std::cout << ' ' << ' ';
            else
                std::cout << board[i][j] << ' ';
        }

        std::cout << '\n';
    }
}

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
bool Sudoku::findEmptyLocation(int& row, int& col) const {
    for (row = 0; row < SIZE; ++row) {
        for (col = 0; col < SIZE; ++col) {
            if (board[row][col] == EMPTY_CELL) {
                return true;
            }
        }
    }
    return false;
}

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
bool Sudoku::solveRecursive() {
    int row, col;

    if (!findEmptyLocation(row, col)) {
        return true;
    }

    for (int num = 1; num <= SIZE; ++num) {
        if (isValidMove(row, col, num)) {
            board[row][col] = num;
            if (solveRecursive()) {
                return true;
            }
            
            board[row][col] = EMPTY_CELL;
        }
    }

    return false;
}

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
bool Sudoku::checkGeneratedBoard() const {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int currentNum = board[i][j];
            if (currentNum == EMPTY_CELL)
                continue;

            for (int col = 0; col < SIZE; ++col) {
                if (col != j && board[i][col] == currentNum) {
                    return false;
                }
            }

            for (int row = 0; row < SIZE; ++row) {
                if (row != i && board[row][j] == currentNum) {
                    return false;
                }
            }
            
            int startRow = i - i % SUBGRID_SIZE;
            int startCol = j - j % SUBGRID_SIZE;
            int filledCellsInSubgrid = 0;
            
            for (int row = 0; row < SUBGRID_SIZE; ++row) {
                for (int col = 0; col < SUBGRID_SIZE; ++col) {
                    int currentRow = startRow + row;
                    int currentCol = startCol + col;
                    if (currentRow != i && currentCol != j && board[currentRow][currentCol] == currentNum) {
                        return false;
                    }
                    
                    if (board[currentRow][currentCol] != EMPTY_CELL) {
                        ++filledCellsInSubgrid;
                    }
                }
            }
            
            if (filledCellsInSubgrid > 6) {
                return false;
            }
        }
    }
    
    return true;
}

/**
 * @brief Resetuje statistike igre.
 *
 * Ova funkcija resetuje statistike igre pozivajući funkciju resetPlacements() i postavlja brojač partija na nulu.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
void Sudoku::resetStatistics() {
    resetPlacements();
    gameCounter = 0;
}

/**
 * @brief Resetuje statistike o postavljenim brojevima.
 *
 * Ova funkcija postavlja brojače ispravno postavljenih i netačno postavljenih brojeva na nulu.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
void Sudoku::resetPlacements() {
    correctPlacements = 0;
    incorrectPlacements = 0;
}

/**
 * @brief Ispisuje statistike igre na konzolu.
 *
 * Ova funkcija ispisuje statistike igre na konzolu, uključujući broj partije, broj tačno postavljenih brojeva
 * i broj netačno postavljenih brojeva.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
void Sudoku::printStatistics() const {
    std::cout << "\nStatistika za partiju #" << gameCounter << ":\n";
    std::cout << "Broj unetih brojeva koji su na pravom mestu: " << correctPlacements << "\n";
    std::cout << "Broj unetih brojeva koji su na pogrešnom mestu: " << incorrectPlacements << "\n";
}

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
int Sudoku::getValue(int row, int col) const {
    return board[row][col];
}

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
void Sudoku::setValue(int row, int col, int value) {
    board[row][col] = value;
}
