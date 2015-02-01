/**
 * @file: task/graph_impl.h 
 * Solution implementation of the programming task 2
 */

namespace Task {
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::node_iterator
		Graph<NodeT, EdgeT>::nodes_begin()
		{
			node_iterator node_iter_tmp;
			node_iter_tmp.iter = list_of_nodes.begin();
			return node_iter_tmp;
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::node_iterator
		Graph<NodeT, EdgeT>::nodes_end()
		{
			node_iterator node_iter_tmp;
			node_iter_tmp.iter = list_of_nodes.end();
			return node_iter_tmp;
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::edge_iterator
		Graph<NodeT, EdgeT>::edges_end()
		{
			edge_iterator edge_iter_tmp;
			edge_iter_tmp.iter = list_of_edges.end();
			return edge_iter_tmp;
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::edge_iterator
		Graph<NodeT, EdgeT>::edges_begin()
		{
			edge_iterator edge_iter_tmp;
			edge_iter_tmp.iter = list_of_edges.begin();
			return edge_iter_tmp;
		}
	template < class NodeT, class EdgeT>
		UInt32 Graph<NodeT, EdgeT>::num_nodes() const
		{
			return nodes_amount;
		}
	template < class NodeT, class EdgeT>
		UInt32 Graph<NodeT, EdgeT>::num_edges() const
		{
			return edges_amount;
		}
	template < class NodeT, class EdgeT> Graph<NodeT, EdgeT>::Node::Node(Graph& g) : 
		ref_to_graph(g),
		uniq_num(g.counter)
		{
			g.counter++;
			g.nodes_amount++;
		}
	template < class NodeT, class EdgeT>
		typename NodeT& Graph<NodeT, EdgeT>::create_node()
		{
			NodeT* node_tmp_ptr = new NodeT(ref_to_graph);
			list_of_nodes.push_front(*node_tmp_ptr);
			list_of_nodes.begin()->get().iter_of_itself_in_general_list = list_of_nodes.begin();
			return *(nodes_begin());
		}
	template < class NodeT, class EdgeT>
		typename EdgeT& Graph<NodeT, EdgeT>::create_edge(NodeT& pred, NodeT& succ)
		{
			EdgeT* edge_tmp_ptr = new EdgeT(pred, succ);
			list_of_edges.push_front(*edge_tmp_ptr);

			pred.list_of_refs_to_succs.push_front(succ);
			list_of_edges.begin()->get().iter_of_ref_to_succ_in_pred = pred.list_of_refs_to_succs.begin();
			pred.list_of_refs_to_succs_edges.push_front(*(list_of_edges.begin()));
			list_of_edges.begin()->get().iter_of_ref_to_edge_in_pred = pred.list_of_refs_to_succs_edges.begin();

			succ.list_of_refs_to_preds.push_front(pred);
			list_of_edges.begin()->get().iter_of_ref_to_pred_in_succ = succ.list_of_refs_to_preds.begin();
			succ.list_of_refs_to_preds_edges.push_front(*(list_of_edges.begin()));
			list_of_edges.begin()->get().iter_of_ref_to_edge_in_succ = succ.list_of_refs_to_preds_edges.begin();

			list_of_edges.begin()->get().iter_of_itself_in_general_list = list_of_edges.begin();
			return list_of_edges.begin()->get();
		}
	template <class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::UId
		Graph<NodeT, EdgeT> ::Node::uid() const
		{
			return uniq_num;
		}

	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>&
		Graph<NodeT, EdgeT> ::Node::graph()
		{
			return ref_to_graph;
		}
	template <class NodeT, class EdgeT> Graph<NodeT, EdgeT>::Graph() : 
		ref_to_graph(*this),
		counter(0),
		nodes_amount(0),
		edges_amount(0)	{}

	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::Node::pred_iterator
		Graph<NodeT, EdgeT>::Node::preds_begin()
		{
			pred_iterator pred_iter_tmp;
			pred_iter_tmp.iter = list_of_refs_to_preds.begin();
			return pred_iter_tmp;
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::Node::pred_iterator
		Graph<NodeT, EdgeT>::Node::preds_end()
		{
			pred_iterator pred_iter_tmp;
			pred_iter_tmp.iter = list_of_refs_to_preds.end();
			return pred_iter_tmp;
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::Node::succ_iterator
		Graph<NodeT, EdgeT>::Node::succs_begin()
		{
			succ_iterator succ_iter_tmp;
			succ_iter_tmp.iter = list_of_refs_to_succs.begin();
			return succ_iter_tmp;
		}
	template < class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::Node::succ_iterator
		Graph<NodeT, EdgeT>::Node::succs_end()
		{
			succ_iterator succ_iter_tmp;
			succ_iter_tmp.iter = list_of_refs_to_succs.end();
			return succ_iter_tmp;
		}
	template <class NodeT, class EdgeT>
		Graph<NodeT, EdgeT>::~Graph()
		{
			typedef typename list<reference_wrapper<NodeT>>::iterator IterTmpN;
			typedef typename list<reference_wrapper<EdgeT>>::iterator IterTmpE;
			IterTmpN iter = list_of_nodes.begin();
			while (iter != list_of_nodes.end())
			{
				IterTmpN iter_tmp = iter;
				iter_tmp++;
				remove((*iter).get());
				iter = iter_tmp;
			};
			IterTmpE iter1 = list_of_edges.begin();
			while (iter1 != list_of_edges.end())
			{
				IterTmpE iter_tmp = iter1;
				iter_tmp++;
				remove((*iter1).get());
				iter1 = iter_tmp;
			};
		}
	template <class NodeT, class EdgeT>
		void Graph<NodeT, EdgeT>::remove(NodeT& node)
		{
			typedef typename list<reference_wrapper<EdgeT>>::iterator IterTmp;
			IterTmp iter = node.list_of_refs_to_preds_edges.begin();
			do
			{
				IterTmp iter_tmp = iter;
				if (iter != node.list_of_refs_to_preds_edges.end())
				{
					iter_tmp++;
					remove((*iter).get());
					iter = iter_tmp;
				}
				else
					break;
			} while (iter != node.list_of_refs_to_preds_edges.end());
			iter = node.list_of_refs_to_succs_edges.begin();
			do
			{
				IterTmp iter_tmp = iter;
				if (iter != node.list_of_refs_to_succs_edges.end())
				{
					iter_tmp++;
					remove((*iter).get());
					iter = iter_tmp;
				}
				else
					break;
			} while (iter != node.list_of_refs_to_succs_edges.end());
			list_of_nodes.erase(node.iter_of_itself_in_general_list);
			node.ref_to_graph.nodes_amount--;
			delete &node;
		}
	template <class NodeT, class EdgeT>
		EdgeT& Graph<NodeT, EdgeT>::Node::first_pred()
		{
			if (num_preds() < 1)
				throw Error("Amount of preds edges < 1, can't return \"first_pred()\"");
			else
				return (*(list_of_refs_to_preds_edges.begin())).get();

		}
	template <class NodeT, class EdgeT>
		EdgeT& Graph<NodeT, EdgeT>::Node::first_succ()
		{
			if (num_succs() < 1)
				throw Error("Amount of succs edges < 1, can't return \"first_succ()\"");
			else
				return (*(list_of_refs_to_succs_edges.begin())).get();
		}
	template <class NodeT, class EdgeT>
		UInt32 Graph<NodeT, EdgeT>::Node::num_preds() const
		{
			return list_of_refs_to_preds.size();
		}
	template <class NodeT, class EdgeT>
		UInt32 Graph<NodeT, EdgeT>::Node::num_succs() const
		{
			return list_of_refs_to_succs.size();
		}
	template <class NodeT, class EdgeT>
		Graph<NodeT, EdgeT>::Node::~Node()	{}

	template <class NodeT, class EdgeT>
		Graph<NodeT, EdgeT>::Edge::~Edge()	{}

	template <class NodeT, class EdgeT>
		NodeT& Graph<NodeT, EdgeT>::Edge::pred()
		{
			return ref_to_pred;
		}
	template <class NodeT, class EdgeT>
		NodeT& Graph<NodeT, EdgeT>::Edge::succ()
		{
			return ref_to_succ;
		}
	template <class NodeT, class EdgeT>
		typename Graph<NodeT, EdgeT>::UId
		Graph<NodeT, EdgeT>::Edge::uid() const
		{
			return uniq_num;
		}
	template <class NodeT, class EdgeT>
		Graph<NodeT, EdgeT>::Edge::Edge(NodeT& p, NodeT& s) :
		ref_to_pred(p),
		ref_to_succ(s),
		ref_to_graph(p.ref_to_graph),
		uniq_num(p.ref_to_graph.counter)
		{
			ref_to_graph.edges_amount++;
			ref_to_graph.counter++;
		}
	template <class NodeT, class EdgeT>
		void Graph<NodeT, EdgeT>::remove(EdgeT& edge)
		{
			edge.ref_to_pred.list_of_refs_to_succs.erase(edge.iter_of_ref_to_succ_in_pred);
			edge.ref_to_pred.list_of_refs_to_succs_edges.erase(edge.iter_of_ref_to_edge_in_pred);

			edge.ref_to_succ.list_of_refs_to_preds.erase(edge.iter_of_ref_to_pred_in_succ);
			edge.ref_to_succ.list_of_refs_to_preds_edges.erase(edge.iter_of_ref_to_edge_in_succ);

			list_of_edges.erase(edge.iter_of_itself_in_general_list);
			edge.ref_to_graph.edges_amount--;
			delete &edge;
		}
	template <class NodeT, class EdgeT> 
		template <class TypeContent, class TypeContainer>
		typename TypeContent&
		Graph<NodeT, EdgeT>::general_iterator<TypeContent, TypeContainer>::operator*()
		{
			return (*iter).get();
		}
	template <class NodeT, class EdgeT>
		template <class TypeContent, class TypeContainer>
		bool Graph<NodeT, EdgeT>::general_iterator<TypeContent, TypeContainer>::operator==(const general_iterator& b)
		{
			return this->iter == b.iter;
		}
	template <class NodeT, class EdgeT>
		template <class TypeContent, class TypeContainer>
		bool Graph<NodeT, EdgeT>::general_iterator<TypeContent, TypeContainer>::operator!=(const general_iterator& b)
		{
			return this->iter != b.iter;
		}
	template <class NodeT, class EdgeT>
		template <class TypeContent, class TypeContainer>
		typename Graph<NodeT, EdgeT>::general_iterator<TypeContent, TypeContainer>&
		Graph<NodeT, EdgeT>::general_iterator<TypeContent, TypeContainer>::operator++()
		{
			++iter;
			return *this;
		}
}; // namespace Task