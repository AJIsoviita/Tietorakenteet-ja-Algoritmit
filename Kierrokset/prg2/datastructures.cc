// Datastructures.cc

#include "datastructures.hh"
#include <iostream>


std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Replace this comment with your implementation
}

Datastructures::~Datastructures()
{
    // Replace this comment with your implementation
}

int Datastructures::place_count()
{
    int Amount = Place_IDs.size();
    return Amount;
}

void Datastructures::clear_all()
{
    Place_IDs.clear();
    Places.clear();
    Region_IDs.clear();
    Regions.clear();
    Relations.clear();
    Way_IDs.clear();
    Ways.clear();
}

std::vector<PlaceID> Datastructures::all_places()
{
    return {Place_IDs};
}

bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{
    if(Places.find(id) != Places.end()) {return false;}

    Coord Coordinates;
    Coordinates.x = xy.x;
    Coordinates.y = xy.y;

    Place_IDs.push_back(id);

    Place place;
    place.name = name;
    place.type = type;
    place.coordinates = Coordinates;
    Places.insert({id, place});
    return true;
}

std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID id)
{
    if  (Places.find(id) == Places.end()){return {NO_NAME, PlaceType::NO_TYPE};}
    else    { return {Places[id].name, Places[id].type}; }
}

Coord Datastructures::get_place_coord(PlaceID id)
{
    if  (Places.find(id) == Places.end()) {return NO_COORD;}
    else    { return {Places[id].coordinates};}
}

bool Datastructures::add_area(AreaID id, const Name &name, std::vector<Coord> coords)
{
    if(Regions.find(id) != Regions.end()) {return false;}

    Region_IDs.push_back(id);

    Coord Coordinates;
    Region region;
    region.name = name;

    for(auto i : coords){
        Coordinates.x = i.x;
        Coordinates.y = i.y;
        region.shape.push_back(Coordinates);
    }

    Regions.insert( {id, region} );

    return true;
}

Name Datastructures::get_area_name(AreaID id)
{
    if  (Regions.find(id) == Regions.end()){return {NO_NAME};}
    else { return {Regions[id].name};}
}

std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{
    if  (Regions.find(id) == Regions.end()) {return {NO_COORD};}
    else {return {Regions[id].shape};}
}

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // NOTE!! It's quite ok to leave this empty, if you don't need operations
    // that are performed after all additions have been done.
}


std::vector<PlaceID> Datastructures::places_alphabetically()
{
    std::vector<std::pair<std::string, PlaceID>> Pairs;
    std::vector<PlaceID> Places_Alpha;

    for (auto i : Places) { Pairs.push_back( {i.second.name, i.first} ); }

    sort(Pairs.begin(), Pairs.end());

    for (auto i : Pairs) {Places_Alpha.push_back(i.second);}

    return {Places_Alpha};
}

std::vector<PlaceID> Datastructures::places_coord_order()
{
    std::vector<std::pair<double, PlaceID>> Pairs;
    std::vector<PlaceID> Places_Coord;

    for(auto i : Places) {
        double distance = sqrt(pow(i.second.coordinates.x,2) + pow(i.second.coordinates.y,2));
        Pairs.push_back( {distance, i.first} );
    }

    sort(Pairs.begin(), Pairs.end());

    for (auto i : Pairs) {Places_Coord.push_back(i.second);}

    return {Places_Coord};
}

std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{
    std::vector<PlaceID> Container;

    for (auto i : Places){
        if (i.second.name == name) {
            Container.push_back(i.first);
        }
    }
    return {Container};
}

std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{
    std::vector<PlaceID> Container;

    for (auto i : Places){
        if (i.second.type == type) {
            Container.push_back(i.first);
        }
    }
    return {Container};
}

bool Datastructures::change_place_name(PlaceID id, const Name& newname)
{
    if(Places.find(id) == Places.end()) {return false;}
    else {
        Places[id].name = newname;
    }
    return true;
}

bool Datastructures::change_place_coord(PlaceID id, Coord newcoord)
{
    if(Places.find(id) == Places.end()) {return false;}
    else {
        Places[id].coordinates.x = newcoord.x;
        Places[id].coordinates.y = newcoord.y;
    }
    return true;
}

