#include <iostream>

int main ()
{
    using namespace std;

    int num_competidores, min_pontos;
    float nota_1, nota_2;

    cout << "\nQuantidade de competidores: \n" ;
    cin >> num_competidores;

    cout << "\nMinimo de pontos: \n" ;
    cin >> min_pontos;

    if (num_competidores > 0 && num_competidores <= 1000)
    {
        if (min_pontos > 0 && min_pontos <=1000)
        {
            cout << num_competidores << " " << min_pontos << "\n";
        }
    }

    cout << "\n NOTA 1o. Fase: \n" ;
    cin >> nota_1;

    cout << "\nNOTA 2o. Fase \n" ;
    cin >> nota_2;


    if (nota_1 > 0 && nota_1 <= 400)
    {
        if (nota_2 > 0 && nota_2 <=400)
        {
            cout << nota_1 << " " << nota_2 << "\n";
        }
    }



return(0);
}
