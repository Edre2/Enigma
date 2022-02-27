function update_nb_rotors() {
    document.getElementById("rotors").innerHTML = "";

    let nb_de_rotors = 5;
    if (! isNaN(Number(document.getElementById("nb_de_rotors").value)) && document.getElementById("nb_de_rotors").value != "")
    {
        nb_de_rotors = Number(document.getElementById("nb_de_rotors").value);
    }

    for (let j = 0; j < nb_de_rotors; j++)
    {
        document.getElementById("rotors").innerHTML += '<div class="ligne espace-haut-bas"><label for="rotor-"'+j+'>Rotor '+ (j +1)+' :</label><input id="rotor-' + j + '" class="espace-caracters fill"></input></div>';
    }
}

function coder() {
    let nb_de_rotors = 5;
    if (! isNaN(Number(document.getElementById("nb_de_rotors").value)) && document.getElementById("nb_de_rotors").value != "")
    {
        nb_de_rotors = Number(document.getElementById("nb_de_rotors").value);
    }

    let rotors = new Array();

    for(let i = 0; i < nb_de_rotors; i++) {
        rotors.push(document.getElementById("rotor-"+i).value);
    }

    let reflecteur = document.getElementById("reflecteur").value;

    let a = new Enigma(rotors, reflecteur);

    let text = document.getElementById("texte_a_coder").value;

    document.getElementById("texte_code").innerHTML = "<p>" + a.coder(text) + "</p>"
}