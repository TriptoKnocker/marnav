#ifndef __NMEA__VDR__HPP__
#define __NMEA__VDR__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(vdr)

/// @brief VDR - Set and Drift
///
/// @code
///        1   2 3   4 5   6
///        |   | |   | |   |
/// $--VDR,x.x,T,x.x,M,x.x,N*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Degress True
/// 2. Degress True reference
///    - T = True
/// 3. Degrees Magnetic
/// 4. Degrees Magnetic reference
///    - M = Magnetic
/// 5. Speed of current
/// 6. Speed of current unit
///    - N = Knots
///
class vdr : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(vdr)

public:
	constexpr static const sentence_id ID = sentence_id::VDR;
	constexpr static const char * TAG = "VDR";

	virtual ~vdr() {}

	vdr();
	vdr(const vdr &) = default;
	vdr & operator=(const vdr &) = default;

protected:
	vdr(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> degrees_true;
	utils::optional<reference> degrees_true_ref; // T:true
	utils::optional<double> degrees_mag;
	utils::optional<reference> degrees_mag_ref; // M:magnetic
	utils::optional<double> speed;
	utils::optional<unit::velocity> speed_unit; // N:knots

public:
	MARNAV_NMEA_GETTER(degrees_true)
	MARNAV_NMEA_GETTER(degrees_true_ref)
	MARNAV_NMEA_GETTER(degrees_mag)
	MARNAV_NMEA_GETTER(degrees_mag_ref)
	MARNAV_NMEA_GETTER(speed)
	MARNAV_NMEA_GETTER(speed_unit)

	void set_degrees_true(double t) noexcept;
	void set_degrees_mag(double t) noexcept;
	void set_speed(double t) noexcept;
};
}
}

#endif
