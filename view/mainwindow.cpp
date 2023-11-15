#include "mainwindow.h"
#include "../ui_mainwindow.h"
#include <QAbstractButton>
#include <QSlider>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    timer = new QTimer;

    ui->setupUi(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(make_gif()));
    connect(ui->gif_btn, SIGNAL(pressed()), this, SLOT(gif_clicked()));
    connect(ui->buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)),this,
            SLOT(screenshot(QAbstractButton*)));

    connect(ui->rotate_x,&QSlider::valueChanged
            ,ui->openGLWidget,&glView::setRotationX);
    connect(ui->rotate_y,&QSlider::valueChanged
            ,ui->openGLWidget,&glView::setRotationY);
    connect(ui->rotate_z,&QSlider::valueChanged
            ,ui->openGLWidget,&glView::setRotationZ);


    connect(ui->translate_x,&QSlider::valueChanged
            ,ui->openGLWidget,&glView::setTranslationX);
    connect(ui->translate_y,&QSlider::valueChanged
            ,ui->openGLWidget,&glView::setTranslationY);
    connect(ui->translate_z,&QSlider::valueChanged
            ,ui->openGLWidget,&glView::setTranslationZ);

    connect(ui->scale,&QSlider::valueChanged
            ,ui->openGLWidget,&glView::scale);
    applyConfig();
    connect(ui->ver_r,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::setConfig);
    connect(ui->ver_g,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::setConfig);
    connect(ui->ver_b,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::setConfig);

    connect(ui->bg_r,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::setConfig);
    connect(ui->bg_g,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::setConfig);
    connect(ui->bg_b,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::setConfig);

    connect(ui->eg_r,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::setConfig);
    connect(ui->eg_g,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::setConfig);
    connect(ui->eg_b,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::setConfig);


    connect(ui->vertex_size,QOverload<double>::of(&QDoubleSpinBox::valueChanged),this,&MainWindow::setConfig);
    connect(ui->line_size,QOverload<double>::of(&QDoubleSpinBox::valueChanged),this,&MainWindow::setConfig);

    connect(ui->radioButton_ortho,&QRadioButton::toggled,this,&MainWindow::setConfig);
    connect(ui->radioButton_central,&QRadioButton::toggled,this,&MainWindow::setConfig);

    connect(ui->radioButton_solid_edge,&QRadioButton::toggled,this,&MainWindow::setConfig);
    connect(ui->radioButton_dotted_edge,&QRadioButton::toggled,this,&MainWindow::setConfig);

    connect(ui->radioButton_no_point,&QRadioButton::toggled,this,&MainWindow::setConfig);
    connect(ui->radioButton_cube,&QRadioButton::toggled,this,&MainWindow::setConfig);
    connect(ui->radioButton_sphere,&QRadioButton::toggled,this,&MainWindow::setConfig);

    connect(ui->pushButton_color_edge_3,&QPushButton::pressed,this,&MainWindow::openDialog);



}


void MainWindow::closeEvent (QCloseEvent *event)
{
    save_info(ui->openGLWidget->getSettings());

    close();
}

void MainWindow::setConfig(){
    object_json* setting = ui->openGLWidget->getSettings();
    setting->color_background[0]=ui->bg_r->value();
    setting->color_background[1]=ui->bg_g->value();
    setting->color_background[2]=ui->bg_b->value();

    setting->color_line[0]=ui->eg_r->value();
    setting->color_line[1]=ui->eg_g->value();
    setting->color_line[2]=ui->eg_b->value();

    setting->color_vertex[0]=ui->ver_r->value();
    setting->color_vertex[1]=ui->ver_g->value();
    setting->color_vertex[2]=ui->ver_b->value();

    int line=0;
    if(ui->radioButton_dotted_edge->isChecked()){
        line = dotted;
    }
    if(ui->radioButton_solid_edge->isChecked()){
        line = solid;
    }
    setting->type_line =line;

    int projection=0;
    if(ui->radioButton_central->isChecked()){
        projection = central;
    }
    if(ui->radioButton_ortho->isChecked()){
        projection = parallel;
    }
    setting->type_projection=projection;


    int vertex=0;
    if(ui->radioButton_no_point->isChecked()){
        vertex =  none;
    }
    if(ui->radioButton_sphere->isChecked()){
        vertex =  circle;
    }
    if(ui->radioButton_cube->isChecked()){
        vertex =  square;
    }
    setting->type_vertex = vertex;

    setting->size_line = ui->line_size->value();
    setting->size_vertex=ui->vertex_size->value();
    ui->openGLWidget->update();
}

void MainWindow::openDialog(){

    QString file_name = QFileDialog::getOpenFileName(nullptr,"Open file",".",nullptr,nullptr,QFileDialog::DontUseNativeDialog);
    if(file_name.length()<3){
        return;
    }

    Status info =ui->openGLWidget->initModel(file_name);

    ui->label->setText(file_name);
    ui->label_2->setText(QString::number(info.vertexes));
    ui->label_3->setText(QString::number(info.edges));

    ui->openGLWidget->update();
}

void MainWindow::applyConfig(){
    object_json* setting = ui->openGLWidget->getSettings();
    ui->bg_r->setValue(setting->color_background[0]);
    ui->bg_g->setValue(setting->color_background[1]);
    ui->bg_b->setValue(setting->color_background[2]);

    ui->eg_r->setValue(setting->color_line[0]);
    ui->eg_g->setValue(setting->color_line[1]);
    ui->eg_b->setValue(setting->color_line[2]);

    ui->ver_r->setValue(setting->color_vertex[0]);
    ui->ver_g->setValue(setting->color_vertex[1]);
    ui->ver_b->setValue(setting->color_vertex[2]);



    switch(setting->type_line){
        case dotted:{
            ui->radioButton_dotted_edge->toggle();
            break;
        }
        case solid:{
            ui->radioButton_solid_edge->toggle();
            break;
        }
    }

    switch(setting->type_projection){
        case central:{
            ui->radioButton_central->toggle();
            break;
        }
        case parallel:{
            ui->radioButton_ortho->toggle();
            break;
        }
    }



    switch(setting->type_vertex){
    case none:{
            ui->radioButton_no_point->toggle();
            break;
    }
    case circle:{
            ui->radioButton_sphere->toggle();
            break;
    }
    case square:{
            ui->radioButton_cube->toggle();
            break;
    }
    }
    ui->line_size->setValue(setting->size_line);
    ui->vertex_size->setValue(setting->size_vertex);
    ui->openGLWidget->update();
}

void MainWindow::gif_clicked(){
    if(!in_process){
        in_process = true;
        ui->gif_btn->setDisabled(true);
        gif_frame = new QGifImage;
        gif_frame->setDefaultDelay(10);
        timer->setInterval(100);
        timer->start();
    }
}
void MainWindow::make_gif() {
    QImage image = ui->openGLWidget->grabFramebuffer();
    QSize image_size(640, 480);
    QImage scaled_image = image.scaled(image_size);
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

void MainWindow::screenshot(QAbstractButton* btn)
{
    QImage img = ui->openGLWidget->grabFramebuffer();
    img.save("screenshot."+btn->text(),btn->text().toStdString().c_str());
}

MainWindow::~MainWindow()
{
    delete ui;
}

