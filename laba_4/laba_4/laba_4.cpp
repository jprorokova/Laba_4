#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <iostream>
#include <cstdint>
#include"Header.h"
using namespace std;


class DataWav;

int  main(int argc, char* argv[])
{
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

    DataWav AudioFile(argv[1]);//Ctor
    AudioFile.interpol(coef);
    AudioFile.writeWav(argv[2]);
    cout << "Scaling sound file... Done." << endl;
    cout << "Written result to " << argv[2]<<endl;

}
