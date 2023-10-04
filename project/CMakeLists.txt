cmake_minimum_required(VERSION 3.0.0)
project(project VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui/)

set(src_files
        "./lib/actions/BaseAction.cpp"
        "./lib/actions/CameraAction.cpp"
        "./lib/actions/ModelAction.cpp"
        "./lib/actions/ModelsAction.cpp"
        "./lib/actions/SceneAction.cpp"
        "./lib/adapters/camera/TransformCameraAdapter.cpp"
        "./lib/adapters/composite/DrawCompositeAdapter.cpp"
        "./lib/adapters/composite/TransformCompositeAdapter.cpp"
        "./lib/adapters/model/DrawCarcassModelAdapter.cpp"
        "./lib/adapters/model/TransformCarcassModelAdapter.cpp"
        "./lib/drawer/QtDrawer.cpp"
        "./lib/drawer/QtFactory.cpp"
        "./lib/facade/Facade.cpp"
        "./lib/load/builders/camera/CameraBuilder.cpp"
        "./lib/load/builders/model/ModelBuilder.cpp"
        "./lib/load/builders/scene/SceneBuilder.cpp"
        "./lib/load/directors/camera/FileCameraDirector.cpp"
        "./lib/load/directors/model/LoadModelDirector.cpp"
        "./lib/load/directors/scene/FileSceneDirector.cpp"
        "./lib/load/loader/BaseLoader.cpp"
        "./lib/load/loader/FileCarcassModelLoader.cpp"
        "./lib/load/mediators/BaseLoadMediator.cpp"
        "./lib/load/mediators/camera/CameraLoadMediator.cpp"
        "./lib/load/mediators/creators/CameraLoadMediatorCreator.cpp"
        "./lib/load/mediators/creators/ModelLoadMediatorCreator.cpp"
        "./lib/load/mediators/creators/SceneLoadMediatorCreator.cpp"
        "./lib/load/mediators/model/ModelLoadMeditor.cpp"
        "./lib/load/mediators/scene/SceneLoadMediator.cpp"
        "./lib/managers/creators/DrawManagerCreator.cpp"
        "./lib/managers/creators/LoadManagerCreator.cpp"
        "./lib/managers/creators/SceneManagerCreator.cpp"
        "./lib/managers/creators/TransformManagerCreator.cpp"
        "./lib/managers/draw/DrawManager.cpp"
        "./lib/managers/load/LoadManager.cpp"
        "./lib/managers/scene/SceneManager.cpp"
        "./lib/managers/transform/TransformManager.cpp"
        "./lib/matrix/Transformer.cpp"
        "./lib/matrix/errors/errors.cpp"
        "./lib/matrix/matrix/BaseMatrix.cpp"
        "./lib/matrix/matrix/Matrix.hpp"
        "./lib/objects/BaseObject.cpp"
        "./lib/objects/Composite.cpp"
        "./lib/objects/invisibleobject/Camera.cpp"
        "./lib/objects/invisibleobject/InvisibleObject.cpp"
        "./lib/objects/visibleobject/BaseModel.cpp"
        "./lib/objects/visibleobject/VisibleObject.cpp"
        "./lib/objects/visibleobject/carcassmodel/CarcassModel.cpp"
        "./lib/objects/visibleobject/carcassmodel/Edge.cpp"
        "./lib/objects/visibleobject/carcassmodel/Side.cpp"
        "./lib/objects/visibleobject/carcassmodel/Vertex.cpp"
        "./lib/scene/Scene.cpp"
        "./src/main.cpp"
        "./src/mainwindow.cpp"
        "./src/Solver.cpp"
)

add_executable(project
        ${src_files}
)
target_include_directories(project PUBLIC ./lib/actions)
target_include_directories(project PUBLIC ./lib/adapters)
target_include_directories(project PUBLIC ./lib/adapters/camera)
target_include_directories(project PUBLIC ./lib/adapters/composite)
target_include_directories(project PUBLIC ./lib/adapters/model)
target_include_directories(project PUBLIC ./lib/drawer)
target_include_directories(project PUBLIC ./lib/exceptions)
target_include_directories(project PUBLIC ./lib/facade)
target_include_directories(project PUBLIC ./lib/load/builders)
target_include_directories(project PUBLIC ./lib/load/builders/camera)
target_include_directories(project PUBLIC ./lib/load/builders/model)
target_include_directories(project PUBLIC ./lib/load/builders/scene)
target_include_directories(project PUBLIC ./lib/load/directors)
target_include_directories(project PUBLIC ./lib/load/directors/camera)
target_include_directories(project PUBLIC ./lib/load/directors/model)
target_include_directories(project PUBLIC ./lib/load/directors/scene)
target_include_directories(project PUBLIC ./lib/load/loader)
target_include_directories(project PUBLIC ./lib/load/mediators)
target_include_directories(project PUBLIC ./lib/load/mediators/camera)
target_include_directories(project PUBLIC ./lib/load/mediators/creators)
target_include_directories(project PUBLIC ./lib/load/mediators/model)
target_include_directories(project PUBLIC ./lib/load/mediators/scene)
target_include_directories(project PUBLIC ./lib/managers)
target_include_directories(project PUBLIC ./lib/managers/creators)
target_include_directories(project PUBLIC ./lib/managers/draw)
target_include_directories(project PUBLIC ./lib/managers/load)
target_include_directories(project PUBLIC ./lib/managers/scene)
target_include_directories(project PUBLIC ./lib/managers/transform)
target_include_directories(project PUBLIC ./lib/matrix)
target_include_directories(project PUBLIC ./lib/matrix/iterator)
target_include_directories(project PUBLIC ./lib/matrix/matrix)
target_include_directories(project PUBLIC ./lib/objects)
target_include_directories(project PUBLIC ./lib/objects/invisibleobject)
target_include_directories(project PUBLIC ./lib/objects/visibleobject)
target_include_directories(project PUBLIC ./lib/objects/visibleobject/carcassmodel)
target_include_directories(project PUBLIC ./lib/scene)
target_include_directories(project PUBLIC ./src)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

target_link_libraries(project Qt6::Widgets)
target_include_directories(project PUBLIC include)
