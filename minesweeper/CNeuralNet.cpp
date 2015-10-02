/*
                                                                           
   (               )                                        )              
 ( )\     )     ( /(       (                  (  (     ) ( /((             
 )((_) ( /(  (  )\())`  )  )(   (  `  )   (   )\))( ( /( )\())\  (   (     
((_)_  )(_)) )\((_)\ /(/( (()\  )\ /(/(   )\ ((_))\ )(_)|_))((_) )\  )\ )  
 | _ )((_)_ ((_) |(_|(_)_\ ((_)((_|(_)_\ ((_) (()(_|(_)_| |_ (_)((_)_(_/(  
 | _ \/ _` / _|| / /| '_ \) '_/ _ \ '_ \/ _` |/ _` |/ _` |  _|| / _ \ ' \)) 
 |___/\__,_\__||_\_\| .__/|_| \___/ .__/\__,_|\__, |\__,_|\__||_\___/_||_|  
                    |_|           |_|         |___/                         

 For more information on back-propagation refer to:
 Chapter 18 of Russel and Norvig (2010).
 Artificial Intelligence - A Modern Approach.
 */

#include <stdlib.h>     /* srand, rand */
#include <math.h>		/* exp */

#include "CNeuralNet.h"

/**
 The constructor of the neural network. This constructor will allocate memory
 for the weights of both input->hidden and hidden->output layers, as well as the input, hidden
 and output layers.
*/
CNeuralNet::CNeuralNet(uint inputLayerSize, uint hiddenLayerSize, uint outputLayerSize, double lRate, double mse_cutoff) :
inputLayerSize(inputLayerSize),
hiddenLayerSize(hiddenLayerSize),
outputLayerSize(outputLayerSize),
lRate(lRate),
mse_cutoff(mse_cutoff)
	//you probably want to use an initializer list here
{
	//TODO
	printf("NODES::: %d %d %d\n", inputLayerSize, hiddenLayerSize, outputLayerSize);
	printf("LRATE::: %f MSECUTOFF::: %f\n", lRate, mse_cutoff);

	//allocate space for input_to_hidden weights
	for (uint i = 0; i < inputLayerSize; i++){
		input_to_hidden.push_back(std::vector<double>());
	}

	//allocate space for hidden_to_output weights
	for (uint i = 0; i < hiddenLayerSize; i++){
		hidden_to_output.push_back(std::vector<double>());
	}

	initWeights(); //REMOOOOVVVEEEE
	//std::vector<double> temp = { 1, 1 }; //REMOOOOOVE
	//feedForward(temp); //REMOOOOOVE
}

/**
 The destructor of the class. All allocated memory will be released here
*/
CNeuralNet::~CNeuralNet() {
	//TODO
}

double getRandomWeight(){
	return -0.5 + ((double)rand() / (double)RAND_MAX);
}

/**
 Method to initialize the both layers of weights to random numbers
*/
void CNeuralNet::initWeights(){
	//TODO

	//initialize input_to_hidden weights
	//input_to_hidden[inputNode][hiddenNode]
	for (uint inputNode = 0; inputNode < inputLayerSize; inputNode++){
		for (uint hiddenNode = 0; hiddenNode < hiddenLayerSize; hiddenNode++){
			input_to_hidden[inputNode].push_back(getRandomWeight());
			//printf("inputNode%d to hiddenNode%d = %f\n", inputNode, hiddenNode, input_to_hidden[inputNode][hiddenNode]);
		}
	}

	//initialize hidden_to_output weights
	//hidden_to_output[hiddenNode][outputNode]
	for (uint hiddenNode = 0; hiddenNode < hiddenLayerSize; hiddenNode++){
		for (uint outputNode = 0; outputNode < outputLayerSize; outputNode++){
			hidden_to_output[hiddenNode].push_back(getRandomWeight());
			//printf("hiddenNode%d to outputNode%d = %f\n", hiddenNode, outputNode, hidden_to_output[hiddenNode][outputNode]);
		}
	}
}


double sigmoid(double t){
	return (1.0) / (1.0 + exp(-1 * t));
}

double sigmoid_d(double t){
	return sigmoid(t) * (1.0 - sigmoid(t));
}

/**
 This is the forward feeding part of back propagation.
 1. This should take the input and copy the memory (use memcpy / std::copy)
 to the allocated _input array.
 2. Compute the output of at the hidden layer nodes 
 (each _hidden layer node = sigmoid (sum( _weights_h_i * _inputs)) //assume the network is completely connected
 3. Repeat step 2, but this time compute the output at the output layer
*/
void CNeuralNet::feedForward(const std::vector<double> inputs) {
	//TODO

	//reset all the output vectors
	_input.clear();
	_hidden.clear();
	_output.clear();

	//get the result of the input layer
	_input.resize(inputs.size());
	std::copy(inputs.begin(), inputs.end(), _input.begin());

	//push inputs' result through the hidden layer to get the _hidden result
	for (uint hiddenNode = 0; hiddenNode < hiddenLayerSize; hiddenNode++) {
		double sum = 0;
		for (uint inputNode = 0; inputNode < inputLayerSize; inputNode++) {
			sum += input_to_hidden[inputNode][hiddenNode] * _input[inputNode];
		}

		_hidden.push_back(sigmoid(sum));
	}

	//push _hidden result through the output layer to get the _output result
	for (uint outputNode = 0; outputNode < outputLayerSize; outputNode++) {
		double sum = 0;
		for (uint hiddenNode = 0; hiddenNode < hiddenLayerSize; hiddenNode++) {
			sum += hidden_to_output[hiddenNode][outputNode] * _hidden[hiddenNode];
		}

		_output.push_back(sigmoid(sum));
	}

	/*for (uint outputNode = 0; outputNode < outputLayerSize; outputNode++) {
		printf("result at outputNode%d = %f\n", outputNode, _output[outputNode]);
	}*/
}



