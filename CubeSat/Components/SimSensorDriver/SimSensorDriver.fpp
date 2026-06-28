module CubeSat {
    @ Synthetic sensor data generator driven by a rate group
    passive component SimSensorDriver {

        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################
        
        @ Called by the rate group once per cycle to produce a sample
        sync input port run: Svc.Sched

        @ Synthetic sun-sensor angle in degrees
        telemetry SunAngle: F32

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Enables telemetry channels handling
        import Fw.Channel

    }
}