// ======================================================================
// \title  SimSensorDriver.cpp
// \author benedwards35
// \brief  cpp file for SimSensorDriver component implementation class
// ======================================================================

#include "CubeSat/Components/SimSensorDriver/SimSensorDriver.hpp"

namespace CubeSat {

namespace {
    constexpr F32 SUN_ANGLE_THRESHOLD_DEG = 150.0f;  //!< Upper bound of valid sun-angle range
}

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

       // Synthetic sun-sensor ramp, 0-359 deg, wraps every 360 ticks
       F32 sunAngle = static_cast<F32>(this->m_tick % 360);
       this->tlmWrite_SunAngle(sunAngle);

       // Synthetic range-sensor countdown, 500-0 m, wraps every 500 ticks
       F32 rangeDistance = 500.0f - static_cast<F32>(this->m_tick % 500);
       this->tlmWrite_RangeDistance(rangeDistance);

       // Raise the event only on the transition into out-of-range
       bool isOutOfRange = (sunAngle > SUN_ANGLE_THRESHOLD_DEG);
       if (isOutOfRange && !this->m_sunAngleOutOfRange) {
           this->log_WARNING_HI_SunAngleOutOfRange(sunAngle);
       }
       this->m_sunAngleOutOfRange = isOutOfRange;
   }

}  // namespace CubeSat