std::vector<AreaID> Datastructures::all_areas()
{
    return {Region_IDs};
}

bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{
    if (Regions.find(id) == Regions.end()) {return false;}
    else if (Regions.find(parentid) == Regions.end()) {return false;}
    else if (Relations.find(id) != Relations.end()) {return false;}
    else { Relations.insert( {id, parentid} );}
    return true;
}

std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{
    std::vector<AreaID> Container;

    if (Regions.find(id) == Regions.end()) {return {NO_AREA};}
    else if (Relations.find(id) == Relations.end()) {return Container;}
    else {
        bool finding = true;
        while(finding) {
            if(Relations.find(id) == Relations.end()) { finding = false;}
            else {
                Container.push_back(Relations[id]);
                id = Relations[id];
            }
        }
    }
    return Container;
}

std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{
    std::vector<PlaceID> Container;
    std::vector<std::pair<double, PlaceID>> Pairs;

    if (type == PlaceType::NO_TYPE) {
        for (auto i : Places) {
                double distance = sqrt(pow(i.second.coordinates.x-xy.x,2)
                                     + pow(i.second.coordinates.y-xy.y,2));
                Pairs.push_back( {distance, i.first});
        }
    }
    else
    {
        for (auto i : Places) {
            if(i.second.type == type) {
                double distance = sqrt(pow(i.second.coordinates.x-xy.x,2)
                                     + pow(i.second.coordinates.y-xy.y,2));
                Pairs.push_back( {distance, i.first});
            }
        }
    }

    sort(Pairs.begin(), Pairs.end());

    for (auto i : Pairs) {Container.push_back(i.second);}

    if(Container.size()>3) {Container.erase(Container.begin() + 3, Container.end());}

    return {Container};
}

bool Datastructures::remove_place(PlaceID id)
{
    if(Places.find(id) == Places.end()) {return false;}
    else {
        std::vector<PlaceID>::iterator it = std::find(Place_IDs.begin(), Place_IDs.end(), id);
        int i = it - Place_IDs.begin();
        Place_IDs.erase(Place_IDs.begin() + i);
        }
        Places.erase(id);

    return true;
}

std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{
    std::vector<AreaID> Container;
    std::vector<AreaID> Childs;
    std::vector<AreaID> Parents;

    if (Regions.find(id) == Regions.end()) {return {NO_AREA};}

    for(auto i : Relations) {
        Childs.push_back(i.first);
        Parents.push_back(i.second);
    }

    for (auto i : Relations) {
        if (i.second == id) {
            Container.push_back(i.first);
            auto it = find(Parents.begin(), Parents.end(), i.first);
            int index;
            if (it != Parents.end()) {
                index = it - Parents.begin();
                Container.push_back(Childs[index]);
            }
        }
    }
    return Container;
}

int Compare(AreaID n1, AreaID n2) {
    if (n1 < n2) {return 1;}
    else if (n2 < n1) {return -1;}
    else {return 0;}
}

AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{
    std::vector<AreaID> Container1;
    std::vector<AreaID> Container2;

    if (Regions.find(id1) == Regions.end()) {return NO_AREA;}
    else if (Regions.find(id2) == Regions.end()) {return NO_AREA;}
    else {
        Container1 = subarea_in_areas(id1);
        Container2 = subarea_in_areas(id2);

        sort(Container1.begin(), Container1.end());
        sort(Container2.begin(), Container2.end());

        unsigned int a = 0;
        unsigned int b = 0;

        while (a < Container1.size() and b < Container2.size()) {
            int c = Compare(Container1[a], Container2[b]);
            if (c == 0) {return Container1[a];}
            else if (c == 1) {a++;}
            else {b++;}
        }
        return NO_AREA;
    }
}


std::vector<WayID> Datastructures::all_ways()
{
    return {Way_IDs};
}

