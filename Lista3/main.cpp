#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include <sys/time.h>
#include "pqueue.hpp"
#include "dijkstra.hpp"
#include "dial.hpp"
#include "radix.hpp"
using namespace std;

int main(int argc, char **argv)
{
    if (strcmp(argv[1], "dijkstra") == 0)
    {
        cout << "dijkstra" << endl;
    }
    else if (strcmp(argv[1], "dial") == 0)
    {
        cout << "dial" << endl;
    }
    else if (strcmp(argv[1], "radix") == 0)
    {
        cout << "radix" << endl;
    }
    else
    {
        cout << "nie ma takiego algorytmu" << endl;
        return 0;
    }

    // handle file with data
    ifstream datafile;
    if (strcmp(argv[2], "-d") == 0)
    {
        datafile.open(argv[3]);
        if (!datafile.good())
        {
            cout << "ERROR: data file is not exist " << endl;
            return 0;
        }
    }
    else
    {
        cout << "nie podałeś pliku" << endl;
        return 0;
    }

    // handle 'source'(-ss) or 'pointtopoint'(-p2p)
    ifstream sourcefile;
    if (strcmp(argv[4], "-ss") == 0)
    {
        sourcefile.open(argv[5]);
        if (!sourcefile.good())
        {
            cout << "ERROR: source file is not exist, problem with -ss file" << endl;
            return 0;
        }
    }
    else if (strcmp(argv[4], "-p2p") == 0)
    {
        sourcefile.open(argv[5]);
        if (!sourcefile.good())
        {
            cout << "ERROR: source file is not exist, , problem with -p2p file" << endl;
            return 0;
        }
    }
    else
    {
        cout << "ERROR: wrong -ss or -p2p file" << endl;
    }

    // NOTE: init dijkstra
    Graph *graph, *testgraph;
    int n, m, u, v, w;
    int lo;
    int hi = 0;
    string mystring;
    int *source;
    int *p2pu, *p2pv;
    int numberOfSource = 0;

    // NOTE: init dial
    GraphDial *graphdial;

    // NOTE: init radix
    GraphRadix *graphradix;

    // read data file and add acrs to graph
    if (datafile.is_open())
    {
        if (strcmp(argv[1], "dijkstra") == 0)
        {
            // NOTE: now read data to dijkstra algorithm
            while (datafile)
            {
                getline(datafile, mystring);
                istringstream input2;
                input2.str(mystring);

                int iterator = 0;

                switch (mystring[0])
                {
                case 'a': // arcs
                    // cout << mystring << " arcs" << endl;
                    for (std::string line; getline(input2, line, ' ');)
                    {
                        if (iterator == 1)
                        {
                            u = stoi(line.substr(0));
                        }
                        if (iterator == 2)
                        {
                            v = stoi(line.substr(0));
                        }
                        if (iterator == 3)
                        {
                            w = stoi(line.substr(0));
                            if (w > hi)
                                hi = w;
                        }
                        iterator++;
                    }
                    graph->addArcs(u, v, w);
                    // testgraph->addArcs(u, v, w);
                    u = 0;
                    v = 0;
                    w = 0;
                    break;
                case 'p': // problem
                    // cout << mystring << " problem" << endl;
                    for (std::string line; getline(input2, line, ' ');)
                    {
                        if (iterator == 2)
                        {
                            n = stoi(line);
                        }
                        if (iterator == 3)
                        {
                            m = stoi(line);
                        }
                        iterator++;
                    }
                    graph = new Graph(n, m);
                    break;
                case 'c': // comment TODO: move to p upper: this is comment not a problem
                    // for (std::string line; getline(input2, line, ' '); ) {
                    //     if (iterator == 3 && line[0] == 'n') {
                    //         n = stoi(line.substr(2));
                    //     }
                    //     if (iterator == 4 && line[0] == 'm') {
                    //         m = stoi(line.substr(2));
                    //     }
                    //     if (iterator == 5 && line[0] == 'l') {
                    //         lo = stoi(line.substr(3));
                    //     }
                    //     if (iterator == 6 && line[0] == 'h') {
                    //         hi = stoi(line.substr(3));
                    //     }
                    //     iterator++;
                    // }
                    // graph = new Graph(n, m);
                    // testgraph = new Graph(n, m);
                    break;
                default:
                    break;
                    iterator = 0;
                }
            }
        }
        else if (strcmp(argv[1], "dial") == 0)
        {
            // NOTE: now read data to dial algorithm, .gr file
            cout << "dane to algorytmu diala" << endl;
            while (datafile)
            {
                // for (int i=0; i<10; i++) { // FIXME: delete after
                getline(datafile, mystring);
                istringstream input2;
                input2.str(mystring);

                int iterator = 0;

                switch (mystring[0])
                {
                case 'a': // arcs
                    for (std::string line; getline(input2, line, ' ');)
                    {
                        if (iterator == 1)
                        {
                            u = stoi(line.substr(0));
                        }
                        if (iterator == 2)
                        {
                            v = stoi(line.substr(0));
                        }
                        if (iterator == 3)
                        {
                            w = stoi(line.substr(0));
                            if (w > hi)
                                hi = w;
                        }
                        iterator++;
                    }
                    graphdial->addArcs(u, v, w);
                    u = 0;
                    v = 0;
                    w = 0;
                    // cout << u << "!" << v << "!" <<  w << endl;
                    // cout << ">>" << graphdial->arcs[graphdial->index][0] << endl;
                    // u = 0; v = 0;  w = 0;
                    break;
                case 'p': // problem
                    for (std::string line; getline(input2, line, ' ');)
                    {
                        if (iterator == 2)
                        {
                            n = stoi(line);
                        }
                        if (iterator == 3)
                        {
                            m = stoi(line);
                        }
                        iterator++;
                    }
                    graphdial = new GraphDial(n, m);
                    break;
                case 'c': // comment
                    for (std::string line; getline(input2, line, ' ');)
                    {
                        // if (iterator == 3 && line[0] == 'n') {
                        //     n = stoi(line.substr(2));
                        // }
                        // if (iterator == 4 && line[0] == 'm') {
                        //     m = stoi(line.substr(2));
                        // }
                        if (iterator == 5 && line[0] == 'l')
                        {
                            lo = stoi(line.substr(3));
                        }
                        if (iterator == 6 && line[0] == 'h')
                        {
                            hi = stoi(line.substr(3));
                        }
                        iterator++;
                    }
                    // graphdial = new GraphDial(n);
                default:
                    break;
                    iterator = 0;
                }
            }
        }
        else if (strcmp(argv[1], "radix") == 0)
        {
            // NOTE: now read data to radix algorithm, .gr file
            while (datafile)
            {
                // for (int i=0; i<10; i++) { // FIXME: delete after
                getline(datafile, mystring);
                istringstream input2;
                input2.str(mystring);

                int iterator = 0;

                switch (mystring[0])
                {
                case 'a': // arcs
                    for (std::string line; getline(input2, line, ' ');)
                    {
                        if (iterator == 1)
                        {
                            u = stoi(line.substr(0));
                        }
                        if (iterator == 2)
                        {
                            v = stoi(line.substr(0));
                        }
                        if (iterator == 3)
                        {
                            w = stoi(line.substr(0));
                            if (w > hi)
                                hi = w;
                        }
                        iterator++;
                    }
                    graphradix->addArcs(u, v, w);
                    u = 0;
                    v = 0;
                    w = 0;
                    // cout << u << "!" << v << "!" <<  w << endl;
                    // cout << ">>" << graphdial->arcs[graphdial->index][0] << endl;
                    // u = 0; v = 0;  w = 0;
                    break;
                case 'p': // problem
                    for (std::string line; getline(input2, line, ' ');)
                    {
                        if (iterator == 2)
                        {
                            n = stoi(line);
                        }
                        if (iterator == 3)
                        {
                            m = stoi(line);
                        }
                        iterator++;
                    }
                    graphradix = new GraphRadix(n, m);
                    break;
                case 'c': // comment
                    for (std::string line; getline(input2, line, ' ');)
                    {
                        // if (iterator == 3 && line[0] == 'n') {
                        //     n = stoi(line.substr(2));
                        // }
                        // if (iterator == 4 && line[0] == 'm') {
                        //     m = stoi(line.substr(2));
                        // }
                        if (iterator == 5 && line[0] == 'l')
                        {
                            lo = stoi(line.substr(3));
                        }
                        if (iterator == 6 && line[0] == 'h')
                        {
                            hi = stoi(line.substr(3));
                        }
                        iterator++;
                    }
                default:
                    break;
                    iterator = 0;
                }
            }
        }
    }

    // NOTE: read source file
    if (sourcefile.is_open())
    {
        int iterator = 0;
        int iterator_source = 0;
        int iterator_p2p = 0;
        int choose = 0;
        while (sourcefile)
        {
            // for (int i=0; i<9;i++) {
            getline(sourcefile, mystring);
            istringstream input3;
            input3.str(mystring);

            // cout << mystring << endl;

            switch (mystring[0])
            {
            case 'p': // problem
                for (std::string line; getline(input3, line, ' ');)
                {
                    if (iterator == 4 && strcmp(argv[4], "-ss") == 0)
                    {
                        // n = stoi(line.substr(2));
                        numberOfSource = stoi(line);
                        source = new int[numberOfSource];
                        // cout << "DL" << stoi(line) << endl;
                    }
                    else if (iterator == 4 && strcmp(argv[4], "-p2p") == 0)
                    {
                        numberOfSource = stoi(line);
                        p2pu = new int[numberOfSource];
                        p2pv = new int[numberOfSource];
                    }
                    iterator++;
                }
                iterator = 0;
                break;
            case 's': // source
                // cout << "::" << mystring.substr(2) << endl;
                source[iterator_source] = stoi(mystring.substr(2));
                iterator_source++;
                break;
            case 'q':
                for (std::string line; getline(input3, line, ' ');)
                {
                    if (iterator == 1)
                    {
                        p2pu[iterator_p2p] = stoi(line);
                    }
                    else if (iterator == 2)
                    {
                        p2pv[iterator_p2p] = stoi(line);
                        iterator_p2p++;
                    }
                    iterator++;
                }
                iterator = 0;
                break;
            default:
                break;
            }
        }
    }

    // NOTE: write result to output file
    if (strcmp(argv[1], "dijkstra") == 0)
    {
        // dist - dijkstra returns array of dist of each vertex in graph
        int dist[graph->n + 1];
        if (strcmp(argv[6], "-oss") == 0)
        {
            // measure time for each source
            long int totaltime = 0;
            numberOfSource = 4; // FIXME: delete delete delete delete
            for (int i = 0; i < numberOfSource; i++)
            {
                // time_t start = time(nullptr);
                // time_t start_m = start * 1000;
                struct timeval tp;
                gettimeofday(&tp, NULL);
                long int start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
                dijkstra(graph, source[i], dist);
                gettimeofday(&tp, NULL);
                long int end = tp.tv_sec * 1000 + tp.tv_usec / 1000;
                // time_t end = time(nullptr);
                // time_t end_m = end * 1000;
                // cout << "Time: " << end - start << endl;
                totaltime = totaltime + (end - start);
            }
            // cout << totaltime << endl;
            // cout << totaltime/numberOfSource << endl;

            // TEST:
            // dijkstra(graph, 1, dist);
            // for (int i=0; i<5;i++) {
            //     cout << dist[i] << endl;
            // }

            ofstream resultfile(argv[7]);
            resultfile << "p res sp ss dikstra" << endl;
            resultfile << "c wyniki testu dla sieci zadanej w pliku " << argv[3] << " i zrodel " << argv[5] << endl;
            resultfile << "f " << argv[3] << " " << argv[5] << endl;
            resultfile << "c" << endl;
            resultfile << "c siec sklada sie z " << graph->n << " wierzcholkow, " << graph->m << " lukow" << endl;
            resultfile << "c koszty naleza do przedzialu [" << lo << ";" << hi << "]:" << endl;
            resultfile << "g " << graph->n << " " << graph->m << " " << lo << " " << hi << endl;
            resultfile << "c" << endl;
            resultfile << "c sredni czas wyznaczenia najkrotszych sciezek miedzy zrodlem a "
                       << " wszystkimi wierzcholkami wynosi " << totaltime / numberOfSource << endl;
            resultfile << "t " << totaltime / numberOfSource << endl;

            // TEST:
            cout << graph->n << " " << graph->m << " " << hi << " " << totaltime / numberOfSource << endl;
        }
        else if (strcmp(argv[6], "-op2p") == 0)
        {
            ofstream resultfile(argv[7]);
            resultfile << "p res sp ss dikstra" << endl;
            resultfile << "c wyniki testu dla sieci zadanej w pliku " << argv[3]
                       << " i par zrodlo-ujscie podanych w pliku" << argv[5] << endl;
            resultfile << "f " << argv[3] << " " << argv[5] << endl;
            resultfile << "c" << endl;
            resultfile << "c siec sklada sie z " << graph->n << " wierzcholkow, " << graph->m << " lukow" << endl;
            resultfile << "c koszty naleza do przedzialu [" << lo << ";" << hi << "]:" << endl;
            resultfile << "g " << graph->n << " " << graph->m << " " << lo << " " << hi << endl;
            resultfile << "c" << endl;
            numberOfSource = 5; // FIXME: change
            for (int i = 0; i < numberOfSource; i++)
            {
                dijkstra(graph, p2pu[i], dist);
                resultfile << "d " << p2pu[i] << " " << p2pv[i] << " " << dist[p2pv[i]] << endl;
            }
        }
        else
        {
            cout << "ERROR: output file" << endl;
        }
    }
    else if (strcmp(argv[1], "dial") == 0)
    {
        cout << "dial output" << endl;
        int dist[n + 1];
        if (strcmp(argv[6], "-oss") == 0)
        {
            // cout << "-oss" << endl;
            // cout << lo << ":" << hi << endl;
            // measure time for each source
            long int totaltime = 0;
            numberOfSource = 1; // FIXME: delete
            for (int i = 0; i < numberOfSource; i++)
            {
                struct timeval tp;
                gettimeofday(&tp, NULL);
                long int start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
                graphdial->dial(source[i], dist);
                gettimeofday(&tp, NULL);
                long int end = tp.tv_sec * 1000 + tp.tv_usec / 1000;
                cout << "Time: " << end - start << endl;
                totaltime = totaltime + (end - start);
            }
            ofstream resultfile(argv[7]);
            resultfile << "p res sp ss dial" << endl;
            resultfile << "c wyniki testu dla sieci zadanej w pliku " << argv[3] << " i zrodel " << argv[5] << endl;
            resultfile << "f " << argv[3] << " " << argv[5] << endl;
            resultfile << "c" << endl;
            resultfile << "c siec sklada sie z " << graphdial->n << " wierzcholkow, " << graphdial->m << " lukow" << endl;
            resultfile << "c koszty naleza do przedzialu [" << lo << ";" << hi << "]:" << endl;
            resultfile << "g " << graphdial->n << " " << graphdial->m << " " << lo << " " << hi << endl;
            resultfile << "c" << endl;
            resultfile << "c sredni czas wyznaczenia najkrotszych sciezek miedzy zrodlem a "
                       << " wszystkimi wierzcholkami wynosi " << totaltime / numberOfSource << endl;
            // resultfile << "t " << totaltime/numberOfSource << endl;
            // TEST:
            cout << graphdial->n << " " << graphdial->m << " " << hi << " " << totaltime / numberOfSource << endl;
        }
        else if (strcmp(argv[6], "-op2p") == 0)
        {
            cout << "-op2p" << endl;
            cout << p2pu[0] << ":" << p2pv[0] << endl;
            ofstream resultfile(argv[7]);
            resultfile << "p res sp ss dikstra" << endl;
            resultfile << "c wyniki testu dla sieci zadanej w pliku " << argv[3]
                       << " i par zrodlo-ujscie podanych w pliku" << argv[5] << endl;
            resultfile << "f " << argv[3] << " " << argv[5] << endl;
            resultfile << "c" << endl;
            resultfile << "c siec sklada sie z " << graphdial->n << " wierzcholkow, " << graphdial->m << " lukow" << endl;
            resultfile << "c koszty naleza do przedzialu [" << lo << ";" << hi << "]:" << endl;
            resultfile << "g " << graphdial->n << " " << graphdial->m << " " << lo << " " << hi << endl;
            resultfile << "c" << endl;
            numberOfSource = 1; // FIXME: change
            for (int i = 0; i < numberOfSource; i++)
            {
                graphdial->dial(p2pu[i], dist);
                resultfile << "d " << p2pu[i] << " " << p2pv[i] << " " << dist[p2pv[i]] << endl;
            }
        }
    }
    else if (strcmp(argv[1], "radix") == 0)
    {
        int dist[n];
        if (strcmp(argv[6], "-oss") == 0)
        {
            // cout << "-oss" << endl;
            // cout << lo << ":" << hi << endl;
            // measure time for each source
            long int totaltime = 0;
            numberOfSource = 5; // FIXME: delete
            for (int i = 0; i < numberOfSource; i++)
            {
                // ms - runtime radix
                struct timeval tp;
                gettimeofday(&tp, NULL);
                long int start = tp.tv_sec * 1000 + tp.tv_usec / 1000;
                // time_t start = time(nullptr);
                // time_t start_m = start * 1000;
                graphradix->radix(source[i], dist);
                gettimeofday(&tp, NULL);
                long int end = tp.tv_sec * 1000 + tp.tv_usec / 1000;
                // time_t end = time(nullptr);
                // time_t end_m = end * 1000;
                cout << "Time: " << end - start << endl; // ms - unit
                totaltime = totaltime + (end - start);
            }
            ofstream resultfile(argv[7]);
            resultfile << "p res sp ss radix" << endl;
            resultfile << "c wyniki testu dla sieci zadanej w pliku " << argv[3] << " i zrodel " << argv[5] << endl;
            resultfile << "f " << argv[3] << " " << argv[5] << endl;
            resultfile << "c" << endl;
            resultfile << "c siec sklada sie z " << graphradix->n << " wierzcholkow, " << graphradix->m << " lukow" << endl;
            resultfile << "c koszty naleza do przedzialu [" << lo << ";" << hi << "]:" << endl;
            resultfile << "g " << graphradix->n << " " << graphradix->m << " " << lo << " " << hi << endl;
            resultfile << "c" << endl;
            resultfile << "c sredni czas wyznaczenia najkrotszych sciezek miedzy zrodlem a "
                       << " wszystkimi wierzcholkami wynosi " << totaltime / numberOfSource << endl;
            resultfile << "t " << totaltime / numberOfSource << endl;

            // TEST:
            cout << graphradix->n << " " << graphradix->m << " " << hi << " " << totaltime / numberOfSource << endl;
            resultfile.close();
        }
        else if (strcmp(argv[6], "-op2p") == 0)
        {
            cout << "-op2p" << endl;
            cout << p2pu[0] << ":" << p2pv[0] << endl;
            ofstream resultfile(argv[7]);
            resultfile << "p res sp ss radix" << endl;
            resultfile << "c wyniki testu dla sieci zadanej w pliku " << argv[3]
                       << " i par zrodlo-ujscie podanych w pliku" << argv[5] << endl;
            resultfile << "f " << argv[3] << " " << argv[5] << endl;
            resultfile << "c" << endl;
            resultfile << "c siec sklada sie z " << graphradix->n << " wierzcholkow, " << graphradix->m << " lukow" << endl;
            resultfile << "c koszty naleza do przedzialu [" << lo << ";" << hi << "]:" << endl;
            resultfile << "g " << graphradix->n << " " << graphradix->m << " " << lo << " " << hi << endl;
            resultfile << "c" << endl;
            numberOfSource = 5; // FIXME: change
            for (int i = 0; i < numberOfSource; i++)
            {
                graphradix->radix(p2pu[i], dist);
                resultfile << "d " << p2pu[i] << " " << p2pv[i] << " " << dist[p2pv[i]] << endl;
            }
        }
    }

    sourcefile.close();
    datafile.close();

    return 0;
}