#pragma once
#include <cmath>
#include <cstring>
#include "network.h"
namespace Info_Coupling{                

template <int dim>
void Network<dim>::assemble_matrix(double* fim)//assuming contribution from anchors is identity matrix
        {
            double coupling_matrix[3],coeff;
            unsigned int i,j;            
            unsigned int matrix_dim=dim*NodeList.size();
            //assemble contribution from anchors
            for(unsigned int i=0;i<matrix_dim;i++)
               fim[i*matrix_dim+i]=1;
            //assemble contribution from agents
            for(auto link_iterator=LinkList.begin();link_iterator!=LinkList.end();link_iterator++){
                if(!link_iterator->isWorking) continue;
                link_iterator->coupling_term(coupling_matrix);
                i=NodeList[link_iterator->Nodes.first][0];
                j=NodeList[link_iterator->Nodes.second][0];
                coeff=link_iterator->RII;
                fim[2*i*matrix_dim+2*i]+=coeff*coupling_matrix[0];
                fim[2*i*matrix_dim+2*i+1]+=coeff*coupling_matrix[1];
                fim[(2*i+1)*matrix_dim+2*i]+=coeff*coupling_matrix[1];
                fim[(2*i+1)*matrix_dim+(2*i+1)]+=coeff*coupling_matrix[2];
                fim[2*j*matrix_dim+2*j]+=coeff*coupling_matrix[0];
                fim[2*j*matrix_dim+2*j+1]+=coeff*coupling_matrix[1];
                fim[(2*j+1)*matrix_dim+2*j]+=coeff*coupling_matrix[1];
                fim[(2*j+1)*matrix_dim+(2*j+1)]+=coeff*coupling_matrix[2];
                
                fim[2*i*matrix_dim+2*j]-=coeff*coupling_matrix[0];
                fim[2*i*matrix_dim+2*j+1]-=coeff*coupling_matrix[1];
                fim[(2*i+1)*matrix_dim+2*j]-=coeff*coupling_matrix[1];
                fim[(2*i+1)*matrix_dim+(2*j+1)]-=coeff*coupling_matrix[2];                
                fim[2*j*matrix_dim+2*i]-=coeff*coupling_matrix[0];
                fim[2*j*matrix_dim+2*i+1]-=coeff*coupling_matrix[1];
                fim[(2*j+1)*matrix_dim+2*i]-=coeff*coupling_matrix[1];
                fim[(2*j+1)*matrix_dim+(2*i+1)]-=coeff*coupling_matrix[2];                                
            }
        }
template <int dim>
void Network<dim>::efim(unsigned int node_index,double* matrix,int& error_code)//!< compute inverse of EFIM for the given node
        {              
              lapack_int n=2*NodeList.size(),info,nrhs=2,lda=n,ldb=n;
              double* a=new double[n*n];
              memset(a,0x00,n*n*sizeof(double));
              assemble_matrix(a);
              double* b=new double[nrhs*n];
              memset(b,0x00,2*n*sizeof(double));
              lapack_int* ipiv=new lapack_int[n];
              b[2*node_index]=1;
              b[2*node_index+n+1]=1;
        /** Subroutine  int dgesv_(integer *n, integer *nrhs, doublereal *a, integer 
        *   lda, integer *ipiv, doublereal *b, integer *ldb, integer *info);
        */
                dgesv_(&n, &nrhs, a, &lda, ipiv,b, &ldb,&info);/*d means double precision*/
                error_code=info;
                /* Check for the exact singularity */
                if(info > 0) {/*info==0 succeeds*/
                        return;
                }
                assert(fabs(b[2*node_index+1]-b[2*node_index+n])<1e-3);
                matrix[0]=b[2*node_index]; 
                matrix[1]=b[2*node_index+1];
                matrix[2]=b[2*node_index+n+1];            
              delete [] a;
              delete [] b;
              delete [] ipiv;

        }

template <int dim>
FIM_API void Network<dim>::add_link(Link<dim>& link)
        {
        LinkList.push_back(link);
        auto iterator=NodeList.find(link.Nodes.first);
        if(iterator==NodeList.end()){//not found,append it
            NodeList[link.Nodes.first].push_back(NodeList.size()); //index for assembling matrix       
            NodeList[link.Nodes.first].push_back(LinkList.size()-1);
        }
        else
            iterator->second.push_back(LinkList.size()-1);
        iterator=NodeList.find(link.Nodes.second);
        if(iterator==NodeList.end()){//not found,append it
            NodeList[link.Nodes.second].push_back(NodeList.size()); //index for assembling matrix               
            NodeList[link.Nodes.second].push_back(LinkList.size()-1);   
        }            
        else
            iterator->second.push_back(LinkList.size()-1);
        }
        /** assemble FIM. Anchor contribution is assumed as identity matrix at present.
        * @param[out] fim positive symmetric matrix for assembling
        */
template <int dim>  
FIM_API void Network<dim>::eigen_info(unsigned int node_index,double* eigenvalues,int& error_code){
            assert(node_index<NodeList.size());
            double matrix[3];
            efim(node_index,matrix,error_code);
            if(error_code>0)
                return;
            double d[]={matrix[0],matrix[2]};
            double e=matrix[1];
            char compz='N'/*compute eigenvalue only*/;
            lapack_int info,n=2,ldz/*leading dimension of DOUBLE	PRECISION array z*/=2;
            /** Subroutine  int dsteqr_(char *compz, integer *n, doublereal *d__, 
            *  doublereal *e, doublereal *z__, integer *ldz, doublereal *work, 
               integer *info);*/
            dsteqr_(&compz,&n,d,&e,NULL,&ldz,NULL,&info);
            error_code=info;
            if(error_code>0) return;
            eigenvalues[0]=d[0];
            eigenvalues[1]=d[1];
        }
template <int dim>
std::ostream& operator << (std::ostream            &out,
                           const Network<dim> &network)
{
  for(auto link_iterator=network.LinkList.begin();link_iterator!=network.LinkList.end();link_iterator++){
      out<<*link_iterator<<std::endl;
  }  
  return out;
}
template <int dim>
FIM_API int Network<dim>::get_degree(Node<dim>& node,std::vector<unsigned int>& AdjacencyList){
            auto iterator=NodeList.find(&node);
            if(iterator==NodeList.end()){
                return -1;
                }
            auto _AdjacencyList=iterator->second;
            AdjacencyList.assign((++_AdjacencyList.begin()),_AdjacencyList.end());
            return 0;
}
}
template
FIM_API
std::ostream& Info_Coupling::operator << (std::ostream            &out,
                           const Info_Coupling::Network<2> &network);

template class Info_Coupling::Network<2>;
