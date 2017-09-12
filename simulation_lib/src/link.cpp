#pragma once
#include "link.h"
namespace Info_Coupling{
template <int dim>
class Network;//forward decleration of class Network
template <int dim>
FIM_API void Link<dim>::direction(double* unit_vector){
            assert(dim==2);
            double delta_x=Nodes.second->x()-Nodes.first->x();
            double delta_y=Nodes.second->y()-Nodes.first->y();
            double delta_norm=sqrt(delta_x*delta_x+delta_y*delta_y);
            unit_vector[0]=delta_x/delta_norm;
            unit_vector[1]=delta_y/delta_norm;            
        }

template <int dim>
FIM_API void Link<dim>::coupling_term(double* coupling_matrix){
            double* unit_vector=new double[dim];
            direction(unit_vector);
            coupling_matrix[0]=RII*unit_vector[0]*unit_vector[0];
            coupling_matrix[1]=RII*unit_vector[0]*unit_vector[1];
            coupling_matrix[2]=RII*unit_vector[1]*unit_vector[1];            
            delete [] unit_vector;
        }
template <int dim>
std::ostream& operator << (std::ostream            &out,
                           const Link<dim> &link)
{
  out<<*link.Nodes.first<<','<<*link.Nodes.second<<",RII "<<link.RII;
  return out;
}
}
template FIM_API
std::ostream& Info_Coupling::operator << (std::ostream            &out,
                           const Info_Coupling::Link<2> &link);
template class Info_Coupling::Link<2>; 
