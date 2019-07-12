/*
This Source Code Form is subject to the
terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not
distributed with this file, You can
obtain one at
http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include "Classes.h"
#include "scenenode.h"
#include "Names.h"

class TTractionPowerSource : public scene::basic_node {

    friend class debug_panel;

public:
// constructor
    TTractionPowerSource( scene::node_data const &Nodedata );
// methods
    void Init(double const u, double const i);
    bool Load(cParser *parser);
    bool Update(double dt);
    double CurrentGet(double res);
    void VoltageSet(double const v) {
        NominalVoltage = v; };
    void PowerSet(TTractionPowerSource *ps);
// members
    TTractionPowerSource *psNode[ 2 ] = { nullptr, nullptr }; // zasilanie na końcach dla sekcji
    bool bSection = false; // czy jest sekcją

private:
// methods
    // serialize() subclass details, sends content of the subclass to provided stream
    void serialize_( std::ostream &Output ) const;
    // deserialize() subclass details, restores content of the subclass from provided stream
    void deserialize_( std::istream &Input );
    // export() subclass details, sends basic content of the class in legacy (text) format to provided stream
    void export_as_text_( std::ostream &Output ) const;

// members
    double NominalVoltage = 0.0;
    double VoltageFrequency = 0.0;
    double InternalRes = 0.2;
    double MaxOutputCurrent = 0.0;
    double FastFuseTimeOut = 1.0;
    int FastFuseRepetition = 3;
    double SlowFuseTimeOut = 60.0;
    bool Recuperation = false;

    double TotalCurrent = 0.0;
    double TotalAdmitance = 1e-10; // 10Mom - jakaś tam upływność
    double TotalPreviousAdmitance = 1e-10; // zero jest szkodliwe
    double OutputVoltage = 0.0;
    bool FastFuse = false;
    bool SlowFuse = false;
    double FuseTimer = 0.0;
    int FuseCounter = 0;

};



// collection of generators for power grid present in the scene
class powergridsource_table : public basic_table<TTractionPowerSource> {

public:
    // legacy method, calculates changes in simulation state over specified time
    void
        update( double const Deltatime );
};

//---------------------------------------------------------------------------
