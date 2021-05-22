#ifndef TBLL3TELESCOPETRIGGERINFO_H
#define TBLL3TELESCOPETRIGGERINFO_H

#include "TTimeStamp.h"
#include "vtbl.h"

// http://romulus.ucsc.edu/phpmyadmin/tbl_structure.php?db=VERITAS&table=tblL3_Telescope_TriggerInfo
class tblL3_Telescope_TriggerInfo: public vtbl
{
    protected:
        TTimeStamp timestamp;
        int run_id;
        unsigned int telescope_id;
        int L2;
        int QI;
        int HM;
        int NP;
        int L2LL3;
        int L3;
        double VDAQBusy;
	unsigned int VDAQBusyScaler;
	unsigned int TenMHzScaler;

	void fillTblFields(TSQLStatement *statement, int verbose = 0);

    public:
        tblL3_Telescope_TriggerInfo();
        ~tblL3_Telescope_TriggerInfo();

	void Clear(Option_t * = "");
        int fillByRun(int runID);

        TTimeStamp get_timestamp() const { return timestamp; }
	int get_run_id() const { return run_id; }
	unsigned int const get_telescope_id() { return telescope_id; }
	int get_L2() const { return L2; }
	int get_QI() const { return QI; }
	int get_HM() const { return HM; }
	int get_NP() const { return NP; }
	int get_L2LL3() const { return L2LL3; }
	int get_L3() const { return L3; }
	double get_VDAQBusy() const { return VDAQBusy; }
	unsigned int get_VDAQBusyScaler() const { return VDAQBusyScaler; }
	unsigned int get_TenMHzScaler() const { return TenMHzScaler; }

	void set_timestamp(TTimeStamp timestamp_) { timestamp = timestamp_; }
	void set_run_id(int run_id_) { run_id = run_id_; }
	void set_telescope_id(unsigned int telescope_id_)
            { telescope_id = telescope_id_; }
	void set_L2(int L2_) { L2 = L2_; }
	void set_QI(int QI_) { QI = QI_; }
	void set_HM(int HM_) { HM = HM_; }
	void set_NP(int NP_) { NP = NP_; }
	void set_L2LL3(int L2LL3_) { L2LL3 = L2LL3_; }
	void set_L3(int L3_) { L3 = L3_; }
	void set_VDAQBusy(double VDAQBusy_) { VDAQBusy = VDAQBusy_; }
	void set_VDAQBusyScaler(unsigned int VDAQBusyScaler_)
		{ VDAQBusyScaler = VDAQBusyScaler_; }
	void set_TenMHzScaler(unsigned int TenMHzScaler_)
		{ TenMHzScaler = TenMHzScaler_; }

	ClassDef(tblL3_Telescope_TriggerInfo, 1);
};

#endif
