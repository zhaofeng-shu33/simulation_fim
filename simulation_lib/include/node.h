#pragma once
#ifdef FIM_EXPORTS
#define FIM_API __declspec(dllexport)
#elif defined FIM_IMPORTS
#define FIM_API __declspec(dllimport)
#else
#define FIM_API
#endif
#include <cassert>
#include <stdexcept>
#include <iostream>
namespace Info_Coupling{
template <int dim>
/** Class for Node 
* 
*/
class Node{
    private:
        double Coordinate[dim];
        bool IsAgent;
        //Additional Info goes here
    public:
        double x() const
        {return Coordinate[0];}
        double y() const
        {return Coordinate[1];}
        double z(){
            assert(dim==3);
            return Coordinate[2];
            }
        /** \param x x coordinate of node
        *   \param y y coordinate of node
        *   \param type IsAgent=type
        */
        Node(double x,double y,bool type=true)
        {
            Coordinate[0]=x;
            Coordinate[1]=y;  
            IsAgent=type;
        }
        Node(){}
        Node(double x,double y,double z)//!< not implemented yet
        {
            throw std::invalid_argument("Node for dim==3 is not implemented yet");
        }
        void toAnchor(){IsAgent=false;}
        void toAgent(){IsAgent=true;}
        bool is_agent(){return IsAgent;}
        bool operator ==(const Node<dim>& other) 
        {return fabs(other.x()-Coordinate[0])+fabs(other.y()-Coordinate[1])<1e-4;}
        template <class Archive>
        inline void serialize(Archive &ar, const unsigned int version=1)//!< save Node to archive
        {
            ar & Coordinate;
            ar & IsAgent;
        }
        template <int dim2>
        friend std::ostream &operator << (std::ostream& out,const Node<dim2>& p);
        template <int dim2>
        friend double distance(const Node<dim2>& Node1,const Node<dim2>& Node2);
};
}