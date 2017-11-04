//#pragma warning (disable:4786)
//#pragma warning (disable:4503)

#include "rail_system.h"


// TODO: собственная реализация класса очереди с приоритетами
#include "priority_queue.h"


// Здесь объявляем псевдоним для специфицированной собственной реализации очереди с приоритетами,
// шаблон которой объявлен в файле "priority_queue.h"
// TODO: необходимо проверить компаратор Cheapest на правильность — т.е. что он выстраивает
// города в «правильном» (с точки зрения алгоритма) порядке.
typedef PriorityQueue<City*, Cheapest> CitiesPriorityQueue;



// в cpp так можно
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

// TODO: тут д.б. КК и оператор копирования, т.к. деструктор объявлен...


void RailSystem::reset(void)
{
    for (std::pair<std::string, City*> s : cities)
    {
        s.second->visited = false;
        s.second->total_fee = 0;
        s.second->total_distance = 0;
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
    for (pair<std::string, City*> city : cities)
    {
        city.second->total_fee = INT_MAX;
        city.second->total_distance = INT_MAX;
    }
    //string currCity = from;
    candidates.push(cities[from]);
    cities[from]->visited = true;
    cities[from]->total_distance = 0;
    cities[from]->total_fee = 0;
    while (!candidates.isEmpty())
    {
        City* currCity = candidates.pop();
        for (Service* service : outgoing_services[currCity->name])
        {
            if (/*!cities[service->destination]->visited || */cities[service->destination]->total_fee > currCity->total_fee + service->fee)
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
    // TODO: walk backwards through the cities
    // container to recover the route we found

    return "";
}


Route RailSystem::getCheapestRoute(const string& from, const string& to)
{
    assert(is_valid_city(from));
    assert(is_valid_city(to));
    reset();
    pair<int, int> p = calc_route(from,to);
    
    return Route(from, to, p.first, p.second);
}
