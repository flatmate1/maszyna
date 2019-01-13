/*
This Source Code Form is subject to the
terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not
distributed with this file, You can
obtain one at
http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include <unordered_map>
#include <queue>
#include <unordered_set>

enum class user_command {

	aidriverenable = 0,
    aidriverdisable,
    mastercontrollerincrease,
    mastercontrollerincreasefast,
    mastercontrollerdecrease,
    mastercontrollerdecreasefast,
    mastercontrollerset,
    secondcontrollerincrease,
    secondcontrollerincreasefast,
    secondcontrollerdecrease,
    secondcontrollerdecreasefast,
    secondcontrollerset,
    mucurrentindicatorothersourceactivate,
    independentbrakeincrease,
    independentbrakeincreasefast,
    independentbrakedecrease,
    independentbrakedecreasefast,
    independentbrakeset,
    independentbrakebailoff,
    trainbrakeincrease,
    trainbrakedecrease,
    trainbrakeset,
    trainbrakecharging,
    trainbrakerelease,
    trainbrakefirstservice,
    trainbrakeservice,
    trainbrakefullservice,
    trainbrakehandleoff,
    trainbrakeemergency,
    trainbrakebasepressureincrease,
    trainbrakebasepressuredecrease,
    trainbrakebasepressurereset,
    trainbrakeoperationtoggle,
    manualbrakeincrease,
    manualbrakedecrease,
    alarmchaintoggle,
    wheelspinbrakeactivate,
    sandboxactivate,
    reverserincrease,
    reverserdecrease,
    reverserforwardhigh,
    reverserforward,
    reverserneutral,
    reverserbackward,
    waterpumpbreakertoggle,
    waterpumpbreakerclose,
    waterpumpbreakeropen,
    waterpumptoggle,
    waterpumpenable,
    waterpumpdisable,
    waterheaterbreakertoggle,
    waterheaterbreakerclose,
    waterheaterbreakeropen,
    waterheatertoggle,
    waterheaterenable,
    waterheaterdisable,
    watercircuitslinktoggle,
    watercircuitslinkenable,
    watercircuitslinkdisable,
    fuelpumptoggle,
    fuelpumpenable,
    fuelpumpdisable,
    oilpumptoggle,
    oilpumpenable,
    oilpumpdisable,
    linebreakertoggle,
    linebreakeropen,
    linebreakerclose,
    convertertoggle,
    converterenable,
    converterdisable,
    convertertogglelocal,
    converteroverloadrelayreset,
    compressortoggle,
    compressorenable,
    compressordisable,
    compressortogglelocal,
    motoroverloadrelaythresholdtoggle,
    motoroverloadrelaythresholdsetlow,
    motoroverloadrelaythresholdsethigh,
    motoroverloadrelayreset,
    notchingrelaytoggle,
    epbrakecontroltoggle,
	trainbrakeoperationmodeincrease,
	trainbrakeoperationmodedecrease,
    brakeactingspeedincrease,
    brakeactingspeeddecrease,
    brakeactingspeedsetcargo,
    brakeactingspeedsetpassenger,
    brakeactingspeedsetrapid,
    brakeloadcompensationincrease,
    brakeloadcompensationdecrease,
    mubrakingindicatortoggle,
    alerteracknowledge,
    hornlowactivate,
    hornhighactivate,
    whistleactivate,
    radiotoggle,
    radiochannelincrease,
    radiochanneldecrease,
    radiostopsend,
    radiostoptest,
    cabchangeforward,
    cabchangebackward,

    viewturn,
    movehorizontal,
    movehorizontalfast,
    movevertical,
    moveverticalfast,
    moveleft,
    moveright,
    moveforward,
    moveback,
    moveup,
    movedown,

    carcouplingincrease,
    carcouplingdisconnect,
    doortoggleleft,
    doortoggleright,
    dooropenleft,
    dooropenright,
    doorcloseleft,
    doorcloseright,
    doorcloseall,
    departureannounce,
    doorlocktoggle,
    pantographcompressorvalvetoggle,
    pantographcompressoractivate,
    pantographtogglefront,
    pantographtogglerear,
    pantographraisefront,
    pantographraiserear,
    pantographlowerfront,
    pantographlowerrear,
    pantographlowerall,
    heatingtoggle,
    heatingenable,
    heatingdisable,
    lightspresetactivatenext,
    lightspresetactivateprevious,
    headlighttoggleleft,
    headlightenableleft,
    headlightdisableleft,
    headlighttoggleright,
    headlightenableright,
    headlightdisableright,
    headlighttoggleupper,
    headlightenableupper,
    headlightdisableupper,
    redmarkertoggleleft,
    redmarkerenableleft,
    redmarkerdisableleft,
    redmarkertoggleright,
    redmarkerenableright,
    redmarkerdisableright,
    headlighttogglerearleft,
    headlighttogglerearright,
    headlighttogglerearupper,
    redmarkertogglerearleft,
    redmarkertogglerearright,
    redmarkerstoggle,
    endsignalstoggle,
    headlightsdimtoggle,
    headlightsdimenable,
    headlightsdimdisable,
    motorconnectorsopen,
    motorconnectorsclose,
    motordisconnect,
    interiorlighttoggle,
    interiorlightenable,
    interiorlightdisable,
    interiorlightdimtoggle,
    interiorlightdimenable,
    interiorlightdimdisable,
    instrumentlighttoggle,
    instrumentlightenable,
    instrumentlightdisable,
    dashboardlighttoggle,
    timetablelighttoggle,
    generictoggle0,
    generictoggle1,
    generictoggle2,
    generictoggle3,
    generictoggle4,
    generictoggle5,
    generictoggle6,
    generictoggle7,
    generictoggle8,
    generictoggle9,
    batterytoggle,
    batteryenable,
    batterydisable,
    motorblowerstogglefront,
    motorblowerstogglerear,
    motorblowersdisableall,

	timejump,
	timejumplarge,
	timejumpsmall,
	vehiclemove,
	vehiclemoveforwards,
	vehiclemovebackwards,
	vehicleboost,
	debugtoggle,

    none = -1
};

enum class command_target {
/*
    // NOTE: there's no need for consist- and unit-specific commands at this point, but it's a possibility.
    // since command targets are mutually exclusive these don't reduce ranges for individual vehicles etc
    consist = 0x4000,
    unit    = 0x8000,
*/
    // values are combined with object id. 0xffff objects of each type should be quite enough ("for everyone")
    vehicle = 0x10000,
    signal  = 0x20000,
	entity  = 0x40000,

	simulation = 0x80000,
};

