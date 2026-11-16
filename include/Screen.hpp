#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class Screen {
public:
    Screen(int width, int height, int wallThickness, const std::string& windowName = "Pong");

    // Accesseurs (getters)
    int getWidth() const;
    int getHeight() const;
    int getWallThickness() const;
    cv::Mat& getFrame();

    // Méthodes de rendu
    void clear();
    void drawArena();
    void drawPaddle(const cv::Rect& paddle);
    void drawScore(int scoreLeft, int scoreRight,
                   const std::string& nameLeft = "Joueur",
                   const std::string& nameRight = "IA");
    void drawMessage(const std::string& message);

    // Affichage de la frame et lecture clavier
    int show(int delayMs = 16);

private:
    int width_;
    int height_;
    int wallThickness_;
    std::string windowName_;
    cv::Mat frame_;
};