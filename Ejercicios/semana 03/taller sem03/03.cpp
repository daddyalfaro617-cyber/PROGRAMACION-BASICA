#include <iostream>
using namespace std;

int main()
{
    const int estudiantes = 5;
    const int dias = 5;
    int asistencia[estudiantes][dias];

    for (int i = 0; i < estudiantes; i++)
    {
        cout << "Ingrese asistencia del estudiante #" << i + 1 << " (5 valores 0/1): ";
        for (int j = 0; j < dias; j++)
        {
            cin >> asistencia[i][j];
        }
    }

    int totalAula = 0;
    for (int i = 0; i < estudiantes; i++)
    {
        int totalEstudiante = 0;
        bool perfecto = true;

        for (int j = 0; j < dias; j++)
        {
            totalEstudiante += asistencia[i][j];
            totalAula += asistencia[i][j];
            if (asistencia[i][j] == 0)
            {
                perfecto = false;
            }
        }

        cout << "\nEstudiante #" << i + 1 << " asistencias: " << totalEstudiante;
        if (perfecto)
        {
            cout << " (Asistencia perfecta)";
        }
    }

    cout << "\n\nTotal de asistencias en el aula: " << totalAula << endl;

    return 0;
}
