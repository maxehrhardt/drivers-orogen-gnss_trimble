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


/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef TRIMBLE_BD970_TASK_TASK_HPP
#define TRIMBLE_BD970_TASK_TASK_HPP


#include <trimble_bd970/Bd970.hpp>
#include "trimble_bd970/TaskBase.hpp"

//#include <ogr_spatialref.h>


/**
 * 
 */
namespace trimble_bd970 
{

    static const int DRIVER_BUFFER_SIZE = 512;

    /**
     * 
     */
    class Bd970;

    /**
     * 
     */
    class Task : public TaskBase
    {
        friend class TaskBase;


        protected:

            /** GDAL Interface for transforming between coordinate systems **/
    	    //OGRCoordinateTransformation *coTransform;

            /** Pointer to the driver **/
            Bd970* mp_bd970;


        public:
            /** TaskContext constructor for Task
             * \param name Name of the task. This name needs to be unique to make it identifiable via nameservices.
             * \param initial_state The initial TaskState of the TaskContext. Default is Stopped state.
             */
            Task(std::string const& name = "trimble_bd970::Task");

            /** TaskContext constructor for Task 
             * \param name Name of the task. This name needs to be unique to make it identifiable for nameservices. 
             * \param engine The RTT Execution engine to be used for this task, which serialises the execution of all commands, programs, state machines and incoming events for a task. 
             * 
             */
            Task(std::string const& name, RTT::ExecutionEngine* engine);

            /** Default deconstructor of Task
             */
            ~Task();

            /**
             * 
             * 
             */
            void processIO();


            /** This hook is called by Orocos when the state machine transitions
             * from PreOperational to Stopped. If it returns false, then the
             * component will stay in PreOperational. Otherwise, it goes into
             * Stopped.
             *
             * It is meaningful only if the #needs_configuration has been specified
             * in the task context definition with (for example):
             \verbatim
             task_context "TaskName" do
               needs_configuration
               ...
             end
             \endverbatim
             */
            bool configureHook();

            /** This hook is called by Orocos when the state machine transitions
             * from Stopped to Running. If it returns false, then the component will
             * stay in Stopped. Otherwise, it goes into Running and updateHook()
             * will be called.
             */
            bool startHook();

            /** This hook is called by Orocos when the component is in the Running
             * state, at each activity step. Here, the activity gives the "ticks"
             * when the hook should be called.
             *
             * The error(), exception() and fatal() calls, when called in this hook,
             * allow to get into the associated RunTimeError, Exception and
             * FatalError states. 
             *
             * In the first case, updateHook() is still called, and recover() allows
             * you to go back into the Running state.  In the second case, the
             * errorHook() will be called instead of updateHook(). In Exception, the
             * component is stopped and recover() needs to be called before starting
             * it again. Finally, FatalError cannot be recovered.
             */
            void updateHook();

            /** This hook is called by Orocos when the component is in the
             * RunTimeError state, at each activity step. See the discussion in
             * updateHook() about triggering options.
             *
             * Call recover() to go back in the Runtime state.
             */
            void errorHook();

            /** This hook is called by Orocos when the state machine transitions
             * from Running to Stopped after stop() has been called.
             */
            void stopHook();

            /** This hook is called by Orocos when the state machine transitions
             * from Stopped to PreOperational, requiring the call to configureHook()
             * before calling start() again.
             */
            void cleanupHook();
    };
}

#endif

