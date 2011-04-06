{{
FILE NAME: mikerobot.spin
DESCRIPTION:
  This SPIN code is to control two DC motors on MikeRobot autonomous vehicle. Each vloop
  is driven by an IFI Victor 883 Speed Controller. The DC motors are equipped with
  incremental 200cpi optical encoders (16,000 ticks/tire rev) and their readings are used
   

  The Propeller MCU communicates with the on-board main PC via Serial Port. All the
  communication is ASCII based and in principal the MCU responds to a command from the PC.
  The only exception is "?B" message which the MCU periodically transmits the optical
  encoder readings to the PC when the mode is enabled by the PC with "!B" command.

  Pin Connections
  ---------------
  P0 - COM tx?
  P1 - COM rx?
  P2 - Right Victor RC PWM
  P3 - Left Victor RC PWM
  P4 - Right Encoder Ch. A
  P5 - Right Encoder Ch. B
  P6 - Left Encoder Ch. A
  P7 - Left Encoder Ch. B
  P8 - Victor Brake (connected to both units)
  P9 - Emergency Botton         
  
  SET Command summary
  ---------------
  !A
  !B - turn on/off encoder monitoring (with period in MCU ticks)
  !C - reset encoder position counters
  !D
  !E - xxx
  !F - reset PID states
  !G - set PID controller parameters (Kp,Ki,Kv,& Q)
  !H 
  !I
  !J
  !K
  !L
  !M - set operation mode (0-Open Loop,1-Velocity Loop,2-Position Loop)
  !N
  !O
  !P - set relative RC PWM pulse width in us (only relevant when mode=0)
  !Q - set RC PWM pulse width via raw command (only relevant when mode=0)
  !R - reset the MCU state
  !S
  !T - set loop update period (in ticks)
  !U
  !V - set short loop commands (for velocity loop)
  !W - set long loop commands (for position loop)
  !X
  !Y
  !Z

  GET Command summary
  ---------------
  ?A
  ?B - periodic encoder broadcast (only MCU->PC)
  ?C - xxx
  ?D
  ?E - get encoder values
  ?F
  ?G - get PID controller parameters (Kp,Ki,Kv,& Q)
  ?H
  ?I
  ?J
  ?K
  ?L
  ?M - get operation mode (0-Open Loop,1-Velocity Loop,2-Position Loop)
  ?N
  ?O
  ?P - get relative RC PWM pulse width in us
  ?Q - get raw command values
  ?R - xxx
  ?S
  ?T - get loop update period (in ticks)
  ?U
  ?V - get short loop commands (for velocity loop)
  ?W - get long loop commands (for position loop)
  ?X
  ?Y
  ?Z

  COG Assignments
  ---------------
  0. MCU Initializer (terminates when complete)
  1. Serial Messaging Process
  2. Encoder Monitoring Process
  3. Velocity Loop Process
  4. Serial Port Driver (for both rx and tx)
  5. Victor Speed Controller Driver (generates RC PWM signals)
  6. Optical Encoder Driver (keeps up with ticks of encoders) 
  
DEPENDS ON:

  Victor_Velocity_Loop.spin
  
  <from Propeller Object Exchange: http://obex.parallax.com/>
  
  Victor_Speed_Controller.spin
  Quadrature_Encoder.spin
  FullDuplexSerial.spin  
          
}}

CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

  com_brate = 115_200           ' COM port baud rate
  msg_maxlen = 65               ' max length of COM message                                                                                
  ch_lf = 10                    ' <LF> character: Use 10 for serial_scip or 13 if testing with gtkterm
  'ch_lf = 13                    ' <LF> character: Use 10 for serial_scip or 13 if testing with gtkterm

OBJ
  serial : "FullDuplexSerial"
  victor : "DutyCycle"
  encoder: "Quadrature_Encoder"

  ploop: "Victor_Position_Loop"
  vloop: "Victor_Velocity_Loop"

VAR
  long encvals[2]     ' captured encoder values for ?B message
  long pos[2]         ' encoder position array
  long pulse[4]       ' PWM pulse width control register array {PHSA, PHSB, CTRA, CTRB}
  long cmd[2]         ' Velocity/Position Commands
  long ctr[2]
  byte bcast          ' true if encoder monitoring is on
  long period         ' encoder monitoring period
  byte ready          ' true if new encoder reading is ready

  byte mode           ' mode of operation: 0 open-loop, 1 closed-loop  
  byte input[msg_maxlen+1]      ' COM message string

  long cog
  long stack[30]
  