bool Datastructures::add_way(WayID id, std::vector<Coord> coords)
{   
    if(Ways.find(id) != Ways.end()) {return false;}

    Way_IDs.push_back(id);

    Coord coordinates;
    Way way;
    std::vector<WayID> container;

    double length = 0;

    // Adding route coordinate by coordinate
    for(auto i : coords){
        coordinates.x = i.x;
        coordinates.y = i.y;
        way.route.push_back(coordinates);
    }

    unsigned int max_index = coords.size();
    unsigned int i = 0;

    // Calculate length of the route
    while ( i < max_index -1) {
        length += std::floor(sqrt(pow((coords[i].x - coords[i+1].x),2) +
                       pow((coords[i].y - coords[i+1].y),2)));
        i++;
    }

    way.length = length;
    Ways.insert( {id, way} );
    container.push_back(id);

    Waypoints.insert( {way.route.front(), false} );
    Waypoints.insert( {way.route.back(), false} );

    // Creating coord - possible ways structure
    if (Crossroads.find(way.route.front()) == Crossroads.end()) {
        Crossroads.insert ( {way.route.front(), container} );
    }
    else {Crossroads.find(way.route.front())->second.push_back(id);}

    if (Crossroads.find(way.route.back()) == Crossroads.end()) {
        Crossroads.insert ( {way.route.back(), container} );
    }
    else {Crossroads.find(way.route.back())->second.push_back(id);}

    return true;
}

std::vector<std::pair<WayID, Coord>> Datastructures::ways_from(Coord xy)
{

    std::vector<std::pair<WayID, Coord>> result;

    if (Crossroads.find(xy) == Crossroads.end()) {return {{result}};}
    else {
        for (auto i : Crossroads.find(xy)->second) {
            std::pair<WayID, Coord> container;
            Coord coordinates;

            if (Ways.find(i)->second.route.back() == xy) {
                coordinates = Ways.find(i)->second.route.front();}
            else {coordinates = Ways.find(i)->second.route.back();}

            container = {i, coordinates};
            result.push_back(container);
        }
    }

    return result;
}

std::vector<Coord> Datastructures::get_way_coords(WayID id)
{
    if(Ways.find(id) == Ways.end()) {return {NO_COORD};}
    else {return {Ways[id].route};}
}

