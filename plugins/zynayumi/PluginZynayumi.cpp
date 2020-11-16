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

PluginZynayumi::DistrhoPluginZynayumi()
	: Plugin(paramCount, 0, 0) // 0 programs, 0 states
	, _parameters(_zynayumi)
{
	deactivate();
}

PluginZynayumi::~PluginZynayumi()
{
}

void PluginZynayumi::initParameter(uint32_t index, Parameter& parameter)
{
	// Initialize mandatory attributes
	parameter.hints = kParameterIsAutomable;
	if (_parameters.is_int(index) or _parameters.is_enum(index))
		parameter.hints |= kParameterIsInteger;
	parameter.name = _parameters.get_name(index);
	parameter.symbol = _parameters.get_symbol(index);
	parameter.unit = _parameters.get_unit(index);
	parameter.ranges.def = _parameters.float_value(index);
	parameter.ranges.min = _parameters.lower(index);
	parameter.ranges.max = _parameters.upper(index);
	if (_parameters.is_enum(index)) {
		parameter.enumValues.count = _parameters.enum_count(index);
		parameter.enumValues.restrictedMode = true;
		ParameterEnumerationValue* const enumValues =
			new ParameterEnumerationValue[parameter.enumValues.count];
		for (size_t ei = 0; ei < parameter.enumValues.count; ei++) {				
			enumValues[0].value = (float)ei / parameter.ranges.max;
			enumValues[0].label = _parameters.enum_value_name(index, ei);
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
	return _parameters.float_value(index);
}

void PluginZynayumi::setParameterValue(uint32_t index, float value)
{
	_parameters.set_value(index, value);
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
	int i, cue, block;
	
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
		cue = me.frames;
	}

	// Process audio
	zynayumi.audio_process(p1, p2, frames - cue);
}

Plugin* createPlugin()
{
	return new PluginZynayumi();
}

END_NAMESPACE_DISTRHO
