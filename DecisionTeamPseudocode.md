A prewriting/brainstorm for the ongoing 'decision' loop.
Text wraparound is annoying...
-Andrew E



while(true)  //or some more specific condition

> evaluateCharge(charge, lastFillupTime) 		//see if we have collected enough charge to go back to the flag
> > //note: after a certain time without filling up, as a failsafe,
> > //go back to the flag no matter how much charge we have


> evaluatePosition(map, ourPosition, feedFromCam) //this calls upon a lot of geographical functionality. it says:
> > //if map position doesn't match vision input, then resolve that problem.
> > //this may be done entirely by geog team


> decideNextDestination(ourPosition, chargeHeld)  //execute team will move to this next destination.


}