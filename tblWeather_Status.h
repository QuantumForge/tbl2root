#ifndef TBLWEATHER_STATUS_H
#define TBLWEATHER_STATUS_H

#include "TTimeStamp.h"
#include "vtbl.h"

class tblWeather_Status: public vtbl
{
    protected:
	TTimeStamp timestamp;
	double Batt_Volt;
	double WS_mph_Avg;
	double WS_mph_Max;
	double WS_mph_Min;
	double WindDir;
	double AirTF_Avg;
	double RH;
	double Rain_in_Tot;
	double SlrW_Avg;
	double SlrkJ_Tot;
	double BP_mbar_Avg;

	void fillTblFields(TSQLStatement *statement, int verbose = 0);
	

    public:
        tblWeather_Status();
        ~tblWeather_Status();

	void Clear(Option_t * = "");
        int fillByDate(const char *yyyymmdd);
        //int fillByDate(TTimeStamp *ts);
	int fillByDate(int year, int month, int day);

	TTimeStamp get_timestamp() const { return timestamp; }
	double get_Batt_Volt() const { return Batt_Volt; }
	double get_WS_mph_Avg() const { return WS_mph_Avg; }
	double get_WS_mph_Max() const { return WS_mph_Max; }
	double get_WS_mph_Min() const { return WS_mph_Min; }
	double get_WindDir() const { return WindDir; }
	double get_AirTF_Avg() const { return AirTF_Avg; }
	double get_RH() const { return RH; }
	double get_Rain_in_Tot() const { return Rain_in_Tot; }
	double get_SlrW_Avg() const { return SlrW_Avg; }
	double get_SlrkJ_Tot() const { return SlrkJ_Tot; }
	double get_BP_mbar_Avg() const { return BP_mbar_Avg; }
	

	void set_timestamp(TTimeStamp timestamp_) { timestamp = timestamp_; }
	void set_Batt_Volt(double Batt_Volt_) { Batt_Volt = Batt_Volt_; }
	void set_WS_mph_Avg(double WS_mph_Avg_) { WS_mph_Avg = WS_mph_Avg_; }	
	void set_WS_mph_Max(double WS_mph_Max_) { WS_mph_Max = WS_mph_Max_; }	
	void set_WS_mph_Min(double WS_mph_Min_) { WS_mph_Min = WS_mph_Min_; }	
	void set_WindDir(double WindDir_) { WindDir = WindDir_; }
	void set_AirTF_Avg(double AirTF_Avg_) { AirTF_Avg = AirTF_Avg_; }
	void set_RH(double RH_) { RH = RH_; }
	void set_Rain_in_Tot(double Rain_in_Tot_)
		{ Rain_in_Tot = Rain_in_Tot_; }
	void set_SlrW_Avg(double SlrW_Avg_) { SlrW_Avg = SlrW_Avg_; }
	void set_SlrkJ_Tot(double SlrkJ_Tot_) { SlrkJ_Tot = SlrkJ_Tot_; }
	void set_BP_mbar_Avg(double BP_mbar_Avg_)
		{ BP_mbar_Avg = BP_mbar_Avg_; }
	
	ClassDef(tblWeather_Status, 1);
};

#endif
