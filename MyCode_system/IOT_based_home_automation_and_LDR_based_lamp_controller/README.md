IoT Based Home Automation

Introduction :
              In this project I am controlling four AC loads(here I am using lamp) using open source application.

Application working mode:

	  1. IoT Mode: In that when you set IoT mode using application then you can control or monitor AC load position (ON/OFF).
        2. LDR Mode: In LDR mode you can not control AC load using application but AC load working on LDR sensor.

Circuit Diagram pin connection:

        Please follow NodeMCU (12E) pin instruction
        pinMode(0, INPUT);      /* IR sensor     nodemcu pin D3   */
        pinMode(1, OUTPUT);     /* buzzer        nodemcu pin TX   */
        pinMode(2, OUTPUT);     /* relay1        nodemcu pin D4   */
        pinMode(3, OUTPUT);     /* relay2        nodemcu pin RX   */
        pinMode(4, OUTPUT);     /* relay3        nodemcu pin D2   */
        pinMode(5, OUTPUT);     /* relay4        nodemcu pin D1   */
        pinMode(A0, INPUT);     /* LPS Sensor    nodemcu pin A0   */

Components:

        NodeMCU board
        MQ9 LPG sensor module
        LDR light detect sensor module
        4-channel relay module
Flow:

        1. Open applicatio and then Connect power to board
        2. if Status icon is blue then go forward
        3. set device in IoT mode
        4. Controll and monitor using switch led mode on application icon
        
wifi config:

         Set user id and password in source code. 

Application:


       if you don't know about IoTMQTTPanel app then visit below lonk first
       Add 6 switch in app panel and give payload as mention in bellow.
       
       
        switch_device Topic name     Publis       Subscibe      on_payloa     off_payload
        relay-1                      Led1outo7    Led1in07         1             0       
        relay-2                      Led2outo7    Led2in07         3             2
        relay-3                      Led3outo7    Led3in07         5             4
        relay-4                      Led4outo7    Led4in07         7             6
        Device Status                07connectledtdemo             8             9
        IOT/ LDR mode                Ledout07_automanul            A             B


