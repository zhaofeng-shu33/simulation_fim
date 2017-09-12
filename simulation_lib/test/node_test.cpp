#include "node.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <sstream>
#include "test.h"
using namespace Info_Coupling;
int main(){
 //test node serialization io
 Node<2> newNode(4.5,5);
 std::ostringstream s_o; 
 boost::archive::text_oarchive oa(s_o);
 newNode.serialize(oa);
 std::istringstream s_i(s_o.str());
 boost::archive::text_iarchive ia(s_i);
 Node<2> newNode2;
 newNode2.serialize(ia);
 assert(newNode==newNode2);
 test_stream<<newNode2<<std::endl;
 
 //test Node distance
 Node<2> thirdNode(4,5.5);
 assert(fabs(distance(newNode,thirdNode)-0.7071)<1e-3);
 return 0;
}