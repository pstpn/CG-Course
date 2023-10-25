#include "mainwindow.h"

#include <cmath>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <source_location>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupScene();

    _facade = std::make_shared<Facade>(Facade());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupScene() {
    _scene = std::make_shared<QGraphicsScene>(this);

    ui->graphicsView->setScene(_scene.get());
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    auto cont = ui->graphicsView->contentsRect();
    _scene->setSceneRect(0, 0, cont.width(), cont.height());
    _cameraIndex = 1;

    auto solution(new DrawerSolution<QtFactory, QGraphicsScene>());
    _drawer = solution->createDrawer(_scene.get());

    _solver = std::shared_ptr<Solver>(new Solver());
    _solver->addWaveSource({0, 0, 0, 10});
    _solver->addObstacle({-100, 100, -100, 100, -100, 100});
}

void MainWindow::updateScene() {
    auto scene = std::make_shared<Scene>();
    ClearScene clear_cmd(_drawer);
    _facade->execute(clear_cmd);

    GetScene get_scene_cmd(scene);
    _facade->execute(get_scene_cmd);

    DrawScene draw_cmd(scene, _drawer);
    _facade->execute(draw_cmd);

    _solver->solve();

    std::shared_ptr<Camera> camera(_facade->getSceneManager()->getCamera());
    if(!camera)
        return;

    QGraphicsScene *_drawingScene = std::reinterpret_pointer_cast<QtDrawer>(_drawer)->getScene();

    std::vector<Wave> _waves = _solver->getWaves();

    Transformer transformer;
    transformer.setRotationMatrix(
        camera->_angle.getX(),
        camera->_angle.getY(),
        camera->_angle.getZ()
    );

    std::vector<Vertex> projections;
    for(auto &wave : _waves) {
        for(auto &vert : wave.points) {
            Vertex tmp = {vert.x, vert.y, vert.z};
            transformer.transform(tmp);
            projections.push_back(tmp + camera->_location);
        }
        for(auto &triag : wave.triangles) {
            // auto dd = (camera->_location -
            //          Vertex(wave.points[std::get<0>(triag)].x,
            //                 wave.points[std::get<0>(triag)].y,
            //                 wave.points[std::get<0>(triag)].z));
            // double distToCamera = dd.dotProduct(dd, dd);

            uint32_t triangle_alpha = 40 - 
                ( wave.points[std::get<0>(triag)].collision_count
                + wave.points[std::get<1>(triag)].collision_count
                + wave.points[std::get<2>(triag)].collision_count) * 10;
            if(triangle_alpha < 0)
                continue;
            
            QPolygonF triangle;
            triangle << QPoint(projections[std::get<0>(triag)].getX(),
                            projections[std::get<0>(triag)].getY())
                    << QPoint(projections[std::get<1>(triag)].getX(),
                            projections[std::get<1>(triag)].getY())
                    << QPoint(projections[std::get<2>(triag)].getX(),
                            projections[std::get<2>(triag)].getY());
            _drawingScene->addPolygon(triangle,
                        QPen(QColor(0, 0, 0, 60)),
                        QBrush(QColor(0, 0, 0, triangle_alpha)));
        }
    }
    // Vertex projection = point;
    // transfomer.transform(projection);
    // return projection + _camera->_location;
}

void MainWindow::checkCamExist() {

    if (!_cameras.size())
    {
        auto loc = std::source_location::current();
        throw CameraException(
            loc.file_name(),
            loc.function_name(),
            loc.line(),
            "No camera found"
        );
    }
}

void MainWindow::checkModelsExist() {

    if (!_models.size()) {

        auto loc = std::source_location::current();
        throw ModelException(
            loc.file_name(),
            loc.function_name(),
            loc.line(),
            "No models found"
        );
    }
}

void MainWindow::checkCamDelete() {
    
    if (_cameras.size() <= 1 && _models.size()) {

        auto loc = std::source_location::current();
        throw CameraException(
            loc.file_name(),
            loc.function_name(),
            loc.line(),
            "Cannot delete the last camera with the loaded models"
        );
    }
}

void MainWindow::on_addCameraBtn_clicked() {

    auto cont = ui->graphicsView->contentsRect();

    auto id = std::make_shared<size_t>(0);
    Vertex location(cont.width() / 2.0, cont.height() / 2.0, 0.0);
    Vertex angles(0);
    AddCamera addCMD(id, location, angles);

    _facade->execute(addCMD);
    _cameras.push_back(*id);

    updateScene();

    auto cam = ui->cameraCB;

    std::string camName = std::string("Camera") + std::to_string(_cameraIndex++);
    cam->addItem(QString(camName.data()));

    ui->cameraCB->setCurrentIndex(ui->cameraCB->count() - 1);
}

