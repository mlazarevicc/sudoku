//
//  FileOperations.hpp
//  Sudoku
//
//  Created by Milan Lazarevic on 16.12.23..
//

#ifndef FileOperations_hpp
#define FileOperations_hpp

#include <iostream>
#include "Sudoku.hpp"

class FileOperations {
public:
    /**
     * @brief Konstruktor klase FileOperations.
     *
     * Ovaj konstruktor inicijalizuje instancu klase FileOperations.
     */
    FileOperations();
    
    /**
     * @brief Destruktor za FileOperations klasu.
     *
     * Oslobađa resurse vezane za instancu FileOperations klase. U ovom slučaju, nema dodatnih resursa koji bi zahtevali ručno oslobađanje.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    ~FileOperations();
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
    
    bool loadFromFile(Sudoku& sudoku, const std::string& filename);
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
    bool saveToFile(const Sudoku& sudoku, const std::string& filename) const;
private:
};

#endif /* FileOperations_hpp */
