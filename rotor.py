alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

class Rotor:
   def __init__(self, rotor_position):

      rotor_position = rotor_position.upper()

      for i in range(len(rotor_position)):
         if not alphabet[i] in rotor_position:
            raise Exception("La position du rotor devrait contenir la lettre " + alphabet[i])

      self.rotor_position = []

      for lettre in rotor_position:
         self.rotor_position.append(alphabet.index(lettre))

      self.N = len(rotor_position)

   def show_rotor_position(self):
      return self.rotor_position

   def tourner(self):
      nouveau_rotor = []
      for i in self.rotor_position:
         nouveau_rotor.append( (i-1) % self.N)
      self.rotor_position = nouveau_rotor[1:] + nouveau_rotor[:1]

   def coder_nombre(self, nombre):
      return self.rotor_position[nombre]

   def coder_lettre(self, lettre):
      return self.rotor_position[alphabet.index(lettre.upper())]

   def decoder_nombre(self, nombre):
      return self.rotor_position.index(nombre)

   def decoder_lettre(self, lettre):
      return self.rotor_position.index(alphabet.index(lettre.upper()))