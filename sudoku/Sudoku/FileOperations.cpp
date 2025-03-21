//
//  FileOperations.cpp
//  Sudoku
//
//  Created by Milan Lazarevic on 16.12.23..
//

#include "FileOperations.hpp"
#include <fstream>
#include <string>

/**
 * @brief Konstruktor klase FileOperations.
 *
 * Ovaj konstruktor inicijalizuje instancu klase FileOperations.
 */
FileOperations::FileOperations() {}

/**
 * @brief Destruktor za FileOperations klasu.
 *
 * Oslobađa resurse vezane za instancu FileOperations klase. U ovom slučaju, nema dodatnih resursa koji bi zahtevali ručno oslobađanje.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
FileOperations::~FileOperations() {}

/**
 * @brief Učitava Sudoku tabelu iz tekstualnog fajla.
 *
 * Funkcija učitava Sudoku tabelu iz tekstualnog fajla čije se ime prosleđuje kao argument.
 * Ako fajl ne postoji, ispisuje odgovarajuću poruku na standardni izlaz za greške.
 *
 * @param sudoku Referenca na instancu Sudoku klase u koju se učitava tabela.
 * @param filename Ime fajla iz kojeg se vrši učitavanje.
 * @return True ako je učitavanje uspešno, false inače.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
bool FileOperations::loadFromFile(Sudoku& sudoku, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "\nGRESKA: Ne postoji fajl sa imenom: " << filename << std::endl;
        return false;
    }

    char c;
    int row = 0, col = 0;

    while (file.get(c) && row < Sudoku::SIZE) {
        if (c >= '0' && c <= '9') {
            sudoku.setValue(row, col, c - '0');
            ++col;

            if (col == Sudoku::SIZE) {
                ++row;
                col = 0;
            }
        }
    }

    file.close();
    return true;
}

/**
 * @brief Čuva Sudoku tabelu u tekstualni fajl.
 *
 * Funkcija čuva Sudoku tabelu u tekstualni fajl čije se ime prosleđuje kao argument.
 * Ako fajl ne postoji, ispisuje odgovarajuću poruku na standardni izlaz za greške.
 *
 * @param sudoku Referenca na konstantnu instancu Sudoku klase koja se čuva u fajlu.
 * @param filename Ime fajla u koji se vrši čuvanje.
 * @return True ako je čuvanje uspešno, false inače.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
bool FileOperations::saveToFile(const Sudoku& sudoku, const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open() || !file) {
        std::cerr << "GRESKA: Ne postoji fajl sa imenom: " << filename << std::endl;
        return false;
    }
    for (int i = 0; i < Sudoku::SIZE; ++i) {
        for (int j = 0; j < Sudoku::SIZE; ++j) {
            file << std::setw(2) << sudoku.getValue(i, j);

            if ((j + 1) % Sudoku::SUBGRID_SIZE == 0 && j < Sudoku::SIZE - 1) {
                file << " | ";
            }
        }

        file << std::endl;

        if ((i + 1) % Sudoku::SUBGRID_SIZE == 0 && i < Sudoku::SIZE - 1) {
            for (int k = 0; k < Sudoku::SIZE * 3 - 2; ++k) {
                file << "-";
            }
            file << std::endl;
        }
    }

    return true;
}
