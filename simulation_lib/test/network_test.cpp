#define _USE_MATH_DEFINES
#include "network.h"
#include "test.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
using namespace Info_Coupling;
int main(){
 //test constructor and ostream
 double theta=0;
 Node<2> node_1(cos(theta),sin(theta));
 Node<2> node_2(cos(M_PI/3+theta),sin(M_PI/3+theta));
 Node<2> node_3(cos(4*M_PI/3+theta),sin(4*M_PI/3+theta));
 Network<2> net;
 Link<2> link_12(&node_1,&node_2,1.0);
 Link<2> link_23(&node_2,&node_3,1.0);
 Link<2> link_31(&node_3,&node_1,1.0);
 
  net.add_link(link_12);
  net.add_link(link_23);
  net.add_link(link_31);
  assert(net.link_count()==3);  
  test_stream<<net;  

   //test eigen info
   int error_code=0;
   double eigenvalues[2];
   net.eigen_info(0/*first node index*/,eigenvalues,error_code);
   if(error_code>0){
       test_stream<<"Error test EFIM!";
       exit(-1);
   }
   test_stream<<eigenvalues[0]<<'\n';
   test_stream<<eigenvalues[1]<<'\n';      
   assert(fabs(eigenvalues[0]-0.625)+fabs(eigenvalues[1]-0.666667)<1e-4);       
     
   
   //test node degree info
   std::vector<unsigned int> degree_list;
   assert(net.get_degree(node_1,degree_list)==0);
   //test_stream<<"error status: "<<net.get_degree(node_1,degree_list)<<std::endl;
   assert(degree_list.size()==2);
   
   //test SPEB
   assert(fabs(net.SPEB(0)-1.29167)<1e-4);
   //test_stream<<net.SPEB(0)<<std::endl;
   
   //test clear_all();
   net.clear_all();
   assert(net.link_count()==0);
   
   
   return 0;
}