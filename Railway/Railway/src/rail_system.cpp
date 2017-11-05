//#pragma warning (disable:4786)
//#pragma warning (disable:4503)

#include "rail_system.h"
#include "priority_queue.h"

typedef PriorityQueue<City*, Cheapest> CitiesPriorityQueue;

using namespace std; 

RailSystem::RailSystem(const string& filename) 
{    
    load_services(filename);
}

RailSystem::~RailSystem(void) 
{
    for (std::pair<std::string, City*> city : cities)
        delete city.second;
    for (std::pair<std::string, std::list<Service*>> serviceList : outgoing_services)
        for (Service* service : serviceList.second)
            delete service;
}

RailSystem::RailSystem(const RailSystem& other)
{
    for (pair<std::string, City*> pair : other.cities)
        cities[pair.first] = new City(*pair.second);
    for (pair<std::string, std::list<Service*>> pair : other.outgoing_services)
        for (Service* service : pair.second)
            outgoing_services[pair.first].push_back(new Service(service->destination, service->fee, service->distance));
}

void RailSystem::swap(RailSystem& lhv, RailSystem& rhv)
{
    std::map<std::string, City*> tempCities = lhv.cities;
    std::map<std::string, std::list<Service*>> tempServices = lhv.outgoing_services;
    lhv.cities = rhv.cities;
    lhv.outgoing_services = rhv.outgoing_services;
    rhv.cities = tempCities;
    rhv.outgoing_services = tempServices;
}

RailSystem& RailSystem::operator=(const RailSystem& rhv)
{
    RailSystem temp(rhv);
    swap(temp, *this);
    return *this;
}

void RailSystem::reset(void)
{
    for (std::pair<std::string, City*> s : cities)
    {
        s.second->visited = false;
        s.second->total_fee = INT_MAX;
        s.second->total_distance = INT_MAX;
        s.second->from_city = "";
    }
}

void RailSystem::load_services(const string& filename) 
{
	ifstream inf(filename.c_str());
	string from, to;
	int fee, distance;

	while (inf.good())
    {
		// Read in the from city, to city, the fee, and distance.
		inf >> from >> to >> fee >> distance;

		if (inf.good())
        {			
            if (cities.count(from) == 0)
                cities[from] = new City(from);
            if (cities.count(to) == 0)
                cities[to] = new City(to);
            if (outgoing_services.count(from) == 0)
                outgoing_services[from] = std::list<Service*>();
            if (outgoing_services.count(to) == 0)
                outgoing_services[to] = std::list<Service*>();
            outgoing_services[from].push_back(new Service(to, fee, distance));
		}
	}
	inf.close();
}


void RailSystem::output_cheapest_route(const string& from,
                const string& to, ostream& out)
{
	reset();
	pair<int, int> totals = calc_route(from, to);

	if (totals.first == INT_MAX)
    {
		out << "There is no route from " << from << " to " << to << "\n";
        return;
    }
    
    out << "The cheapest route from " << from << " to " << to << "\n";
    out << "costs " << totals.first << " euros and spans " << totals.second
        << " kilometers\n";
    cout << recover_route(to) << "\n\n";	
}

bool RailSystem::is_valid_city(const string& name)
{
	return cities.count(name) == 1;
}

pair<int, int> RailSystem::calc_route(const string& from, const string& to)
{
    // NB: здесь необходимо использовать собственную реализацию очереди с приоритетами,
    // псевдоним для которой описан в верху этого файла
    CitiesPriorityQueue candidates;
    candidates.push(cities[from]);
    cities[from]->visited = true;
    cities[from]->total_distance = 0;
    cities[from]->total_fee = 0;
    while (!candidates.isEmpty())
    {
        City* currCity = candidates.pop();
        for (Service* service : outgoing_services[currCity->name])
        {
            if (cities[service->destination]->total_fee > currCity->total_fee + service->fee)
            {
                cities[service->destination]->visited = true;
                cities[service->destination]->from_city = currCity->name;
                cities[service->destination]->total_fee = currCity->total_fee + service->fee;
                cities[service->destination]->total_distance = currCity->total_distance + service->distance;
                candidates.push(cities[service->destination]);
            }
        }
    }

    // Return the total fee and total distance.
    // Return (INT_MAX, INT_MAX) if not path is found.
    if (cities[to]->visited) 
        return pair<int,int>(cities[to]->total_fee, cities[to]->total_distance);

    return pair<int,int>(INT_MAX, INT_MAX);
}

string RailSystem::recover_route(const string& city) 
{	
    string result = "";
    string currCity = city;
    while (currCity != "")
    {
        result = currCity + " " + result;
        currCity = cities[currCity]->from_city;
    }

    return result;
}


Route RailSystem::getCheapestRoute(const string& from, const string& to)
{
    assert(is_valid_city(from));
    assert(is_valid_city(to));
    reset();
    pair<int, int> p = calc_route(from,to);
    
    return Route(from, to, p.first, p.second);
}
