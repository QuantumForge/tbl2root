#ifndef TBLRUN_INFO_H
#define TBLRUN_INFO_H

#include "TTimeStamp.h"
#include "vtbl.h"

class tblRun_Info: public vtbl
{
    protected:
        int run_id;
	int run_type;
	int observing_mode;
	int run_status;
	TTimeStamp db_start_time;
	TTimeStamp db_end_time;
	TTimeStamp data_start_time;
	TTimeStamp data_end_time;
	unsigned int duration;
	int weather;
	unsigned int config_mask;
	int pointing_mode;
	int trigger_config;
	unsigned int trigger_multiplicity;
	double trigger_coincidence;
	double offsetRA;
	double offsetDEC;
	double offset_distance;
	double offset_angle;
	std::string source_id;

	void fillTblFields(TSQLStatement *statement, int verbose = 0);
	

    public:
        tblRun_Info();
        ~tblRun_Info();

	void Clear(Option_t * = "");

	int get_run_id() const { return run_id; }
	int get_run_type() const { return run_type; }
	int get_observing_mode() const { return observing_mode; }
	int get_run_status() const { return run_status; }
	TTimeStamp get_db_start_time() const { return db_start_time; }
	TTimeStamp get_db_end_time() const { return db_end_time; }
	TTimeStamp get_data_start_time() const { return data_start_time; }
	TTimeStamp get_data_end_time() const { return data_end_time; }
	unsigned int get_duration() const { return duration; }
	int get_weather() const { return weather; }
	unsigned int get_config_mask() const { return config_mask; }
	int get_pointing_mode() const { return pointing_mode; }
	int get_trigger_config() const { return trigger_config; }
	unsigned int get_trigger_multiplicity() const
            { return trigger_multiplicity; }
	double get_trigger_coincidence() const { return trigger_coincidence; }
	double get_offsetRA() const { return offsetRA; }
	double get_offsetDEC() const { return offsetDEC; }
	double get_offset_distance() const { return offset_distance; }
	double get_offset_angle() const { return offset_angle; }
	std::string get_source_id() const { return source_id; }

	void set_run_id(int run_id_) { run_id = run_id_; }
	void set_run_type(int run_type_) { run_type = run_type_; }
	void set_observing_mode(int observing_mode_)
	    { observing_mode = observing_mode_; }
	void set_run_status(int run_status_) { run_status = run_status_; }
	void set_db_start_time(TTimeStamp db_start_time_)
	    { db_start_time = db_start_time_; }
	void set_db_end_time(TTimeStamp db_end_time_)
	    { db_end_time = db_end_time_; }
	void set_data_start_time(TTimeStamp data_start_time_)
	    { data_start_time = data_start_time_; }
	void set_data_end_time(TTimeStamp data_end_time_)
	    { data_end_time = data_end_time_; }
	void set_duration(unsigned int duration_) { duration = duration_; }
	void set_weather(int weather_) { weather = weather_; }
	void set_config_mask(unsigned short config_mask_)
	     { config_mask = config_mask_; };
	void set_pointing_mode(int pointing_mode_)
	    { pointing_mode = pointing_mode_; }
	void set_trigger_config(int trigger_config_)
	    { trigger_config = trigger_config_; }
	void set_trigger_multiplicity(unsigned short trigger_multiplicity_)
	    { trigger_multiplicity = trigger_multiplicity_; }
	void set_trigger_coincidence(double trigger_coincidence_)
	    { trigger_coincidence = trigger_coincidence_; }
	void set_offsetRA(double offsetRA_) { offsetRA = offsetRA_; }
	void set_offsetDEC(double offsetDEC_) { offsetDEC = offsetDEC_; }
	void set_offset_distance(double offset_distance_)
	    { offset_distance = offset_distance_; }
	void set_offset_angle(double offset_angle_)
	    { offset_angle = offset_angle_; }
	void set_source_id(const char *source_id_) { source_id = source_id_; }
	
	ClassDef(tblRun_Info, 1);
};

#endif
