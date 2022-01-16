// Datastructures.cc
#include <iostream>
#include <algorithm>
#include "datastructures.hh"

#include <random>

#include <cmath>

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
