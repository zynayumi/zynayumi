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

#include "PluginZynayumi.hpp"

START_NAMESPACE_DISTRHO

PluginZynayumi::PluginZynayumi()
	: Plugin(zynayumi::PARAMETERS_COUNT, 0, 0) // 0 programs, 0 states
	, _parameters(_zynayumi)
{
	deactivate();
}

PluginZynayumi::~PluginZynayumi()
{
}

void PluginZynayumi::initParameter(uint32_t index, Parameter& parameter)
{
	zynayumi::ParameterIndex pidx = (zynayumi::ParameterIndex)index;
	// Initialize mandatory attributes
	parameter.hints = kParameterIsAutomable;
	if (_parameters.is_int(pidx) or _parameters.is_enum(pidx))
		parameter.hints |= kParameterIsInteger;
	// NEXT
	parameter.name = _parameters.get_name(pidx).c_str();
	parameter.symbol = _parameters.get_symbol(pidx).c_str();
	parameter.unit = _parameters.get_unit(pidx).c_str();
	parameter.ranges.def = _parameters.float_value(pidx);
	parameter.ranges.min = _parameters.float_low(pidx);
	parameter.ranges.max = _parameters.float_up(pidx);
	if (_parameters.is_enum(pidx)) {
		parameter.enumValues.count = _parameters.enum_count(pidx);
		parameter.enumValues.restrictedMode = true;
		ParameterEnumerationValue* const enumValues =
			new ParameterEnumerationValue[parameter.enumValues.count];
		for (size_t ei = 0; ei < parameter.enumValues.count; ei++) {				
			enumValues[0].value = (float)ei / parameter.ranges.max;
			enumValues[0].label = _parameters.enum_value_name(pidx, ei).c_str();
		}
		parameter.enumValues.values = enumValues;
	}

	// NEXT:
	// // Initialize optional attributes
	// switch(index) {
	// case zynayumi::ENV_ATTACK_TIME:
	// 	parameter.midiCC = XX;
	// 	break;
	// case zynayumi::ENV_DECAY_TIME:
	// 	parameter.midiCC = XX;
	// 	break;
	// case zynayumi::ENV_SUSTAIN_LEVEL:
	// 	parameter.midiCC = XX;
	// 	break;
	// case zynayumi::ENV_RELEASE:
	// 	parameter.midiCC = XX;
	// 	break;
	// case zynayumi::LFO_FREQ:
	// 	parameter.midiCC = XX;
	// 	break;
	// case zynayumi::LFO_DELAY:
	// 	parameter.midiCC = XX;
	// 	break;
	// case zynayumi::LFO_DEPTH:
	// 	parameter.midiCC = XX;
	// 	break;
	// case zynayumi::PORTAMENTO_TIME:
	// 	parameter.midiCC = XX;
	// 	break;
	// default:
	// 	break;
	// }
	// NEXT:
	//     case paramBypass:
	//        parameter.initDesignation(kParameterDesignationBypass);
}

float PluginZynayumi::getParameterValue(uint32_t index) const
{
	return _parameters.float_value((zynayumi::ParameterIndex)index);
}

void PluginZynayumi::setParameterValue(uint32_t index, float value)
{
	_parameters.set_value((zynayumi::ParameterIndex)index, value);
}

void PluginZynayumi::activate()
{
}

void PluginZynayumi::deactivate()
{
}

void PluginZynayumi::run(const float**, float** outputs,
                         uint32_t frames,
                         const MidiEvent* midiEvents,
                         uint32_t midiEventCount)
{
	uint32_t i, cue, block;
	
	// Outputs buffers
	float* p1 = outputs[0];
	float* p2 = outputs[1];

	// Process audio on midi events
	cue = 0;
	for (i = 0; i < midiEventCount; i++)
	{
		const MidiEvent& me = midiEvents[i];
		block = me.frame - cue;
		if (block > 0) {
			_zynayumi.audio_process(p1, p2, block);
			p1 += block;
			p2 += block;
		}
		_zynayumi.raw_event_process(me.size, me.data);
		cue = me.frame;
	}

	// Process audio
	_zynayumi.audio_process(p1, p2, frames - cue);
}

Plugin* createPlugin()
{
	return new PluginZynayumi();
}

END_NAMESPACE_DISTRHO