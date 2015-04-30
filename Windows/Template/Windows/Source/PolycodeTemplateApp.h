#ifndef __Polycode_Template__
#define __Polycode_Template__

#include "PolycodeView.h"
#include "Polycode.h"
#include "TavernaMain.h"

using namespace Polycode;

class PolycodeTemplateApp {
public:
   PolycodeTemplateApp(PolycodeView *view);
   ~PolycodeTemplateApp();
   
   bool Update();
   TavernaMain *game;
   Core *core;

};

#endif