#include "PolycodeTemplateApp.h"

/**
 * Mandatory windowing class.  Holds the single Update method.
 * This class should only handle core creation, as it is platform specific.
 */
PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) {
   
   //Core (int xRes, int yRes, bool fullScreen, bool vSync, int aaLevel, int anisotropyLevel, int frameRate, int monitorIndex)
   core = new CocoaCore(view, 1280,720,false,true, 0,0, 60);
   
   //set up the game using a non platform specific file
   game = new TavernaMain(core);
}

bool PolycodeTemplateApp::Update() {
   game->Update();
   return core->updateAndRender();
}