PUB Begin

  vloop.init(@pos,@cmd,@pulse)
  ploop.init(@pos,@cmd,@pulse)

  victor.setDuty(0, 0, @pulse)
  longfill(@cmd,0,2)   
  
  cog := false
  bcast := false
  ready := false
  period := 80_000_000
   
  serial.start(31, 30, 0, com_brate)
  victor.start(@pulse)
  encoder.start(4, 2, 0, @pos)

  ' Start Serial Message Process on this cog
  SerialMessageProc
   
PUB StartIP:pass ' start the loop update
  return (cog := cognew(IntervalProc, @stack) + 1) > 0


PUB StopIP  ' stop the loop update
  if cog
    cogstop(cog~-1)

Pub IntervalProc|cnt0

  cnt0 := cnt                              ' Mark current cnt

  repeat
    longmove(@encvals,@pos,2)   ' copy current encoder positions
    ready := true               ' flag SMP to output
    
    cnt0 += period              ' get end time of current period
    waitcnt(cnt0)
       
PUB SerialMessageProc | count, temp[4], status

  repeat
     {Check for the existence of a character in the rx buffer (without waiting)}
    input[0] := serial.rxcheck

    {If found, RX next command and process it}
    ifnot input[0] == 255 ' new message is in

      ' Receive the rest of the message       
      count := 0  ' index to the input array
      repeat until input[count] == ch_lf OR count == msg_maxlen
        input[++count] := serial.rx
      input[++count] := 0       '' string termination character

      ' Echo received message
      serial.str(@input)          

      status :=  "0"  '=valid command

      ' Parse command & process it
      case input[0]
        "!":  ' set commands       
          case input[1]
            "B":  'set encoder monitoring: !B########<LF> period in ticks 
              if count == 11
                if Str2Long(@temp[0], @input[2], 8)
                  if temp[0]==0
                    bcast := 0
                    StopIP      ' terminate if IntervalProc is running 
                  else
                    period := temp[0] 
                    ifnot cog           ' if already running, just update the period
                      bcast := 1
                      StartIP     ' start IntervalProc 
                else
                  status :=  "2"                        ' invalid numeric string                                                                                                
              else
                status :=  "1"                          ' invalid messag length
              'end if count == 11
              
            "C":  'clear encoder counter: !C<LF>
              if count==3
                longfill(@pos,0,2)
              else
                status :=  "1"
              'end if count==3
              
            "F":  'reset PID states: !FC<LF>
              if count==4
                if input[2]=="V"
                  vloop.resetStates
                elseif input[2]=="P"
                  ploop.resetStates
                else
                  status :=  "2"  ' invalid loop type
              else
                status :=  "1"    ' invalid message length
              'end if count==3
              
            "G":  'set control loop gains: !GCXXXXXXXXYYYYYYYYZZZZZZZZWW<LF>
              if count == 30
                if Str2Long(@temp[0], @input[3], 8) AND Str2Long(@temp[1],@input[11],8) AND Str2Long(@temp[2], @input[19],8) AND Str2Long(@temp[3],@input[27],2)               
                  if input[2]=="V" 
                    vloop.setGains(@temp[0],temp[3])            ' set PID gains & shift
                  elseif input[2]=="P" 
                    ploop.setGains(@temp[0],temp[3])            ' set PID gains & shift
                  else
                    status :=  "3"                      ' invalid loop type
                else
                  status :=  "2"                        ' invalid numeric string                           
              else
                status :=  "1"                          ' invalid message length
              'end if count == 29

            "M":  'set operating mode: !M#<LF>
              if count == 4
                if input[2]=="0"                      ' OPEN-LOOP 
                  if mode==1                          ' if vloop or ploop is active, terminate
                    vloop.stop
                  elseif mode==2
                    ploop.stop
                  mode := 0          
                elseif input[2]=="1"                  ' VELOCITY LOOP
                  if mode==2                        ' stop position loop if running
                    ploop.stop
                  if (vloop.start==true)            ' start velocity loop 
                    mode := 1
                  else
                    mode := 0
                    status :=  "3"                    ' velocity loop failed to start
                elseif input[2]=="2"                  ' POSITION LOOP
                  if mode==1                        ' stop velocity loop if running
                    vloop.stop
                  if (ploop.start==true) 
                    mode := 2
                  else
                    mode := 0
                    status :=  "3"                    ' failed to start position loop
                else
                    status :=  "2"                        ' invalid mode value                           
              else
                status :=  "1"                          ' invalid message length
              'end if count == 4

            "P": 'set pulse width: !PXXXXYYYY<LF>   
              if count == 11
                if Str2Long(@temp[0], @input[2], 4) AND Str2Long(@temp[1],@input[6],4)
                  
                  temp[0] -= 1500
                  temp[1] -= 1500
                  if temp[0] =< 500 AND temp[0] => -500 AND temp[1] =< 500 AND temp[1] => -500
                    victor.setDuty(temp[0], temp[1], @pulse)
                                                        ' set PWM pulse widths
                  else                      
                    status :=  "3"                      ' data out of range
                else
                  status :=  "2"                        ' invalid numeric string                           
              else
                status :=  "1"                          ' invalid message length
              'end if count == 11
              
            "Q": 'set raw command: !QCXXDYY<LF>
              if count == 9
                if (input[2]=="+" OR input[2]=="-") AND Str2Long(@temp[0], @input[3], 2) AND (input[5]=="+" OR input[5]=="-") AND Str2Long(@temp[1],@input[6],2)
                  if temp[0] =< 78 AND temp[1] =< 78
                    ' adjust sign
                    if (input[2]=="-")
                      temp[0]*=-1
                    if (input[5]=="-")
                      temp[1]*=-1
                    ' convert to RC PWM pulse-widths
                    temp[0] := vloop.cmd2pwm(temp[0],0)
                    temp[1] := vloop.cmd2pwm(temp[1],1)                 
                    victor.setDuty(temp[0], temp[1], @pulse) ' set PWM pulse widths
                  else                      
                    status :=  "3"                      ' data out of range
                else
                  status :=  "2"                        ' invalid numeric string                           
              else
                status :=  "1"                          ' invalid message length
              'end if count == 9

            "R":  'reset MCU: !R<LF>
              if count==3       
                ' turn off the PID controller (open the loop)
                if mode==1
                  vloop.stop
                elseif mode==2
                  ploop.stop
                mode := 0

                ' stop the motors 
                longfill(@cmd[0],0,2)
                victor.setDuty(0, 0, @pulse)

                ' stop encoder monitoring
                bcast := false
                StopIP      ' terminate if IntervalProc is running 
              else
                status :=  "1"                            ' invalid messge length
              'end if count==3
              
            "T":  'set loop period: !TC########<LF>
              if count == 12
                if Str2Long(@temp[0], @input[3], 8)
                  if input[2]=="V"
                    vloop.setPeriod(temp[0])
                  elseif input[2]=="P"
                    ploop.setPeriod(temp[0])
                  else
                    status :=  "3"                      ' invalid loop type
                else
                  status :=  "2"                        ' invalid numeric string                                                                                                
              else
                status :=  "1"                          ' invalid messag length
              'end if count == 11
              
            "V":  'set loop command: !VCXXXXDYYYY<LF>
              if count == 13
                if (input[2]=="+" OR input[2]=="-") AND Str2Long(@temp[0], @input[3], 4) AND (input[7]=="+" OR input[7]=="-") AND Str2Long(@temp[1],@input[8],4)
               
                  ' adjust sign
                  if (input[2]=="-")
                    temp[0]*=-1
                  if (input[7]=="-")
                    temp[1]*=-1
                    
                  longmove(@cmd[0],@temp[0],2)            ' set PWM pulse widths
                else
                  status :=  "2"                        ' invalid numeric string                           
              else
                status :=  "1"                          ' invalid message length
              'end if count == 13

            "W":  'set long loop command: !WXXXXXXXXYYYYYYYY<LF>
              if count == 19
                if Str2Hex(@temp[0], @input[2]) AND Str2Hex(@temp[1],@input[10])
                  longmove(@cmd[0],@temp[0],2)            ' set loop commands
                else
                  status :=  "2"                        ' invalid numeric string
              else
                status :=  "1"                          ' invalid message length
              'end if count == 19

          'end case input[1]
          
        "?":  ' GET MESSAGES
          case input[1]
            "E":  'get curernt encoder positions
              if count==3
                serial.tx("0")      ' command length
                serial.tx(ch_lf)      ' to terminate the response reply block
                serial.hex(pos[0], 8)
                serial.tx(ch_lf)
                serial.hex(pos[1], 8)
                status :=  -1
              else
                status :=  "1"      ' invalid length
                                 
            "G":  'get control loop gains: ?GC<LF>R<LF>XXXXXXXX<LF>YYYYYYYY<LF>ZZZZZZZZ<LF>WW<LF><LF>
              if count==4
                if input[2]=="V"
                  vloop.getGains(@temp[0],@temp[3])
                elseif input[2]=="P"
                  ploop.getGains(@temp[0],@temp[3])
                else
                  status :=  "2"                 

                if status == "0"
                  serial.tx("0")      ' command length
                  serial.tx(ch_lf)      ' to terminate the response reply block
                   
                  serial.dec(temp[0])
                  serial.tx(ch_lf)
                  serial.dec(temp[1])
                  serial.tx(ch_lf)
                  serial.dec(temp[2])
                  serial.tx(ch_lf)
                  serial.dec(temp[3])
                  status :=  -1
                'end if status := = "0"
              else
                status :=  "1"                            ' invalid length
            "M":  'get operating mode: ?M<LF>R<LF>#<LF>
              if count==3
                serial.tx("0")      ' command length
                serial.tx(ch_lf)      ' to terminate the response reply block
                serial.dec(mode)
                status :=  -1
              else
                status :=  "1"                            ' invalid length
            "P": 'get pulse width: ?P<LF>R<LF>XXXXYYYY<LF>
              if count==3
                serial.tx("0")      ' command length
                serial.tx(ch_lf)      ' to terminate the response reply block
                serial.dec(pulse[0]+1500)
                serial.tx(ch_lf)
                serial.dec(pulse[1]+1500)
                status :=  -1
              else
                status :=  "1"                            ' invalid length
            "T":  'get control loop period: ?TC<LF>R<LF>########<LF>
              if count==4
                if input[2]=="V"
                  vloop.getPeriod(@temp[0])
                elseif input[2]=="P"
                  ploop.getPeriod(@temp[0])
                else
                  status :=  "2"                          ' invalid loop type

                if status=="0"                 
                  serial.tx("0")      ' command length
                  serial.tx(ch_lf)      ' to terminate the response reply block
                  serial.dec(temp[0])
                  status :=  -1
              else
                status :=  "1"                            ' invalid length
                
            "V":  'get loop command: ?V<LF>R<LF>CXXXX<LF>DYYYY<LF>
              if count==3
                serial.tx("0")      ' command length
                serial.tx(ch_lf)      ' to terminate the response reply block
                serial.dec(cmd[0])
                serial.tx(ch_lf)
                serial.dec(cmd[1])
                status :=  -1
              else
                status := "1"
          ' end case input[1]

            "W":  'get long loop command: ?V<LF>R<LF>XXXXXXXX<LF>YYYYYYYY<LF>
              if count==3
                serial.tx("0")      ' command length
                serial.tx(ch_lf)      ' to terminate the response reply block
                serial.hex(cmd[0],8)
                serial.tx(ch_lf)
                serial.hex(cmd[1],8)
                status :=  -1
              else
                status := "1"
           
      'end case input[0]

      if status<>-1             ' if status not sent yet, do so
        serial.tx(status)
      serial.tx(ch_lf)
      serial.tx(ch_lf)          ' empty message block
    'end ifnot char== 255

    {TX encoder position values if encoder monitoring is ON}
    if bcast AND ready  '?B<LF>{RENC####}<LF>{LENC####}<LF><LF>
      serial.tx("?")
      serial.tx("B")
      serial.tx(ch_lf)
      serial.hex(encvals[0], 8)
      serial.tx(ch_lf)
      serial.hex(encvals[1], 8)
      serial.tx(ch_lf)
      serial.tx(ch_lf)
      ready := false
    'end if bcase AND ready
  'end repeat

PRI STR2LONG(valptr,strptr,N)|mult,i
{Converts a positive decimal string to long integer}

  ' get the multiplier for the first digit
  mult := 1
  i := 1
  repeat until i == N
    mult *= 10
    i++
   
  ' build val
  long[valptr] := 0
  i := 0
  repeat until i == N
  
    ' if character is not numeric, exit
    if byte[strptr+i] < "0" or byte[strptr+i] > "9"
      return false

    long[valptr] += (byte[strptr+(i++)]-48)*mult
    mult /= 10

  return true

PRI STR2HEX(valptr,strptr)|mult,i
{Converts a 8-digit hex string to long integer}
  ' initialize
   
  mult := $1000_0000
  i := 0
  repeat until i == 8
          long[valptr] += lookdownz(byte[strptr+(i++)]: "0".."9","A".."F") << mult
          mult ~>= 4
   
  return true