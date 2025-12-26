/*
MIT License

Copyright (c) 2025 Fabrizio Morciano

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <iostream>
#include <ostream>
#include <GL/glut.h>

#include <Inventor/SoSceneManager.h>

#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/engines/SoElapsedTime.h>
#include <Inventor/nodes/SoRotationXYZ.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoCube.h>

SoSeparator *createScene();

void idle();

void reshape(int w, int h);

void display();

void redraw(void *user, SoSceneManager *manager);

SoSceneManager *sceneManager=nullptr;
SoRotationXYZ *rotation = nullptr;
float angle = 0.0;

SoSeparator *createScene() {
    auto root = new SoSeparator;
    root->ref();

    SoRotationXYZ *globalRotXYZ = new SoRotationXYZ;
    globalRotXYZ->axis = SoRotationXYZ::X;
    globalRotXYZ->angle = M_PI / 9;
    root->addChild(globalRotXYZ);

    // Set up the globe transformations
    rotation = new SoRotationXYZ;
    root->addChild(rotation);
    rotation->angle = 0.0;
    rotation->axis = SoRotationXYZ::Y; // rotate about Y axis

    root->addChild(new SoCube);
    root->unrefNoDelete();
    return root;
}


int main(int argc, char **argv) {
    // Initialize the Open Inventor Database
    SoDB::init();

    // print Inventor's version on the console
    std::cout<<"Open Inventor version: "<<SoDB::getVersion()<<std::endl;

    // initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    // initialize sceneManager
    sceneManager = new SoSceneManager;

    auto root = new SoSeparator;
    root->ref();

    // add a camera to the graph
    auto perspCamera = new SoPerspectiveCamera;
    root->addChild(perspCamera);

    //add a light
    root->addChild(new SoDirectionalLight);
    // finally add our scene by calling createScene()
    root->addChild(createScene());

    // set render action for sceneManager
    sceneManager->setRenderCallback(redraw, nullptr);
    // set a background color BLACK
    sceneManager->setBackgroundColor(SbColor(0.0, 0.0, 0.0));
    // sceneManager needs to be activated for rendering a scene
    sceneManager->activate();

    // Pass the scene graph to sceneManager
    sceneManager->setSceneGraph(root);

    // view the whole scene
    perspCamera->viewAll(root, sceneManager->getViewportRegion());

    glutInitWindowSize(400, 400);
    SbString title("Open Inventor Tutorial : SoSceneManager");
    glutCreateWindow(title.getString());
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();

    root->unref();
    delete sceneManager;

    return (0);
}

void redraw(void *user, SoSceneManager *manager) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    sceneManager->render();

    glutSwapBuffers();
}


// Redraw on expose events.
void display()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    sceneManager->render();

    glutSwapBuffers();
}

// Reconfigure on changes to window dimensions.
void reshape(int w, int h)
{
    sceneManager->setWindowSize(SbVec2s(w, h));
    sceneManager->setSize(SbVec2s(w, h));
    sceneManager->setViewportRegion(SbViewportRegion(w, h));
    sceneManager->scheduleRedraw();
}

// update event
void idle()
{
    if (rotation) {
        angle += 0.01;
        rotation->angle = angle;
    }
    SoDB::getSensorManager()->processTimerQueue();
    SoDB::getSensorManager()->processDelayQueue(TRUE);
}