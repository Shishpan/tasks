/**
 * @file: task/iface.h 
 * Interface of a programming task 2
 */
#include "../Utils/utils_iface.h"
#include <unordered_set>

/* namespaces import */
using namespace Utils;

//Debug assert with diagnostic info
#if !defined(GRAPH_ASSERTXD)
#    define GRAPH_ASSERTXD(cond, what) ASSERT_XD(cond, "Graph", what)
#endif

// Simple debug assert
#if !defined(GRAPH_ASSERTD)
#    define GRAPH_ASSERTD(cond) ASSERT_XD(cond, "Graph", "")
#endif

/**
 * Namespace for the programming task
 */
namespace Task
{
    //
    // Graph representation template
    // @param NodeT class representing nodes of graph, should be inherited from Graph::Node
    // @param EdgeT class representing edges of graph, should be inherited from Graph::Edge
    //
    template < class NodeT, class EdgeT> class Graph
    {
    public:
        typedef UInt32 UId; //< Unique id type for node and edge

		typedef typename std::set<NodeT>::iterator node_iterator;
		typedef typename std::set<EdgeT>::iterator edge_iterator;

        static const UId INVALID_UID = (UId) (-1);

        class Error: public std::exception
        {
		public:
			Error(const char* error_text)
			{
				text(error_text);
			}
			const char* what()
			{
				return text.c_str();
			}
		private:
			std::string text;
        };


        //
        // Graph node representation
        //
        class Node
        {
        public:
            //---- Iterator types ----
			class pred_iterator // iterator for node's predecessor edges 
			{
			public:
				typedef typename std::set<typename Graph<NodeT, EdgeT>::edge_iterator>::iterator tmpTypeForIterPreds;
				tmpTypeForIterPreds link_to_preds_set;
				pred_iterator& pred_iterator::operator++()
				{
					link_to_preds_set++;
					return *this;
				}					
				edge_iterator& pred_iterator::operator* ()
				{
					return *(*link_to_preds_set);
				}
				bool operator==(pred_iterator& right)
				{
					if (this->link_to_preds_set == right.link_to_preds_set)
						return true;
					else
						return false;
				}		
				bool operator!=(pred_iterator& right)
				{
					if (*this == right)
						return false;
					else
						return true;
				}				
			};
			class succ_iterator // iterator for node's successor edges 
			{
			public:
				typedef typename std::set<typename Graph::edge_iterator>::iterator tmpTypeForIterSuccs;
				tmpTypeForIterSuccs link_to_succs_set;
				succ_iterator& operator++()
				{
					link_to_succs_set++;
					return *this;
				}
				edge_iterator& operator* ()
				{
					return *(*link_to_succs_set);
				}
				bool operator==(succ_iterator& right)
				{
					if (this->link_to_succs_set == right.link_to_succs_set)
						return true;
					else
						return false;
				}
				bool operator!=(succ_iterator& right)
				{
					if (*this == right)
						return false;
					else
						return true;
				}		
			};

            pred_iterator preds_begin(); // Get iterator to the first predecessor edge
            pred_iterator preds_end();   // Get end iterator for the predecessors

            succ_iterator succs_begin(); // Get iterator to the first successor edge
            succ_iterator succs_end();   // Get end iterator for the successors

            Graph& graph();  // Get the graph reference
            UId uid() const; // Get the node's unique id 

            EdgeT& first_pred(); // Convinience routine returns first predecessor edge or throws an exception
            EdgeT& first_succ(); // Convinience routine returns first successor edge or throws an exception
            
            UInt32 num_preds() const; // Get the number of predecessors
            UInt32 num_succs() const; // Get the number of successors

        protected:
            Node( Graph& g); // Constructor of the node
            virtual ~Node();
        private:
            // ---- Default  and copy constructors turned off ---
            Node();
            Node(const Node &n);
			
            // ---- The internal implementation routines ----
			friend Graph<NodeT, EdgeT>::Edge;
			UId id;
			typename Graph::node_iterator link_in_all_nodes;
			std::set<typename Graph::edge_iterator> predecessors;
			std::set<typename Graph::edge_iterator> successors;
			Graph& link_to_graph;
			UInt32 pred_counter;
			UInt32 succ_counter;
            // ---- The data involved in the implementation ----
        };

        // 
        // Graph edge representation
        //
        class Edge
        {
        public:
            NodeT &pred(); // Get edge predecessor
            NodeT &succ(); // Get edge successor

            Graph& graph(); // Get the graph
            UId uid() const;// Get the edge's unique id
        protected:
            Edge( NodeT& p, NodeT& s); // Construct an edge between given nodes
            virtual ~Edge();
        private:
        // ---- Default  and copy constructors turned off ---
            Edge();
            Edge( const Edge &e);
        // ---- The internal implementation routines ----
			UId id;
			typename Graph::edge_iterator link_in_all_edges;
			typename Graph::node_iterator predecessor;
			typename Graph::node_iterator successor;

			Graph& link_to_graph;

        // ---- The data involved in the implementation ----
    };

    public:
    // ---- Graph interface ----
		
//        class node_iterator; // Iterator for the graph's nodes
//        class edge_iterator; // Iterator for the graph's edges
               
        node_iterator nodes_begin(); // Get the iterator to the first node
        node_iterator nodes_end();   // Get the end iterator for the nodes

        edge_iterator edges_begin(); // Get the iterator to the first edge
        edge_iterator edges_end();   // Get the end iterator for the edges

        UInt32 num_nodes() const; // Get the number of nodes
        UInt32 num_edges() const; // Get the number of edges

        NodeT &create_node();                   // Create a new node and return reference to it
        EdgeT &create_edge( NodeT& pred, NodeT& succ); // Create a new edge between given nodes
    
        void remove( NodeT& node); // Remove and delete node
        void remove( EdgeT& edge); // Remove and delete edge

        virtual ~Graph(); // Destructor, deletes all nodes and edges
    private:
        // ---- The internal implementation routines ----
		std::set<NodeT> AllNodes;
		std::set<EdgeT> AllEdges;
		UInt32 node_counter;
		UInt32 edge_counter;
		UInt32 counter_for_id;
        // ---- The data involved in the implementation ----
    };

    bool uTest( UnitTest *utest_p);
};

#include "graph_impl.h"
