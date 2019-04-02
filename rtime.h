#ifndef RTIME_H
#define RTIME_H

#ifdef _WIN32
#pragma once
#endif

class CRTime
{
public:
	static void UpdateRealTime() { sm_nTimeCur = time( 0 ); }
	static uint32 RTime32TimeCur() { return sm_nTimeCur; }
private:
	static uint32 sm_nTimeCur;
};

uint32 CRTime::sm_nTimeCur = 0;

#endif // !RTIME_H
