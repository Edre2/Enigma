#ifndef DEF_REFLECTEUR
#define DEF_REFLECTEUR

#include <iostream>
#include <algorithm> 
#include <string> 
#include <vector>

// Une classe représentant le reflecteur dans une machine Enigma
class Reflecteur
{
    public:
        Reflecteur(std::string reflecteur_position)
        {
            transform(reflecteur_position.begin(), reflecteur_position.end(), reflecteur_position.begin(), ::toupper);

            // On vérifie que toutes les lettres seront bien codées en d'autres lettres
            for(int i = 0; i < int(reflecteur_position.length()); i++)
                if (reflecteur_position.find(char(i + 65)) == std::string::npos)
                    throw std::invalid_argument( "La position du reflecteur devrait contenir " + std::string(1,char(i+65)));

            m_N = reflecteur_position.length();

            for(int i = 0; i < m_N; i++)
                m_reflecteur_position.push_back(int(reflecteur_position[i]) - 65);

            // On vérifie que le réflecteur code et décode bien de la même manière (c'est à dire si a -> b, alors b -> a):
            for(int i = 0; i < m_N; i++)
                if (m_reflecteur_position[i] != m_reflecteur_position[m_reflecteur_position[m_reflecteur_position[i]]])
                    throw std::invalid_argument("La lettre " + std::string(1,char(m_reflecteur_position[i]+65)) + " est codée en  " + std::string(1,char(m_reflecteur_position[m_reflecteur_position[i]]+65)) + " et cette lettre est codée elle-même en " + std::string(1,char(m_reflecteur_position[m_reflecteur_position[m_reflecteur_position[i]]]+65)) + " alors qu'elle devrait être codée en " + std::string(1,char(m_reflecteur_position[i]+65)));
        };

        // Code un nombre (correspondant à une lettre) avec le reflecteur
        int coder(int nombre)
        {
            if (nombre >= m_N)
                throw std::invalid_argument( "Nombre trop grand pour le reflecteur (" + std::to_string(nombre) + "  > " + std::to_string(m_N-1) + ")");
            return m_reflecteur_position[nombre];
        };

        char coder(char caractere)
        {
            return coder(toupper(caractere) - 65) + 65;
        };

        // Pas besoin de fonction pour décoder car le reflecteur code et décode de la même manière

        // Montre le nombre de lettres dans le reflecteur
        int show_N() const
        {
            return m_N;
        };

    private:
        // Position du reflecteur (A devient la première lettre, B la seconde ...)
        std::vector<int> m_reflecteur_position;
        // Nombre de lettres dans le reflecteur
        int m_N;
};

#endif // REFLECTEUR_H