void MainWindow::on_loadModelBtn_clicked() {

    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Добавьте камеру!");
        return;
    }

    auto path = QFileDialog::getOpenFileName(nullptr, "Загрузка модели", ".");

    if (path.isNull())
        return;

    std::shared_ptr<BaseObject> model = std::make_shared<CarcassModel>();
    auto id = std::make_shared<size_t>(0);
    std::string pathFileName = path.toStdString();

    try
    {
        LoadModel load_cmd(model, pathFileName);
        _facade->execute(load_cmd);

        AddModel add_cmd(id, model);
        _facade->execute(add_cmd);
    }
    catch (const BaseException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при загрузке модели из файла!");
        return;
    }

    _models.push_back(*id);
    updateScene();
    _modelIndex++;
    auto fileName = QFileInfo(path.toUtf8().data()).fileName();
    QString figName = QString("CarcasModel") + QString::number(_modelIndex) + QString(" load from ") + QString(fileName);
    ui->modelsCB->addItem(figName);
    ui->modelsCB->setCurrentIndex(ui->modelsCB->count() - 1);
}

void MainWindow::on_deleteModelBtn_clicked() {

    try
    {
        checkModelsExist();
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет загруженных моделей!");
        return;
    }

    std::size_t id = _models.at(ui->modelsCB->currentIndex());
    RemoveModel cmd(id);
    _facade->execute(cmd);

    _models.erase(_models.begin() + ui->modelsCB->currentIndex());
    ui->modelsCB->removeItem(ui->modelsCB->currentIndex());

    updateScene();
}

void MainWindow::on_deleteModelsBtn_clicked() {

    try
    {
        checkModelsExist();
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет загруженных моделей!");
        return;
    }

    for (int i = ui->modelsCB->count() - 1; i >= 0; --i)
    {
        std::size_t id = _models.at(i);
        RemoveModel cmd(id);
        _facade->execute(cmd);

        _models.erase(_models.begin() + i);
        ui->modelsCB->removeItem(i);
    }

    updateScene();
}


void MainWindow::on_cameraCB_currentIndexChanged(int index)
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        return;
    }

    std::size_t id = _cameras.at(index);
    SetCamera cmd(id);
    _facade->execute(cmd);

    updateScene();
}

void MainWindow::on_deleteCameraBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }

    try
    {
        checkCamDelete();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Для удаления этой камеры необходимо удалить все модели");
        return;
    }

    std::size_t id = _cameras.at(ui->cameraCB->currentIndex());
    RemoveCamera cmd(id);
    _facade->execute(cmd);

    _cameras.erase(_cameras.begin() + ui->cameraCB->currentIndex());
    ui->cameraCB->removeItem(ui->cameraCB->currentIndex());

    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        return;
    }

    updateScene();
}

void MainWindow::on_upBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::warning(nullptr, "Предупреждение", "Пожалуйста, загрузите камеру");
        return;
    }

    std::shared_ptr<Camera> camera;

    GetMainCamera get_camera(camera);
    _facade->execute(get_camera);

    TranslateCamera move_cmd(camera, 0, 10, 0);
    _facade->execute(move_cmd);

    updateScene();
}

void MainWindow::on_downBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::warning(nullptr, "Предупреждение", "Пожалуйста, загрузите камеру");
        return;
    }

    std::shared_ptr<Camera> camera;

    GetMainCamera get_camera(camera);
    _facade->execute(get_camera);

    TranslateCamera move_cmd(camera, 0, -10, 0);
    _facade->execute(move_cmd);

    updateScene();
}

void MainWindow::on_rightBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::warning(nullptr, "Предупреждение", "Пожалуйста, загрузите камеру");
        return;
    }

    std::shared_ptr<Camera> camera;

    GetMainCamera get_camera(camera);
    _facade->execute(get_camera);

    TranslateCamera move_cmd(camera, 10, 0, 0);
    _facade->execute(move_cmd);

    updateScene();
}


void MainWindow::on_leftBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::warning(nullptr, "Предупреждение", "Пожалуйста, загрузите камеру");
        return;
    }

    std::shared_ptr<Camera> camera;

    GetMainCamera get_camera(camera);
    _facade->execute(get_camera);

    TranslateCamera move_cmd(camera, -10, 0, 0);
    _facade->execute(move_cmd);

    updateScene();
}

