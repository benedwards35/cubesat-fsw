// ======================================================================
// \title  SimSensorDriver.cpp
// \author benedwards35
// \brief  cpp file for SimSensorDriver component implementation class
// ======================================================================

#include "CubeSat/Components/SimSensorDriver/SimSensorDriver.hpp"

namespace CubeSat {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

SimSensorDriver ::SimSensorDriver(const char* const compName) : SimSensorDriverComponentBase(compName) {}

SimSensorDriver ::~SimSensorDriver() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

   void SimSensorDriver ::run_handler(FwIndexType portNum, U32 context) {
       this->m_tick++;
       F32 sunAngle = static_cast<F32>(this->m_tick % 360);
       this->tlmWrite_SunAngle(sunAngle);
   }

}  // namespace CubeSat
