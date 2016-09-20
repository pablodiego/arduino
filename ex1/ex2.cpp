#include <iostream>

int main ()
{

    using namespace std;

    char letra;
    int digito;

    std::cin >> letra;

    switch (letra)
    {
    case 'a':
    case 'b':
    case 'c':

        digito = 2;

        std::cout << "\n" << digito ;

        break;

    case 'd':
    case 'e':
    case 'f':

        digito = 3;

        std::cout << "\n" << digito;

        break;

    case 'g':
    case 'h':
    case 'i':

        digito = 4;

         std::cout << "\n" << digito;

        break;

    case 'j':
    case 'k':
    case 'l':

        digito  = 5 ;

         std::cout << "\n" << digito;

        break;

    case 'm':
    case 'n':
    case 'o':

        digito = 6;

         std::cout << "\n" << digito;

        break;

    case 'p':
    case 'q':
    case 'r':
    case 's':

        digito = 7;

         std::cout << "\n" << digito;

        break;

    case 't':
    case 'u':
    case 'v':

        digito = 8;

         std::cout << "\n" << digito;

        break;

    case 'w':
    case 'x':
    case 'y':
    case 'z':

        digito = 9;

         std::cout << "\n" << digito;

        break;

    case '*':

        digito = 01;

         std::cout << "\n" << digito;

         break;

    case '#':
        digito = 01;


        std:: cout << "\n" << digito;

        break;

    }

    return (0);

}


