// Initialisation des PV si ce n'est pas encore fait
if (localStorage.getItem("pv") === null) {
    localStorage.setItem("pv", "100");
}

function getJoueurPv() {
    return parseInt(localStorage.getItem("pv"));
}

function setJoueurPv(pv) {
    localStorage.setItem("pv", pv.toString());
}

function calculDegatsJoueur(degatsBase) {
    var chance = Math.floor(Math.random() * 100);
    var degats = 0;

    if (chance < 60) {
        degats = degatsBase;
    } else if (chance < 65) {
        degats = degatsBase * 2;
    } else if (chance < 75) {
        degats = Math.floor(degatsBase / 2);
    } else {
        degats = 0;
    }

    return degats;
}

function calculDegatsMonstre(degatsBase) {
    var variation = Math.floor(Math.random() * 5) - 2;
    var degats = degatsBase + variation;
    if (degats < 0) degats = 0;
    return degats;
}

function afficherMessage(message) {
    var zone = document.getElementById("log");
    var ligne = document.createElement("p");
    ligne.textContent = message;
    zone.appendChild(ligne);
}

// Variables de combat globales
var joueurPv = getJoueurPv();
var joueurDegats = 10;
var monstreNom = "Monstre sauvage";
var monstrePv = 30;
var monstreDegats = 5;

// Lancement du combat avec interface
function initialiserCombat() {
    // Crée une zone de combat si elle n'existe pas
    var zoneCombat = document.getElementById("combat");
    if (!zoneCombat) {
        zoneCombat = document.createElement("div");
        zoneCombat.id = "combat";
        document.body.appendChild(zoneCombat);
    }

    // Crée un conteneur pour les messages
    var log = document.createElement("div");
    log.id = "log";
    log.style.backgroundColor = "#111";
    log.style.color = "#eee";
    log.style.padding = "10px";
    log.style.fontFamily = "monospace";
    log.style.marginTop = "10px";
    zoneCombat.appendChild(log);

    // Crée le bouton Attaquer
    var bouton = document.createElement("button");
    bouton.textContent = "Attaquer";
    bouton.onclick = joueurAttaque;
    bouton.id = "attaqueBtn";
    bouton.disabled = false;
    zoneCombat.appendChild(bouton);

    // Affiche les PV initiaux
    afficherMessage("⚔️ Vous êtes attaqué par " + monstreNom + " !");
    afficherMessage("Votre PV : " + joueurPv + " | " + monstreNom + " : " + monstrePv);
}

// Fonction déclenchée par le bouton "Attaquer"
function joueurAttaque() {
    if (joueurPv <= 0 || monstrePv <= 0) return;

    var degats = calculDegatsJoueur(joueurDegats);
    monstrePv -= degats;
    afficherMessage("🗡️ Vous infligez " + degats + " dégâts à " + monstreNom + " (reste " + Math.max(monstrePv, 0) + " PV)");

    if (monstrePv <= 0) {
        afficherMessage("✅ Vous avez vaincu " + monstreNom + " !");
        document.getElementById("attaqueBtn").disabled = true;
        setJoueurPv(joueurPv);
        return;
    }

    // Laisser une petite pause avant le tour du monstre
    setTimeout(monstreAttaque, 600);
}

// Fonction automatique du tour du monstre
function monstreAttaque() {
    if (monstrePv <= 0 || joueurPv <= 0) return;

    var degats = calculDegatsMonstre(monstreDegats);
    joueurPv -= degats;
    if (joueurPv < 0) joueurPv = 0;

    afficherMessage("👹 " + monstreNom + " vous inflige " + degats + " dégâts (reste " + joueurPv + " PV)");

    setJoueurPv(joueurPv);

    if (joueurPv <= 0) {
        afficherMessage("💀 Vous êtes mort...");
        document.getElementById("attaqueBtn").disabled = true;
    }
}

// Quand la page est chargée
window.addEventListener("DOMContentLoaded", function () {
    var chance = Math.random(); // 0 à 1
    var combatDoitSeLancer = (chance < 0.5); // 50% de chance

    if (combatDoitSeLancer) {
        // Optionnel : choisir un monstre au hasard
        var monstres = [
            { nom: "Gobelin", pv: 30, degats: 4 },
            { nom: "Loup affamé", pv: 25, degats: 6 },
            { nom: "Spectre", pv: 40, degats: 5 }
        ];
        var index = Math.floor(Math.random() * monstres.length);
        var monstre = monstres[index];

        monstreNom = monstre.nom;
        monstrePv = monstre.pv;
        monstreDegats = monstre.degats;

        initialiserCombat();
    }
});
