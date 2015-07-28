#ifndef __NMEA__OSD__HPP__
#define __NMEA__OSD__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief OSD - Own Ship Data
///
/// @code
///        1   2 3   4 5   6 7   8   9
///        |   | |   | |   | |   |   |
/// $--OSD,x.x,A,x.x,a,x.x,a,x.x,x.x,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Heading, degrees true
/// 2. Status
///    - A = Data Valid
///    - V = Invalid
/// 3. Vessel Course, degrees True
/// 4. Course Reference
///    - T = True
/// 5. Vessel Speed
/// 6. Speed Unit
/// 7. Vessel Set, degrees True
/// 8. Vessel drift (speed)
/// 9. Speed Units
///
class osd : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::OSD;
	constexpr static const char * TAG = "OSD";

	osd();
	osd(const osd &) = default;
	osd & operator=(const osd &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> heading; // degrees true
	utils::optional<status> data_valid;
	utils::optional<double> course; // degrees true
	utils::optional<reference> course_ref;
	utils::optional<double> speed;
	utils::optional<unit::velocity> speed_unit;
	utils::optional<double> vessel_set; // degrees true
	utils::optional<double> vessel_drift; // (speed)
	utils::optional<unit::velocity> vessel_drift_unit;

public:
	NMEA_GETTER(heading)
	NMEA_GETTER(data_valid)
	NMEA_GETTER(course)
	NMEA_GETTER(course_ref)
	NMEA_GETTER(speed)
	NMEA_GETTER(speed_unit)
	NMEA_GETTER(vessel_set)
	NMEA_GETTER(vessel_drift)
	NMEA_GETTER(vessel_drift_unit)

	void set_heading(double t) { heading = t; }
	void set_data_valid(status t) { data_valid = t; }
	void set_course(double t);
	void set_speed(double t, unit::velocity u);
	void set_vessel_set(double t) { vessel_set = t; }
	void set_drift(double t, unit::velocity u);
};
}
}

#endif
