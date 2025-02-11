#include <iostream>
#include "Date.h"
#include <stdexcept>

int main()
{
    setlocale(LC_ALL, "ru");
    try
    {
        Date A;
        A.Fill();


        cout << endl;

        A.Display();

        cout << endl;

        Date B;

        int a = 0;
        cin >> a;
        B = A + a;
        B.Display();

        int seCUNTs = 0;
        seCUNTs = B - A;
        cout << seCUNTs<<endl;

        Date C = A;
        if (C > B)
        {
            cout << "Даты равны" << endl;
        }
    }
    catch (exception& exc)
    {
        cerr << exc.what() << endl;
        exit(0);
    }

}

