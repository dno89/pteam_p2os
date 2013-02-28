rosbuild_add_library(target_detector TargetDetector.cpp)
rosbuild_add_library(take_the_ball TakeTheBall.cpp)
rosbuild_add_library(collision_avoidance CollisionAvoidance.cpp)
rosbuild_add_library(move_throughward_goal MoveThroughwardGoal.cpp)
rosbuild_add_library(stay_in_the_middle StayInTheMiddle.cpp)


#TODO: quando si aggiunge un nuovo behaviors aggiungere una riga come quella sopra con i rispettivi file e modificare il file CMakeLists.txt principale includendo il nuovo behavior come link_libraries al nodo behaviors_node