/**
 This is the actual back propagation part of the back propagation algorithm
 It should be executed after feeding forward. Given a vector of desired outputs
 we compute the error at the hidden and output layers (allocate some memory for this) and
 assign 'blame' for any error to all the nodes that fed into the current node, based on the
 weight of the connection.
 Steps:
 1. Compute the error at the output layer: sigmoid_d(output) * (difference between expected and computed outputs)
    for each output
 2. Compute the error at the hidden layer: sigmoid_d(hidden) * 
	sum(weights_o_h * difference between expected output and computed output at output layer)
	for each hidden layer node
 3. Adjust the weights from the hidden to the output layer: learning rate * error at the output layer * error at the hidden layer
    for each connection between the hidden and output layers
 4. Adjust the weights from the input to the hidden layer: learning rate * error at the hidden layer * input layer node value
    for each connection between the input and hidden layers
 5. REMEMBER TO FREE ANY ALLOCATED MEMORY WHEN YOU'RE DONE (or use std::vector ;)
*/
void CNeuralNet::propagateErrorBackward(const std::vector<double> desiredOutput){
	//TODO

	//compute the error at the output layer
	std::vector<double> _output_err;
	for (uint outputNode = 0; outputNode < outputLayerSize; outputNode++) {
		double o = _output[outputNode];
		double t = desiredOutput[outputNode];

		double error = o * (1.0 - o) * (t - o);
		_output_err.push_back(error);
	}

	//compute the error at the hidden layer
	std::vector<double> _hidden_err;
	for (uint hiddenNode = 0; hiddenNode < hiddenLayerSize; hiddenNode++) {
		double sum = 0;
		for (uint outputNode = 0; outputNode < outputLayerSize; outputNode++) {
			sum += hidden_to_output[hiddenNode][outputNode] * _output_err[outputNode];
		}

		double o = _hidden[hiddenNode];

		double error = o * (1.0 - o) * sum;
		_hidden_err.push_back(error);
	}

	//TODO: adjust hidden_to_output weights
	//3. Adjust the weights from the hidden to the output layer : learning rate * error at the output layer * error at the hidden layer
	//	for each connection between the hidden and output layers
	for (uint hiddenNode = 0; hiddenNode < hiddenLayerSize; hiddenNode++) {
		for (uint outputNode = 0; outputNode < outputLayerSize; outputNode++) {
			hidden_to_output[hiddenNode][outputNode] += lRate * _output_err[outputNode] * _hidden_err[hiddenNode];
		}
	}


	//TODO: adjust input_to_hidden weights
	//4. Adjust the weights from the input to the hidden layer : learning rate * error at the hidden layer * input layer node value
	//	for each connection between the input and hidden layers
	for (uint inputNode = 0; inputNode < inputLayerSize; inputNode++) {
		for (uint hiddenNode = 0; hiddenNode < hiddenLayerSize; hiddenNode++) {
			input_to_hidden[inputNode][hiddenNode] += lRate * _hidden_err[hiddenNode] * _input[inputNode];
		}
	}
}

/**
This computes the mean squared error
A very handy formula to test numeric output with. You may want to commit this one to memory
*/
double CNeuralNet::meanSquaredError(const std::vector<double> desiredOutput){
	/*TODO:
	sum <- 0
	for i in 0...outputLayerSize -1 do
		err <- desiredoutput[i] - actualoutput[i]
		sum <- sum + err*err
	return sum / outputLayerSize
	*/
	
	/*return 1;*/

	double sum = 0;
	for (uint outputNode = 0; outputNode < outputLayerSize; outputNode++) {
		double err = desiredOutput[outputNode] - _output[outputNode];
		sum += (err * err);
	}
	//printf("mseSum::: %f\n", sum);
	return (sum / (double)outputLayerSize);
}

/**
This trains the neural network according to the back propagation algorithm.
The primary steps are:
for each training pattern:
  feed forward
  propagate backward
until the MSE becomes suitably small
*/
void CNeuralNet::train(const std::vector<std::vector<double> > inputs,
	const std::vector<std::vector<double> > outputs, uint trainingSetSize) {
	//TODO
	printf("TRAINING\n");
	double error_sum = 0;
	do {
		error_sum = 0;

		for (uint trainingExample = 0; trainingExample < trainingSetSize; trainingExample++) {
			feedForward(inputs[trainingExample]);
			propagateErrorBackward(outputs[trainingExample]);

			error_sum += meanSquaredError(outputs[trainingExample]);
		}

		printf("Err:: %f %d\n", error_sum, trainingSetSize);
		//error_sum /= trainingSetSize;
	} while (error_sum > mse_cutoff);
}

/**
Once our network is trained we can simply feed it some input though the feed forward
method and take the maximum value as the classification
*/
uint CNeuralNet::classify(const std::vector<double> input){
	//return 1; //TODO: fix me
	feedForward(input);

	double max_value = _output[0];
	uint max_index = 0;

	for (uint outputNode = 0; outputNode < outputLayerSize; outputNode++) {
		if (_output[outputNode] > max_value) {
			max_value = _output[outputNode];
			max_index = outputNode;
		}
	}

	return max_index;
}

/**
Gets the output at the specified index
*/
double CNeuralNet::getOutput(uint index) const{
	return _output[index]; //TODO: fix me
}