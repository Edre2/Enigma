from rotor import *
from reflecteur import *

class Enigma:
    def __init__(self, rotors, reflecteur):
        self.__rotors = []

        self.__N = len(rotors[0])

        # On ajoute les rotors à notre machine et on vérifie qu'ils ont tous la même taille
        for rotor in rotors:
            if len(rotor) != self.__N:
                raise Exception("Les rotors doivent être de même taille")
            self.__rotors.append(Rotor(rotor))

        # Nombre de rotors
        self.__N_rotors = len(self.__rotors)

        # Position des rotors (0 = il n'a pas bougé, 1 = il a tourné 1 fois ..)
        self.__rotor_rotation = [0] * self.__N_rotors

        # On ajoute le reflecteur après avoir vérifier qu'il avait la bonne taille
        if len(reflecteur) != self.__N:
            raise Exception("Le reflecteur doit être de la même taille que les rotors")

        self.__reflecteur = Reflecteur(reflecteur)

    # Fonction pour coder un texte avec notre machine enigma
    def coder(self, text):
        text_code = ""

        for lettre in text:
            # Si la le caractère est une lettre de l'alphabet, on le code :
            if lettre.upper() in alphabet:
                lettre_codee = alphabet.index(lettre.upper())

                # On code la lettre à travers tous les rotors
                for rotor in self.__rotors:
                    lettre_codee = rotor.coder_nombre(lettre_codee)

                # Puis le reflecteur
                lettre_codee = self.__reflecteur.coder_nombre(lettre_codee)

                # Et enfin à travers les rotors mais dans l'autre sens
                for rotor in reversed(self.__rotors):
                    lettre_codee = rotor.decoder_nombre(lettre_codee)

                text_code += alphabet[lettre_codee]

                # On fait tourner les rotors
                self.__tourner()
            # Sinon, on ne le code pas :
            else:
                text_code += lettre

        return text_code

    # Fait tourner les rotors
    def __tourner(self):
        # Le premier rotor tourne tout le temps        
        self.__rotors[0].tourner()
        self.__rotor_rotation[0] += 1

        # Si le rotor a fait un nombre de tours divisible par le nombre de lettres par rotor, on fait tourner celui d'après
        i = 0
        while (self.__rotor_rotation[i] % self.__N == 0) and (i < self.__N_rotors - 1):
            self.__rotor_rotation[i] = 0
            self.__rotors[i+1].tourner()
            self.__rotor_rotation[i+1] += 1
            i += 1

    # Remet la machine enigma dans sa position initiale
    def position_initiale(self):
        # Pour chaque rotor :
        for i in range(self.__N_rotors):
            # On le fait tourner assez de fois pour qu'il retrouve sa position initiale :
            for j in range((self.__N - self.__rotor_rotation[i]) % self.__N):
                self.__rotors[i].tourner()
            self.__rotor_rotation[i] = 0