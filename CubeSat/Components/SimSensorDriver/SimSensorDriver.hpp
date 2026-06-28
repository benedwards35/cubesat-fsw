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

    U32 m_tick = 0;  //!< Rate group tick counter
};

}  // namespace CubeSat

#endif
