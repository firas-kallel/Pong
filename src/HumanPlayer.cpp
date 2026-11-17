#include "HumanPlayer.hpp"
#include <algorithm>

HumanPlayer::HumanPlayer(int x, int screenHeight, int width, int height, double speed, int wallThickness)
    : x_(x),
      y_((screenHeight - height) / 2.0),
      vy_(0.0),
      width_(width),
      height_(height),
      speed_(speed),
      screenHeight_(screenHeight),
      wallThickness_(wallThickness) {}

void HumanPlayer::moveUp() {
    vy_ = -speed_;
}

void HumanPlayer::moveDown() {
    vy_ = speed_;
}

void HumanPlayer::stop() {
    vy_ = 0.0;
}

void HumanPlayer::setSpeed(double speed) {
    speed_ = speed;
}

void HumanPlayer::handleInput(int key) {
    const int UP_ARROW_WIN = 2490368;
    const int DOWN_ARROW_WIN = 2621440;
    const int UP_ARROW_LINUX = 65362;
    const int DOWN_ARROW_LINUX = 65364;

    if (key == 'z' || key == 'Z' || key == UP_ARROW_WIN || key == UP_ARROW_LINUX) {
        moveUp();
    } else if (key == 's' || key == 'S' || key == DOWN_ARROW_WIN || key == DOWN_ARROW_LINUX) {
        moveDown();
    } else if (key == -1) {
        stop();
    }
}

void HumanPlayer::update() {
    y_ += vy_;

    double minY = static_cast<double>(wallThickness_);
    double maxY = static_cast<double>(screenHeight_ - wallThickness_ - height_);
    y_ = std::clamp(y_, minY, maxY);
}

void HumanPlayer::reset() {
    y_ = (screenHeight_ - height_) / 2.0;
    vy_ = 0.0;
}

void HumanPlayer::draw(cv::Mat& image) const {
    cv::rectangle(image, getHitbox(), cv::Scalar(255, 255, 255), -1);
}

cv::Rect HumanPlayer::getHitbox() const {
    return cv::Rect(x_, static_cast<int>(y_), width_, height_);
}

double HumanPlayer::getVy() const {
    return vy_;
}