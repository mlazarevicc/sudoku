//
//  Test.cpp
//  Sudoku
//
//  Created by Milan Lazarevic on 27.12.23..
//

#include "Test.hpp"

/**
 * @brief Izvršava sve testove za Sudoku klasu.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
void Test::testSudoku() {
    
    std::cout << "  -- SUDOKU TEST --" << std::endl;
    Sudoku sudoku;
    
    testGenerateBoard(sudoku);
    testIsSolved(sudoku);
    testCheckValidity(sudoku);
    testSolveRecursive(sudoku);
}

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
void Test::testGenerateBoard(Sudoku& sudoku) {
    std::cout << "Testing generate board...\n\n";
    sudoku.generateBoard();
    sudoku.printBoard();
    
    if (sudoku.checkGeneratedBoard()) {
        std::cout << "Expected result: Generated Sudoku is valid.\n";
    } else {
        std::cout << "Unexpacted result: Generated Sudoku is not valid.\n";
    }
}

/**
 * @brief Testira proveru da li je Sudoku rešenje.
 *
 * Funkcija vrši testiranje za rešeno i nerešeno stanje Sudoku table.
 *
 * @param sudoku Referenca na Sudoku instancu.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
void Test::testIsSolved(Sudoku& sudoku) {

    int unsolvedBoard[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 0}
    };
    
    sudoku = unsolvedBoard;
    std::cout << "Unsolved Sudoku board:\n";
    sudoku.printBoard();
    if (!sudoku.isSolved()) {
        std::cout << "Expected result: Sudoku is not solved.\n";
    } else {
        std::cout << "Unexpected result: Sudoku is solved.\n";
    }

    int solvedBoard[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    sudoku = solvedBoard;
    std::cout << "\nSolved Sudoku board:\n";
    sudoku.printBoard();
    if (sudoku.isSolved()) {
        std::cout << "Expected result: Sudoku is solved.\n";
    } else {
        std::cout << "Unexpected result: Sudoku is not solved.\n";
    }
    
    std::cout << "\n";
    
}

/**
 * @brief Testira rekurzivno rešavanje Sudoku table.
 *
 * Funkcija vrši testiranje za resivu i neresivu Sudoku tablu.
 *
 * @param sudoku Referenca na Sudoku instancu.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
void Test::testSolveRecursive(Sudoku& sudoku) {
    int solvableBoard[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 0}
    };
    sudoku = solvableBoard;
    std::cout << "Solvable Sudoku board:\n";
    sudoku.printBoard();
    sudoku.solveRecursive();
    
    if (sudoku.isSolved()){
        std::cout << "Expected result: Sudoku is solved.\n";
        sudoku.printBoard();
    } else {
        std::cout << "Unexpected result: Unable to solve Sudoku.\n";
    }
    
    int unsolvableBoard[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    sudoku = unsolvableBoard;
    std::cout << "\nUnsolvable Sudoku board:\n";
    sudoku.printBoard();
    sudoku.solveRecursive();
    
    if (sudoku.isSolved()) {
        std::cout << "Expected result: Unable to solve Sudoku.\n";
    } else {
        std::cout << "Unexpected result: Sudoku is solved.\n";
    }
    
    int unsolvedBoard[9][9] = {
        {8, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 3, 6, 0, 0, 0, 0, 0},
        {0, 7, 0, 0, 9, 0, 2, 0, 0},
        {0, 5, 0, 0, 0, 7, 0, 0, 0},
        {0, 0, 0, 0, 4, 5, 7, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 3, 0},
        {0, 0, 1, 0, 2, 0, 0, 6, 8},
        {0, 0, 8, 5, 0, 0, 0, 1, 0},
        {0, 9, 0, 0, 0, 0, 4, 0, 0}
    };

    sudoku = unsolvedBoard;

    std::cout << "Unsolved Sudoku board:\n";
    sudoku.printBoard();
    sudoku.solveRecursive();
    
    if (sudoku.isSolved()){
        std::cout << "\nUnxpected result: Sudoku is solved.\n";
        sudoku.printBoard();
    } else {
        std::cout << "Expected result: Unable to solve Sudoku.\n";
    }
}

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
void Test::testCheckValidity(Sudoku& sudoku) {

    int validBoard[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    sudoku = validBoard;
    std::cout << "Valid Sudoku board:\n";
    sudoku.printBoard();
    if (sudoku.checkValidity()) {
        std::cout << "Expected result: Sudoku is valid.\n";
    } else {
        std::cout << "Unexpected result: Sudoku is not valid.\n";
    }

    int invalidBoard[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 1, 5, 2, 8, 6, 1, 7, 9}
    };
    sudoku = invalidBoard;
    std::cout << "\nInvalid Sudoku board:\n";
    sudoku.printBoard();
    if (!sudoku.checkValidity()) {
        std::cout << "Expected result: Sudoku is not valid.\n";
    } else {
        std::cout << "Unexpected result: Sudoku is valid.\n";
    }

    int invalidBoard2[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 9},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    sudoku = invalidBoard2;
    std::cout << "\nInvalid Sudoku board:\n";
    sudoku.printBoard();
    if (!sudoku.checkValidity()) {
        std::cout << "Expected result: Sudoku is not valid.\n";
    } else {
        std::cout << "Unexpected result: Sudoku is valid.\n";
    }
    
    int invalidBoard3[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 1, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    sudoku = invalidBoard3;
    std::cout << "\nInvalid Sudoku board:\n";
    sudoku.printBoard();
    if (!sudoku.checkValidity()) {
        std::cout << "Expected result: Sudoku is not valid.\n";
    } else {
        std::cout << "Unexpected result: Sudoku is valid.\n";
    }
    
    int invalidBoard4[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 0, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    sudoku = invalidBoard4;
    std::cout << "\nInvalid Sudoku board:\n";
    sudoku.printBoard();
    if (!sudoku.checkValidity()) {
        std::cout << "Expected result: Sudoku is not valid.\n";
    } else {
        std::cout << "Unexpected result: Sudoku is valid.\n";
    }

    std::cout << "\n";

}

/**
 * @brief Testira operacije nad fajlovima.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
void Test::testFileOperations() {
    std::cout << "\n\n  -- TEST File Operations --\n";
    
    Sudoku sudoku;
    FileOperations fo;
    
    sudoku.generateBoard();
    
    testLoadFromFile(sudoku, fo);
    testSaveToFile(sudoku, fo);
}

/**
 * @brief Testira učitavanje iz fajla.
 *
 * @param sudoku Referenca na Sudoku instancu.
 * @param fo Referenca na FileOperations instancu.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
void Test::testLoadFromFile(Sudoku& sudoku, FileOperations& fo) {
    std::cout << "Testing loadFromFile...\n";
    std::string validFilename = "/Users/milanlazarevic/Desktop/Milan Lazarevic - SV 4:2022/Semestar 3/OOP2/Projekat/Sudoku/Sudoku/files/initial/sudoku7.txt";
    std::string invalidFilename = "nonexistent_file2.txt";
    
    if (fo.loadFromFile(sudoku, validFilename)) {
        std::cout << "Expected result: Loading from file successful:\n";
        sudoku.printBoard();
    } else {
        std::cout << "Unexpected result: Error loading from file " << validFilename << "\n";
    }
    
    if (fo.loadFromFile(sudoku, invalidFilename)) {
        std::cout << "Unxpected result: Loading from file successful: " << invalidFilename << "\n";
    } else {
        std::cout << "Expected result: Loading from nonexistent file failed.\n";
    }
}

/**
 * @brief Testira čuvanje u fajl.
 *
 * @param sudoku Referenca na konstantnu Sudoku instancu.
 * @param fo Referenca na FileOperations instancu.
 *
 * Created by Milan Lazarevic on 27.12.2023.
 */
void Test::testSaveToFile(const Sudoku& sudoku, FileOperations& fo) {
    std::cout << "\nTesting saveToFile...\n";
    std::string saveFilename = "/Users/milanlazarevic/Desktop/Milan Lazarevic - SV 4:2022/Semestar 3/OOP2/Projekat/Sudoku/Sudoku/files/result/sudoku1.txt";

    if (fo.saveToFile(sudoku, saveFilename)) {
        std::cout << "Expected result: Saving to file successful. Check the file " << saveFilename << "\n";
    } else {
        std::cout << "Unxpected result: Error saving to file " << saveFilename << "\n";
    }

    std::cout << "\n";
}
