// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <map>
#include <list>
#include <algorithm>
#include <random>
#include <cmath>

// Types for IDs
using PlaceID = long long int;
using AreaID = long long int;
using Name = std::string;
using WayID = std::string;

// Return values for cases where required thing was not found
PlaceID const NO_PLACE = -1;
AreaID const NO_AREA = -1;
WayID const NO_WAY = "!!No way!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Enumeration for different place types
// !!Note since this is a C++11 "scoped enumeration", you'll have to refer to
// individual values as PlaceType::SHELTER etc.
enum class PlaceType { OTHER=0, FIREPIT, SHELTER, PARKING, PEAK, BAY, AREA, NO_TYPE };

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Duration is unknown
Distance const NO_DISTANCE = NO_VALUE;



// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Returns number of elements in vector
    int place_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Must go through every element
    void clear_all();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Only returns vector
    std::vector<PlaceID> all_places();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Using find function on unordered_map
    bool add_place(PlaceID id, Name const& name, PlaceType type, Coord xy);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Using find function on unordered_map
    std::pair<Name, PlaceType> get_place_name_type(PlaceID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Using find function on unordered_map
    Coord get_place_coord(PlaceID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: Must loop through every element
    std::vector<PlaceID> places_alphabetically();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Must loop through every element
    std::vector<PlaceID> places_coord_order();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Must loop through every element
    std::vector<PlaceID> find_places_name(Name const& name);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Must loop through every element
    std::vector<PlaceID> find_places_type(PlaceType type);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Using find function on unordered_map
    bool change_place_name(PlaceID id, Name const& newname);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Using find function on unordered_map
    bool change_place_coord(PlaceID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(1)
    // Short rationale for estimate: Using find function on unordered_map
    bool add_area(AreaID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Using find function on unordered_map
    Name get_area_name(AreaID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Using find function on unordered_map
    std::vector<Coord> get_area_coords(AreaID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Only returns vector
    std::vector<AreaID> all_areas();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Using find function on unordered_map
    bool add_subarea_to_area(AreaID id, AreaID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: O(1) for using find function on unordered map,
    // but must loop through unordered_map so O(n)
    std::vector<AreaID> subarea_in_areas(AreaID id);

    // Non-compulsory operations

    // Estimate of performance:-
    // Short rationale for estimate:-
    void creation_finished();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Must loop through vector
    std::vector<AreaID> all_subareas_in_area(AreaID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Must loop through elements of unordered_map,
    // vector and sort vector
    std::vector<PlaceID> places_closest_to(Coord xy, PlaceType type);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Must loop through vector to find right ID
    // and erase it
    bool remove_place(PlaceID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Must loop through vectors using helper function
    AreaID common_area_of_subareas(AreaID id1, AreaID id2);

    // Phase 2 operations

    // Estimate of performance: O(1)
    // Short rationale for estimate: Only returns a vector
    std::vector<WayID> all_ways();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Number of way coordinates cant be too long, and
    // using find for unordered_map is O(1), worst case O(n)
    bool add_way(WayID id, std::vector<Coord> coords);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Using find on unordered_map is O(1), worst case O(n)
    std::vector<std::pair<WayID, Coord>> ways_from(Coord xy);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Using find on unordered_map is O(1), worst case O(n)
    std::vector<Coord> get_way_coords(WayID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Depends on the size (amount of n) of the containers
    void clear_ways();

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Used my own dijkstra implementation
    // to finding any route
    std::vector<std::tuple<Coord, WayID, Distance>> route_any(Coord fromxy, Coord toxy);

    // Non-compulsory operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: Must iterate through vector to remove id
    bool remove_way(WayID id);

    // Estimate of performance: -
    // Short rationale for estimate: Not implemented
    std::vector<std::tuple<Coord, WayID, Distance>> route_least_crossroads(Coord fromxy, Coord toxy);

    // Estimate of performance: -
    // Short rationale for estimate: Not implemented
    std::vector<std::tuple<Coord, WayID>> route_with_cycle(Coord fromxy);

    // Estimate of performance: O(n log n)
    // Short rationale for estimate: Copy of route_any
    std::vector<std::tuple<Coord, WayID, Distance>> route_shortest_distance(Coord fromxy, Coord toxy);

    // Estimate of performance: -
    // Short rationale for estimate: Not implemented
    Distance trim_ways();

private:
    // Add stuff needed for your class implementation here
    struct Place {
        Name name;
        PlaceType type;
        Coord coordinates;
    };

    struct Region {
        Name name;
        std::vector<Coord> shape;
    };

    struct Way {
        std::vector<Coord> route;
        unsigned int length;
        bool on_stack = false;
    };

    // Containers
    std::vector<PlaceID> Place_IDs;
    std::vector<AreaID> Region_IDs;
    std::vector<WayID> Way_IDs;


    std::unordered_map <PlaceID, Place> Places;
    std::unordered_map <AreaID, Region> Regions;
    std::unordered_map<AreaID, AreaID> Relations;

    std::unordered_map <WayID, Way> Ways;
    std::unordered_map <Coord, bool, CoordHash> Waypoints;
    std::unordered_map< Coord, std::vector<WayID>, CoordHash > Crossroads;


    // Functions
    std::vector<std::tuple<Coord, WayID, Distance> > Dijkstra (Coord, Coord);
    std::vector<WayID> AddEdge (Coord);



};

#endif // DATASTRUCTURES_HH
