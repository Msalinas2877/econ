#include "cbase.h"
#include "econ_holidays.h"

int EconHolidays_GetHolidayForString( const char * pszHolidayName )
{
	return kHoliday_None;
}

const char* EconHolidays_GetActiveHolidayString()
{
	return "";
}

bool EconHolidays_IsHolidayActive( /*EHoliday*/ int holiday, const uint32 curtime )
{
	return false;
}
