Balle::Balle(int largeurEcran, int hauteurEcran, int rayon, double vitesseBase, int epaisseurMur)
    : x_(largeurEcran / 2.0),
      y_(hauteurEcran / 2.0),
      vx_(0.0),
      vy_(0.0),
      rayon_(rayon),
      vitesseBase_(vitesseBase),
      largeurEcran_(largeurEcran),
      hauteurEcran_(hauteurEcran),
      epaisseurMur_(epaisseurMur) {}

void Balle::reinitialiser() {
    x_ = largeurEcran_ / 2.0;
    y_ = hauteurEcran_ / 2.0;
    vx_ = 0.0;
    vy_ = 0.0;
}

EtatBalle Balle::move(const cv::Rect& barreGauche, double vyBarreGauche,
                      const cv::Rect& barreDroite, double vyBarreDroite) {
}

void Balle::draw(cv::Mat& image) const {
}   