/*
	Program Name: Perceptron
	@author: Gonzales Cenelia
	homepage: www.ai-search.4t.com

	This program features a complete Perceptron Neural Net Application.
	
	The perceptron is a program that learn concepts, i.e. it can learn to respond 
	with True (1) or False (0) for inputs we present to it, by repeatedly "studying" 
	examples presented to it. The Perceptron is a single layer neural network 
	whose weights and biases could be trained to produce a correct target vector when 
	presented with the corresponding input vector. 
	The training technique used is called the perceptron learning rule. 
	The perceptron generated great interest due to its ability to generalize 
	from its training vectors and work with randomly distributed connections. 
	Perceptrons are especially suited for simple problems in pattern classification.

    This code is copyrighted and has limited warranty.
*/
#include "cpnet.h"
#define WAIT(x) Sleep((long)(x));
#define CLEAR_SCREEN() system("cls");
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define MIN_ACCURACY 0.01
#define SECOND 1000

enum {DEFAULT, ANIM_T1, ANIM_T2, ANIM_T3, UNKNOWN} eAnimType;



CPnet::CPnet() {
	threshold = 0;
	Weight = 0;
	Target = 0;
	Output = 0;
	Input = 0;
	input = 0;
	delta = 0;
	bNeuralNetCreated = false;
	bNeuralNetTrained = false;
	bNeuralNetSaved = false;
	bNeuralNetLoaded = false;
	bNewModifications = false;
	szNeuralNetName = new char[MAX_PATH];
}

CPnet::~CPnet() {
	delete Weight;
	delete Input;
	delete Output;
	delete input;
	delete delta;
	delete Target;
	delete szNeuralNetName;
}

