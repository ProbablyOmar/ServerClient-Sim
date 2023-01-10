#include <iostream>
#include <stack>
#include <queue>
#include <list>
using namespace std;

class Server
{
private:
    bool isBusy = 0;
    int servetime;
    int time_left;

public:
    Server(int timetoserve)
    {
        servetime = timetoserve;
    }
    void serve()
    {
        isBusy = 1;
        time_left = servetime;
    }
    void finsh_up()
    {
        if (!time_left)
            isBusy = 0;
    }
    bool status()
    {
        return isBusy;
    }
    void pass_time()
    {
        time_left--;
        finsh_up();
    }
};

class Customer
{
public:
    Server *personal_server;

    void get_served(Server &my_server)
    {
        personal_server = &my_server;
        personal_server->serve();
    }
};

void sim(int timetoserve, int freq, int simtime, int numberOfServers)
{
    stack<Server *> serverStack;
    queue<Customer *> customerqueue;
    list<Server *> busy_servers;
    int customers_served = 0;
    Server *serverptr;
    Customer *customerptr;

    // Added available servers

    for (int _ = 0; _ < numberOfServers; _++)
    {
        serverptr = new Server(timetoserve);
        serverStack.push(serverptr);
    }

    for (int i = 0; i < simtime; i++)
    {
        // Adding customers according to frequency
        if (i % freq == 0)
        {
            customerptr = new Customer;
            customerqueue.push(customerptr);
        }

        // Returning free servers to stack and passing time for busy servers
        for (auto it = busy_servers.begin(); it != busy_servers.end(); ++it)
        {
            (*it)->pass_time();
        }

        while (!busy_servers.empty() && busy_servers.front()->status() == false)
        {
            serverptr = busy_servers.front();
            serverStack.push(serverptr);
            busy_servers.pop_front();
            customers_served++;
        }

        // Giving each customer a server and classfying them as being server
        // cout << serverStack.empty() << "\n";
        // cout << customerqueue.empty() << "\n";
        while (!customerqueue.empty() && !serverStack.empty())
        {
            customerptr = customerqueue.front();
            serverptr = serverStack.top();
            customerqueue.pop();
            serverStack.pop();
            customerptr->get_served(*serverptr);
            serverptr->serve();
            busy_servers.push_back(serverptr);
        }
    }
    cout << "Servers were able to serve " << customers_served << " Customers\n";
}

int main()
{
    int time_to_serve = 50;
    int frequency = 1;
    int simtime = 10000;
    int number_of_servers = 20;

    cout << "-------------------------------------------------------------------------------\n\n";
    cout << "                      Simulation Settings\n\n";
    cout << "Number of Servers: " << number_of_servers << "\n";
    cout << "Time to Serve: " << time_to_serve << "\n";
    cout << "Customer Frequency: " << frequency << "\n";
    cout << "Simulation Time: " << simtime << "\n";
    cout << "-------------------------------------------------------------------------------\n\n";
    cout << "                      Simulation Results\n\n";
    sim(time_to_serve, frequency, simtime, number_of_servers);
    cout << "\n";
    cout << "-------------------------------------------------------------------------------\n";

    return (0);
}