#include <string>

#include <math.h>
#include <rtxi/widgets.hpp>


// This is an generated header file. You may change the namespace, but 
// make sure to do the same in implementation (.cpp) file
namespace AM_SigGen
{

constexpr std::string_view MODULE_NAME = "AM Signal Generator";

enum PARAMETER : Widgets::Variable::Id
{
    // set parameter ids here
//  CARRIER_FREQUENCY=0,
//  CARRIER_AMPLITUDE,
    AM_OFFSET
};

inline  std::vector<Widgets::Variable::Info> get_default_vars() 
{
  return {
//    {
//      CARRIER_FREQUENCY,
//      "Carrier Frequency (Hz)",
//      "Frequency of the carrier signal for the output amplitude-modulated signal",     
//      Widgets::Variable::DOUBLE_PARAMETER,
//      double{10.0}
//    },
//    {
//      CARRIER_AMPLITUDE,
//      "Carrier Amplitude",
//      "Amplitude of carrier signal for the output amplitude-modulated signal",
//      Widgets::Variable::DOUBLE_PARAMETER,
//      double{2.0}
//    },
      {
        AM_OFFSET,
        "AM Signal Offset (s)",
        "Time offset for the output amplitude-modulated signal",
        Widgets::Variable::DOUBLE_PARAMETER,
        double{0.0}
      },
  };
}

inline std::vector<IO::channel_t> get_default_channels()
{
  return {
    {"Carrier Signal", "Carrier signal to be modulated", IO::INPUT},
    {"Message Signal", "Signal to modulate carrier signal", IO::INPUT}, 
    {"Amplitude-Modulated Signal", "Carrier modulated by message, plus offset", IO::OUTPUT}  
  };
}

class Panel : public Widgets::Panel
{
  Q_OBJECT
public:
  Panel(QMainWindow* main_window, Event::Manager* ev_manager);
};

class Component : public Widgets::Component
{
public:
  explicit Component(Widgets::Plugin* hplugin);
  void execute() override;
};

class Plugin : public Widgets::Plugin
{
public:
  explicit Plugin(Event::Manager* ev_manager);
};

}  // namespace AM_SigGen
