#ifndef TBLL3_ARRAY_TRIGGERINFO_H
#define TBLL3_ARRAY_TRIGGERINFO_H

#include "TTimeStamp.h"
#include "vtbl.h"

class tblL3_Array_TriggerInfo: public vtbl
{
    protected:
        TTimeStamp timestamp;
        int run_id;
        int L3;
        double L3orVDAQBusy;
        double VDAQBusy;
        double SpareBusy;
        unsigned int PED;
        unsigned int OC;
	unsigned int VDAQBusyScaler;
	unsigned int L3orVDAQBusyScaler;
	unsigned int TenMHzScaler;

	void fillTblFields(TSQLStatement *statement, int verbose = 0);

    public:
        tblL3_Array_TriggerInfo();
        ~tblL3_Array_TriggerInfo();

	void Clear(Option_t * = "");
        int fillByRun(int runID);

        TTimeStamp get_timestamp() const { return timestamp; }
	int get_run_id() const { return run_id; }
	int get_L3() const { return L3; }
        double get_L3orVDAQBusy() const { return L3orVDAQBusy; }
        double get_SpareBusy() const { return SpareBusy; }
        unsigned int get_PED() const { return PED; }
        unsigned int get_OC() const { return OC; }
	unsigned int get_VDAQBusyScaler() const { return VDAQBusyScaler; }
	unsigned int get_L3orVDAQBusyScaler() const
            { return L3orVDAQBusyScaler; }
	unsigned int get_TenMHzScaler() const { return TenMHzScaler; }

	void set_timestamp(TTimeStamp timestamp_) { timestamp = timestamp_; }
	void set_run_id(int run_id_) { run_id = run_id_; }
	void set_L3(int L3_) { L3 = L3_; }
        void set_L3orVDAQBusy(double L3orVDAQBusy_)
            { L3orVDAQBusy = L3orVDAQBusy_; }
	void set_VDAQBusy(double VDAQBusy_) { VDAQBusy = VDAQBusy_; }
	void set_SpareBusy(double SpareBusy_) { SpareBusy = SpareBusy_; }
	void set_PED(unsigned int PED_) { PED = PED_; }
	void set_OC(unsigned int OC_) { OC = OC_; }
	void set_VDAQBusyScaler(unsigned int VDAQBusyScaler_)
		{ VDAQBusyScaler = VDAQBusyScaler_; }
	void set_L3orVDAQBusyScaler(unsigned int L3orVDAQBusyScaler_)
		{ L3orVDAQBusyScaler = L3orVDAQBusyScaler_; }
	void set_TenMHzScaler(unsigned int TenMHzScaler_)
		{ TenMHzScaler = TenMHzScaler_; }

	ClassDef(tblL3_Array_TriggerInfo, 1);
};

#endif
