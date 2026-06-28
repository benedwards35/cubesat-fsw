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

    // Fault: drop telemetry entirely for N cycles
    if (this->m_dropCyclesRemaining > 0) {
        this->m_dropCyclesRemaining--;
        return;
    }

    F32 sunAngle;
    F32 rangeDistance;

    if (this->m_forceStale) {
        // Fault: freeze output at last known values
        sunAngle = this->m_lastSunAngle;
        rangeDistance = this->m_lastRangeDistance;
    } else {
        // Synthetic sun-sensor ramp, 0-359 deg, wraps every 360 ticks
        sunAngle = static_cast<F32>(this->m_tick % 360);
        // Synthetic range-sensor countdown, 500-0 m, wraps every 500 ticks
        rangeDistance = 500.0f - static_cast<F32>(this->m_tick % 500);
    }

    // Fault: one-shot out-of-range override, independent of the ramp
    if (this->m_forceOutOfRange) {
        sunAngle = this->m_overrideAngle;
        this->m_forceOutOfRange = false;
    }

    this->m_lastSunAngle = sunAngle;
    this->m_lastRangeDistance = rangeDistance;

    this->tlmWrite_SunAngle(sunAngle);
    this->tlmWrite_RangeDistance(rangeDistance);

    // Raise the event only on the transition into out-of-range
    bool isOutOfRange = (sunAngle > SUN_ANGLE_THRESHOLD_DEG);
    if (isOutOfRange && !this->m_sunAngleOutOfRange) {
        this->log_WARNING_HI_SunAngleOutOfRange(sunAngle);
    }
    this->m_sunAngleOutOfRange = isOutOfRange;
}

void SimSensorDriver ::FORCE_STALE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, bool enable) {
    this->m_forceStale = enable;
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void SimSensorDriver ::FORCE_OUT_OF_RANGE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, F32 angle) {
    this->m_forceOutOfRange = true;
    this->m_overrideAngle = angle;
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void SimSensorDriver ::DROP_TELEMETRY_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, U32 cycles) {
    this->m_dropCyclesRemaining = cycles;
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace CubeSat
