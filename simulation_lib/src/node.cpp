#pragma once
#include "node.h"
namespace Info_Coupling{
template <int dim>
std::ostream &operator << (std::ostream            &out,
                           const Node<dim> &p)
{
  for (unsigned int i=0; i<dim-1; ++i)
    out << p.Coordinate[i] << ' ';
  out << p.Coordinate[dim-1];
  return out;
}
template <int dim>
double distance(const Node<dim>& Node1,const Node<dim>& Node2){
        double D=0;
        for(int i=0;i<dim;i++){
            D+=(Node1.Coordinate[i]-Node2.Coordinate[i])*(Node1.Coordinate[i]-Node2.Coordinate[i]);
        }
        D=std::sqrt(D);
        return D;
}
template FIM_API std::ostream& operator << (std::ostream &out,const Node<2> &p);
template FIM_API double distance(const Node<2>& Node1,const Node<2>& Node2);
}
template class Info_Coupling::Node<2>;
