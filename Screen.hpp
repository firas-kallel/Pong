class Screen
{
private:
    int width;
    int height;

public:
    Screen(int width, int height);

    int getWidth() const;
    int getHeight() const;

    void clear();
    void drawMiddleLine();
    void show();
};