void CPnet::CPMenu(void) {
	int selection;
	while(selection != 8) {
		cout << "=================================================================\n";
		cout << "\tPerceptron Neural Net using Perceptron learning rule\n";
		cout << "=================================================================\n\n";
		cout << "[1]. Create a new Neural Net" << endl;
		cout << "[2]. Train the current Neural Net" << endl;
		cout << "[3]. Load a Neural Net from file" << endl;
		cout << "[4]. Test Neural Net" << endl;
		cout << "[5]. Save the current Net" << endl;
		cout << "[6]. Set training display" << endl;
		cout << "[7]. Display Neural Net Info" << endl;
		cout << "[8]. Quit the program" << endl  << endl;
		cout << "selection: ";
		selection = getche() - '0';
		WAIT(0.5*SECOND);
		CLEAR_SCREEN();
		switch(selection) {
		case 1:
			SaveCurrentData();
			cout << "\nCreating Neural Net...";
			WAIT(1*SECOND);
			CreateNet();
			break;
		case 2:
			if (bNeuralNetCreated) {
				cout << "\nTraining \"" << szNeuralNetName << "\" function..." << endl;
				WAIT(0.7*SECOND);
				cout << "Enter Learning rate: ";
				cin >> LEARNING_RATE;
				WAIT(0.7*SECOND);
				cout << "Enter number of epochs: ";
				cin >> CPN_ITER;
				NormalizeInput();
				NormalizeTarget();
				CLEAR_SCREEN();
				WAIT(0.7*SECOND);
				cout << "\nTraining \"" << szNeuralNetName << "\" function..." << endl;
				WAIT(2*SECOND);
				CLEAR_SCREEN();
				TrainNetwork();
			} else {
				UpdateScreen();
			}
			break;
		case 3:
			SaveCurrentData();
			cout << "\n\nLoading Neural Net..." << endl;
			WAIT(0.85*SECOND);
			cout << "\nEnter the name of the Neural Net or the complete path where "
			     << "the Net data can be found\n: ";
			cin.sync();
			cin.getline(szNeuralNetName, MAX_PATH);
			LoadNet();
			WAIT(1.5*SECOND);
			CLEAR_SCREEN();
			cout << "\n\n\n\n\n\n\n\n\n\t\t\tNeural Net loaded successfuly!" << endl;
			UpdateScreen();
			break;
		case 4:
			if (bNeuralNetTrained) {
				cout << "\nTesting \"" << szNeuralNetName << "\" function..." << endl;
				cout << "1. default test" << endl;
				cout << "2. selective test" << endl;
				cout << "\nselection: ";
				int nNumOfPattern;
				int sel = getche();
				CLEAR_SCREEN();
				WAIT(0.7*SECOND);
				DeNormalizeInput();
				DeNormalizeTarget();
				switch(sel) {
				case '1':
					TestNetwork();
					break;
				case '2':
					cout << "\nEnter the number of patterns to be tested: ";
					cin >> nNumOfPattern;
					SelectiveTest(nNumOfPattern);
					UpdateScreen();
					break;
				default:
					cout << "\nunknown selection." << endl;
					UpdateScreen();
				}
			} else {
				UpdateScreen();
			}
			break;
		case 5:
			if (bNeuralNetCreated) {
				if (fExist(szNeuralNetName)) {
					CLEAR_SCREEN();
					WAIT(0.5*SECOND);
					cout << "\n\"" << szNeuralNetName << "\"";
					cout << ": this file already exist,do you want to overwrite it?" << endl;
					cout << "Yes(y) No(n): ";
					char response;
					cin >> response;
					response = tolower(response);
					if(response == 'y') {
						SaveNet();
					} else {
						WAIT(0.5*SECOND);
						cout << "\nPlease enter a new name or a complete file path where the " 
							<< "Neural Net will be saved\n: ";
						cin.sync();
						cin.getline(szNeuralNetName, MAX_PATH);
						SaveNet();
					}
				} else {
					SaveNet();
				}
				CLEAR_SCREEN();
				WAIT(1.5*SECOND);
				cout << "\n\n\n\n\n\n\n\n\n\t\t\tThe Neural Net was saved successfuly!" << endl;
			}
			UpdateScreen();
			break;
		case 6:
			cout << "\n1. No animation" << endl;
			cout << "2. Animation type1" << endl;
			cout << "3. Animation type2" << endl;
			cout << "4. Animation type3" << endl;
			cout << "\nselection: ";
			char response;
			response = getche();
			switch(response) {
			case '1':
				eAnimType = DEFAULT;
				break;
			case '2':
				eAnimType = ANIM_T1;
				break;
			case '3':
				eAnimType = ANIM_T2;
				break;
			case '4':
				eAnimType = ANIM_T3;
				break;
			default:
				eAnimType = UNKNOWN;
				WAIT(0.7*SECOND);
				cout << "\nunknown selection." << endl;
			}
			if(eAnimType != UNKNOWN) {
				WAIT(0.7*SECOND);
				cout << "\nAnimation type set successfully!" << endl;
			} else {
				eAnimType = DEFAULT;
			}
			UpdateScreen();
			break;
		case 7:
			if (bNeuralNetCreated) {
				cout << "\nNeural Net Description..." << endl;
				WAIT(0.7*SECOND);
				cout << "Neural Net type: Perceptron" << endl;
				WAIT(0.5*SECOND);
				cout << "Number of Layers: 1" << endl;
				WAIT(0.5*SECOND);
				cout << "Neural Net Name: " << szNeuralNetName << endl;
				WAIT(0.5*SECOND);
				cout << "Number of Inputs per Neuron: " << input_num << endl;
				WAIT(0.5*SECOND);
				cout << "Number of Neurons: " << neuron_num << endl;
				WAIT(0.5*SECOND);
				cout << "Number of Targets: " << target_num << endl;
				WAIT(0.5*SECOND);
				cout << "Total Number of Inputs: " << total_input_num << endl;
				WAIT(1.4*SECOND);
				cout << "\nDisplaying inputs..." << endl;
				for(int i = 0; i < total_input_num; ++i) {
					WAIT(0.3*SECOND);
					cout << "Input[" << i << "] = " << Input[i] << endl;
				}
				WAIT(1.4*SECOND);
				cout << "\nDisplaying targets..." << endl;
				for(i = 0; i < target_num; ++i) {
					WAIT(0.3*SECOND);
					cout << "Target[" << i << "] = " << Target[i] << endl;
				}
			}
			UpdateScreen();
			break;
		case 8:
			SaveCurrentData();
			cout << "\n\n\n\n\nauthor: Gonzales Cenelia" << endl;
			cout << "homepage: www.ai-search.4t.com" << endl;
			cout << "Thanks for using this program!" << endl;
			break;
		default:
			cout << "\ninvalid selection." << endl;
			UpdateScreen();
		}
	}
}

