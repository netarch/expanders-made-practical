#ifndef connection_matrix
#define connection_matrix

#include "main.h"
#include "tcp.h"
#include "topology.h"
#include "randomqueue.h"
#include "eventlist.h"
#include <random>
#include <list>
#include <set>
#include <map>

struct connection{
  int src, dst;
};

struct Flow{
  int src, dst, bytes;
  double start_time_ms;
  Flow (int _src, int _dst, int _bytes, double _start_time_ms):
    src(_src), dst(_dst), bytes(_bytes), start_time_ms(_start_time_ms) {}
};

class ConnectionMatrix{
 public:
  ConnectionMatrix(int );
  void setPermutation(int conn);
  void setPermutation();
  void setRandom(int conns);
  void setRandomFlows(int conns);
  void setStride(int many);
  void setLocalTraffic(Topology* top);
  void setStaggeredRandom(Topology* top,int conns,double local);
  void setStaggeredPermutation(Topology* top,double local);
  void setVL2();
  void setHotspot(int hosts_per_spot,int count);
  void setManytoMany(int hosts); 
  void setAlltoAll(Topology *top); 
  void setAlltoFew(Topology *top, int nmasters); 
  void setFewtoSome(Topology *top, int nmasters, int nclients); 
  //All to all between a specified number of racks
  void setRacktoRack(Topology *top, int nracks);
  //permutation among racks, nflows b/w each permutation pair
  void setRackPermutation(Topology *top, int nRackFlows);
  void setUniform(int flowsPerHost);
  void setTrafficFromFile(Topology *top, string filename);
  void setTrafficFromFile2(Topology *top, string filename);
  void setMaxWeightMatching(Topology *top);

  vector<connection*>* getAllConnections();
  set<pair<int, int> > addExtraConns(int num);
  map<int,vector<int>*> connections;
  int N;


  /* For flow sizes */
  vector<Flow> flows;
  void setFlowsFromFile(Topology* top, string filename);
  void setFewtoSomeFlows(Topology* top, int nmasters, int nclients);
  void setRacktoRackFlows(Topology* top, int nmasters, int nclients);
  int genFlowBytes();
  /* For generating pareto dist. via exp dist. */
  int mean_bytes = 100.0 * 1024;
  double shape = 1.05;
  double scale; // = mean_bytes * (shape - 1)/shape;   
  std::default_random_engine generator;
  std::exponential_distribution<double> exp_distribution;

};

#endif
