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
    // TODO: release all the City* and Service*
    // from cities and outgoing_services
}

// TODO: тут д.б. КК и оператор копирования, т.к. деструктор объявлен...


void RailSystem::reset(void)
{
    // TODO: reset the data objects of the 
    // City objects' contained in cities   
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
			// TODO: Add entries in the cities container and
			// and services in the rail system for the new 
            // cities we read in.	
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

pair<int, int> RailSystem::calc_route(string from, string to)
{
    // NB: здесь необходимо использовать собственную реализацию очереди с приоритетами,
    // псевдоним для которой описан в верху этого файла
    CitiesPriorityQueue candidates;

    // TODO: Implement Dijkstra's shortest path algorithm to
    // find the cheapest route between the cities
    

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
