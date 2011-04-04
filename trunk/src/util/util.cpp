

//TODO: check this; it may have to be edited, if sleep(...) suspends too much of the bot's execution
//Input: time is in milliseconds
void wait(int milliseconds) {
	sleep( ((double)milliseconds)/1000 );   //the "/1000" is because sleep() takes parameters in seconds ?TODO
}
