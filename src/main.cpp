#include "Screen.hpp"
#include "Ball.hpp"
#include "HumanPlayer.hpp"
#include "AIPlayer.hpp"

int main() {
    // Paramètres généraux de l'arène et du jeu
    const int width = 800;
    const int height = 600;
    const int wallThickness = 15;
    const int maxScore = 10;

    // Paramètres des raquettes et de la balle
    const int paddleWidth = 12;
    const int paddleHeight = 90;
    const int paddleMargin = 30;
    const double playerSpeed = 8.0;
    const double aiSpeed = 5.5;
    const int ballRadius = 8;
    const double ballSpeed = 6.0;

    // Instanciation des 4 modules
    Screen screen(width, height, wallThickness, "Pong");
    HumanPlayer player(paddleMargin, height, paddleWidth, paddleHeight, playerSpeed, wallThickness);
    AIPlayer ai(width - paddleMargin - paddleWidth, height, paddleWidth, paddleHeight, aiSpeed, wallThickness);
    Ball ball(width, height, ballRadius, ballSpeed, wallThickness);

    int scorePlayer = 0;
    int scoreAI = 0;
    bool inPlay = false;
    bool gameOver = false;

    while (true) {
        // 1. Mise à jour de la physique (uniquement si la partie n'est pas finie)
        if (!gameOver) {
            player.update();
            ai.update(ball.getY(), ball.getVx());

            if (inPlay) {
                BallState state = ball.move(player.getHitbox(), player.getVy(),
                                            ai.getHitbox(), ai.getVy());

                if (state == BallState::Player1Point) {
                    scorePlayer++;
                    inPlay = false;
                    ball.reset();
                } else if (state == BallState::Player2Point) {
                    scoreAI++;
                    inPlay = false;
                    ball.reset();
                }

                if (scorePlayer >= maxScore || scoreAI >= maxScore) {
                    gameOver = true;
                }
            }
        }

        // 2. Rendu graphique de la frame
        screen.clear();
        screen.drawArena();
        screen.drawScore(scorePlayer, scoreAI, "Player", "AI");

        player.draw(screen.getFrame());
        ai.draw(screen.getFrame());
        ball.draw(screen.getFrame());

        if (gameOver) {
            if (scorePlayer >= maxScore) {
                screen.drawMessage("Victoire ! (R pour rejouer, ECHAP pour quitter)");
            } else {
                screen.drawMessage("Defaite ! (R pour rejouer, ECHAP pour quitter)");
            }
        } else if (!inPlay) {
            screen.drawMessage("Appuyez sur ESPACE pour lancer");
        }

        // 3. Affichage et gestion des entrées clavier
        int key = screen.show(16);

        if (key == 27) { // ECHAP : quitter
            break;
        }

        if (key == 'r' || key == 'R') { // R : réinitialiser toute la partie
            scorePlayer = 0;
            scoreAI = 0;
            inPlay = false;
            gameOver = false;
            player.reset();
            ai.reset();
            ball.reset();
            continue;
        }

        if (!gameOver) {
            // Lancement de la balle avec la barre d'espace[cite: 3]
            if (key == ' ' && !inPlay) {
                ball.reset();
                inPlay = true;
            }

            // Contrôle vertical du joueur humain (Z/S, W/S ou flèches Haut/Bas)
            if (key == 'z' || key == 'Z' || key == 'w' || key == 'W' || key == 82) {
                player.moveUp();
            } else if (key == 's' || key == 'S' || key == 84) {
                player.moveDown();
            } else {
                player.stop();
            }
        }
    }

    return 0;
}