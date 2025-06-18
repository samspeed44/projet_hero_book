// === Gestion des PV ===
function getJoueurPv() {
    return parseInt(localStorage.getItem("pv"));
}

function setJoueurPv(pv) {
    localStorage.setItem("pv", pv.toString());
}

function initialiserPv() {
    if (localStorage.getItem("pv") === null) {
        localStorage.setItem("pv", "100");
    }
}

function reinitialiserPv() {
    if (window.location.href.includes("01.html")) {
        localStorage.setItem("pv", "100");
    }
}

// === Dégâts ===
function calculDegatsJoueur(base) {
    let chance = Math.floor(Math.random() * 100);
    if (chance < 60) return base;
    if (chance < 65) return base * 2;
    if (chance < 75) return Math.floor(base / 2);
    return 0;
}

function calculDegatsMonstre(base) {
    let variation = Math.floor(Math.random() * 5) - 2;
    return Math.max(0, base + variation);
}

// === Affichage messages ===
function afficherMessage(msg) {
    let zone = document.getElementById("zoneMessages");
    let ligne = document.createElement("p");
    ligne.textContent = msg;
    zone.appendChild(ligne);
}

// === Désactiver/Réactiver les liens vers les chapitres ===
function bloquerLiens() {
    let liens = document.querySelectorAll("a[href$='.html']");
    liens.forEach(function (lien) {
        lien.dataset.href = lien.href; // sauvegarde
        lien.href = "#";
        lien.style.pointerEvents = "none";
        lien.style.opacity = "0.5";
    });
}

function debloquerLiens() {
    let liens = document.querySelectorAll("a[data-href]");
    liens.forEach(function (lien) {
        lien.href = lien.dataset.href;
        lien.style.pointerEvents = "auto";
        lien.style.opacity = "1";
    });
}

// === Variables de combat ===
let joueurPv = 0;
let joueurDegats = 10;
let monstreNom = "Monstre sauvage";
let monstrePv = 30;
let monstreDegats = 5;

// === Combat ===
function demarrerCombat() {
    joueurPv = getJoueurPv();

    let zoneCombatHtml = document.getElementById("combat");
    if (!zoneCombatHtml) {
        zoneCombatHtml = document.createElement("div");
        zoneCombatHtml.id = "combat";
        document.body.appendChild(zoneCombatHtml);
    }

    // Zone des messages
    let zoneMessages = document.createElement("div");
    zoneMessages.id = "zoneMessages";
    zoneMessages.style.backgroundColor = "#111";
    zoneMessages.style.color = "#eee";
    zoneMessages.style.padding = "10px";
    zoneMessages.style.fontFamily = "monospace";
    zoneMessages.style.marginTop = "10px";
    zoneCombatHtml.appendChild(zoneMessages);

    // Bouton "Attaquer"
    let boutonAttaque = document.createElement("button");
    boutonAttaque.textContent = "Attaquer";
    boutonAttaque.id = "boutonAttaque";
    boutonAttaque.onclick = joueurAttaque;
    boutonAttaque.disabled = false;
    zoneCombatHtml.appendChild(boutonAttaque);

    afficherMessage(" Vous êtes attaqué par " + monstreNom + " !");
    afficherMessage("Votre PV : " + joueurPv + " | " + monstreNom + " : " + monstrePv);
    afficherMessage("=================================");

    // On bloque les liens pendant le combat
    bloquerLiens();
}

function joueurAttaque() {
    if (joueurPv <= 0 || monstrePv <= 0) return;

    let degats = calculDegatsJoueur(joueurDegats);
    monstrePv -= degats;
    afficherMessage("⚔️ Vous infligez " + degats + " dégâts à " + monstreNom + " (reste " + Math.max(monstrePv, 0) + " PV)");

    if (monstrePv <= 0) {
        afficherMessage("Vous avez vaincu " + monstreNom + " !");
        document.getElementById("boutonAttaque").disabled = true;
        setJoueurPv(joueurPv);
        debloquerLiens();
        return;
    }

    setTimeout(monstreRiposte, 600);
}

function monstreRiposte() {
    if (monstrePv <= 0 || joueurPv <= 0) return;

    let degats = calculDegatsMonstre(monstreDegats);
    joueurPv -= degats;
    if (joueurPv < 0) joueurPv = 0;

    afficherMessage("👹 " + monstreNom + " vous inflige " + degats + " dégâts (reste " + joueurPv + " PV)");

    setJoueurPv(joueurPv);

    if (joueurPv <= 0) {
        afficherMessage("💀 Vous êtes mort...");
        document.getElementById("boutonAttaque").disabled = true;
        setTimeout(() => {
            window.location.href = "01.html";
        }, 1500);
    }
}

// === Initialisation ===
window.addEventListener("DOMContentLoaded", function () {
    reinitialiserPv();
    initialiserPv();

    // Pas de combat au chapitre 1
    if (window.location.href.includes("01.html")) {
        return;
    }

    // 50 % de chance d’avoir un combat
    let alea = Math.random();
    let declencherCombat = alea < 0.5;

    if (declencherCombat) {
        let monstres = [
            { nom: "Gobelin", pv: 30, degats: 4 },
            { nom: "Loup affamé", pv: 25, degats: 6 },
            { nom: "Spectre", pv: 40, degats: 5 }
        ];

        let index = Math.floor(Math.random() * monstres.length);
        let m = monstres[index];

        monstreNom = m.nom;
        monstrePv = m.pv;
        monstreDegats = m.degats;

        demarrerCombat();
    }
});
