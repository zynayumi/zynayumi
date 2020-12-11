/*
 * This file is part of Zynayumi.
 *
 * Zynayumi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PLUGIN_ZYNAYUMI_HPP
#define PLUGIN_ZYNAYUMI_HPP

#include "DistrhoPlugin.hpp"
#include "../../libzynayumi/src/zynayumi/zynayumi.hpp"
#include "../../libzynayumi/src/zynayumi/parameters.hpp"
#include "../../libzynayumi/src/zynayumi/programs.hpp"

START_NAMESPACE_DISTRHO

class PluginZynayumi : public Plugin
{
public:

	PluginZynayumi();
	~PluginZynayumi() override;

protected:

	const char* getLabel() const noexcept override;
	const char* getDescription() const override;
	const char* getMaker() const noexcept override;
	const char* getHomePage() const override;
	const char* getLicense() const noexcept override;
	uint32_t getVersion() const noexcept override;
	int64_t getUniqueId() const noexcept override;

	void initParameter(uint32_t index, Parameter& parameter) override;
	void initProgramName(uint32_t index, String& programName) override;

	float getParameterValue(uint32_t index) const override;
	void  setParameterValue(uint32_t index, float value) override;

	void loadProgram(uint32_t index) override;

	void run(const float**, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount) override;

private:

	zynayumi::Zynayumi _zynayumi;
	zynayumi::Parameters _parameters;
	zynayumi::Programs _programs;

	DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginZynayumi)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // PLUGIN_ZYNAYUMI_HPP
