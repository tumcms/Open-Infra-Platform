/*
    This file is part of TUM Open Infra Platform Early Binding EXPRESS 
	Generator, a simple early binding generator for EXPRESS.
	Copyright (c) 2016-2017 Technical University of Munich
	Chair of Computational Modeling and Simulation.

	TUM Open Infra Platform Early Binding EXPRESS Generator is free 
	software; you can redistribute it and/or modify it under the terms 
	of the GNU General Public License Version 3 as published by the Free
	Software Foundation.

    TUM Open Infra Platform Early Binding EXPRESS Generator is 
	distributed in the hope that it will be useful, but WITHOUT ANY 
	WARRANTY; without even the implied warranty of MERCHANTABILITY or 
	FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
	for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef OpenInfraPlatform_ExpressBindingGenerator_stack_0295a4f7_934e_44e3_970a_929d57bf9ff6_a
#define OpenInfraPlatform_ExpressBindingGenerator_stack_0295a4f7_934e_44e3_970a_929d57bf9ff6_a

#include "namespace.h"
#include <stack>
#include <list>
#include <vector>
#include <algorithm>

OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_BEGIN

// taken from https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/

// A class that represents a directed graph 
// can find strongly connected components (SCC)
class Graph 
{ 
private:
    size_t V;    //< No. of vertices 
    std::vector<std::list<size_t>> adj;    //< An array of adjacency lists 
  
    /** \brief Recursive DFS based function used by SCC() 
     *
     * A recursive function that finds and prints strongly connected 
     * components using DFS traversal 
     *
     * \param[in] u The vertex to be visited next 
     * \param[in] disc Stores discovery times of visited vertices 
     * \param[in] low earliest visited vertex (the vertex with minimum 
     *                discovery time) that can be reached from subtree 
     *                rooted with current vertex 
     * \param[in] st To store all the connected ancestors (could be part of SCC) 
     * \param[in] stackMember bit/index array for faster check whether a node is in stack 
     * \param[in] time discovery time
     * \param[out] an array of [lists of indices = a SCC loop]
     */
    void SCCRec(size_t u,
                 std::vector<size_t>& disc,
                 std::vector<size_t>& low,
                 std::stack<size_t>& st,
                 std::vector<bool>& stackMember,
				 size_t& time,
                 std::vector<std::list<size_t>>& results)
    {
        // Initialize discovery time and low value 
        disc[u] = low[u] = ++time; 
        st.push(u); 
        stackMember[u] = true; 
      
        // Go through all vertices adjacent to this
        for ( auto v : adj[u] ) // v is current adjacent of 'u' 
        {         
            // If v is not visited yet, then recur for it 
            if (disc[v] == NIL) 
            { 
				SCCRec(v, disc, low, st, stackMember, time, results);
      
                // Check if the subtree rooted with 'v' has a 
                // connection to one of the ancestors of 'u' 
                // Case 1 (per above discussion on Disc and Low value) 
                low[u]  = std::min(low[u], low[v]); 
            } 
      
            // Update low value of 'u' only if 'v' is still in stack 
            // (i.e. it's a back edge, not cross edge). 
            // Case 2 (per above discussion on Disc and Low value) 
            else if (stackMember[v] == true) 
                low[u]  = std::min(low[u], disc[v]); 
        } 
      
        // head node found, pop the stack and print an SCC 
		size_t w = 0;  // To store stack extracted vertices 
        if (low[u] == disc[u]) 
        { 
            std::list<size_t> newLoop;
            while (st.top() != u) 
            { 
                w = st.top(); 
                newLoop.push_back(w); //cout << w << " "; 
                stackMember[w] = false; 
                st.pop(); 
            } 
            w = st.top(); 
            newLoop.push_back(w); //cout << w << "\n"; 
            stackMember[w] = false; 
            st.pop(); 
            // add to the results list
            results.push_back(newLoop);
        } 
    }

    static const size_t NIL = ULLONG_MAX; // means no connection, no visit

public: 
    //! Constructor  
    Graph(size_t noOfVertices)
    { 
        this->V = noOfVertices; 
        adj.resize(V);
    } 

    //! Destructor
    ~Graph() { }

    //! function to add an edge to graph 
    void addEdge(size_t v, size_t w)
    { 
        adj[v].push_back(w); 
    } 

    //! finds strongly connected components 
    std::vector<std::list<size_t>> SCC()
    { 
        // Initialize disc and low, and stackMember arrays 
        std::vector<size_t> disc(V, NIL), low(V, NIL);
        std::vector<bool> stackMember(V, false); 
      
        // Call the recursive helper function to find strongly 
        // connected components in DFS tree with vertex 'i' 
        std::stack<size_t> st;
        std::vector<std::list<size_t>> results;
        for (int i = 0; i < V; i++) 
            if (disc.at(i) == NIL) 
			{
				size_t dummy = 0;
				SCCRec(i, disc, low, st, stackMember, dummy, results);
			}

        return results;
    } 
}; 


OIP_NAMESPACE_OPENINFRAPLATFORM_EXPRESSBINDINGGENERATOR_END

#endif // end define OpenInfraPlatform_ExpressBindingGenerator_stack_0295a4f7_934e_44e3_970a_929d57bf9ff6_a
