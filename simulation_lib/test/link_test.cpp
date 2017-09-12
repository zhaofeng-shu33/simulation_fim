#include "test.h"
#include "link.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
using namespace Info_Coupling;
int main(){
 //test constructor and ostream
 Node<2> node_1(1,2);
 Node<2> node_2(2,4.0);
 Link<2> my_link(&node_1,&node_2,1.0);
 test_stream<<my_link<<std::endl;
 //test unit vector
 double unit_vector[2];
 my_link.direction(unit_vector);
 test_stream<<"unit vector: "<<unit_vector[0]<<' '<<unit_vector[1]<<std::endl;
 assert(fabs(unit_vector[0]-1.0/sqrt(5.0))+fabs(unit_vector[1]-2.0/sqrt(5.0))<1e-5);
 //test coupling term
 double coupling_matrix[3];
 my_link.coupling_term(coupling_matrix);
 test_stream<<"coupling_term: "<<coupling_matrix[0]<<' '<<coupling_matrix[1]<<' '<<coupling_matrix[2]<<std::endl;
 assert(fabs(coupling_matrix[0]-0.2)+fabs(coupling_matrix[1]-0.4)+fabs(coupling_matrix[2]-0.8)<1e-5); 
 //test oarchive
 std::ofstream fout("link_data.txt");
 boost::archive::text_oarchive oa(fout);
 my_link.serialize(oa);
 fout.close();
 
 //test iarchive
 Link<2> your_link;
 std::ifstream fin("link_data.txt");
 boost::archive::text_iarchive ia(fin);
 your_link.serialize(ia);
 assert(my_link==your_link); 
 test_stream<<your_link;
 return 0;
}