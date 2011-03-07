#include "mci.h"

MCI::MCI(){}

MCI::MCI(const char *portName,int baudRate){}

MCI::~MCI(){}

void MCI::reset(){}

void MCI::resetEncoders(){}

void MCI::getEncVal(int &left,int &right){}

void MCI::setPIDVal(float P, float I, float D){}

void MCI::getPIDVal(float &P, float &I, float &D){}

void MCI::setLoopStatus(int status){}

int MCI::getLoopStatus(){}

void MCI::setModeStatus(int status){}

int MCI::getModeStatus(){}

void MCI::setVelocity(int a, int b){}

void MCI::getVelocity(int &a, int &b){}

