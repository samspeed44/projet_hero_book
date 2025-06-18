// Lance le jeu une fois que le DOM est chargé
document.addEventListener("DOMContentLoaded", startBlackjack);

// Liste les chapitres ou le jeu doit apparaitre
const chapitresAvecJeu = [3]; 

// Tire une carte entre 1 et 10 
function drawCard() {
    return Math.floor(Math.random() * 10) + 1;
}

// Calcule le total d'une main 
function total(hand) {
    return hand.reduce((a, b) => a + b, 0);
}

// Mains du joueur et du croupier
let player = [], dealer = [], gameOver = false;

// Fonction principale appelée au chargement de la page
function startBlackjack() {
    // Récupère le numéro de la page actuelle à partir de l'URL (ex : 03.html → 3)
    const currentPage = parseInt(window.location.pathname.match(/(\d+)\.html$/)[1]);

    // Si la page ne fait pas partie des chapitres concernés, ne rien faire
    if (!chapitresAvecJeu.includes(currentPage)) return;

    // Bloque l'accès aux liens tant que le jeu n'est pas gagné
    blockLinks();

    // Crée l'interface HTML du jeu
    const container = document.createElement("div");
    container.id = "blackjack";
    container.innerHTML = `
        <h2>Gagner contre le croupier pour changer de page</h2>
        <div id="log"></div>
        <div id="controls">
            <button onclick="hit()">Tirer une carte</button>
            <button onclick="stand()">Rester</button>
        </div>
        <div id="result"></div>
    `;
    document.body.appendChild(container);

    // Démarre une nouvelle partie
    initGame();
}

// Désactive tous les liens HTML menant aux chapitres
function blockLinks() {
    const links = document.querySelectorAll("a[href$='.html']");
    links.forEach(link => {
        // Sauvegarde l'URL originale
        link.dataset.originalHref = link.href;
        // Désactive le lien 
        link.removeAttribute("href");  
        // Désactive les clics       
        link.style.pointerEvents = "none"; 
        // Visuellement grisé    
        link.style.opacity = "0.5";            
    });
}

// Réactive les liens (appelé après une victoire)
function unlockLinks() {
    const links = document.querySelectorAll("a[data-original-href]");
    links.forEach(link => {
        link.href = link.dataset.originalHref; // Restaure l'URL originale
        link.style.pointerEvents = "auto";     // Réactive le clic
        link.style.opacity = "1";              // Restaure l'apparence normale
    });
}

// Initialise les mains du joueur et du croupier
function initGame() {
    player = [drawCard(), drawCard()]; // Deux cartes pour le joueur
    dealer = [drawCard(), drawCard()]; // Deux cartes pour le croupier
    gameOver = false;                  // Réinitialise l'état du jeu
    updateLog();                       // Affiche les mains

    // Réinitialise les boutons de jeu
    document.getElementById("result").innerHTML = "";
    const controls = document.getElementById("controls");
    controls.innerHTML = `
        <button onclick="hit()">Tirer une carte</button>
        <button onclick="stand()">Rester</button>
    `;
}

// Affiche les cartes actuelles du joueur et du croupier
function updateLog() {
    const log = document.getElementById("log");
    log.innerText = `Vos cartes : ${player.join(", ")} (total: ${total(player)})\n` +
                    `Cartes du dealer : ${dealer.join(", ")} (total: ${total(dealer)})`;
}

// Action : le joueur tire une carte
function hit() {
    // Si le jeu est fini, ne rien faire
    if (gameOver) return;    
    // Ajoute une carte              
    player.push(drawCard()); 
    // Met à jour l'affichage            
    updateLog();
    // Si le joueur dépasse 21                         
    if (total(player) > 21) {            
        endGame(false, "Vous avez dépassé 21. Vous perdez.");
    }
}

// Action : le joueur reste, c'est au tour du croupier
function stand() {
    if (gameOver) return;

    // Le croupier tire jusqu'à atteindre au moins 17
    while (total(dealer) < 17) {
        dealer.push(drawCard());
    }

    updateLog();

    // Compare les scores
    const p = total(player), d = total(dealer);
    if (d > 21 || p > d) {
        endGame(true, "Vous avez gagné !");
    } else {
        endGame(false, "Vous avez perdu.");
    }
}

// Fin de la partie
function endGame(win, message) {
    gameOver = true;
    document.getElementById("result").innerText = message;

    const controls = document.getElementById("controls");

    if (win) {
        // Le joueur peut continuer
        unlockLinks(); 
        controls.innerHTML = "<p style='color:white;'>Vous pouvez continuer l'histoire !</p>";
    } else {
        // Bouton pour rejouer si le joueur perd
        controls.innerHTML += `
            <br><button onclick="initGame()">Rejouer</button>
        `;
    }
}



