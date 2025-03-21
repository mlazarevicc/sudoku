//
//  main.cpp
//  Sudoku
//
//  Created by Milan Lazarevic on 16.12.23..
//

#include <iostream>
#include <cstdlib>
#include <fstream>

#include "Sudoku.hpp"
#include "FileOperations.hpp"
#include "Test.hpp"

std::string filename1;
std::string filename2;

void sudokuGame();
void sudokuTests();

int main(int argc, char** argv) {
    filename1 = argv[1];
    filename2 = argv[2];
    sudokuGame();
    sudokuTests();
    return 0;
}



void sudokuGame() {
    std::string path = "/Users/milanlazarevic/Desktop/Milan Lazarevic - SV 4:2022/Semestar 3/OOP2/Projekat/Sudoku/Sudoku/files/arguments/";
    Sudoku sudoku;
    FileOperations fo;

    char choice;
    do {
        std::cout << "\n   -- Meni --\n";
        std::cout << "1. Ucitaj Sudoku zagonetku iz datoteke\n";
        std::cout << "2. Generisi novu Sudoku zagonetku\n";
        std::cout << "Izaberite opciju: ";
        std::cin >> choice;

        bool success = true;
        switch (choice) {
            case '1': {
                success = fo.loadFromFile(sudoku, path + filename1);
                if (!success)
                    break;
                
                if (sudoku.isSolved()) {
                    std::cout << "Uneli ste resenu Sudoku zagonetku, a ne postavku." << std::endl;
                }
                sudoku.printBoard();
                
                break;
            }
            case '2': {
                sudoku.generateBoard();
                sudoku.printBoard();
                success = fo.saveToFile(sudoku, path + filename1);
                break;
            }
            default:
                std::cout << "Nepoznata opcija. Unesite ponovo.\n";
                continue;
        }

        if (!success) return;

        do {
            std::cout << "\n -- Resi zagonetku --\n";
            std::cout << "1. Ucitaj iz datoteke\n";
            std::cout << "2. Resenje (program resava)\n";
            std::cout << "3. Napusti program\n";
            std::cout << "Izaberite opciju: ";
            std::cin >> choice;
            
            switch(choice) {
                case '1': {
                    std::string filename;
                    std::cout << "Unesite naziv datoteke za ucitavanje resene Sudoku zagonetke: ";
                    std::cin >> filename;
                    success = fo.loadFromFile(sudoku, path + filename2);
                    if (!success)
                        break;
                    
                    bool valid = sudoku.checkValidity();
                    sudoku.printStatistics();
                    
                    if (valid) {
                        std::cout << "USPESNO STE RESILI SUDOKU ZAGONETKU!" << std::endl;
                        break;
                    } else {
                        std::cout << "Zagonetka nije uspešno rešena." << std::endl;
                        std::cout << "Zelite li pokusati ponovo? (y/n): ";
                        std::cin >> choice;
                    }
                    break;
                }
                case '2':
                    sudoku.solveRecursive();
                    std::cout << "Rešena sudoku zagonetka: " << std::endl;
                    sudoku.printBoard();
                    sudoku.checkValidity();
                    sudoku.printStatistics();
                    fo.saveToFile(sudoku, path + filename2);
                    break;
                case '3':
                    return;
                default:
                    std::cout << "Nepoznata opcija. Unesite ponovo.\n";
            }
            
        } while (std::tolower(choice) == 'y');
        
        std::cout << "Zelite li jos jednu partiju (y/n): ";
        std::cin >> choice;

    } while (std::tolower(choice) == 'y');
}

void sudokuTests() {
    Test test;
    test.testSudoku();
    test.testFileOperations();
}