enum class command_mode {
	oneoff,
	continuous
};

struct command_description {
    std::string name;
    command_target target;
	command_mode mode;
};

struct command_data {

    user_command command;
    int action; // press, repeat or release
    double param1;
    double param2;
    double time_delta;

	bool freefly;
	glm::vec3 location;
};

// command_queues: collects and holds commands from input sources, for processing by their intended recipients
// NOTE: this won't scale well.
// TODO: turn it into a dispatcher and build individual command sequences into the items, where they can be examined without lookups

class command_queue {

public:
// types
	typedef std::deque<command_data> commanddata_sequence;
	typedef std::unordered_map<uint32_t, commanddata_sequence> commands_map;

// methods
    // posts specified command for specified recipient
	virtual void
	    push( command_data const &Command, uint32_t const Recipient );
    // retrieves oldest posted command for specified recipient, if any. returns: true on retrieval, false if there's nothing to retrieve
    bool
	    pop( command_data &Command, uint32_t const Recipient );
	void update();
	bool is_network_target(const uint32_t Recipient);

private:
// members
	// main command queue
	commands_map m_commands;

	// hash operator for m_active_continuous
	struct command_set_hash {
		uint64_t operator() (const std::pair<user_command, uint32_t> &pair) const {
			return ((uint64_t)pair.first << 32) | ((uint64_t) pair.second);
		}
	};

	// currently pressed continuous commands
	std::unordered_set<std::pair<user_command, uint32_t>, command_set_hash> m_active_continuous;
};

class command_queue_server : public command_queue {
public:
	void push( command_data const &Command, uint32_t const Recipient ) override;

	commands_map pop_queued_commands();
	void push_client_commands(const commands_map &commands);

private:
	// contains copies of commands to be sent to clients
	commands_map network_queue;
};

class command_queue_client : public command_queue {
public:
	void push( command_data const &Command, uint32_t const Recipient ) override;

	commands_map pop_queued_commands();
	void push_server_commands(const commands_map &commands);

private:
	// contains intercepted commands to be sent for execution to server
	commands_map network_queue;
};

// NOTE: simulation should be a (light) wrapper rather than namespace so we could potentially instance it,
//       but realistically it's not like we're going to run more than one simulation at a time
namespace simulation {

typedef std::vector<command_description> commanddescription_sequence;

extern std::unique_ptr<command_queue> Commands;
// TODO: add name to command map, and wrap these two into helper object
extern commanddescription_sequence Commands_descriptions;

}

// command_relay: composite class component, passes specified command to appropriate command stack

class command_relay {

public:
// methods
	// posts specified command for the specified recipient
    void
	    post(user_command const Command, double const Param1, double const Param2,
	        int const Action, uint16_t Recipient ) const;
};

//---------------------------------------------------------------------------
