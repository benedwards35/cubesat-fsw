module CubeSat {
    @ Synthetic sensor data generator driven by a rate group
    passive component SimSensorDriver {

        @ Called by the rate group once per cycle to produce a sample
        sync input port run: Svc.Sched

        @ Synthetic sun-sensor angle in degrees
        telemetry SunAngle: F32

        @ Synthetic range-to-target distance in meters
        telemetry RangeDistance: F32

        @ Raised once when SunAngle crosses above its valid upper bound
        event SunAngleOutOfRange(
                                  angle: F32 @< Sun angle at the moment of the crossing
                                ) \
          severity warning high \
          format "Sun angle out of range: {f} deg"

        @ Force telemetry to stop updating (simulate a stuck/stale sensor)
        sync command FORCE_STALE(
            enable: bool @< True = freeze output at current values, false = resume normal updates
        )

        @ Force SunAngle to a specific value immediately, independent of the ramp
        sync command FORCE_OUT_OF_RANGE(
            angle: F32 @< Value to report immediately, overriding the ramp signal
        )

        @ Suppress telemetry output entirely for N rate-group cycles, then resume automatically
        sync command DROP_TELEMETRY(
            cycles: U32 @< Number of cycles to drop telemetry for
        )

        @ Command receive
        command recv port cmdIn

        @ Command registration
        command reg port cmdRegOut

        @ Command response
        command resp port cmdResponseOut

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Enables telemetry channels handling
        import Fw.Channel

        @ Enables event (log) handling
        import Fw.Event

    }
}