#pragma once

#include <opencv2/opencv.hpp>

class HumanPlayer {
public:
    HumanPlayer(int x, int screenHeight, int width, int height, double speed, int wallThickness);

    void moveUp();
    void moveDown();
    void stop();
    void update();
    void reset();
    void draw(cv::Mat& image) const;

    cv::Rect getHitbox() const;
    double getVy() const;

private:
    int x_;
    double y_;
    double vy_;
    int width_;
    int height_;
    double speed_;
    int screenHeight_;
    int wallThickness_;
};