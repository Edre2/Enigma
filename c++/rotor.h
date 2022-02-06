#ifndef DEF_ROTOR
#define DEF_ROTOR

#include <iostream>
#include <algorithm> 
#include <vector>
#include <string> 

// Une classe représentant les rotors dans la machine Enigma
class Rotor
{
    public:
        Rotor(std::string rotor_position)
        {
            // On met tout en majuscules
            transform(rotor_position.begin(), rotor_position.end(), rotor_position.begin(), ::toupper);

            m_N = rotor_position.length();

            // On vérifie que toutes les lettres seront bien codées en d'autres lettres
            for(int i = 0; i < m_N; i++)
                if (rotor_position.find(char(i+65)) == std::string::npos)
                    throw std::invalid_argument( "La position du rotor devrait contenir " + std::string(1,char(i+65)));

            for(int i = 0; i < m_N; i++)
                m_rotor_position.push_back(int(rotor_position[i]) - 65);
        };

        // Montre la position du rotor (en nombres) dans le vecteur passé en argument
        void show_rotor_position(std::vector<int> & rotor_position) const
        {
            for(int i = 0; i < m_N; i++)
                rotor_position.push_back(m_rotor_position[i]);
        };

        // Fait tourner le rotor
        void tourner()
        {
            int nouveau_rotor[26];
            for (int i = 0; i < m_N; i++)
                nouveau_rotor[i] = (m_rotor_position[i]-1 + m_N) % m_N;
            for(int i = 0; i < m_N - 1; i++)
                m_rotor_position[i] = nouveau_rotor[i+1];
            m_rotor_position[m_N - 1] = nouveau_rotor[0];
        };

        // Fonction pour coder un nombre avec le rotor
        int coder(int nombre)
        {
            if (nombre >= m_N)
                throw std::invalid_argument( "Nombre trop grand pour un rotor");
            return m_rotor_position[nombre];
        };

        // Fonction pour coder un caractère avec le rotor
        char coder(char caractere)
        {
            return coder(toupper(caractere) - 65) + 65;
        };


        int decoder(int nombre)
        {
            if (nombre >= m_N)
                throw std::invalid_argument( "Nombre trop grand ");
            //int n = sizeof(m_rotor_position)/sizeof(m_rotor_position[0]);

            auto res = find (m_rotor_position.begin(), m_rotor_position.end(), nombre);
        
            return res - m_rotor_position.begin();
        };

        char decoder(char caractere)
        {
            return char(this->decoder(int(caractere)-65) + 65);
        };

        int show_N() const
        {
            return m_N;
        };

    private:
        std::vector<int> m_rotor_position;
        int m_N;
};

#endif // ROTOR_H