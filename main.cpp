#include <iostream>
#include "enigma.h"
using namespace std;

int main()
{
    // On crée une machine enigma
    Enigma a({"bcda" ,"dcba"}, "badc");

    // On code un texte
    string code = a.coder("ABDDBBABBD");
    cout << code << endl;

    // On fait reprendre sa position initiale à la machine
    a.position_initiale();

    // On peut alors décoder le texte
    cout << a.coder(code) << endl;

    return EXIT_SUCCESS;
}