// Creates a new Neural Net
void CPnet::CreateNet(void) {
	cout << "\n\nPlease enter a name for the Neural Net: ";
	cin.sync();
	cin.getline(szNeuralNetName, 30);
	WAIT(0.8*SECOND);
	cout << "Enter the number of inputs per Neuron: ";
	cin >> input_num;
	WAIT(0.8*SECOND);
	cout << "Enter the number of neurons: ";
	cin >> neuron_num;
	WAIT(0.8*SECOND);
	cout << "Enter threshold: ";
	cin >> threshold;
	cout << endl;
	target_num = neuron_num;
	total_input_num = input_num * neuron_num;
	bNeuralNetCreated = false;
	bNeuralNetTrained = false;
	bNeuralNetSaved = false;
	// allocating memory for the inputs
	Input = new float[total_input_num];
	if(!Input) {
		std::cerr << "Error while allocating memory for inputs.\n";
	}
	// allocating memory for the outputs
	Output = new float[target_num];
	if(!Output) {
		std::cerr << "Error while allocating memory for outputs.\n";
	}
	// allocating memory for temporary inputs
	input = new float[input_num];
	if(!input) {
		std::cerr << "Error while allocating memory for temporary inputs variable.\n";
	}
	// allocating memory for delta
	delta = new float[target_num];
	if(!delta) {
		std::cerr << "Error while allocating memory for delta.\n";
	}
	// allocating memory for the targets
	Target = new float[target_num];
	if(!Target) {
		std::cerr << "Error while allocating memory for targets.\n";
	}
	// allocating memory for the weights
	Weight = new float[input_num];
	if(!Weight) {
		std::cerr << "Error while allocating memory for weights.\n";
	}
	WAIT(1*SECOND);
	for(int i = 0; i < total_input_num; ++i) {
		cout << "input[" << i << "] = ";
		cin >> Input[i];
		if ( input_num > 1 && !((i + 1) % input_num)) {
			cout << endl;
		}
		WAIT(0.4*SECOND);
	}
	WAIT(1*SECOND);
	cout << endl << endl;
	for(i = 0; i < target_num; ++i) {
		cout << "target[" << i << "] = ";
		cin >> Target[i];
		WAIT(0.4*SECOND);
	}
	RandomizeWeights();
	bNeuralNetCreated = true;
	CLEAR_SCREEN();
	cout << "\nCreating Neural Net...";
	WAIT(2*SECOND);
	cout << "\n\nThe Neural Net was created successfuly!" << endl;
	WAIT(0.6*SECOND);
	cout << "\nNext step: Training\n\n";
	UpdateScreen();
}

// initialise the weights with 
// random values between -1 and 1
void CPnet::RandomizeWeights() {
	srand( ( unsigned )time( NULL ) );
	for(int i=0; i<input_num; ++i) {
		Weight[i] = (float)(rand())/(RAND_MAX/2) - 1;
	}
}

// normalize the given input vector
void CPnet::NormalizeInput() {
	Max = abs(Input[0]);
	for(int i = 0; i < total_input_num; ++i) {
		if(abs(Input[i]) > Max) {
			Max = abs(Input[i]);
		}
	}
	if(Max > 1) {
		for(i = 0; i < total_input_num; ++i) {
			Input[i] /= Max;
		}
	}
}

// denormalize input vector		
void CPnet::DeNormalizeInput() {
	if(Max > 1) {
		for(int i = 0; i < total_input_num; ++i) {
			Input[i] *= Max;
		}
	}
}

// normalize target vector
void CPnet::NormalizeTarget() {
	MaxT = abs(Target[0]);
	for(int i = 0; i < target_num; ++i) {
		if(abs(Target[i]) > MaxT) {
			MaxT = abs(Target[i]);
		}
	}
	if(MaxT > 1) {
		for(i = 0; i < target_num; ++i) {
			Target[i] /= MaxT;
		}
	}
}

// denormalize target vector
void CPnet::DeNormalizeTarget() {
	if(MaxT > 1) {
		for(int i = 0; i < target_num; ++i) {
			Target[i] *= MaxT;
		}
	}
}

// compute weighted sum for the current neuron
float CPnet::ComputeWeightedSum( float *Input ) {
	float sum = 0.0f;
	for(int i = 0; i < input_num; ++i) {
		sum += Input[i]*Weight[i];
	}
	return sum;
}

// function for training process
void CPnet::Train() {
    float net;
	int first_index = 0, last_index = input_num;
	bool out;
	for(int i = 0; i < neuron_num; ++i) {
		for(int j = first_index, k = 0; j < last_index; ++j, ++k) {
			input[k] = Input[j];
			if(eAnimType != DEFAULT) {
				cout << Input[j];
				if (j < last_index - 1) {
					cout << ", ";
				}
			}
		}
		net = ComputeWeightedSum(input) + (-1)*threshold;
		if (net>0)
			out = 1;
		else if (net <= 0)
			out = 0;

		Output[i] = out;

		if(eAnimType != DEFAULT) {
			cout << " -> " << out << endl;
			if(eAnimType == ANIM_T3) {
				WAIT(0.1*SECOND);
			}
		}

		float d = Target[i];
		j = first_index;
		for(k = 0; j < last_index; ++j, ++k) {
			delta[k] = LEARNING_RATE*(d-out)*Input[j];
			Weight[k] += delta[k];
		}
		threshold -= (d-out);

		first_index = j;
		last_index += input_num;
	}
	if(bNeuralNetLoaded) {
		bNewModifications = true;
	}
}
	
