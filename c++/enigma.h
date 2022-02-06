#ifndef DEF_ENIGMA
#define DEF_ENIGMA

#include "rotor.h"
#include "reflecteur.h"
#include <vector>

// Une classe reproduisant la machine Enigma
class Enigma
{
    public:
        Enigma(std::vector<std::string>  rotors, std::string reflecteur)
        {
            // Nombre de caractères par rotor/reflecteur
            m_N = rotors[0].length();
            // Nombre de rotors
            m_N_rotors = rotors.size();

            // On ajoute les rotors à notre machine et on vérifie qu'ils ont tous la même taille
            for (int i = 0; i < m_N_rotors; i++)
                if (int(rotors[i].length()) == m_N)
                    m_rotors.push_back(Rotor(rotors[i]));
                else
                    throw std::invalid_argument( "Les rotors doivent avoir le même nombre de caractères");

            // Position des rotors (0 = il n'a pas bougé, 1 = il a tourné 1 fois ..) (au début : tout est à 0)
            m_position_rotors = std::vector<int>(m_N_rotors, 0);

            // On ajoute le reflecteur après avoir vérifier qu'il avait la bonne taille
            if (int(reflecteur.length()) == m_N)
                m_reflecteur = new Reflecteur(reflecteur);
            else
                throw std::invalid_argument( "Les rotors et le reflecteur doivent avoir le même nombre de caractères");
        };

        /*Enigma(std::vector<Rotor> rotors, Reflecteur reflecteur)
        {
            m_N = rotors[0].show_N();
            m_N_rotors = rotors.size();

            for (int i = 0; i < m_N_rotors; i++)
                if (int(rotors[i].show_N()) == m_N)
                    m_rotors.push_back(rotors[i]);
                else
                    throw std::invalid_argument( "Les rotors doivent avoir le même nombre de caractères");

            m_position_rotors = std::vector<int>(m_N_rotors, 0);

            if (int(reflecteur.show_N()) == m_N)
                m_reflecteur = new Reflecteur(reflecteur);
            else
                throw std::invalid_argument( "Les rotors et le reflecteur doivent avoir le même nombre de caractères");
        };*/

        // Destructeur de la class Enigma : on supprime m_reflecteur car il a été alloué dynamiquement
        ~Enigma()
        {
            delete m_reflecteur;
        };

        // Fait tourner les rotors de la machine
        void tourner()
        {
            // Le premier rotor tourne tout le temps
            m_rotors[0].tourner();
            m_position_rotors[0] += 1;

            // Si le rotor a fait un nombre de tours divisible par le nombre de lettres par rotor, on fait tourner celui d'après
            int i = 0;
            while ( (m_position_rotors[i] % m_N == 0) && (i != m_N_rotors))
            {
                m_position_rotors[i] = 0;
                m_rotors[i+1].tourner();
                m_position_rotors[i+1]++;
                i++;
            }
        };

        // Remet la machine enigma dans sa position initiale
        void position_initiale()
        {
            // Pour chaque rotor :
            for(int i = 0; i < m_N_rotors; i++)
            {
                // On le fait tourner assez de fois pour qu'il retrouve sa position initiale :
                for(int j=0; j < ((m_N - m_position_rotors[i]) % m_N); j++)
                    m_rotors[i].tourner();
                m_position_rotors[i] = 0;
            }
        };

        std::string coder(std::string text)
        {
            std::string text_code = "";

            for(int i = 0; i < int(text.length()); i++)
            {
                // Si la le caractère est une lettre de l'alphabet, on le code
                if(toupper(text[i]) >= 65 && toupper(text[i]) <= 91)
                {
                    int lettre_codee = toupper(text[i]) - 65;

                    // On code la lettre à travers tous les rotors
                    for(int j = 0; j < m_N_rotors; j++)
                        lettre_codee = m_rotors[j].coder(lettre_codee);

                    // Puis le reflecteur
                    lettre_codee = m_reflecteur->coder(lettre_codee);

                    // Et enfin à travers les rotors mais dans l'autre sens
                    for(int j = m_N_rotors - 1; j >= 0; j--)
                        lettre_codee = m_rotors[j].decoder(lettre_codee);

                    // On fait tourner les rotors
                    tourner();

                    text_code += lettre_codee + 65;
                }
                else 
                    text_code += text[i];
            }

            return text_code;
        };

    private:
        // Vector stoquant les rotors
        std::vector<Rotor> m_rotors;
        // Le reflecteur
        Reflecteur * m_reflecteur;
        // Nombre de rotors
        int m_N_rotors;
        // Nombre de lettres par rotor/reflecteur
        int m_N;
        // Position des rotors
        std::vector<int> m_position_rotors;
};

#endif // ENIGMA_H