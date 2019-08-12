#pragma once
#include "node.h"
#include <cmath>
#include <boost/serialization/utility.hpp>
namespace Info_Coupling{
template <int dim>
class Network;//forward decleration of class Network

template <int dim>
class Link{
    private:
        double RII;
        std::pair<Node<dim>*,Node<dim>*> Nodes;
        bool isWorking;
        //additional info
    public:
        /**
        * @param[out] unit_vector directional vector of two Nodes
        */
		FIM_API void direction(double* unit_vector);

        /** compute \f$ \lambda \mathbf{u}\mathbf{u}^T\f$
        * @param[out] coupling_matrix 2 times 2 coupling matrix,only the lower triangle is stored
        */
		FIM_API void coupling_term(double* coupling_matrix);
        /** constructor
        */
        Link(){}  
        Link(Node<dim>* node_1,Node<dim>* node_2,double ranging_info):
            RII(ranging_info),Nodes(node_1,node_2)
        {
            assert(ranging_info>=0);
            isWorking=true;
        }
        template <class Archive>
        inline void serialize(Archive &ar, const unsigned int version=1)//!< save Node to archive
        {
            ar & Nodes;
            ar & RII;
        }
        template <int dim2>
        friend std::ostream &operator << (std::ostream &out,const Link<dim2> &link);
        template <int dim2>
        friend bool operator == (const Link<dim2>& lhs,const Link<dim2>& rhs){
            return (fabs(lhs.RII-rhs.RII)<1e-4)&&(*lhs.Nodes.first==*rhs.Nodes.first)&&(*lhs.Nodes.second==*rhs.Nodes.second);
        }
        
        friend class Network<dim>;
};
}