void MainWindow::on_botLeftBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::warning(nullptr, "Предупреждение", "Пожалуйста, загрузите камеру");
        return;
    }

    std::shared_ptr<Camera> camera;

    GetMainCamera get_camera(camera);
    _facade->execute(get_camera);

    RotateCamera rot_cmd(camera, 0, -M_PI / 10., 0);
    _facade->execute(rot_cmd);

    updateScene();
}

void MainWindow::on_botRightBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::warning(nullptr, "Предупреждение", "Пожалуйста, загрузите камеру");
        return;
    }

    std::shared_ptr<Camera> camera;

    GetMainCamera get_camera(camera);
    _facade->execute(get_camera);

    RotateCamera rot_cmd(camera, 0, M_PI / 10., 0);
    _facade->execute(rot_cmd);
    
    updateScene();
}

void MainWindow::on_topLeftBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::warning(nullptr, "Предупреждение", "Пожалуйста, загрузите камеру");
        return;
    }

    std::shared_ptr<Camera> camera;

    GetMainCamera get_camera(camera);
    _facade->execute(get_camera);

    RotateCamera rot_cmd(camera, 0, 0, M_PI / 10.);
    _facade->execute(rot_cmd);
    
    updateScene();
}

void MainWindow::on_topRightBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::warning(nullptr, "Предупреждение", "Пожалуйста, загрузите камеру");
        return;
    }

    std::shared_ptr<Camera> camera;

    GetMainCamera get_camera(camera);
    _facade->execute(get_camera);

    RotateCamera rot_cmd(camera, 0, 0, -M_PI / 10.);
    _facade->execute(rot_cmd);
    
    updateScene();
}


void MainWindow::on_moveBtn_clicked()
{
    try
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет каркасных фигур!");
        return;
    }

    std::shared_ptr<BaseObject> model;

    GetSceneObject get_object_cmd(model, _models.at(ui->modelsCB->currentIndex()));
    _facade->execute(get_object_cmd);

    TranslateModel move_cmd(model, ui->dxDSB->value(), -ui->dyDSB->value(), ui->dzDSB->value());
    _facade->execute(move_cmd);

    updateScene();
}

void MainWindow::on_moveAllBtn_clicked()
{
    try
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет моделей!");
        return;
    }

    std::shared_ptr<BaseObject> composite;
    GetSceneObjects get_objs(composite);
    _facade->execute(get_objs);

    TranslateModels move_cmd(composite, ui->dxDSB->value(), ui->dyDSB->value(), ui->dzDSB->value());

    _facade->execute(move_cmd);
    updateScene();
}

void MainWindow::on_scaleBtn_clicked()
{
    try
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет моделей!");
        return;
    }

    std::shared_ptr<BaseObject> model;

    GetSceneObject get_object_cmd(model, _models.at(ui->modelsCB->currentIndex()));
    _facade->execute(get_object_cmd);


    ScaleModel scale_cmd(model, ui->kxDSB->value(), ui->kyDSB->value(), ui->kzDSB->value());
    _facade->execute(scale_cmd);

    updateScene();
}

void MainWindow::on_scaleAllBtn_clicked()
{
    try
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет моделей!");
        return;
    }

    std::shared_ptr<BaseObject> composite;
    GetSceneObjects get_objs(composite);
    _facade->execute(get_objs);

    ScaleModels scale_cmd(composite,
        ui->kxDSB->value(),
        ui->kyDSB->value(),
        ui->kzDSB->value());
    _facade->execute(scale_cmd);

    updateScene();
}

void MainWindow::on_rotateBtn_clicked()
{
    try
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет моделей!");
        return;
    }

    shared_ptr<BaseObject> model;

    GetSceneObject get_object_cmd(model, _models.at(ui->modelsCB->currentIndex()));
    _facade->execute(get_object_cmd);

    RotateModel rotate_cmd(model,
        ui->axDSB->value() * M_PI / 180,
        ui->ayDSB->value() * M_PI / 180,
        ui->azDSB->value() * M_PI / 180);
    _facade->execute(rotate_cmd);

    updateScene();
}

void MainWindow::on_rotateAllBtn_clicked()
{
    try
    {
        checkCamExist();
        checkModelsExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет моделей!");
        return;
    }

    std::shared_ptr<BaseObject> composite;
    GetSceneObjects get_objs(composite);
    _facade->execute(get_objs);

    RotateModels rotate_cmd(composite,
        ui->axDSB->value() * M_PI / 180,
        ui->ayDSB->value() * M_PI / 180,
        ui->azDSB->value() * M_PI / 180);
    _facade->execute(rotate_cmd);

    updateScene();
}
