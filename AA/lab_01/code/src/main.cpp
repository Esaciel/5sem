#include "solution.hpp"
#include "io.hpp"
#include "extras.hpp"

#include <iostream>

#define ITERATION_COUNT 50

int handcontrol()
{
    Matrix first;
    Matrix second;
    try
    {
        cout << "\nПервая матрица\n";
        first = read_matrix_from_сin();
        cout << "\nВторая матрица\n";
        second = read_matrix_from_сin();
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    matrix_time base_result, Vin_result, Vin_upd_result;
    clock_t time_basic = 0, time_Vinograd = 0, time_Vinograd_upd = 0;
    try
    {
        for (size_t i = 0; i < ITERATION_COUNT; ++i)
        {
            base_result = multiply_standart(first, second);
            Vin_result = multiply_Vinograd(first, second);
            Vin_upd_result = multiply_Vinograd_upd(first, second);

            time_basic += base_result.second;
            time_Vinograd += Vin_result.second;
            time_Vinograd_upd += Vin_upd_result.second;
        }
        cout << endl;
    }
    catch(const exception& e)
    {
        cerr << e.what() << "\n";
        return 2;
    }
    // cout << "\nПервая матрица:\n";
    // print_matrix(first);
    // cout << "Вторая матрица\n";
    // print_matrix(second);

    // cout << "Обычное умножение\n";
    // print_matrix(base_result.first);
    cout << "Время обычного умножения: " << ((float)time_basic / (ITERATION_COUNT)) << " тиков\n\n";

    cout << "Умножение методом винограда\n";
    print_matrix(Vin_result.first);
    cout << "Время умножения методом винограда умножения: " << ((float)time_Vinograd / (ITERATION_COUNT)) << " тиков\n\n";

    // cout << "Умножение методом винограда c оптимизациями по варианту\n";
    // print_matrix(Vin_upd_result.first);
    cout << "Время умножения оптимизированным по варианту методом винограда: " << ((float)time_Vinograd_upd / (ITERATION_COUNT)) << " тиков\n\n";

    cout << ((cmpMatrixes(base_result.first, Vin_result.first) && cmpMatrixes(base_result.first, Vin_upd_result.first)) ? "Результаты совпадают" : "Результаты не совпали!") << "\n";
    return 0;
    //  (ITERATION_COUNT *  CLOCKS_PER_SEC) при выводе для расчета в секундах
}

int main()
{
    short mode;
    // cout << "Режим работы?\n'1'-ввод вручную\n'2'-ввод из файла\n'3'-автогенерация\n";
    cin >> mode;
    switch (mode)
    {
        case 1:
        {
            return handcontrol();
        }
        case 2:
        {
            cout << "not yet" << endl;
            return -1;
        }
        case 3:
        {
            cout << "not yet" << endl;
            return -1;
        }
        default:
        {
            cout << "Неправильный режим" << endl;
            return 255;
        }
    }
    return 127;
}