void Datastructures::clear_ways()
{
    Way_IDs.clear();
    Ways.clear();
    Crossroads.clear();
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::Dijkstra (Coord fromxy, Coord toxy) {

    std::vector<std::tuple<Coord, WayID, Distance> > result = {};
    std::tuple<Coord, WayID, Distance> container = {};

    std::vector<WayID> temp = {};
    std::vector<WayID> stack = {};
    std::vector<WayID> visited = {};
    std::vector<WayID> backtrack = {};

    Coord origin = {};
    Coord destination = {};

    WayID next_ID = {};

    Distance distance=0;

    // To reset bool values
    for(auto & i : Waypoints) {i.second = false;}
    for(auto & i : Ways) {i.second.on_stack = false;}

    stack = AddEdge(fromxy);

    while(!stack.empty()){

        // To find shortest distance from the stack
        unsigned int min_length = 0;
        unsigned int length = 0;

        for(auto i : stack) {

            length = Ways.find(i)->second.length;

            if(min_length == 0 or length < min_length) {
                min_length = length;
                next_ID = i;
            }
        }

        visited.push_back(next_ID);

        int index = 0;
        for(auto i : stack) {
            if(i == next_ID) {
                stack.erase(stack.begin()+index);
                break;
            }
            index++;
        }

        if(toxy == Ways.find(next_ID)->second.route.front()){
            stack.clear();
            break;
        }
        else if(toxy == Ways.find(next_ID)->second.route.back()){
            stack.clear();
            break;
        }

        origin = Ways.find(next_ID)->second.route.front();
        destination = Ways.find(next_ID)->second.route.back();

        temp = AddEdge(destination);
        if(temp.size() == 0) {temp = AddEdge(origin);}

        for(auto i : temp) {stack.push_back(i);}
    }

    origin = toxy;

    // Create stack of used routes from toxy to fromxy
    while(destination != fromxy and visited.size() != 0) {
        int index = 0;

        for(auto i : visited) {
            if(Ways.find(i)->second.route.back() == origin) {
                backtrack.push_back(i);
                visited.erase(visited.begin()+index);
                destination = Ways.find(i)->second.route.front();
                break;
            }
            else if (Ways.find(i)->second.route.front() == origin) {
                backtrack.push_back(i);
                visited.erase(visited.begin()+index);
                destination = Ways.find(i)->second.route.back();
                break;
            }
            else {
                index++;
            }
        }
        origin = destination;
    }

    origin = fromxy;
    // Calculate distance and add coordinates to result
    while(backtrack.size() > 0){

        result.push_back( {origin, backtrack.back(), distance} );
        distance += Ways.find(backtrack.back())->second.length;

        if(Ways.find(backtrack.back())->second.route.front() == origin) {
            destination = Ways.find(backtrack.back())->second.route.back();
        }
        else {
            destination = Ways.find(backtrack.back())->second.route.front();
        }

        if(destination == toxy or origin == toxy) {
            result.push_back( {toxy, NO_WAY, distance} );
            return result;
        }

        origin = destination;
        backtrack.pop_back();
    }
    return result = {};
}

std::vector<WayID> Datastructures::AddEdge (Coord origin) {

    std::vector<WayID> result;

    if(Waypoints.find(origin)->second == true) {
        return result;
    }
    else {
        for(auto i : Crossroads.find(origin)->second) {
            if(Ways.find(i)->second.on_stack == false) {
                Ways.find(i)->second.on_stack = true;
                Waypoints.find(origin)->second = true;
                result.push_back(i);
            }
        }
    }
    return result;
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_any(Coord fromxy, Coord toxy)
{
    std::vector<std::tuple<Coord, WayID, Distance> > result = {};

    if(Crossroads.find(fromxy) == Crossroads.end() or
       Crossroads.find(toxy) == Crossroads.end() or
       Crossroads.find(fromxy)->second.size() == 0 or
       Crossroads.find(toxy)->second.size() == 0) {return {{NO_COORD, NO_WAY, NO_DISTANCE}};};

    result = Dijkstra(fromxy, toxy);

    return result;
}

bool Datastructures::remove_way(WayID id)
{
    if (Ways.find(id) == Ways.end()) {return false;}

    Coord origin = Ways.find(id)->second.route.front();
    Coord destination = Ways.find(id)->second.route.back();

    unsigned int index = 0;
    unsigned int o_index = 0;
    unsigned int d_index = 0;


    for(auto i : Way_IDs) {
        if(i == id) {Way_IDs.erase(Way_IDs.begin()+index);}
        else{index++;}
    }

    Ways.erase(id);

    for(auto i : Crossroads.find(origin)->second) {
        if(i == id) {
            if(Crossroads.find(origin)->second.size() == 1) {Crossroads.erase(origin);}
            else {
                Crossroads.find(origin)->second.erase(Crossroads.find(origin)->second.begin()+o_index);
            }
        }
        else {o_index++;}
    }

    for(auto i : Crossroads.find(destination)->second) {
        if(i == id) {
            if(Crossroads.find(destination)->second.size() == 1) {Crossroads.erase(destination);}
            else {
                Crossroads.find(destination)->second.erase(Crossroads.find(destination)->second.begin()+d_index);
            }
        }
        else {d_index++;}
    }

    return true;
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_least_crossroads(Coord fromxy, Coord toxy)
{
    // Replace this comment with your implementation
    return {{NO_COORD, NO_WAY, NO_DISTANCE}};
}

std::vector<std::tuple<Coord, WayID> > Datastructures::route_with_cycle(Coord fromxy)
{
    // Replace this comment with your implementation
    return {{NO_COORD, NO_WAY}};
}

std::vector<std::tuple<Coord, WayID, Distance> > Datastructures::route_shortest_distance(Coord fromxy, Coord toxy)
{
    return route_any(fromxy, toxy);
}

Distance Datastructures::trim_ways()
{
    // Replace this comment with your implementation
    return NO_DISTANCE;
}
