#ifndef trimble_bd970_TYPES_HPP
#define trimble_bd970_TYPES_HPP


#ifndef __orogen
    #include <vector>
#endif

/**
 * 
 */
//#include <vector>
#include <base/time.h>



/**
 * 
 */
namespace trimble_bd970 
{
    
    enum BD970_FIRMWARE_OPTIONS
    {
        BD970_UPDATE_RATE        = 1,
        BD970_RTK_ROVER          = 2,
        BD970_RTK_BASE           = 4,
        BD970_PPS_OUTPUT         = 8,
        BD970_EVENT_MARKER       = 16,
        BD970_SBAS_TRACKING      = 32,
        BD970_GLONASS_TRACKING   = 64,
        BD970_RTK_MOVING_BASE    = 128,
        BD970_HEADING            = 256,
        BD970_ADVANCED_MULTIPATH = 512
    };

    enum BD970_DYNAMICS_MODEL
    {
        BD970_STATIC       = 1,
        BD970_QUASI_STATIC = 2,
        BD970_WALKING      = 3,
        BD970_SHIP         = 4,
        BD970_AUTOMOBILE   = 5,
        BD970_AIRCRAFT     = 6,
        BD970_UNLIMITED    = 7,
        BD970_ADAPTIVE     = 8,
        BD970_USER_DEFINED = 9
    };

    enum BD970_AMBIGUITY_THRESHOLD
    {
        BD970_NO_FIX     = 0,
        BD970_FIX_95_0 = 1,
        BD970_FIX_99_0 = 2,
        BD970_FIX_99_9 = 3
    };

    enum BD970_GNSS_MODE
    {
        BD970_GP_L1   = 0,
        BD970_GPGL_L1 = 1,
        BD970_GP_L2   = 2,
        BD970_GP_L2CS = 3,
        BD970_GPGL_L1L2 = 4,
        BD970_GPGL_L1L2CS = 5
    };
    
    enum GPS_SOLUTION_TYPES
    {
        NO_SOLUTION  = 0,
        AUTONOMOUS_2D  = 6, // is 6 for historical reasons
        AUTONOMOUS   = 1,
        DIFFERENTIAL = 2,
        INVALID      = 3,
        RTK_FIXED    = 4,
        RTK_FLOAT    = 5
    };

    struct Time 
    { 
      base::Time cpu_time; 
      base::Time gps_time; 
      double processing_latency;
    };
    
    struct GNSS_Raw 
    {
        base::Time time;
        double latitude;
        double longitude;
        GPS_SOLUTION_TYPES positionType;
        int noOfSatellites;
        double altitude;
        double geoidalSeparation;
        double ageOfDifferentialCorrections;

        double deviationLatitude;
        double deviationLongitude;
        double deviationAltitude;
#ifndef __orogen
        
        GNSS_Raw()
            : positionType(INVALID)
        {
        }
        
#endif

    };

    struct Position 
    {
        base::Time time;
        double latitude;
        double longitude;
        GPS_SOLUTION_TYPES positionType;
        int noOfSatellites;
        double altitude;
        double geoidalSeparation;
        double ageOfDifferentialCorrections;
        
#ifndef __orogen

        Position()
            : positionType(INVALID)
        {
        }
        
#endif

    };

    struct Errors 
    {
        base::Time time;
        double deviationLatitude;
        double deviationLongitude;
        double deviationAltitude;
    };

    struct SolutionQuality 
    {
        base::Time time;
        std::vector<int> usedSatellites;
        double pdop;
        double hdop;
        double vdop;
    };

    enum CONSTELLATIONS 
    {
        CONSTELLATION_GPS,
        CONSTELLATION_SBAS,
        CONSTELLATION_GLONASS
    };
    
    struct Satellite 
    {
        int PRN;
        int elevation;
        int azimuth;
        double SNR;

#ifndef __orogen

        static CONSTELLATIONS getConstellationFromPRN(int prn)
        {
            if (prn < 33)
                return CONSTELLATION_GPS;
            else if (prn < 65)
                return CONSTELLATION_SBAS;
            else
                return CONSTELLATION_GLONASS;
        }

        CONSTELLATIONS getConstellation() const
        {
            return getConstellationFromPRN(PRN);
        }
        
#endif

    };

    struct SatelliteInfo 
    {
        base::Time time;
        std::vector < trimble_bd970::Satellite> knownSatellites;
    };

    struct UserDynamics 
    {
        int hSpeed;
        int hAccel;
        int vSpeed;
        int vAccel;
#ifndef __orogen

        UserDynamics()
            : hSpeed(0)
            , hAccel(0)
            , vSpeed(0)
            , vAccel(0)
            {
            }
#endif
    };

    struct ConstellationInfo 
    {
        trimble_bd970::SolutionQuality quality;
        trimble_bd970::SatelliteInfo  satellites;
    };
    
}

#endif //trimble_bd970_TYPES_HPP

