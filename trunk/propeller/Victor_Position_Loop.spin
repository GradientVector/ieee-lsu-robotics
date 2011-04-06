CON
  maxFwOUT = 73
  minFwOUT = 6
  minRvOUT = -6
  maxRvOUT = -68
   
  ' "Raw PID Command" to RC PWM Pulse Width Conversion
  cmd2pw = 420642
  q1 = 16
   
VAR
  long INptr            'address to the velocity feedback [left,right]
  long CMDptr           'address to the velocity command [left,right]
  long OUTptr           'address to the output (input to Victor) [left right], range:: -47:47 ??
  long T                'control loop update period 
  long K[3]             'address to the PID gains [Kp_l Ki_l Kd_l Kp_r Ki_r Kd_r]
  long z[4]             'memory for I & D
  long q                'gain binary point offset                                                                      
   
  long cog
  long stack[64]
   
PUB init(feedback,command,output)
 ''Initializes PID controller
''  feedback = Address of long variable array holding differential encoder feedbacks
''  command  = Address of long variable array holding differential encoder commands
''  output   = Address of long variable array holding output to PWM 
 
  INptr := feedback
  CMDptr := command
  OUTptr := output
   
  K[0] := 0  '=0.09
  K[1] := 0  '=0.02
  K[2] := 0  '=0.1
  q := 16
  T := 800_000

  longfill(@z,0,6)
  
  cog := 0

PUB resetStates
  longfill(@z,0,6)
  z[0] := long[INptr][0] 
  z[3] := long[INptr][1]

PUB setPeriod(newT)
  T := newT

PUB getPeriod(Tptr)
  long[Tptr] := T
   
PUB setGains(Kptr,newQ)
  longmove(@K,Kptr,3)
  q := newQ

PUB getGains(outKptr,outQptr)
  longmove(outKptr,@K,3)
  long[outQptr] := q

PUB cmd2pwm(cmd):pwm
'' Converts PID command (-68:73) to RC PWM pulse-width
'' by multiplying it by 6.4185 (cmd2pw*2^-q1)
  pwm := cmd * cmd2pw
  pwm ~>= q1  

PUB start:pass ' start the loop update

  ' if already running, do nothing
  if cog
    return true
    
  resetStates

  return (cog := cognew(update, @stack) + 1) > 0


PUB stop  ' stop the loop update
  if cog   
    cogstop(cog~-1)

PRI update | cnt0, motor,vel,e,out[2]

  cnt0 := cnt

  repeat
    ''Calculate PID controller output
    repeat motor from 0 to 1
      e := long[CMDptr][motor] - long[INptr][motor]       ' error signal
      out[motor] := K[0] * e                     ' proportional
      z[3*motor] += K[1] * e
      out[motor] += z[3*motor]          ' integral
      out[motor] += K[2] * (e-z[3*motor+1])    ' differential
      z[3*motor+1] := e
     
      out[motor] ~>= q                  ' remove the gain offset
     
      ' convert command to RC PWM pulse-width
      out[motor] := cmd2pwm(out[motor])    
    'end repeat motor
     
    ' copy the resulting PWM pulse-widths  
    longmove(OUTptr,@out,2)

    ' wait til the end of the interval
    cnt0 += T
    waitcnt(cnt0)
  'end repeat
  