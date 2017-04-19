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
using namespace gnss_trimble;


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
    mp_bd970 = NULL;
}


/**
 * 
 * 
 */
void Task::processIO()
{
    /** Retrieve NMEA messages **/
    mp_bd970->processNMEA();

    /** Get the Time information **/
    gnss_trimble::Time gnss_time = mp_bd970->getTime();
    _time.write(gnss_time);

    /** Solution pose **/
    gnss_trimble::Solution gnss_solution = mp_bd970->getSolution();
    _raw_data.write(gnss_solution);

    if(gnss_solution.positionType != gnss_trimble::NO_SOLUTION)
    {
        double la = gnss_solution.latitude;
        double lo = gnss_solution.longitude;
        double alt = gnss_solution.altitude;

        coTransform->Transform(1, &lo, &la, &alt);
        gnss_pose.time = gnss_solution.time;

        /** Position **/
        gnss_pose.position.x() = lo - _pose_origin.value().x();
        gnss_pose.position.y() = la - _pose_origin.value().y();
        gnss_pose.position.z() = alt - _pose_origin.value().z();
        gnss_pose.cov_position = mp_bd970->getPositionUncertainty();
        /*gnss_pose.cov_position(0, 0) = gnss_solution.deviationLongitude * gnss_solution.deviationLongitude;
        gnss_pose.cov_position(1, 1) = gnss_solution.deviationLatitude * gnss_solution.deviationLatitude;
        gnss_pose.cov_position(2, 2) = gnss_solution.deviationAltitude * gnss_solution.deviationAltitude;*/

        /** Orientation **/
        gnss_pose.orientation = mp_bd970->getOrientation();
        gnss_pose.cov_orientation = mp_bd970->getOrientationUncertainty();

        _pose_samples.write(gnss_pose);
    }
    
    switch(gnss_solution.positionType)
    {
    case gnss_trimble::INVALID:
        state(INVALID);
        break;
    case gnss_trimble::NO_SOLUTION:
        state(NO_SOLUTION);
        break;
    case gnss_trimble::AUTONOMOUS:
        state(AUTONOMOUS);
        break;
    case gnss_trimble::RTK_FLOAT:
        state(RTK_FLOAT);
        break;
    case gnss_trimble::RTK_FIXED:
        state(RTK_FIXED);
        break;
    case gnss_trimble::DIFFERENTIAL:
        state(DIFFERENTIAL);
        break;
    default:
        state(RUNNING);
    }

    /* DEBUG + TESTING */
    /*mp_bd970->printBufferNMEA();
    mp_bd970->printNMEA();*/
}


/**
 * 
 */

bool Task::configureHook()
{
    if (! TaskBase::configureHook())
    {
        return false;
    }

    /** Serial port connection configuration **/
    mp_bd970 = new Bd970(DRIVER_BUFFER_SIZE, this->getPeriod());

    mp_bd970->setupNMEA(_serial_port.get(), _serial_baudrate.get());

    /** setup conversion from WGS84 to UTM **/
    OGRSpatialReference oSourceSRS;
    OGRSpatialReference oTargetSRS;

    oSourceSRS.SetWellKnownGeogCS(_geodetic_datum.get().c_str());
    oTargetSRS.SetWellKnownGeogCS(_geodetic_datum.get().c_str());
    oTargetSRS.SetUTM( _utm_zone, _utm_north );

    coTransform = OGRCreateCoordinateTransformation(&oSourceSRS, &oTargetSRS);

    if( coTransform == NULL )
    {
	RTT::log(RTT::Error) << "failed to initialize CoordinateTransform UTM_ZONE:" << _utm_zone << " UTM_NORTH:" << _utm_north << RTT::endlog();
	return false;
    }

    /** Initial invalid pose **/
    gnss_pose.invalidate();
    gnss_pose.sourceFrame = _gnss_source_frame.get();
    gnss_pose.targetFrame = _gnss_target_frame.get();
    gnss_pose.cov_position.setZero(); //set to zero to put the variance afterwards in the updateHook

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
