#include "Screen.hpp"
#include "Ball.hpp"

int main() {
    const int width = 800;
    const int height = 600;
    const int wallThickness = 15;

    Screen screen(width, height, wallThickness, "Pong");
    Ball ball(width, height, 8, 6.0, wallThickness);

    // Raquettes temporaires fixes sur les côtés pour tester les rebonds
    cv::Rect leftPaddle(30, height / 2 - 45, 12, 90);
    cv::Rect rightPaddle(width - 42, height / 2 - 45, 12, 90);

    bool inPlay = false;

    while (true) {
        screen.clear();
        screen.drawArena();
        screen.drawPaddle(leftPaddle);
        screen.drawPaddle(rightPaddle);
        screen.drawScore(0, 0);

        if (!inPlay) {
            screen.drawMessage("Appuyez sur ESPACE pour lancer");
        } else {
            BallState state = ball.move(leftPaddle, 0.0, rightPaddle, 0.0);
            if (state != BallState::InPlay) {
                inPlay = false;
            }
        }

        ball.draw(screen.getFrame());

        int key = screen.show(16);
        if (key == 27) { // Touche Echap pour quitter
            break;
        }
        if (key == ' ' && !inPlay) { // Barre d'espace pour lancer la balle
            ball.reset();
            inPlay = true;
        }
    }

    return 0;
}