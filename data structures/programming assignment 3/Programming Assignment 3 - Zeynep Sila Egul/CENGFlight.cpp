#include "CENGFlight.h"
#include <iostream>

//=======================//
// Implemented Functions //
//=======================//
void CENGFlight::PrintCanNotHalt(const std::string& airportFrom,
                                 const std::string& airportTo,
                                 const std::string& airlineName)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" via "
              << airlineName
              << " airlines is not found and cannot be halted"
              << std::endl;
}

void CENGFlight::PrintCanNotResumeFlight(const std::string& airportFrom,
                                         const std::string& airportTo,
                                         const std::string& airlineName)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" via "
              << airlineName
              << " airlines cannot be resumed"
              << std::endl;
}

void CENGFlight::PrintFlightFoundInCache(const std::string& airportFrom,
                                         const std::string& airportTo,
                                         bool isCostWeighted)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" using "
              << ((isCostWeighted) ? "cost" : "price")
              <<  " is found in cache." << std::endl;
}

void CENGFlight::PrintFlightCalculated(const std::string& airportFrom,
                                       const std::string& airportTo,
                                       bool isCostWeighted)
{
    std::cout << "A flight path is calculated between \""
              << airportFrom << "\" and \""
              << airportTo << "\" using "
              << ((isCostWeighted) ? "cost" : "price")
              <<  "." << std::endl;
}

void CENGFlight::PrintPathDontExist(const std::string& airportFrom,
                                    const std::string& airportTo)
{
    std::cout << "A flight path does not exists between \""
              << airportFrom << "\" and \""
              << airportTo <<"\"." << std::endl;
}

void CENGFlight::PrintSisterAirlinesDontCover(const std::string& airportFrom)
{
    std::cout << "Could not able to generate sister airline list from \""
              << airportFrom <<"\"." << std::endl;
}

void CENGFlight::PrintMap()
{
    navigationMap.PrintEntireGraph();
}

void CENGFlight::PrintCache()
{
    lruTable.PrintTable();
}

CENGFlight::CENGFlight(const std::string& flightMapPath)
    : navigationMap(flightMapPath)
{}

//=======================//
//          TODO         //
//=======================//
void CENGFlight::HaltFlight(const std::string& airportFrom,
                            const std::string& airportTo,
                            const std::string& airlineName)
{
    /* TODO */
    bool exist = navigationMap.edgeExists(airlineName, airportFrom, airportTo);

    if (exist) {
        try {
            const GraphEdge& edge = navigationMap.getEdgeDetails(airlineName, airportFrom, airportTo);
            navigationMap.RemoveEdge(airlineName, airportFrom, airportTo);

            HaltedFlight hf;
            hf.airportFrom = airportFrom;
            hf.airportTo = airportTo;
            hf.airline = airlineName;
            hf.w0 = edge.weight[0];
            hf.w1 = edge.weight[1];

            haltedFlights.push_back(hf);
        } catch (EdgeNotFoundException& e) {
            PrintCanNotHalt(airportFrom, airportTo, airlineName);
        }
    } else {
        PrintCanNotHalt(airportFrom, airportTo, airlineName);
    }
}

    // (Direct Function call)
void CENGFlight::ContinueFlight(const std::string& airportFrom,
                                const std::string& airportTo,
                                const std::string& airlineName)
{
    /* TODO */
    int foundIndex = -1;

    for (size_t i = 0; i < haltedFlights.size(); ++i) {
        if (haltedFlights[i].airportFrom == airportFrom && haltedFlights[i].airportTo == airportTo && haltedFlights[i].airline == airlineName) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // Retrieve the halted flight details
        HaltedFlight& hf = haltedFlights[foundIndex];

        try {
            navigationMap.AddEdge(hf.airline, hf.airportFrom, hf.airportTo, hf.w0, hf.w1);
            haltedFlights.erase(haltedFlights.begin() + foundIndex);
        } catch (SameNamedEdgeException& e) {
            PrintCanNotResumeFlight(airportFrom, airportTo, airlineName);
        }
    } else {
        PrintCanNotResumeFlight(airportFrom, airportTo, airlineName);
    }
    
}

void CENGFlight::FindFlight(const std::string& startAirportName,
                            const std::string& endAirportName,
                            float alpha)
{
    /* TODO */
    int startAirportIndex = navigationMap.GetVertexIndex(startAirportName);
    int endAirportIndex = navigationMap.GetVertexIndex(endAirportName);

    bool isFullyWeighted = (alpha == 0.0f || alpha == 1.0f);
    std::vector<int> pathIndices;

    if (isFullyWeighted) {
        bool pathExistsInCache = lruTable.Find(pathIndices, startAirportIndex, endAirportIndex, isFullyWeighted, false);

        if (pathExistsInCache) {
            PrintFlightFoundInCache(startAirportName, endAirportName, isFullyWeighted);
            navigationMap.PrintPath(pathIndices, alpha);
            return;
        }
    }

    std::vector<int> calculatedPathIndices;
    bool pathExists = false;

    if (isFullyWeighted) {
        pathExists = navigationMap.HeuristicShortestPath(calculatedPathIndices, startAirportName, endAirportName, alpha);
    }

    if (pathExists) {
        PrintFlightCalculated(startAirportName, endAirportName, isFullyWeighted);
        navigationMap.PrintPath(calculatedPathIndices, alpha, true);
        if (isFullyWeighted) {
            lruTable.Insert(calculatedPathIndices, isFullyWeighted);
        }
    } else {
        PrintPathDontExist(startAirportName, endAirportName);
    }
}

void CENGFlight::FindSpecificFlight(const std::string& startAirportName,
                                    const std::string& endAirportName,
                                    float alpha,
                                    const std::vector<std::string>& unwantedAirlineNames) const
{
    /* TODO */
}

void CENGFlight::FindSisterAirlines(std::vector<std::string>& airlineNames,
                               const std::string& startAirlineName,
                               const std::string& airportName) const
{
    /* TODO */
}

int CENGFlight::FurthestTransferViaAirline(const std::string& airportName,
                                           const std::string& airlineName) const
{
    /* TODO */
    return -1;
}