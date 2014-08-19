/*    Robotic Construction Kit (ROCK) Driver  for the BD970 GNSS receiver 
 *    from Trimble.
 *    Copyright (C) 2014  Vassilios Tsounis
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *    
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *    
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    Bd970.cpp  Copyright (C) 2014  Vassilios Tsounis
 *    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 *    This is free software, and you are welcome to redistribute it
 *    under certain conditions; type `show c' for details.
 */



/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */


/**
 * 
 */
#include "Task.hpp"


/**
 * 
 */
using namespace trimble_bd970;


/**
 * 
 */
Task::Task(std::string const& name)
    : TaskBase(name)
    , mp_bd970(0)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
    , mp_bd970(0)
{
}

Task::~Task()
{
    // Do nothing?
}


/**
 * 
 * 
 */
void Task::processIO()
{
    /** Retrieve NMEA messages **/
    mp_bd970->getNMEA();
    
    /** Process the NMEA data **/
    /* TODO */
    
    /* DEBUG + TESTING */
    mp_bd970->printBufferNMEA();
    mp_bd970->printNMEA();
    
    /** Output the resulting data **/
    //_gnss_pose_samples.write();
    //_gnss_data_raw.write();
    //_time.write();
    //_constellation.write();
}


/**
 * 
 */

bool Task::configureHook()
{
    mp_bd970 = new Bd970(512, 1.0);
    
    //mp_bd970->setupNMEA(_port_nmea.get(), _baudrate_nmea.get());
    mp_bd970->setupNMEA("/home/vassilis/ttyV0", _baudrate_nmea.get());
    
    if (! TaskBase::configureHook())
    {
        return false;
    }
    
    return true;
}

bool Task::startHook()
{
    if (! TaskBase::startHook())
    {
        return false;
    }
    
    return true;
}

void Task::updateHook()
{
    TaskBase::updateHook();
    
    processIO();
}

void Task::errorHook()
{
    TaskBase::errorHook();
}

void Task::stopHook()
{
    TaskBase::stopHook();
}

void Task::cleanupHook()
{
    mp_bd970->closeNMEA();
    
    delete mp_bd970;
    
    TaskBase::cleanupHook();
}



/**
 * 
 */
