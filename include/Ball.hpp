#pragma once

#include <opencv2/opencv.hpp>

enum class BallState {
    InPlay,
    Player1Point,
    Player2Point
};

class Ball {
public:
    Ball(int screenWidth, int screenHeight, int radius, double baseSpeed, int wallThickness);

    void reset();
    BallState move(const cv::Rect& leftPaddle, double leftPaddleVy,
                   const cv::Rect& rightPaddle, double rightPaddleVy);
    void draw(cv::Mat& image) const;
    double getY() const;
    double getVx() const;

private:
    double x_;
    double y_;
    double vx_;
    double vy_;
    int radius_;
    double baseSpeed_;
    int screenWidth_;
    int screenHeight_;
    int wallThickness_;
};