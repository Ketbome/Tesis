#include "ibex_SimulatedAnnealing.h"
#include "ibex_IntervalVector.h"
#include <vector>
#include <iomanip>
#include "ibex_Random.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
namespace ibex
{
    SimulatedAnnealing::SimulatedAnnealing(const IntervalVector &box, const System &sys) : box(box), sys(sys) {}

    double SimulatedAnnealing::f_obj(const IntervalVector &x, int ctr) const
    {
        return sys.f_ctrs[ctr].eval(x).mid();
    }

    Vector SimulatedAnnealing::v1(const IntervalVector &box)
    {
        IntervalVector inicial(box.size());
        double restriccion1 = RNG::rand(0, this->sys.nb_ctr - 1); // Escoger restriccion aleatoria
        int restriccion = std::round(restriccion1);

        // Solución inicial
        for (int i = 0; i < box.size(); i++)
        {
            double random_num = RNG::rand(box[i].lb(), box[i].ub());
            inicial[i] = Interval(random_num, random_num);
        }

        double mejor = f_obj(inicial, restriccion); // Evaluar la restriccion en la solucion inicial
        bool cambio = true;
        // Generar vecindario
        IntervalVector vecino = inicial;
        double temperaturaInicial = 1.0;
        double temperatura = 1.0;
        double enfriamiento = 0.8; // Tasa de enfriamiento, puedes ajustar este valor
        double k = 1.0;

        int iter = 0;
        while (cambio && iter < 250)
        {
            cambio = false;
            for (int i = 0; i < inicial.size(); i++)
            {
                // Generar una solución vecina
                double ruido = RNG::rand(0, 1);
                double magnitud = (box[i].ub() - box[i].lb()) * 0.1;
                ruido = ruido * magnitud;
                vecino[i] = Interval(inicial[i].lb() + ruido, inicial[i].ub() + ruido);

                // Calcular el cambio en la energía
                double deltaE = f_obj(vecino, restriccion) - mejor;
                // Calcular la probabilidad de aceptación
                Interval PInterval = exp(-deltaE / (k * temperatura));
                double P = PInterval.mid();

                // Generar un número aleatorio
                double R = RNG::rand(0, 1);

                if (P > R || deltaE < 0)
                {
                    mejor = f_obj(vecino, restriccion);
                    inicial = vecino;
                    cambio = true;
                    break;
                }
                else
                {
                    vecino = inicial;
                }
            }
            iter++;
            // temperatura = temperaturaInicial / std::log(iter + 2.0);
            temperatura = temperaturaInicial * std::pow(enfriamiento, iter + 2);
        }
        return inicial.mid();
    }

    Vector SimulatedAnnealing::v2(const IntervalVector &box)
    {
        IntervalVector inicial(box.size());
        double restriccion1 = RNG::rand(0, this->sys.nb_ctr - 1); // Escoger restriccion aleatoria
        int restriccion = std::round(restriccion1);

        // Solución inicial
        for (int i = 0; i < box.size(); i++)
        {
            double random_num = RNG::rand(box[i].lb(), box[i].ub());
            inicial[i] = Interval(random_num, random_num);
        }

        double mejor = f_obj(inicial, restriccion); // Evaluar la restriccion en la solucion inicial
        bool cambio = true;
        // Generar vecindario
        IntervalVector vecino = inicial;
        double temperaturaInicial = 1.0;
        double temperatura = 1.0;
        double enfriamiento = 0.5; // Tasa de enfriamiento, puedes ajustar este valor
        double k = 1.0;

        int iter = 0;
        while (cambio && iter < 30)
        {
            cambio = false;
            for (int i = 0; i < inicial.size(); i++)
            {
                // Generar una solución vecina
                double ruido = RNG::rand(0, 1);
                double magnitud = (box[i].ub() - box[i].lb()) * 0.1;
                ruido = ruido * magnitud;
                vecino[i] = Interval(inicial[i].lb() + ruido, inicial[i].ub() + ruido);

                // Calcular el cambio en la energía
                double deltaE = f_obj(vecino, restriccion) - mejor;
                // Calcular la probabilidad de aceptación
                Interval PInterval = exp(-deltaE / (k * temperatura));
                double P = PInterval.mid();

                // Generar un número aleatorio
                double R = RNG::rand(0, 1);

                if (P > R || deltaE < 0)
                {
                    mejor = f_obj(vecino, restriccion);
                    inicial = vecino;
                    cambio = true;
                    break;
                }
                else
                {
                    vecino = inicial;
                }
            }
            iter++;
            // temperatura = temperaturaInicial / std::log(iter + 2.0);
            temperatura = temperaturaInicial * std::pow(enfriamiento, iter + 1);
        }
        return inicial.mid();
    }

    Vector SimulatedAnnealing::v3(const IntervalVector &box)
    {
        IntervalVector inicial(box.size());
        double restriccion1 = RNG::rand(0, this->sys.nb_ctr - 1); // Escoger restriccion aleatoria
        int restriccion = std::round(restriccion1);

        // Solución inicial
        for (int i = 0; i < box.size(); i++)
        {
            double random_num = RNG::rand(box[i].lb(), box[i].ub());
            inicial[i] = Interval(random_num, random_num);
        }

        double mejor = f_obj(inicial, restriccion); // Evaluar la restriccion en la solucion inicial
        bool cambio = true;
        // Generar vecindario
        IntervalVector vecino = inicial;
        double temperaturaInicial = 1.0;
        double temperatura = 1.0;
        double enfriamiento = 0.7; // Tasa de enfriamiento, puedes ajustar este valor
        double k = 1.0;

        int iter = 0;
        while (cambio && iter < 100)
        {
            cambio = false;
            for (int i = 0; i < inicial.size(); i++)
            {
                // Generar una solución vecina
                double ruido = RNG::rand(0, 1);
                double magnitud = (box[i].ub() - box[i].lb()) * 0.1;
                ruido = ruido * magnitud;
                vecino[i] = Interval(inicial[i].lb() + ruido, inicial[i].ub() + ruido);

                // Calcular el cambio en la energía
                double deltaE = f_obj(vecino, restriccion) - mejor;
                // Calcular la probabilidad de aceptación
                Interval PInterval = exp(-deltaE / (k * temperatura));
                double P = PInterval.mid();

                // Generar un número aleatorio
                double R = RNG::rand(0, 1);

                if (P > R || deltaE < 0)
                {
                    mejor = f_obj(vecino, restriccion);
                    inicial = vecino;
                    cambio = true;
                    break;
                }
                else
                {
                    vecino = inicial;
                }
            }
            iter++;
            // temperatura = temperaturaInicial / std::log(iter + 2.0);
            temperatura = temperaturaInicial * std::pow(enfriamiento, iter + 1);
        }
        return inicial.mid();
    }
}