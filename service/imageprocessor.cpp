#include "imageprocessor.hpp"



void ImageProcessor::gif_clicked(){
    if(!in_process){
        in_process = true;
        ui->gif_btn->setDisabled(true);
        gif_frame = new QGifImage;
        gif_frame->setDefaultDelay(10);
        timer->setI=nterval(100);
        timer->start();
    }
}
void ImageProcessor::make_gif() {
    QImage image = ui->openGLWidget->grabFramebuffer();
    QImage scaled_image = image.scaled(QSize(640, 480));
    gif_frame->addFrame(scaled_image);
    if (frames_counter == 50) {
        timer->stop();
        gif_frame->save("screencast.gif");
        frames_counter = 0;
        QMessageBox messageBoxGif;
        messageBoxGif.information(0, "", "Gif animation saved successfully");
        delete gif_frame;
        ui->gif_btn->setText("");
        ui->gif_btn->setEnabled(true);
    }
    frames_counter++;
    if (!ui->gif_btn->isEnabled()) {
        ui->gif_btn->setText(QString::number(frames_counter / 10) + "s");
    }
}

void ImageProcessor::screenshot(QAbstractButton* btn)
{
    QImage img = ui->openGLWidget->grabFramebuffer();
    img.save("screenshot."+btn->text(),btn->text().toStdString().c_str());
}