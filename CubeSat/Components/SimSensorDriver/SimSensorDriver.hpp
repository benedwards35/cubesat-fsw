// ======================================================================
// \title  SimSensorDriver.hpp
// \author benedwards35
// \brief  hpp file for SimSensorDriver component implementation class
// ======================================================================

#ifndef CubeSat_SimSensorDriver_HPP
#define CubeSat_SimSensorDriver_HPP

#include "CubeSat/Components/SimSensorDriver/SimSensorDriverComponentAc.hpp"

namespace CubeSat {

class SimSensorDriver final : public SimSensorDriverComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct SimSensorDriver object
    SimSensorDriver(const char* const compName  //!< The component name
    );

    //! Destroy SimSensorDriver object
    ~SimSensorDriver();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for run
    //!
    //! Called by the rate group once per cycle to produce a sample
    void run_handler(FwIndexType portNum,  //!< The port number
                     U32 context           //!< The call order
                     ) override;
                     
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! Handler implementation for command FORCE_STALE
    void FORCE_STALE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, bool enable) override;

    //! Handler implementation for command FORCE_OUT_OF_RANGE
    void FORCE_OUT_OF_RANGE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, F32 angle) override;

    //! Handler implementation for command DROP_TELEMETRY
    void DROP_TELEMETRY_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, U32 cycles) override;

    U32 m_tick = 0;
    bool m_sunAngleOutOfRange = false;
    
    bool m_forceStale = false;          //!< Toggle: freeze output at last known values
    bool m_forceOutOfRange = false;     //!< One-shot: override SunAngle on the next cycle
    F32 m_overrideAngle = 0.0f;         //!< Value to report when m_forceOutOfRange is set
    U32 m_dropCyclesRemaining = 0;      //!< Remaining cycles to suppress telemetry output
    F32 m_lastSunAngle = 0.0f;          //!< Held during a stale fault
    F32 m_lastRangeDistance = 0.0f;     //!< Held during a stale fault
};

}  // namespace CubeSat

#endif
