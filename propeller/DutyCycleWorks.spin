''File:DutyCycle.spin


CON
  'some values arbitrarily set PWMFrequency=400Hz maxintvalue=12(max for 8 bit bidirectional input)


  MULTIPLIER    = 198            'Constant value based on desired PWM frequency and the maximum value of the input integer  MULTIPLIER=(1/maxintvalue)*(1/PWMFrequency)*SCALE 
  CTIME         = 25000          'CTIME=(1/(PWMFrequency))* SCALE
  SCALE         = 10_000_000     'Scale value to avoid floating point needs to be large enough to shift the multiplier term to a useful integer value
  MOTORAPIN     = 6             'pin output A
  MOTORBPIN     = 7              'pin output B


VAR

  byte  cog
  long  stack[128]
  long  pwmA
  long  pwmB      
  long  lctra
  long  lctrb
  long  period


PUB Start(NewPeriod) : success
  ''dutya and dutyb are integer values from 0 to 127 where 0 is 0V DC and 127 is 3.3V DC and the intermediate values are variable duty cycles
  ''runs in one cog
  Stop

  period := NewPeriod
  pwmA := 0
  pwmB := 0
  
  lctra := (%00100 << 26) | (%111 << 23) | (24 & %11111)
  lctrb := (%00100 << 26) | (%111 << 23) | (25 & %11111)
  
  success := (cog := cognew(pwmLoop(@pwmA, @pwmB, @lctra, @lctrb), @stack) + 1)
PUB Stop

  if cog
    cogstop(cog~ - 1)

PUB SetDuty(dutya, dutyb)

  dira[24..27]:= %1111
  
  if(dutya < 0)
    pwmA := dutya
    outa[24] := 0
    lctra := (%00100 << 26) | (%111 << 23) | (26 & %11111)
  else
    pwmA := -dutya                                        
    outa[26] := 0
    lctra := (%00100 << 26) | (%111 << 23) | (24 & %11111)
    
  if(dutyb < 0)
    pwmB := dutyb                               
    outa[25] := 0
    lctrb := (%00100 << 26) | (%111 << 23) | (27 & %11111)
  else
    pwmB := -dutyb                              
    outa[27] := 0
    lctrb := (%00100 << 26) | (%111 << 23) | (25 & %11111)
  

PUB pwmLoop(addPWMA, addPWMB, addCTRA, addCTRB) | time
  dira[24..27] := %1111
  outa[24..27] := %0000     
  frqa := 1
  frqb := 1
  ctra := long[addCTRA]
  ctrb := long[addCTRB]
  time := cnt + period
                         
  repeat
    waitcnt(time)
    phsa := long[addPWMA]
    phsb := long[addPWMB]
    ctra := long[addCTRA]
    ctrb := long[addCTRB]
    time += period


{{
DAT
        org

pwmLoop mov addPWMA, par
        add par, #4
        mov addPWMB, par
        add par, #4
        mov addCTRA, par
        add par, #4
        mov addCTRB, par
        add par, #4
        rdlong lperiod, par

        rdlong ctra, addCTRA
        rdlong ctrb, addCTRB
        mov frqa, #1
        mov frqb, #1

        mov time, cnt
        add time, lperiod

:loop   waitcnt time, lperiod
        rdlong phsa, addPWMA
        rdlong phsb, addPWMB
        rdlong ctra, addCTRA
        rdlong ctrb, addCTRB
        jmp #:loop
        

time          res 1
addPWMA       res 1
addPWMB       res 1
addCTRA       res 1
addCTRB       res 1
lperiod       res 1
}}
                