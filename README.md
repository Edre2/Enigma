# Enigma

Une reproduction de la machine enigma faite par `Erik` en python et en c++

## Utilisation

Pour utiliser ce projet :

```bash
git clone https://github.com/edre2/enigma
cd enigma
# En c++
g++ main.cpp -O2 -Wall -Wextra -Werror -o test
./test
# En python
python3 main.py
```

## Code

En `python` :

```python
# Il faut choisir la taille de l'alphabet avec lequel on veut travailler
# Dans cet exemple, elle est de 4 : la taille des rotors et du reflecteur
# il faut donc qu'ils contiennent les lettres A,B,C et D

# Pour créer une machine enigma :
a = Enigma(["bcda","dcba"], "badc")
# ["bcda","dcba"] : rotors, "badc" : reflecteur

# Pour coder un texte :
code = a.coder("ABDDBBABBD")
print(code)

# Pour faire revenir la machine à son état initial :
a.position_initiale()

# On peut alors décoder le texte :
print(a.coder(code))
```

En `c++` :

```cpp
// Il faut choisir la taille de l'alphabet avec lequel on veut travailler
// Dans cet exemple, elle est de 4 : la taille des rotors et du reflecteur
// il faut donc qu'ils contiennent les lettres A,B,C et D
Enigma a({"bcda" ,"dcba"}, "badc");
// {"bcda","dcba"} : rotors, "badc" : reflecteur

// On code un texte
string code = a.coder("ABDDBBABBD");
cout << code << endl;

// On fait reprendre sa position initiale à la machine
a.position_initiale();

// On peut alors décoder le texte
cout << a.coder(code) << endl;
```
