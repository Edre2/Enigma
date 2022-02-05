from enigma import *

# On crée une machine enigma           
a = Enigma(["bcda","dcba","dcba","dcba"], "badc")

# On code un texte
code = a.coder("AB BBA")
print(code)

# On fait reprendre sa position initiale à la machine
a.position_initiale()

# On peut alors décoder le texte
print(a.coder(code))