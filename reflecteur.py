alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

class Reflecteur:
    def __init__(self, reflecteur_position):

        self.N = len(reflecteur_position)

        reflecteur_position = reflecteur_position.upper()

        # On vérifie que toutes les lettres sont bien codées :
        for i in range(self.N):
         if not alphabet[i] in reflecteur_position:
            raise Exception("La position du rotor devrait contenir la lettre " + alphabet[i])

        # On définit la position du reflecteur avec des nombres :
        self.reflecteur_position = []

        for lettre in reflecteur_position:
            self.reflecteur_position.append(alphabet.index(lettre))

        # On vérifie que le réflecteur code et décode bien de la même manière (c'est à dire si a -> b, alors b -> a):
        for i in range(self.N):
            if self.reflecteur_position[i] != self.reflecteur_position[self.reflecteur_position[self.reflecteur_position[i]]]:
                raise Exception("La lettre " + alphabet[self.reflecteur_position[i]] + " est codée en  " + alphabet[self.reflecteur_position[self.reflecteur_position[i]]] + " et cette lettre est codée elle-même en " + alphabet[self.reflecteur_position[self.reflecteur_position[self.reflecteur_position[i]]]] + " alors qu'elle devrait être codée en " + alphabet[self.reflecteur_position[i]])

        for i in range(self.N):
            if self.reflecteur_position[i] == self.reflecteur_position[self.reflecteur_position[i]]:
                raise Exception("La lettre " + alphabet[self.reflecteur_position[i]] + " est codée en  " + alphabet[self.reflecteur_position[self.reflecteur_position[i]]] + " or une lettre ne peut être codée en elle-même")

    def coder_nombre(self, nombre):
        return self.reflecteur_position[nombre]

    def coder_lettre(self, lettre):
        return self.reflecteur_position[alphabet.index(lettre.upper())]