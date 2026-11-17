#include "AIPlayer.hpp"
#include <algorithm>
#include <cmath>

AIPlayer::AIPlayer(int x, int screenHeight, int width, int height, double speed, int wallThickness)
    : x_(x),
      y_((screenHeight - height) / 2.0),
      vy_(0.0),
      width_(width),
      height_(height),
      speed_(speed),
      screenHeight_(screenHeight),
      wallThickness_(wallThickness) {}

void AIPlayer::update(double ballY, double ballVx) {
    const double paddleCenterY = y_ + height_ / 2.0;
    const double deadZone = 10.0;

    double targetY = (ballVx > 0.0) ? ballY : (screenHeight_ / 2.0);
    double diff = targetY - paddleCenterY;

    if (std::abs(diff) <= deadZone) {
        vy_ = 0.0;
    } else if (diff > 0.0) {
        vy_ = speed_;
    } else {
        vy_ = -speed_;
    }

    y_ += vy_;

    double minY = static_cast<double>(wallThickness_);
    double maxY = static_cast<double>(screenHeight_ - wallThickness_ - height_);
    y_ = std::clamp(y_, minY, maxY);
}

void AIPlayer::reset() {
    y_ = (screenHeight_ - height_) / 2.0;
    vy_ = 0.0;
}

void AIPlayer::draw(cv::Mat& image) const {
    cv::rectangle(image, getHitbox(), cv::Scalar(255, 255, 255), -1);
}

cv::Rect AIPlayer::getHitbox() const {
    return cv::Rect(x_, static_cast<int>(y_), width_, height_);
}

double AIPlayer::getVy() const {
    return vy_;
}