// function for testing results after training	
void CPnet::Run() {
    float net;
	int first_index = 0, last_index = input_num;
	bool out;
	for(int i = 0; i < neuron_num; ++i) {
		WAIT(0.6*SECOND);
		for(int j = first_index, k = 0; j < last_index; ++j, ++k) {
			input[k] = Input[j];
			cout << Input[j];
			if (j < last_index - 1) {
				cout << ", ";
			}
		}
		net = ComputeWeightedSum(input) + (-1)*threshold;
		if (net>0) {
			out = 1;
		}
		else if (net <= 0) {
			out = 0;
		}

		cout << " -> " << out << endl;

		first_index = j;
		last_index += input_num;
	}
}

// Training Neural Net
void CPnet::TrainNetwork(void) {
	cout << "\nTraining net..." << endl;
	for(int i=0; i<CPN_ITER; ++i) {
		Train();
		if(eAnimType == ANIM_T1 || eAnimType == ANIM_T3) {
			cout << "\nnumber of iterations = " << i + 1 << endl << endl ;
			WAIT(0.3 * SECOND);
		}
		else if(eAnimType == ANIM_T2) {
			cout << "\nnumber of iterations = " << i + 1 << endl << endl;
			WAIT(0.3 * SECOND);
			if (i < CPN_ITER - 1) {
				CLEAR_SCREEN();
			}
		}
		if(eAnimType != DEFAULT && i < CPN_ITER - 1) {
			cout << "\nTraining net..." << endl;
		}
	}
	bNeuralNetTrained = true;
	WAIT(1*SECOND);
	cout << "\n\nTraining completed,";
	ComputeAverageError();
	if (fAverageError <= MIN_ACCURACY) {
		cout << "the learning process was successful!" << endl;
		WAIT(0.6*SECOND);
		cout << "\nNext step: Testing\n\n" << endl;
	} else {
		cout << "learning unsuccessful." << endl;
	}
	UpdateScreen();
}

// computes average error between
// target vector and ouput vector
void CPnet::ComputeAverageError() {
	float sum = 0.0f;
	for(int i = 0; i < target_num; ++i) {
		sum += abs(Target[i] - Output[i]);
	}
	fAverageError = sum/target_num;
}

// Tests the current Neural Net with inputs
void CPnet::TestNetwork(void) {
	cout << "\nTesting \"" << szNeuralNetName << "\" function..." << endl;
	WAIT(0.5*SECOND);
	cout << "\nTest results" << endl;
	Run();
	WAIT(1*SECOND);
	cout << "\nTest completed!" << endl;
	UpdateScreen();
}

// Test the Neural with the selected patterns
void CPnet::SelectiveTest( int pattern_num ) {
	float net;
	int first_index = 0, last_index = input_num;
	bool out;
	int nNumOfInputs = input_num * pattern_num;
	float *Input = new float[nNumOfInputs];
	for(int i = 0; i < nNumOfInputs; ++i) {
		cout << "input[" << i << "] = ";
		cin >> Input[i];
		if ( input_num > 1 && !((i + 1) % input_num)) {
			cout << endl;
		}
		WAIT(0.5*SECOND);
	}

	CLEAR_SCREEN();
	WAIT(0.5*SECOND);
	cout << "\nTesting \"" << szNeuralNetName << "\" function..." << endl;
	WAIT(0.5*SECOND);

	for(i = 0; i < pattern_num; ++i) {
		for(int j = first_index, k = 0; j < last_index; ++j, ++k) {
			input[k] = Input[j];
			cout << Input[j];
			if (j < last_index - 1) {
				cout << ", ";
			}
		}
		net = ComputeWeightedSum(input) + (-1)*threshold;
		if (net>0)
			out = 1;
		else if (net <= 0)
			out = 0;

		cout << " -> " << out << endl;
		WAIT(0.5*SECOND);
		first_index = j;
		last_index += input_num;
	}
	cout << "\nTest completed!" << endl;
	delete Input;
}

void CPnet::UpdateScreen() {
	cout << "Press any key to continue...";
	getch();
	CLEAR_SCREEN();
}

