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