#include <iostream>

int main ()
{
    using namespace std;

    int num_competidores = 0;
    int min_pontos = 0;
    int qtd_aprovados = 0;
    int a = 0;
    float nota_1, nota_2;

    // std::cout << "\nQuantidade de competidores: \n" ;
    std::cin >> num_competidores;

    // std::cout << "\nMinimo de pontos: \n" ;
    std::cin >> min_pontos;

    if (num_competidores > 0 && num_competidores <= 1000)
    {
        if (min_pontos > 0 && min_pontos <=1000)
        {
            while ( a <= num_competidores )
            {
                // std::cout << "\n NOTA 1o. Fase: \n" ;
                std::cin >> nota_1;

                // std::cout << "\nNOTA 2o. Fase \n" ;
                std::cin >> nota_2;

                if (nota_1 > 0 && nota_1 <= 400)
                {
                    if (nota_2 > 0 && nota_2 <=400)
                    {
                        qtd_aprovados = qtd_aprovados + 1;
                    }
                }
                a++;
            }
        }
    }

    std::cout << /* "\nQuantidade de aprovados :  " << */ qtd_aprovados << "\n";
    return(0);
}