// checks to see if a file or directory exist
// in the current hard drive
bool CPnet::fExist( char* filepath ) {
    WIN32_FIND_DATA file;
    HANDLE hFile;
    if (( hFile = FindFirstFile( filepath, &file ))  
         == INVALID_HANDLE_VALUE ) {
          return false;
    }
    return true;
}

// saves current neural net data before proceding to a new step
void CPnet::SaveCurrentData() {
	if(!bNeuralNetLoaded || (bNeuralNetLoaded && bNewModifications)) {
		if(bNeuralNetCreated && !bNeuralNetSaved) {
			cout << "\nBefore continuing,do you want to save the current Neural Net data?\n"
				<< "Yes(y) No(n): ";
			char response;
			cin >> response;
			response = tolower(response);
			if(response == 'y') {
				SaveNet();
				cout << "The Neural Net was saved successfuly!" << endl;
				UpdateScreen();
			}
		}
	}
}

// Save Neural Net variables to a file
void CPnet::SaveNet(void) {
	FILE *fw = fopen(szNeuralNetName,"w");
	if(!fw) {
		perror(szNeuralNetName);
	}
	// saving input number
	fprintf(fw, "%d\n", input_num);
	// saving neuron number
	fprintf(fw, "%d\n", neuron_num); 
	// saving max input value
	fprintf(fw, "%f\n", Max); 
	// saving max target value
	fprintf(fw, "%f\n", MaxT); 
	// saving the inputs
	total_input_num = input_num * neuron_num;
	for(int i = 0; i < total_input_num; ++i) {
		fprintf(fw, "%f ", Input[i]);
		if (i > 0 && i < total_input_num - 1 && !((i + 1) % 8)) {
			putc('\n', fw);
		}
	}
	// saving the threshold
	fprintf( fw, "\n%f\n", threshold );
	// saving the targets
	for(i = 0; i < target_num; ++i) {
		fprintf(fw, "%f ", Target[i]);
	}
	putc('\n', fw);
	// saving the weights
	for(i = 0; i < input_num; ++i) {
		fprintf(fw, "%f ", Weight[i]);
		if (i > 0 && i < input_num - 1 && !((i + 1) % 8)) {
			putc('\n', fw);
		}
	}
	fflush(fw);
	fclose(fw);

	bNeuralNetSaved = true;
}

// Load Neural Net variables from a file
void CPnet::LoadNet(void) {
	FILE *fw = fopen(szNeuralNetName,"r");
	if(!fw) {
		perror(szNeuralNetName);
	}
	// loading input number
	fscanf(fw, "%d", &input_num);
	// loading neuron number
	fscanf(fw, "%d", &neuron_num);
	// loading max input value
	fscanf(fw, "%f", &Max);
	// loading max target value
	fscanf(fw, "%f", &MaxT);
	// loading the Inputs
	if(Input != NULL) {
		delete Input;
	}
	if(input != NULL) {
		delete input;
	}
	if(Output != NULL) {
		delete Output;
	}
	if(Target != NULL) {
		delete Target;
	}
	if(delta != NULL) {
		delete delta;
	}
	bNeuralNetTrained = false;
	total_input_num = input_num * neuron_num;
	Input = new float[total_input_num];
	if(!Input) {
		std::cerr << "Error while allocating memory for inputs.\n";
	}
	input = new float[input_num];
	if(!input) {
		std::cerr << "Error while allocating memory for temporary inputs variable.\n";
	}
	Target = new float[neuron_num];
	if(!Target) {
		std::cerr << "Error while allocating memory for targets.\n";
	}
	Output = new float[neuron_num];
	if(!Output) {
		std::cerr << "Error while allocating memory for outputs.\n";
	}
	delta = new float[neuron_num];
	if(!delta) {
		std::cerr << "Error while allocating memory for delta.\n";
	}
	// loading the inputs
	for(int i = 0; i < total_input_num; ++i) {
		fscanf(fw, "%f", &Input[i]);
	}
	// loading the threshold
	fscanf(fw, "%f", &threshold);
	// loading the targets
	for(i = 0; i < neuron_num; ++i) {
		fscanf(fw, "%f ", &Target[i]);
	}
	// loading the weights
	if(Weight != NULL) {
		delete Weight;
	}
	Weight = new float[input_num];
	if(!Weight) {
		std::cerr << "Error while allocating memory for weights.\n";
	}
	for(i = 0; i < input_num; ++i) {
		fscanf(fw, "%f", &Weight[i]);
	}
	target_num = neuron_num;
	bNeuralNetCreated = true;
	bNeuralNetLoaded = true;
	bNewModifications = false;
	if(Max > 0 && MaxT > 0) {
		bNeuralNetTrained = true;
	}
	fclose(fw);
}
