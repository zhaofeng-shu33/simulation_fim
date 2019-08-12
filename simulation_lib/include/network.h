#pragma once
#include "link.h"
#include <map>
#include <vector>
#if _WIN32
#include "f2c.h"
#endif
#include "clapack.h"
namespace Info_Coupling{                

template <int dim>
class Link;//forward decleration of class Link
template <int dim>
class Network{
    typedef long int lapack_int;
    private:
        std::map<Node<dim>*,std::vector<unsigned int>/*Index+AdjacencyList*/> NodeList;
        std::vector<Link<dim>> LinkList;
		void assemble_matrix(double* fim);
    public:
        Network(){}
        /** given the node, return its adjacency list vector in AdjacencyList
        * error code -1 represents the node is not in the network
        */
        FIM_API int get_degree(Node<dim>& node,std::vector<unsigned int>& AdjacencyList);
        void get_direction(unsigned int link_index,double* unit_vector){LinkList[link_index].direction(unit_vector);}
		FIM_API void add_link(Link<dim>& link);
        void clear_all(){
            LinkList.clear();
            NodeList.clear();
        }
        unsigned int link_count(){return LinkList.size();}
        void disable_link(unsigned int link_index){LinkList[link_index].isWorking=false;}
        void enable_link(unsigned int link_index){LinkList[link_index].isWorking=true;}
        void enable_all(){
            for(auto& i:LinkList) i.isWorking=true;
        }
        /** assemble FIM. Anchor contribution is assumed as identity matrix at present.
        * @param[out] fim positive symmetric matrix for assembling
        */
        template <class Archive>
        inline void serialize(Archive &ar, const unsigned int version=1)//!< save Node to archive
        {
            throw std::invalid_argument("serialization for network is not implemented yet");
        }
        double SPEB(unsigned int node_index){
            int error_code=0;
            double eigenvalues[2];      
            eigen_info(node_index/*first node index*/,eigenvalues,error_code);
            if(error_code>0 || eigenvalues[0]<0 || eigenvalues[1]<0){
                return -1;/*invalid SPEB*/
            }
            return (eigenvalues[0]+eigenvalues[1]);//return matrix trace of (EFIM)^{-1}
        }            
		void efim(unsigned int node_index,double* matrix,int& error_code);//!< compute inverse of EFIM for the given node        
		FIM_API void eigen_info(unsigned int node_index,double* eigenvalues,int& error_code);
        template <int dim>
        friend std::ostream &operator << (std::ostream &out,const Network<dim> &network);        
};
}