#define _USE_MATH_DEFINES
#include <chrono>
#include "network.h"
#include <cstring>
#include <random>
#include <fstream>
#include <ostream>
#define MAX_NODE 9
#define AVERAGE_TIMES 1000
using namespace Info_Coupling;
namespace linear_network_simulation{
    void inline upper_q1(std::ostream& out,double MU/*velocity mean*/,double base){
        double last=base;
        for(int i=1;i<MAX_NODE;i++){
            last-=log(1+MU*MU);
            out<<last;
            if(i!=MAX_NODE-1)
                out<<',';
        }
        out<<std::endl;
    }
    void inline upper_q2(std::ostream& out,double MU/*velocity mean*/){
        double base=log(MU);
        upper_q1(out,MU,base);
    }
    void inline sim_q2(std::default_random_engine& generator,std::ostream& out,double MU,double SIGMA){
      std::uniform_real_distribution<double> random_angle(0.0,2*M_PI);
      std::normal_distribution<double> random_speed(MU,SIGMA);
      //random velocity:Gauss

       /*network initialization */ 
       Node<2> node_list[MAX_NODE];
       node_list[0]=Node<2>(0,0);
       Network<2> net;

        double x,y,angle,speed,bound; /*variables related to model */
        double result_log_array[MAX_NODE];
        /*purely anchor*/
        int average_counter=0; /*data storage */
        memset(result_log_array,0x00,sizeof(double)*(MAX_NODE));
        result_log_array[0]=2.0;
        std::cout<<"Sim Q2 starts: MU="<<MU<<",SIGMA="<<SIGMA<<std::endl;
     while(average_counter<AVERAGE_TIMES){     
         for(int i=1;i<MAX_NODE;i++){
              x=node_list[i-1].x();
              y=node_list[i-1].y();
              angle=random_angle(generator);
              speed=random_speed(generator);
              node_list[i]=Node<2>(x+speed*cos(angle),y+speed*sin(angle));
              Link<2> tmp_link(&node_list[i-1],&node_list[i],1.0/(speed*speed));
              net.add_link(tmp_link);      
              bound=net.SPEB(0);//node_index=0
              if(bound<0){
               std::cerr<<"Fatal Error: SPEB less than zero!";
               exit(-1);
              }
              #ifdef _DEBUG
              if(isinf(bound)){
                 std::cout<<"At "<<average_counter<<", node index "<<i<<" bound is infinity"<<std::endl;              
              }
              #endif
             result_log_array[i]+=bound;         
          }
        average_counter++;  
        net.clear_all();
     }
     for(int i=1;i<MAX_NODE;i++){
        result_log_array[i]/=AVERAGE_TIMES;
        //std::cout<<result_log_array[i-1]<<std::endl;
        result_log_array[i-1]=log(result_log_array[i-1]-result_log_array[i]);
        
        out<<std::fixed<<result_log_array[i-1];
        if(i!=MAX_NODE-1)
            out<<',';
     }
     out<<std::endl;
     std::cout<<"Sim Q2 Ends."<<std::endl;     
 }
}
int main(){
  /*random seed*/
  auto seed1 = std::chrono::system_clock::now().time_since_epoch().count();      
  
   /*random generator initialization*/
   std::default_random_engine generator(seed1);
   //random angle:uniform
   //file io
    std::ofstream fout("result.csv");
    //first group
    double MU=1.0,SIGMA=0.1;
    std::cout<<"Start computation of first group..."<<std::endl; 
    
    linear_network_simulation::sim_q2(generator,fout,MU,SIGMA);
    std::cout<<"Computes upper q2..."<<std::endl; 
    linear_network_simulation::upper_q2(fout,MU);

    std::cout<<"computation of first group ends."<<std::endl; 
    
    //second group
    MU=0.5;SIGMA=0.05;

    std::cout<<"Start computation of second group..."<<std::endl; 
    
    linear_network_simulation::sim_q2(generator,fout,MU,SIGMA);    
    std::cout<<"Computes upper q2..."<<std::endl;     
    linear_network_simulation::upper_q2(fout,MU);    

    std::cout<<"computation of second group ends."<<std::endl; 

    fout.close();
    exit(0);
}
