#ifndef __NMEA__HDM__HPP__
#define __NMEA__HDM__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(hdm)

/// @brief HDM - Heading - Magnetic
///
/// Vessel heading in degrees with respect to magnetic north produced by any device
/// or system producing magnetic heading.
///
/// @note As of 2009, this sentence is designaged 'obsolete'. Older devices may
///   support them, therefore it makes sense to implement it.
///
/// @code
///        1   2
///        |   |
/// $--HDM,x.x,M*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Heading Degrees magnetic
/// 2. Heading Degrees magnetic reference
///    - M = magnetic
///
class hdm : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(hdm)

public:
	constexpr static const sentence_id ID = sentence_id::HDM;
	constexpr static const char * TAG = "HDM";

	virtual ~hdm() {}

	hdm();
	hdm(const hdm &) = default;
	hdm & operator=(const hdm &) = default;

protected:
	hdm(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> heading; // magnetic sensor heading in deg
	utils::optional<reference> heading_mag;

public:
	MARNAV_NMEA_GETTER(heading)
	MARNAV_NMEA_GETTER(heading_mag)

	void set_heading(double t) noexcept;
};
}
}

#endif
