#include "Balle.hpp"
#include <algorithm>


void Ball::reinitialiser() {

    x_ = largeurEcran_ / 2.0;
    y_ = hauteurEcran_ / 2.0;

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distDirection(0, 1);
    int direction = (distDirection(gen) == 0) ? -1 : 1;

    constexpr double PI = 3.14;
    std::uniform_real_distribution<double> distAngle(-PI / 4.0, PI / 4.0);
    double angle = distAngle(gen);

    if (std::abs(angle) < 0.1) {
        angle = (angle >= 0.0) ? 0.15 : -0.15;
    }

    
    vx_ = direction * vitesseBase_ * std::cos(angle);
    vy_ = vitesseBase_ * std::sin(angle);
}

EtatBalle Ball::move(const cv::Rect& barreGauche, double vyBarreGauche,
                      const cv::Rect& barreDroite, double vyBarreDroite) {
    x_ += vx_;
    y_ += vy_;

    if (y_ - rayon_ <= epaisseurMur_) {
        y_ = epaisseurMur_ + rayon_;
        vy_ = -vy_;
    } else if (y_ + rayon_ >= hauteurEcran_ - epaisseurMur_) {
        y_ = hauteurEcran_ - epaisseurMur_ - rayon_;
        vy_ = -vy_;
    }

    cv::Rect hitboxBall(static_cast<int>(x_ - rayon_),
                         static_cast<int>(y_ - rayon_),
                         rayon_ * 2,
                         rayon_ * 2);

    if (vx_ < 0.0 && (hitboxBalle & barreGauche).area() > 0) {
        x_ = barreGauche.x + barreGauche.width + rayon_;
        vx_ = -vx_;
        vy_ += vyBarreGauche * 0.3;
    } else if (vx_ > 0.0 && (hitboxBalle & barreDroite).area() > 0) {
        x_ = barreDroite.x - rayon_;
        vx_ = -vx_;
        vy_ += vyBarreDroite * 0.3;
    }

    double vyMax = vitesseBase_ * 1.2;
    vy_ = std::clamp(vy_, -vyMax, vyMax);

    if (x_ + rayon_ < 0) {
        return EtatBalle::PointJoueur2;
    }
    if (x_ - rayon_ > largeurEcran_) {
        return EtatBalle::PointJoueur1;
    }

    return EtatBall::EnJeu;
}void Ball::draw(cv::Mat& image) const {
    cv::circle(image, cv::Point(static_cast<int>(x_), static_cast<int>(y_)), rayon_, cv::Scalar(255, 255, 255), -1);
}
