/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */


/**
 * 
 */
#include "Task.hpp"


/**
 * 
 */
using namespace gnss_rx_trimble_bd970;


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
    
    mp_bd970->setupNMEA(_port_nmea.get(), _baudrate_nmea.get());
    
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
