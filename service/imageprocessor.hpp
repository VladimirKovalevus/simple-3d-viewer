


class ImageProcessor{

public:
    void gif_clicked();
    void make_gif();
    void screenshot();
private:
    char frames_counter=0;
    bool in_process=0;
    QGifImage* gif_image;
}