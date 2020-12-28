#include "shared/memory/procedure.hpp"

namespace shared::memory
{
	std::string ToLower(std::string data)
	{
		auto dest = ""s;

		dest.resize(data.size());
		std::transform(data.begin(), data.end(), dest.begin(), ::tolower);

		return dest;
	}

	std::wstring ToLower(std::wstring data)
	{
		auto dest = L""s;

		dest.resize(data.size());
		std::transform(data.begin(), data.end(), dest.begin(), ::towlower);

		return dest;
	}

	std::string ToUpper(std::string data)
	{
		auto dest = ""s;

		dest.resize(data.size());
		std::transform(data.begin(), data.end(), dest.begin(), ::toupper);

		return dest;
	}

	std::wstring ToUpper(std::wstring data)
	{
		auto dest = L""s;

		dest.resize(data.size());
		std::transform(data.begin(), data.end(), dest.begin(), ::towupper);

		return dest;
	}
}