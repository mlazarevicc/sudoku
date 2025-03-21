//
//  Test.hpp
//  Sudoku
//
//  Created by Milan Lazarevic on 27.12.23..
//

#ifndef Test_hpp
#define Test_hpp

#include "Sudoku.hpp"
#include "FileOperations.hpp"

class Test {
public:
    /**
     * @brief Izvršava sve testove za Sudoku klasu.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    static void testSudoku();
    /**
     * @brief Testira operacije nad fajlovima.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    static void testFileOperations();
private:
    /**
     * @brief Testira proveru da li je Sudoku rešenje.
     *
     * Funkcija vrši testiranje za rešeno i nerešeno stanje Sudoku table.
     *
     * @param sudoku Referenca na Sudoku instancu.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    static void testIsSolved(Sudoku& sudoku);
    /**
     * @brief Testira generisanje Sudoku table.
     *
     * Funkcija generiše Sudoku tablu, prikazuje je i proverava da li je generisana tabla validna.
     * Ukoliko je validna, ispisuje poruku očekivanog rezultata, u suprotnom ispisuje poruku o neočekivanom rezultatu.
     *
     * @param sudoku Referenca na Sudoku instancu.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    static void testGenerateBoard(Sudoku& sudoku);
    /**
     * @brief Testira proveru validnosti Sudoku table.
     *
     * Funkcija vrši testiranje za validnu i nevalidnu Sudoku tablu. Redosled provere:
     * 1. Validna tabla
     * 2. Nevalidna tabla - dve jedinice u poslednjem redu
     * 3. Nevalidna tabla - dve devetke u poslednjoj koloni
     * 4. Nevalidna tabla - dve jedinice u poslednjoj podmatrici
     * 5. Nevalidna tabla - prazno polje u matrici
     *
     * @param sudoku Referenca na Sudoku instancu.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    static void testCheckValidity(Sudoku& sudoku);
    /**
     * @brief Testira rekurzivno rešavanje Sudoku table.
     *
     * Funkcija vrši testiranje za resivu i neresivu Sudoku tablu.
     *
     * @param sudoku Referenca na Sudoku instancu.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    static void testSolveRecursive(Sudoku& sudoku);

    /**
     * @brief Testira učitavanje iz fajla.
     *
     * @param sudoku Referenca na Sudoku instancu.
     * @param fo Referenca na FileOperations instancu.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    static void testLoadFromFile(Sudoku& sudoku, FileOperations& fo);
    /**
     * @brief Testira čuvanje u fajl.
     *
     * @param sudoku Referenca na konstantnu Sudoku instancu.
     * @param fo Referenca na FileOperations instancu.
     *
     * Created by Milan Lazarevic on 27.12.2023.
     */
    static void testSaveToFile(const Sudoku& sudoku, FileOperations& fo);
    
};

#endif /* Test_hpp */
