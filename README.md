##Machine Learning: Prac1 - Artificial Neural Network Backpropagation

**Author** : Muhummad Yunus Patel  
**Student#** : PTLMUH006  
**Date**  : 29-October-2015

###Introduction:
The backpropagation algorithm is a supervised learning algorithm based on gradient descent. For this assignment, the back-propagation algorithm was used to train a neural network used to control minesweeper objects. The minesweepers are then placed in a simulation framework where they must gather mines whilst also avoiding rocks and super-mines. The neural network is trained to turn away from rocks and super-mines and turn towards mines.

This report serves to document the algorithms used to implement and train the neural network and present the results of the training. The implementation of the neural network can be found in the CNeuralNet.cpp file. This class is then used by the backpropagation controller to train the neural network that controls the minesweepers in the simulation.


###Conclusions:
The CBackPropagationController file used the CNeuralNet class to create and train  a neural network that will be used to control the minesweepers in the simulation. The network is trained based on the training data file specified in the params.ini file.

In order to test that the neural net was correctly trained, the simulation was run for 20 trials in 3 test environments. The simulation was run for both a trained and untrained neural network in each case. The averaged results of the 20 trial runs were then tabulated in the report (available on request).

From the tabulated results, we see that the trained minesweepers have clearly learned the behaviour that we have trained them for. The trained minesweepers, on average, die much, much less than the untrained minesweepers. Even though, the untrained minesweepers did pick up more mines than the trained minesweepers, their behaviour was not sustainable. We see this in the third environment where almost all of the untrained  minesweepers were dying on every trial but the trained minesweepers were successfully staying alive and still collecting mines. The trained minesweepers had effectively learned to avoid the super-mines and rocks whilst still collecting the mines.


###Usage:
 * Compile and run as a Visual Studio 2013 project.
 * Only works on Windows.