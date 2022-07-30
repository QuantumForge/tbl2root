#ifndef TBLFIR_PYROMETER_INFO_H
#define TBLFIR_PYROMETER_INFO_H

#include "TTimeStamp.h"
#include "vtbl.h"

// http://romulus.ucsc.edu/phpmyadmin/index.php?db=VERITAS&token=c11f5e693f445a4e2241c0bcb915e82f
class tblFIR_Pyrometer_Info: public vtbl
{
    protected:
	TTimeStamp timestamp;
        unsigned short telescope_id;
        double ambient_temp;
        double radiant_sky_temp;

	void fillTblFields(TSQLStatement *statement, int verbose = 0);

    public:
        tblFIR_Pyrometer_Info();
        ~tblFIR_Pyrometer_Info();

	void Clear(Option_t * = "");
	TTimeStamp get_timestamp() const { return timestamp; }
        unsigned short get_telescope_id() const { return telescope_id; }
        double get_ambient_temp() const { return ambient_temp; }
        double get_radiant_sky_temp() const { return radiant_sky_temp; }


	void set_timestamp(TTimeStamp timestamp_) { timestamp = timestamp_; }
        void set_telescope_id(unsigned short telescope_id_)
            { telescope_id = telescope_id_; }
        void set_ambient_temp(double ambient_temp_)
            { ambient_temp = ambient_temp_; }
        void set_radiant_sky_temp(double radiant_sky_temp_)
            { radiant_sky_temp = radiant_sky_temp_; }
	
	ClassDef(tblFIR_Pyrometer_Info, 1);
};

#endif
