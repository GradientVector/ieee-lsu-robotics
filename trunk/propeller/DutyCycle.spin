''File:DutyCycle.spin
VAR

  byte  cog
  long  stack[128]         

PUB Start(regAddr) : success | period
  ''dutya and dutyb are integer values from 0 to 127 where 0 is 0V DC and 127 is 3.3V DC and the intermediate values are variable duty cycles
  ''runs in one cog
  Stop            
  period := 8_010
  success := (cog := cognew(pwmLoop(regAddr,period), @stack) + 1)
PUB Stop

  if cog
    cogstop(cog~ - 1)

PUB SetDuty(dutya, dutyb, regAddr)

  dira[24..27]:= %1111
  
  if(dutya < 0)
    long[regAddr] := dutya * 16
    outa[24] := 0
    long[regAddr+8] := (%00100 << 26) | (%111 << 23) | (26 & %11111)
  else
    long[regAddr] := -dutya * 16                                        
    outa[26] := 0
    long[regAddr+8] := (%00100 << 26) | (%111 << 23) | (24 & %11111)
    
  if(dutyb < 0)
    long[regAddr+4] := dutyb * 16                               
    outa[25] := 0
    long[regAddr+12] := (%00100 << 26) | (%111 << 23) | (27 & %11111)
  else
    long[regAddr+4] := -dutyb * 16                              
    outa[27] := 0
    long[regAddr+12] := (%00100 << 26) | (%111 << 23) | (25 & %11111)

PUB pwmLoop(regAddr,period) | time
  dira[24..27] := %1111
  outa[24..27] := %0000     
  frqa := 1
  frqb := 1
  time := cnt + period
                       
  repeat
    waitcnt(time)
    phsa := long[regAddr]
    phsb := long[regAddr+4]
    ctra := long[regAddr+8]
    ctrb := long[regAddr+12]

    time += period
                