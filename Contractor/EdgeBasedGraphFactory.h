/*
 open source routing machine
 Copyright (C) Dennis Luxen, others 2010

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU AFFERO General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 or see http://www.gnu.org/licenses/agpl.txt.
 */

/*
 * This class constructs the edge base representation of a graph from a given node based edge list
 */

#ifndef EDGEBASEDGRAPHFACTORY_H_
#define EDGEBASEDGRAPHFACTORY_H_

#include <boost/shared_ptr.hpp>
#include <vector>

#include "../typedefs.h"
#include "../DataStructures/DynamicGraph.h"
#include "../DataStructures/ExtractorStructs.h"
#include "../DataStructures/ImportEdge.h"
#include "../DataStructures/Percent.h"

class EdgeBasedGraphFactory {
private:
    union _MiddleName {
        unsigned middle;
        unsigned nameID;
    };

    struct _NodeBasedEdgeData {
        unsigned distance;
        unsigned newNodeID;
        unsigned originalEdges : 29;
        bool shortcut : 1;
        bool forward : 1;
        bool backward : 1;
        short type:6;
        _MiddleName middleName;
    } data;

    struct _EdgeBasedEdgeData {
        unsigned distance;
        unsigned instruction;
        bool forward;
        bool backward;
        short type;
    };

    typedef DynamicGraph< _NodeBasedEdgeData > _NodeBasedDynamicGraph;
    typedef _NodeBasedDynamicGraph::InputEdge _NodeBasedEdge;

public:
    typedef DynamicGraph< _EdgeBasedEdgeData> _EdgeBasedDynamicGraph;
    typedef _EdgeBasedDynamicGraph::InputEdge _EdgeBasedEdge;
private:
    boost::shared_ptr<_NodeBasedDynamicGraph> _nodeBasedGraph;
    boost::shared_ptr<_EdgeBasedDynamicGraph> _edgeBasedGraph;

    std::vector<_Restriction> & inputRestrictions;

    std::vector<_EdgeBasedEdge> edgeBasedEdges;

public:
    template< class InputEdgeT >
    explicit EdgeBasedGraphFactory(int nodes, std::vector<InputEdgeT> & inputEdges, std::vector<_Restriction> & inputRestrictions);
    virtual ~EdgeBasedGraphFactory();

    void Run();
    template< class ImportEdgeT >
    void GetEdges( std::vector< ImportEdgeT >& edges );
    template< class NodeT >
    void GetNodes( std::vector< NodeT >& edges );

    unsigned GetNumberOfNodes() const;
};

#endif /* EDGEBASEDGRAPHFACTORY_H_ */