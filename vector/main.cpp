#include "trianglematrix.h"
#include <iostream>
#include <string>
#include <vector>

std::pair<int, int> input_coord(bool flag) {
    while (true) {
        std::string str1, str2;
        std::pair<int, int> res;
        if (flag) {
            std::cout << "Input dimension matrix A(except N M ): ";
        }
        else {
            std::cout << "Input dimension matrix B(except N M ): ";
        }
        std::cin >> str1 >> str2;
        try {
            res.first = std::stoi(str1);
            res.second = std::stoi(str2);
        }
        catch (...) {
            std::cout << "Error input\n";
            std::cin.clear();
            continue;
        }
        return res;
    }
}

void inputMatrix(Matrix<int>& matrix,bool flag) {
    while (true) {
        if (flag) {
            std::cout << "Input matrix 1:\n";
        }
        else {
            std::cout << "Input matrix 2:\n";
        }
        try {
            std::cin >> matrix;
        }
        catch (...) {
            std::cout << "Error,try again\n";
            std::cin.clear();
            continue;
        }
        return;
    }
}

int main() {
    std::pair<int, int> pair1 = input_coord(true);
    std::pair<int, int> pair2 = input_coord(false);
    size_t N_matr1 = static_cast<size_t>(pair1.first);
    size_t M_matr1 = static_cast<size_t>(pair1.second);
    size_t N_matr2 = static_cast<size_t>(pair2.first);
    size_t M_matr2 = static_cast<size_t>(pair2.second);
    Matrix<int> matr1(N_matr1, M_matr1);
    Matrix<int> matr2(N_matr2, M_matr2);
    inputMatrix(matr1, true);
    inputMatrix(matr2, false);
    TriangleMatrix<int> tri_matr1;
    TriangleMatrix<int> tri_matr2;
    bool is_A_triangle = false;
    bool is_B_triangle = false;
    while (true) {
        system("cls");
        std::cout << "\n================ MENU ================\n";
        std::cout << "1. Print Matrix A or B\n";
        std::cout << "2. Add matrix (A + B)\n";
        std::cout << "3. Subtract matrix (A - B)\n";
        std::cout << "4. Multiply matrices (A * B)\n";
        std::cout << "5. Calculate Determinant (Det A or Det B)\n";
        std::cout << "6. Convert to Triangle form\n";
        std::cout << "7. Exit\n";
        std::cout << "Choose option: ";
        std::string choice_str;
        std::cin >> choice_str;
        int choice = 0;
        try {
            choice = std::stoi(choice_str);
        }
        catch (...) {
            std::cout << "Invalid menu item! Try again.\n";
            continue;
        }
        if (choice == 7) {std::cout << "Exiting calculator. Goodbye!\n";break;}
        try {
            system("cls");
            switch (choice) {
            case 1: { 
                std::cout << "Print (1 - Matrix A, 2 - Matrix B): ";
                int m_choice; std::cin >> m_choice;
                if (m_choice == 1) {
                    if (is_A_triangle) std::cout << "\nMatrix A (Triangle Form):\n" << tri_matr1;
                    else {
                        std::cout << "\nMatrix A:\n" << matr1;
                    }
                }
                else if (m_choice == 2) {
                    if (is_B_triangle) std::cout << "\nMatrix A (Triangle Form):\n" << tri_matr2;
                    else {
                        std::cout << "\nMatrix B:\n" << matr2;
                    }
                }
                else std::cout << "Invalid choice!\n";
                break;
            }
            case 2: {
                std::cout << "\nResult A + B:\n";
                if (is_A_triangle) {
                    TriangleMatrix<int> res_add_tri = tri_matr1 + tri_matr2;
                    std::cout << res_add_tri;
                }
                else {
                    Matrix<int> res_add = matr1 + matr2;
                    std::cout << res_add;
                }
                break;
            }
            case 3: {
                std::cout << "\nResult A - B:\n";
                if (is_A_triangle) {
                    TriangleMatrix<int> res_sub_tri = tri_matr1 - tri_matr2;
                    std::cout << res_sub_tri;
                }
                else {
                    Matrix<int> res_sub = matr1 - matr2;
                    std::cout << res_sub;
                }
                break;
            }
            case 4: { 
                std::cout << "\nResult A * B\n";
                if (is_A_triangle) {
                    TriangleMatrix<int> res_mul_tri = tri_matr1 * tri_matr2;
                    std::cout << res_mul_tri;
                }
                else {
                    Matrix<int> res_mul = matr1 * matr2;
                    std::cout << res_mul;
                }
                break;
            }
            case 5: {
                std::cout << "Calculate Det for (1 - Matrix A, 2 - Matrix B): ";
                int m_choice; std::cin >> m_choice;
                if (m_choice == 1) {
                    if (is_A_triangle) {
                        std::cout << "Determinant of A: " << tri_matr1.calcDeterminant() << "\n";
                    }
                    else {
                        TriangleMatrix<int> tri1(matr1);
                        std::cout << "Determinant of A: " << tri1.calcDeterminant() << "\n";
                    }
                }
                else if (m_choice == 2) {
                    if (is_B_triangle) {
                        std::cout << "Determinant of B: " << tri_matr2.calcDeterminant() << "\n";
                    }
                    else {
                        TriangleMatrix<int> tri2(matr2);
                        std::cout << "Determinant of B: " << tri2.calcDeterminant() << "\n";
                    }
                }
                else {
                    std::cout << "Invalid choice!\n";
                }
                break;
            }
            case 6: { 
                if (is_A_triangle) {
                    std::cout << "\nMatrix already triangle\n";
                    break;
                }
                std::cout << "Convert to Triangle form\n ";
                tri_matr1 = TriangleMatrix<int>(matr1);
                tri_matr2 = TriangleMatrix<int>(matr2);
                is_A_triangle = true;
                is_B_triangle = true;
                break;
            }
            default:
                std::cout << "Unknown option. Try again.\n";
                break;
            }
        }
        catch (const std::exception& e) {
            std::cout << "\nMath error: " << e.what() << "\n";
        }
        system("pause");
    }
    return 0;
}
