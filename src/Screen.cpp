#include "Screen.hpp"

Screen::Screen(int width, int height, int wallThickness, const std::string& windowName)
    : width_(width),
      height_(height),
      wallThickness_(wallThickness),
      windowName_(windowName),
      frame_(height, width, CV_8UC3, cv::Scalar(0, 0, 0)) {
    cv::namedWindow(windowName_, cv::WINDOW_AUTOSIZE);
}

int Screen::getWidth() const {
    return width_;
}

int Screen::getHeight() const {
    return height_;
}

int Screen::getWallThickness() const {
    return wallThickness_;
}

cv::Mat& Screen::getFrame() {
    return frame_;
}

void Screen::clear() {
    frame_.setTo(cv::Scalar(0, 0, 0));
}

void Screen::drawArena() {
    const cv::Scalar white(255, 255, 255);

    // Mur supérieur et mur inférieur (correspond exactement à wallThickness_ de Ball)
    cv::rectangle(frame_, cv::Rect(0, 0, width_, wallThickness_), white, -1);
    cv::rectangle(frame_, cv::Rect(0, height_ - wallThickness_, width_, wallThickness_), white, -1);

    // Filet central en pointillés (style Figure 1 du sujet)
    const int centerX = width_ / 2;
    const int dashHeight = 12;
    const int dashGap = 10;
    const int dashWidth = 4;

    for (int y = wallThickness_; y < height_ - wallThickness_; y += dashHeight + dashGap) {
        int currentDashHeight = std::min(dashHeight, (height_ - wallThickness_) - y);
        cv::rectangle(frame_,
                      cv::Rect(centerX - dashWidth / 2, y, dashWidth, currentDashHeight),
                      white,
                      -1);
    }
}

void Screen::drawPaddle(const cv::Rect& paddle) {
    cv::rectangle(frame_, paddle, cv::Scalar(255, 255, 255), -1);
}

void Screen::drawScore(int scoreLeft, int scoreRight,
                       const std::string& nameLeft,
                       const std::string& nameRight) {
    const cv::Scalar white(255, 255, 255);
    const int fontFace = cv::FONT_HERSHEY_SIMPLEX;

    // Affichage des noms des joueurs (option prévue dans l'énoncé)
    const double nameScale = 0.6;
    const int nameThickness = 1;
    int baseline = 0;

    cv::Size leftNameSize = cv::getTextSize(nameLeft, fontFace, nameScale, nameThickness, &baseline);
    cv::Point leftNamePos(width_ / 4 - leftNameSize.width / 2, wallThickness_ + 30);
    cv::putText(frame_, nameLeft, leftNamePos, fontFace, nameScale, white, nameThickness, cv::LINE_AA);

    cv::Size rightNameSize = cv::getTextSize(nameRight, fontFace, nameScale, nameThickness, &baseline);
    cv::Point rightNamePos(3 * width_ / 4 - rightNameSize.width / 2, wallThickness_ + 30);
    cv::putText(frame_, nameRight, rightNamePos, fontFace, nameScale, white, nameThickness, cv::LINE_AA);

    // Affichage des scores centrés de chaque côté du filet
    const std::string leftText = std::to_string(scoreLeft);
    const std::string rightText = std::to_string(scoreRight);
    const double scoreScale = 1.8;
    const int scoreThickness = 3;

    cv::Size leftScoreSize = cv::getTextSize(leftText, fontFace, scoreScale, scoreThickness, &baseline);
    cv::Point leftScorePos(width_ / 4 - leftScoreSize.width / 2, wallThickness_ + 85);
    cv::putText(frame_, leftText, leftScorePos, fontFace, scoreScale, white, scoreThickness, cv::LINE_AA);

    cv::Size rightScoreSize = cv::getTextSize(rightText, fontFace, scoreScale, scoreThickness, &baseline);
    cv::Point rightScorePos(3 * width_ / 4 - rightScoreSize.width / 2, wallThickness_ + 85);
    cv::putText(frame_, rightText, rightScorePos, fontFace, scoreScale, white, scoreThickness, cv::LINE_AA);
}

void Screen::drawMessage(const std::string& message) {
    const int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    const double scale = 0.8;
    const int thickness = 2;
    int baseline = 0;

    cv::Size textSize = cv::getTextSize(message, fontFace, scale, thickness, &baseline);
    cv::Point pos((width_ - textSize.width) / 2, height_ - wallThickness_ - 30);

    cv::putText(frame_, message, pos, fontFace, scale, cv::Scalar(200, 200, 200), thickness, cv::LINE_AA);
}

int Screen::show(int delayMs) {
    cv::imshow(windowName_, frame_);
    return cv::waitKey(delayMs);
}