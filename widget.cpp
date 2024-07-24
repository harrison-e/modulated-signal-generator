#include <QTimer>
#include <math.h>

#include "widget.hpp"

AM_SigGen::Plugin::Plugin(Event::Manager* ev_manager)
    : Widgets::Plugin(ev_manager, std::string(AM_SigGen::MODULE_NAME))
{
}

AM_SigGen::Panel::Panel(QMainWindow* main_window, Event::Manager* ev_manager)
    : Widgets::Panel(std::string(AM_SigGen::MODULE_NAME), main_window, ev_manager)
{
  setWhatsThis("FM-TACS Signal Generator");
  createGUI(AM_SigGen::get_default_vars(), {});  // this is required to create the GUI
  refresh();
  QTimer::singleShot(0, this, SLOT(resizeMe()));
}

AM_SigGen::Component::Component(Widgets::Plugin* hplugin)
    : Widgets::Component(hplugin,
                         std::string(AM_SigGen::MODULE_NAME),
                         AM_SigGen::get_default_channels(),
                         AM_SigGen::get_default_vars())
{
}

void AM_SigGen::Component::execute()
{
  switch (this->getState()) {
    case RT::State::EXEC:
      writeoutput(0, readinput(0) * readinput(1));
      break;
    case RT::State::INIT:
      this->setState(RT::State::EXEC);
      break;
    case RT::State::MODIFY:
      this->setState(RT::State::EXEC);  // for debug
      break;
    case RT::State::PERIOD:
      break;
    case RT::State::PAUSE:
      writeoutput(0, 0);
      break;
    case RT::State::UNPAUSE:
      this->setState(RT::State::EXEC);
      break;
    default:
      break;
  }
}


///////// DO NOT MODIFY BELOW //////////
// The exception is if your plugin is not going to need real-time functionality. 
// For this case just replace the craeteRTXIComponent return type to nullptr. RTXI
// will automatically handle that case and won't attach a component to the real
// time thread for your plugin.

std::unique_ptr<Widgets::Plugin> createRTXIPlugin(Event::Manager* ev_manager)
{
  return std::make_unique<AM_SigGen::Plugin>(ev_manager);
}

Widgets::Panel* createRTXIPanel(QMainWindow* main_window,
                                Event::Manager* ev_manager)
{
  return new AM_SigGen::Panel(main_window, ev_manager);
}

std::unique_ptr<Widgets::Component> createRTXIComponent(
    Widgets::Plugin* host_plugin)
{
  return std::make_unique<AM_SigGen::Component>(host_plugin);
}

Widgets::FactoryMethods fact;

extern "C"
{
Widgets::FactoryMethods* getFactories()
{
  fact.createPanel = &createRTXIPanel;
  fact.createComponent = &createRTXIComponent;
  fact.createPlugin = &createRTXIPlugin;
  return &fact;
}
};

//////////// END //////////////////////
