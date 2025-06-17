document.addEventListener("DOMContentLoaded", () => {
  // Création dynamique de toute la page
  document.body.innerHTML = `
    <h1>Défi : Gagnez au Black Jack pour continuer l'histoire</h1>
    <p>Pour accéder au chapitre suivant, vous devez battre le croupier.</p>
    <button id="startBtn">Jouer</button>
    <div id="controls" style="display:none;">
      <button id="tirerBtn">Tirer une carte</button>
      <button id="resterBtn">Rester</button>
    </div>
    <div id="log" style="white-space: pre-wrap; background: #f0f0f0; padding: 10px; margin-top: 10px;">Cliquez sur "Jouer" pour commencer.</div>
    <div id="next" style="margin-top: 20px;"></div>
  `;

  let deck = [], playerHand = [], dealerHand = [], gameOver = false;

  function createDeck() {
    const suits = ['♠', '♥', '♦', '♣'];
    const values = ['2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A'];
    let d = [];
    for (let s of suits) {
      for (let v of values) d.push({ value: v, suit: s });
    }
    return d.sort(() => Math.random() - 0.5);
  }

  function getValue(card) {
    if (['K', 'Q', 'J'].includes(card.value)) return 10;
    if (card.value === 'A') return 11;
    return parseInt(card.value);
  }

  function handValue(hand) {
    let value = hand.reduce((sum, c) => sum + getValue(c), 0);
    let aces = hand.filter(c => c.value === 'A').length;
    while (value > 21 && aces--) value -= 10;
    return value;
  }

  function display() {
    const log = document.getElementById("log");
    const playerVal = handValue(playerHand);
    const dealerVal = handValue(dealerHand);
    log.innerText = 
      `Vos cartes : ${playerHand.map(c => c.value + c.suit).join(', ')} (${playerVal})\n` +
      `Croupier : ${dealerHand.map(c => c.value + c.suit).join(', ')} (${dealerVal})`;
  }

  function tirer() {
    if (gameOver) return;
    playerHand.push(deck.pop());
    display();
    if (handValue(playerHand) > 21) {
      endGame(false, "Vous avez dépassé 21. Défaite !");
    }
  }

  function rester() {
    if (gameOver) return;
    while (handValue(dealerHand) < 17) {
      dealerHand.push(deck.pop());
    }
    display();
    const p = handValue(playerHand);
    const d = handValue(dealerHand);
    if (d > 21 || p > d) {
      endGame(true, "Bravo ! Vous avez gagné !");
    } else if (p === d) {
      endGame(false, "Égalité. Réessayez.");
    } else {
      endGame(false, "Le croupier a gagné. Vous avez perdu.");
    }
  }

  function endGame(win, message) {
    gameOver = true;
    const log = document.getElementById("log");
    const next = document.getElementById("next");
    log.innerText += "\n" + message;
    if (win) {
      next.innerHTML = `<a href="05.html">👉 Continuer vers le chapitre suivant</a>`;
    } else {
      next.innerHTML = `<p style="color:red;">Vous ne pouvez pas continuer. Essayez encore.</p>`;
    }
    document.getElementById("controls").style.display = "none";
  }

  function startGame() {
    deck = createDeck();
    playerHand = [deck.pop(), deck.pop()];
    dealerHand = [deck.pop(), deck.pop()];
    gameOver = false;
    document.getElementById("next").innerHTML = "";
    display();
    document.getElementById("controls").style.display = "block";
  }

  // Événements
  document.getElementById("startBtn").onclick = startGame;
  document.getElementById("tirerBtn").onclick = tirer;
  document.getElementById("resterBtn").onclick = rester;
});