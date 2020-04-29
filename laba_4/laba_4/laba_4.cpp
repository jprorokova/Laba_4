#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <iostream>
#include <cstdint>
#include"Header.h"
using namespace std;


int  main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    if (argc != 4) {
        cout << "Ошибка введенных данных!!" << endl;
        return 0;
    }
    double coef;//коэффициент для интерполяционного поиска
    coef= atof(argv[3]);
    if (coef == 0) {
        cout << "Ошибка коефициента" << endl;
        return 0;
    }
    DataWav AudioFile(argv[1]);


    /*WavFile wavFile(argv[1]);
    wavFile.interpolation(resize);
    wavFile.writeWav(argv[2]);
    return 0;*/
}
