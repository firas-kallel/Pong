#pragma once

#include <opencv2/opencv.hpp>

class AIPlayer {
public:
    AIPlayer(int x, int screenHeight, int width, int height, double speed, int wallThickness);

    void update(double ballY, double ballVx);
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