/**
 * @file: task/graph_impl.h 
 * Solution implementation of the programming task 2
 */

namespace Task {
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::node_iterator 
		Graph<NodeT, EdgeT>::nodes_begin()
		{
			return AllNodes.begin();
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::node_iterator
		Graph<NodeT, EdgeT>::nodes_end()
		{
			return AllNodes.end();
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::edge_iterator
		Graph<NodeT, EdgeT>::edges_begin()
		{
			return AllEdges.begin();
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::edge_iterator
		Graph<NodeT, EdgeT>::edges_end()
		{
			return AllEdges.end();
		}
	template < class NodeT, class EdgeT>
		UInt32 Graph<NodeT, EdgeT>::num_nodes() const
		{
			return node_counter;
		}
	template < class NodeT, class EdgeT>
		UInt32 Graph<NodeT, EdgeT>::num_edges() const
		{
			return edge_counter;
		}
	template < class NodeT, class EdgeT>
		NodeT& Graph<NodeT, EdgeT>::create_node()
		{
			NodeT* tmpnode = static_cast<NodeT*>(new NodeT(*this));
			NodeT link = *((AllNodes.insert(*tmpnode)).first);
			delete tmpnode;
			return link;
		}
	template < class NodeT, class EdgeT>
		EdgeT& Graph<NodeT, EdgeT>::create_edge( NodeT& pred, NodeT& succ)
		{
			EdgeT* tmpedge = static_cast<EdgeT*>(new EdgeT(pred, succ));
			EdgeT link = *((AllEdges.insert(*tmpedge)).first);
			delete tmpedge;
			return link;
		}
	template < class NodeT, class EdgeT>
		void Graph<NodeT, EdgeT>::remove( NodeT& node)
		{
			for (Graph<NodeT, EdgeT>::Node::pred_iterator iter = node.preds_begin(); iter != node.preds_end(); ++iter)
			{
				delete iter;
			}
			for (Graph<NodeT, EdgeT>::Node::succ_iterator iter = node.succs_begin(); iter != node.succs_end(); ++iter)
			{
				delete iter;
			}
			delete node;
		}
	template < class NodeT, class EdgeT>
		Graph<NodeT, EdgeT>::~Graph()
		{
			for (set<NodeT>::iterator iter = AllNodes.begin(); iter != AllNodes.end(); ++iter)
			{
				delete &(*iter);
			}
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::Node::succ_iterator
		Graph<NodeT, EdgeT>::Node::succs_begin()
		{
			succ_iterator tmpIter;
			tmpIter.link_to_succs_set = successors.begin();
			return tmpIter;
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::Node::succ_iterator
		Graph<NodeT, EdgeT>::Node::succs_end()
		{
				succ_iterator tmpIter;
				tmpIter.link_to_succs_set = successors.end();
				return tmpIter;
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::Node::pred_iterator
		Graph<NodeT, EdgeT>::Node::preds_begin()
		{
				pred_iterator tmpIter;
				tmpIter.link_to_preds_set = predecessors.begin();
				return tmpIter;
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::Node::pred_iterator
		Graph<NodeT, EdgeT>::Node::preds_end()
		{
				pred_iterator tmpIter;
				tmpIter.link_to_preds_set = predecessors.end();
				return tmpIter;
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>& 
		Graph<NodeT, EdgeT>::Node::graph()
		{
			return link_to_graph;
		}
	template < class NodeT, class EdgeT>
		UInt32 Graph<NodeT, EdgeT>::Node::uid() const
		{
			return id;
		}
	template < class NodeT, class EdgeT>
		UInt32 Graph<NodeT, EdgeT>::Node::num_preds() const
		{
			return pred_counter;
		}
	template < class NodeT, class EdgeT>
		UInt32 Graph<NodeT, EdgeT>::Node::num_succs() const
		{
			return succ_counter;
		}

	template < class NodeT, class EdgeT>
		NodeT& Graph<NodeT, EdgeT>::Edge::pred()
		{
			return static_cast<NodeT>(*predecessor);
		}
	template < class NodeT, class EdgeT>
		NodeT& Graph<NodeT, EdgeT>::Edge::succ()
		{
			return static_cast<NodeT>(*successor);
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>&
		Graph<NodeT, EdgeT>::Edge::graph()
		{
				return link_to_graph;
		}
	template < class NodeT, class EdgeT>
		UInt32 Graph<NodeT, EdgeT>::Edge::uid() const
		{
			return id;
		}

	template < class NodeT, class EdgeT>///////////////////////////////////////
	Graph<NodeT, EdgeT>::Edge::Edge(NodeT& p, NodeT& s) : 
		predecessor(p.link_in_all_nodes),
		successor(s.link_in_all_nodes),
		link_to_graph(p.link_to_graph),
		id(p.link_to_graph.counter_for_id),
		link_in_all_edges()
		{

//			link_to_graph = static_cast<Graph&>(p.link_to_graph);			
//			id = p.link_to_graph.countr_for_id;
			p.link_to_graph.counter_for_id++;
			edge_iterator tmpIter = AllEdges.insert(tmpEdge);
			tmpIter->link_in_all_edges = tmpIter;
			p.link_to_graph.edge_counter++;
			tmpIter->predecessor.successors.insert(s.link_in_all_nodes);
			tmpIter->successor.predecessors.insert(p.link_in_all_nodes);
			tmpIter->predecessor.succ_counter++;
			tmpIter->successor.pred_counter++;
		}

}; // namespace Task