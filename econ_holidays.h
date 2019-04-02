#ifndef ECON_HOLIDAYS_H
#define ECON_HOLIDAYS_H

#ifdef _WIN32
#pragma once
#endif

enum EHoliday
{
	kHoliday_None,
	kHoliday_Birthday,
	kHoliday_Halloween,
	kHoliday_Christmas,
	kHolidayCount,
};

int EconHolidays_GetHolidayForString( const char* pszHolidayName );
const char* EconHolidays_GetActiveHolidayString();
bool EconHolidays_IsHolidayActive( /*EHoliday*/ int holiday, const uint32 curtime );
#endif // !ECON_HOLIDAYS_H