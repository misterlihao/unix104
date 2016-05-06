###plugin architecture
  
events are delivered along with a EventData \*data  
insert any needed variables into data.field[xxx]  
  
event data for each event should be *invariant*
  
###plugin interface
all plugins are placed in indivdual directory under plugin/  
and need to offer following files
-   impl.cpp: implementation.
-   headr.h : header.
-   evnt.inc: declare new events the plugin offers.  
    ```
    EVENT_XXXX
    ```  
    no space, no indent.
-   clbk.inc: declare callbacks here  
    ```
    EVENT_XXXX, the_callback_func
    ```  
    comma seperated, arbitrary spaces are permitted.

###generated files
- plugin\_headers.h:  not willing to be included except in main.cpp
- events.h:           header for event definions
- register\_\*.inc:   insert plugin registering codes to main.cpp

###'essential' plugin
not a real plugin, just offer essential events
