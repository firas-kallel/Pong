#include "Ball.hpp"
#include <algorithm>
#include <random>
#include <cmath>

Ball::Ball(int screenWidth, int screenHeight, int radius, double baseSpeed, int wallThickness)
    : x_(screenWidth / 2.0),
      y_(screenHeight / 2.0),
      vx_(0.0),
      vy_(0.0),
      radius_(radius),
      baseSpeed_(baseSpeed),
      screenWidth_(screenWidth),
      screenHeight_(screenHeight),
      wallThickness_(wallThickness) {}

void Ball::reset() {
    x_ = screenWidth_ / 2.0;
    y_ = screenHeight_ / 2.0;

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distDirection(0, 1);
    int direction = (distDirection(gen) == 0) ? -1 : 1;

    constexpr double PI = 3.14159265358979323846;
    std::uniform_real_distribution<double> distAngle(-PI / 4.0, PI / 4.0);
    double angle = distAngle(gen);

    if (std::abs(angle) < 0.1) {
        angle = (angle >= 0.0) ? 0.15 : -0.15;
    }

    vx_ = direction * baseSpeed_ * std::cos(angle);
    vy_ = baseSpeed_ * std::sin(angle);
}

BallState Ball::move(const cv::Rect& leftPaddle, double leftPaddleVy,
                     const cv::Rect& rightPaddle, double rightPaddleVy) {
    x_ += vx_;
    y_ += vy_;

    if (y_ - radius_ <= wallThickness_) {
        y_ = wallThickness_ + radius_;
        vy_ = -vy_;
    } else if (y_ + radius_ >= screenHeight_ - wallThickness_) {
        y_ = screenHeight_ - wallThickness_ - radius_;
        vy_ = -vy_;
    }

    cv::Rect ballHitbox(static_cast<int>(x_ - radius_),
                        static_cast<int>(y_ - radius_),
                        radius_ * 2,
                        radius_ * 2);

    if (vx_ < 0.0 && (ballHitbox & leftPaddle).area() > 0) {
        x_ = leftPaddle.x + leftPaddle.width + radius_;
        vx_ = -vx_;
        vy_ += leftPaddleVy * 0.3;
    } else if (vx_ > 0.0 && (ballHitbox & rightPaddle).area() > 0) {
        x_ = rightPaddle.x - radius_;
        vx_ = -vx_;
        vy_ += rightPaddleVy * 0.3;
    }

    double maxVy = baseSpeed_ * 1.2;
    vy_ = std::clamp(vy_, -maxVy, maxVy);

    if (x_ + radius_ < 0) {
        return BallState::Player2Point;
    }
    if (x_ - radius_ > screenWidth_) {
        return BallState::Player1Point;
    }

    return BallState::InPlay;
}

void Ball::draw(cv::Mat& image) const {
    cv::circle(image, cv::Point(static_cast<int>(x_), static_cast<int>(y_)), radius_, cv::Scalar(255, 255, 255), -1);
}