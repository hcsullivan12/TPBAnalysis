std::string dataDirectory = "/home/hunter/Desktop/TPBTests/data";
std::string outputWaveformFile = "./waveforms/waveformFiles.txt";
double run2Time = 741; ///min
double run3Time = 711; ///min 
double controlTime = 128; ///min

/*//Run2
int firstSiPMTrigger      = 15;
int lastSiPMTrigger       = 983; 
std::string PMT1Filename  = "/Run2/pmt1/M1pmt1_00000.txt";
std::string PMT2Filename  = "/Run2/pmt2/M2pmt2_00000.txt";
std::string sipmFile      = "/Run2/sipm/C3Run2_coinSiPM_"; */

///Run3
int firstSiPMTrigger      = 0;
int lastSiPMTrigger       = 981;
std::string PMT1Filename  = "/Run3/pmt1/M1pmt_1_00000.txt";
std::string PMT2Filename  = "/Run3/pmt2/M2pmt_2_00000.txt";
std::string sipmFile      = "/Run3/sipm/C3sipm";
std::string controlFile   = "/Run3/control/C3Control_3_SiPM_";
int controlFirstSiPMTrigger     = 0;
int controlLastSiPMTrigger       = 238; 

///Histogram parameters
int controlAmplitudeDistributionBins = 1000;
double controlAmplitudeDistributionMin = -2;
double controlAmplitudeDistributionMax = 2;

int controlWidthDistributionBins = 1000;
double controlWidthDistributionMin = 0;
double controlWidthDistributionMax = 1/(10000000.0); //units are time

int controlTimeDistBins = 100;
double controlTimeDistMin = -0.00002;
double controlTimeDistMax = 0.00008;

int controlMinBins = 100;
double controlMinMin = -0.5;
double controlMinMax = 0;

int timeDistBins   = 100;
double timeDistMin = -0.00002;
double timeDistMax = 0.00008;

int singleMinTimeDistBins   = 100;
double singleMinTimeDistMin = -0.00002;
double singleMinTimeDistMax = 0.00008;

int singleMinMinDistBins   = 100;
double singleMinMinDistMin = -0.5;
double singleMinMinDistMax = 0;

///Thresholds
double controlAmplitudeMean;   ///Getting this info from control run
double controlAmplitudeSigma;  ///Getting this info from control run
double controlWidthMean;       ///Getting this info from control run
double controlWidthSigma;      ///Getting this info from control run
int    discAmplitude  = 1;     ///Pulse discrimination 
int    discWidth = 10000;          ///Pulse discrimination 
double threshWidth = 1/100000.0;

void readData() {
	
	///IDENTIFY WHICH RUN
	std::string RUN = "3";
	
	///File to write data to
	std:string rootFile = "./Run" + RUN + "Data.root";
	TFile *data = new TFile(rootFile.c_str(), "RECREATE");
	
	////////////////////////////////////////////////////////////////////////
	// Need to find pedestal of amplitude distibution of the control run. // 
	// Potential pulses must meet mean + int*sigma threshold.             //
	// Of the pulses that pass, need to make width distribution of control//
	// run. Potential pulse widths must meet some width threshold. This   //
	// should subtract out noise of both control run and TPB run.         //
	////////////////////////////////////////////////////////////////////////
	
	//////////////////
	// CONTROL RUN ///
	//////////////////
	
	/*///
	/// Write raw waveforms to rawControlWaveforms.root
	///
	
	std::cout << "\nWriting control raw waveforms...\n";
	
	std::string rawControlWaveformsName = "./waveforms/controlRun" + RUN + "Raw.root";
	TFile *rawControl = new TFile(rawControlWaveformsName.c_str(), "RECREATE");
	
	//std::multimap<double, double> controlSingleMinSipmPeaks; //(time, amplitude)
	for (int trigger = controlFirstSiPMTrigger; trigger <= controlLastSiPMTrigger; trigger++) {
		
		///READ FROM SIPM WAVEFORMS TO FIND PEDESTAL
		///Define filename
		std::string temp = to_string(trigger);
		int numberOfDigits = temp.length();
		
		int numberOfZeros = 5 - numberOfDigits;
		std::string zeroTag = "";
		for (int i = 0; i < numberOfZeros; i++) {
			zeroTag = zeroTag + "0";
		}
		
		//std::cout << "Trigger: " << trigger << "    Number of digits: " << numberOfDigits << "   Number of zeros: " << numberOfZeros << "    zeroTag: " << zeroTag << std::endl;
		std::string filename = dataDirectory + controlFile + zeroTag + to_string(trigger) + ".txt";
		
		///NEED TO FIND ALL MINIMUMS IN SIPM PULSE
		
		std::ifstream fileSecond(filename.c_str());
		if (!fileSecond) {
			std::cout << "Cannot open " << filename << std::endl;
		} else {
			///Read file
			std::string word = "";
			std::vector<double> time;
			std::vector<double> voltage;
			//double min = 0;
			//double minTime;
			
			std::cout << "Reading trigger: " << trigger << std::endl;
			///Skip first text
			while (word != "Time,Ampl") {
				fileSecond >> word;
			}
			
			while(!fileSecond.eof()) {
				///Data starts
				std::string vTemp;
				std::string tTemp;
					
				std::getline(fileSecond, tTemp, ',');
				std::getline(fileSecond, vTemp);
				
				double v = atof(vTemp.c_str());
				double t = atof(tTemp.c_str());
				
				time.push_back(t);
				voltage.push_back(v);
			}
			///Make graph
			TGraph *graph = new TGraph(time.size(), &time[0], &voltage[0]);
			graph->Write();
			
			fileSecond.close();
		}
	}*/
	
	/*///
	/// Amplitude distribution
	///
	
	///Make amplitude distribution
	//TCanvas *c1 = new TCanvas("c1", "c1", 1000, 500);
	TH1D *controlAmplitudeDist = new TH1D("controlAmplitudeDist", "controlAmplitudeDist", controlAmplitudeDistributionBins, 
											controlAmplitudeDistributionMin, controlAmplitudeDistributionMax);
	std::cout << "\nFinding control run amplitude distribution...\n";
	
	for (int trigger = controlFirstSiPMTrigger; trigger <= controlLastSiPMTrigger; trigger++) {
		
		///READ FROM SIPM WAVEFORMS TO FIND PEDESTAL
		///Define filename
		std::string temp = to_string(trigger);
		int numberOfDigits = temp.length();
		
		int numberOfZeros = 5 - numberOfDigits;
		std::string zeroTag = "";
		for (int i = 0; i < numberOfZeros; i++) {
			zeroTag = zeroTag + "0";
		}
		
		//std::cout << "Trigger: " << trigger << "    Number of digits: " << numberOfDigits << "   Number of zeros: " << numberOfZeros << "    zeroTag: " << zeroTag << std::endl;
		std::string filename = dataDirectory + controlFile + zeroTag + to_string(trigger) + ".txt";
	
		///Open file to insert amplitudes into distibrution 
		//std::multimap< int, std::pair< double, double > > amplitudeParameters;  ///( trigger, ( mean, sigma )  )
		std::ifstream fileFirst(filename.c_str());
		if (!fileFirst) {
			std::cout << "Cannot open " << filename << std::endl;
		} else {
			///Read file
			//std::cout << "Reading trigger: " << trigger << std::endl;
			std::string word = "";
			//std::vector<double > time;
			//std::vector<double > voltage;
			//double min = 0;
			
			///Skip first text
			while (word != "Time,Ampl") {
				fileFirst >> word;
			}
			
			while(!fileFirst.eof()) {
				///Data starts
				std::string vTemp;
				std::string tTemp;
				
				std::getline(fileFirst, tTemp, ',');
				std::getline(fileFirst, vTemp);
				
				double v = atof(vTemp.c_str());
				//double t = atof(tTemp.c_str());
				//voltage.push_back(v);	
				
				controlAmplitudeDist->Fill( v );
			}
		}
		fileFirst.close();
	}
	
	///Fit pedastal with gaussian
	TF1 *controlAmplitudeGaussian = new TF1("controlAmplitudeGaussian", "gaus");
	controlAmplitudeDist->Fit("controlAmplitudeGaussian","0Q","",-0.05,0.05);
	controlAmplitudeMean  = controlAmplitudeGaussian->GetParameter(1);
	controlAmplitudeSigma = controlAmplitudeGaussian->GetParameter(2);
	controlAmplitudeDist->Write();
	//std::cout << controlAmplitudeMean << "  " << controlAmplitudeSigma << std::endl;
	
	///
	/// Width distribution
	///
	
	// Pulses must meet amplitude threshold
	
	///Make width distribution
	//TCanvas *c2 = new TCanvas("c2", "c2", 1000, 500);
	TH1D *controlWidthDist = new TH1D("controlWidthDist", "controlWidthDist", controlWidthDistributionBins, 
											controlWidthDistributionMin, controlWidthDistributionMax);
	
	///Rising Edge threshold
	double threshRisingEdge = controlAmplitudeMean - discAmplitude*controlAmplitudeSigma;
	
	std::cout << "\nFinding control run width distribution...\n";
	
	for (int trigger = controlFirstSiPMTrigger; trigger <= controlLastSiPMTrigger; trigger++) {
		
		///READ FROM SIPM WAVEFORMS AND DISCRIMINATE 
		///Define filename
		std::string temp = to_string(trigger);
		int numberOfDigits = temp.length();
		
		int numberOfZeros = 5 - numberOfDigits;
		std::string zeroTag = "";
		for (int i = 0; i < numberOfZeros; i++) {
			zeroTag = zeroTag + "0";
		}
		
		//std::cout << "Trigger: " << trigger << "    Number of digits: " << numberOfDigits << "   Number of zeros: " << numberOfZeros << "    zeroTag: " << zeroTag << std::endl;
		std::string filename = dataDirectory + controlFile + zeroTag + to_string(trigger) + ".txt";
		
		///NEED TO FIND ALL MINIMUMS IN SIPM PULSE
		std::ifstream fileSecond(filename.c_str());
		if (!fileSecond) {
			std::cout << "Cannot open " << filename << std::endl;
		} else {
			///Read file
			std::string word = "";
			std::vector<double > time;
			std::vector<double > voltage;
			//double min = 0;
			
			//std::cout << "Reading trigger: " << trigger << std::endl;
			///Skip first text
			while (word != "Time,Ampl") {
				fileSecond >> word;
			}
			
			while(!fileSecond.eof()) {
				///Data starts
				std::string vTemp;
				std::string tTemp;
					
				std::getline(fileSecond, tTemp, ',');
				std::getline(fileSecond, vTemp);
				
				double v = atof(vTemp.c_str());
				double t = atof(tTemp.c_str());
				
				///Search for rising edge
				if (v < threshRisingEdge) {
					///Found start of pulse 
					double tRisingEdge = t;
					///Find falling edge or eof
					while (v < threshRisingEdge && !fileSecond.eof()) {
						std::getline(fileSecond, tTemp, ',');
						std::getline(fileSecond, vTemp);
						v = atof(vTemp.c_str());
						t = atof(tTemp.c_str());
					}
					if (fileSecond.eof()) continue;
					///Found falling edge
					double tFallingEdge = t;
					double width = abs(tFallingEdge - tRisingEdge);
					
					///Fill width distribution
					controlWidthDist->Fill( width );
				}
			}
		}
			
		fileSecond.close();
	}
	
	///Fit pedastal with gaussian
	TF1 *controlWidthGaussian = new TF1("controlWidthGaussian", "gaus");
	controlWidthDist->Fit("controlWidthGaussian","0Q","",-0.05,0.05);
	controlWidthMean  = controlWidthGaussian->GetParameter(1);
	controlWidthSigma = controlWidthGaussian->GetParameter(2);
	controlWidthDist->Write();
	
	std::cout << "Control Amplitude mean: " << controlAmplitudeMean << "    Control Amplitude sigma: " << controlAmplitudeSigma << std::endl;
	std::cout << "Control Width mean:    " << controlWidthMean     << "    Control Width sigma:     " << controlWidthSigma << std::endl;
	
	///
	/// FINDING ALL PULSES IN EACH WAVEFORM
	/// 
	
	// Pulses must meet mean and sigma thresholds
	// Vector containing "pulse" info from each waveform
	// Each entry is a vector containing all peaks found in waveform
	// with time and amplitude specified as a pair
	std::vector< std::pair<double, double> > controlAllSiPMPeaks;
	
	///Already defined threshRisingEdge
	///Width threshold to get rid of noise
	//double threshWidth = 1/100000.0;//controlWidthMean + discWidth*controlWidthSigma;
	
	std::cout << "\nFinding all pulses in control run...\n";
	
	for (int trigger = controlFirstSiPMTrigger; trigger <= controlLastSiPMTrigger; trigger++) {
		
		///READ FROM SIPM WAVEFORMS AND DISCRIMINATE 
		///Define filename
		std::string temp = to_string(trigger);
		int numberOfDigits = temp.length();
		
		int numberOfZeros = 5 - numberOfDigits;
		std::string zeroTag = "";
		for (int i = 0; i < numberOfZeros; i++) {
			zeroTag = zeroTag + "0";
		}
		
		//std::cout << "Trigger: " << trigger << "    Number of digits: " << numberOfDigits << "   Number of zeros: " << numberOfZeros << "    zeroTag: " << zeroTag << std::endl;
		std::string filename = dataDirectory + controlFile + zeroTag + to_string(trigger) + ".txt";
		
		///NEED TO FIND ALL MINIMUMS IN SIPM PULSE
		std::ifstream fileSecond(filename.c_str());
		if (!fileSecond) {
			std::cout << "Cannot open " << filename << std::endl;
		} else {
			///Read file
			std::string word = "";
			std::vector<double > time;
			std::vector<double > voltage;
			double min = 0;
			
			//std::cout << "Reading trigger " << trigger << std::endl;
			///Skip first text
			while (word != "Time,Ampl") {
				fileSecond >> word;
			}
			
			while(!fileSecond.eof()) {
				///Data starts
				std::string vTemp;
				std::string tTemp;
					
				std::getline(fileSecond, tTemp, ',');
				std::getline(fileSecond, vTemp);
				
				double v = atof(vTemp.c_str());
				double t = atof(tTemp.c_str());
				
				///Search for rising edge
				if (v < threshRisingEdge) {
					///Found start of pulse 
					double tRisingEdge = t;
					min = v;
					///Find falling edge or eof
					while (v < threshRisingEdge && !fileSecond.eof()) {
						std::getline(fileSecond, tTemp, ',');
						std::getline(fileSecond, vTemp);
						v = atof(vTemp.c_str());
						t = atof(tTemp.c_str());
						if (v < min) min = v;
					}
					if (fileSecond.eof()) continue;
					
					///Found falling edge
					double tFallingEdge = t;
					double width = abs(tFallingEdge - tRisingEdge);
					
					///Width threshold used to filter out noise
					if (width > threshWidth) {
						///Found local minimum and pulse
						std::pair<double, double> p;
						p = make_pair(tRisingEdge, min);
						controlAllSiPMPeaks.push_back(p);
					}
				}
			}
		}
			
		fileSecond.close();
	}
	
	TH1D *controlRisingTimeDist = new TH1D("controlRisingTimeDist", "controlRisingTimeDist", controlTimeDistBins, controlTimeDistMin, controlTimeDistMax);
	for (auto it = allSiPMPeaks.begin(); it != allSiPMPeaks.end(); it++) {
		controlRisingTimeDist->Fill( it->first );
	}
	//TCanvas *c4 = new TCanvas("c4", "c4", 1000, 500);
	std::string title1 = "Time of Rising Edge SiPM Pulse (Control Run " + RUN + ")";
	controlRisingTimeDist->SetTitle(title1.c_str());
	//controlRisingTimeDist->Draw();
	controlRisingTimeDist->Write();
	
	TH1D *controlMinDist = new TH1D("controlMinDist", "controlMinDist", controlMinBins, controlMinMin, controlMinMax);
	for (auto it = allSiPMPeaks.begin(); it != allSiPMPeaks.end(); it++) {
		controlMinDist->Fill( it->second );
	}
	///Divide hist by runtime
	for (int bin = 1; bin <= controlMinDist->GetNbinsX(); bin++) {
		double contentNormalized = controlMinDist->GetBinContent(bin)/controlTime;
		controlMinDist->SetBinContent(bin, contentNormalized);
	}
	//TCanvas *c5 = new TCanvas("c5", "c5", 1000, 500);
	std::string title2 = "Minimum SiPM Amplitudes (Control Run " + RUN + ")";
	controlMinDist->SetTitle(title2.c_str());
	controlMinDist->GetXaxis()->SetTitle("V");
	//c5->SetLogy();
	//minDist->Draw();
	controlMinDist->Write();
	
	///
	/// Write filenames of waveforms of accepted pulses
	///
	
	std::cout << "\nWriting out filenames of accepted control waveforms...\n";
	
	std::string outputFileControlAccepted = "./waveforms/controlRun" + RUN + "acceptedWaveforms.txt";
	std::ofstream output(outputFileControlAccepted.c_str());
	
	for (int trigger = controlFirstSiPMTrigger; trigger <= controlLastSiPMTrigger; trigger++) {
		
		///READ FROM SIPM WAVEFORMS TO FIND PEDESTAL
		///Define filename
		std::string temp = to_string(trigger);
		int numberOfDigits = temp.length();
		
		int numberOfZeros = 5 - numberOfDigits;
		std::string zeroTag = "";
		for (int i = 0; i < numberOfZeros; i++) {
			zeroTag = zeroTag + "0";
		}
		
		//std::cout << "Trigger: " << trigger << "    Number of digits: " << numberOfDigits << "   Number of zeros: " << numberOfZeros << "    zeroTag: " << zeroTag << std::endl;
		std::string filename = dataDirectory + controlFile + zeroTag + to_string(trigger) + ".txt";
		
		std::ifstream fileSecond(filename.c_str());
		if (!fileSecond) {
			std::cout << "Cannot open " << filename << std::endl;
		} else {
			///Read file
			std::string word = "";
			std::vector<double > time;
			std::vector<double > voltage;
			double min = 0;
			double minTime;
			
			//std::cout << "Reading Filename: " << filename << "\n" << std::endl;
			///Skip first text
			while (word != "Time,Ampl") {
				fileSecond >> word;
			}
			
			while(!fileSecond.eof()) {
				///Data starts
				std::string vTemp;
				std::string tTemp;
					
				std::getline(fileSecond, tTemp, ',');
				std::getline(fileSecond, vTemp);
				
				double v = atof(vTemp.c_str());
				double t = atof(tTemp.c_str());
				
				///Search for rising edge
				if (v < threshRisingEdge) {
					///Found start of pulse 
					double tRisingEdge = t;
					min = v;
					///Find falling edge or eof
					while (v < threshRisingEdge && !fileSecond.eof()) {
						std::getline(fileSecond, tTemp, ',');
						std::getline(fileSecond, vTemp);
						v = atof(vTemp.c_str());
						t = atof(tTemp.c_str());
						if (v < min) min = v;
					}
					if (fileSecond.eof()) continue;
					
					///Found falling edge
					double tFallingEdge = t;
					double width = abs(tFallingEdge - tRisingEdge);
					
					///Width threshold used to filter out noise
					if (width > threshWidth) {
						//std::cout << "threshRisingEdge: " << threshRisingEdge << "   min: " << min << "     threshWidth: " << threshWidth << "    width: " << width << std::endl;
						///Found local minimum and pulse
						///Write out filename
						output << filename << "\n";
					}
				}
			}
			fileSecond.close();
		}
	}
	output.close();*/
	
	//////////////////
	// TPB RUN ///
	//////////////////
	
	/*///
	/// Write raw waveforms to rawControlWaveforms.root
	///
	
	std::cout << "\nWriting TPB raw waveforms...\n";
	
	std::string rawTPBWaveformsName = "./waveforms/tpbRun" + RUN + "Raw.root";
	TFile *rawTPB = new TFile(rawTPBWaveformsName.c_str(), "RECREATE");
	
	//std::multimap<double, double> controlSingleMinSipmPeaks; //(time, amplitude)
	for (int trigger = firstSiPMTrigger; trigger <= lastSiPMTrigger; trigger++) {
		
		///READ FROM SIPM WAVEFORMS TO FIND PEDESTAL
		///Define filename
		std::string temp = to_string(trigger);
		int numberOfDigits = temp.length();
		
		int numberOfZeros = 5 - numberOfDigits;
		std::string zeroTag = "";
		for (int i = 0; i < numberOfZeros; i++) {
			zeroTag = zeroTag + "0";
		}
		
		//std::cout << "Trigger: " << trigger << "    Number of digits: " << numberOfDigits << "   Number of zeros: " << numberOfZeros << "    zeroTag: " << zeroTag << std::endl;
		std::string filename = dataDirectory + sipmFile + zeroTag + to_string(trigger) + ".txt";
		
		///NEED TO FIND ALL MINIMUMS IN SIPM PULSE
		
		std::ifstream fileSecond(filename.c_str());
		if (!fileSecond) {
			std::cout << "Cannot open " << filename << std::endl;
		} else {
			///Read file
			std::string word = "";
			std::vector<double> time;
			std::vector<double> voltage;
			//double min = 0;
			//double minTime;
			
			std::cout << "Reading trigger: " << trigger << std::endl;
			///Skip first text
			while (word != "Time,Ampl") {
				fileSecond >> word;
			}
			
			while(!fileSecond.eof()) {
				///Data starts
				std::string vTemp;
				std::string tTemp;
					
				std::getline(fileSecond, tTemp, ',');
				std::getline(fileSecond, vTemp);
				
				double v = atof(vTemp.c_str());
				double t = atof(tTemp.c_str());
				
				time.push_back(t);
				voltage.push_back(v);
			}
			///Make graph
			TGraph *graph = new TGraph(time.size(), &time[0], &voltage[0]);
			graph->Write();
			
			fileSecond.close();
		}
	}*/
	
	
	///
	/// FINDING ALL PULSES IN EACH WAVEFORM
	/// 
	
	// Pulses must meet mean and sigma thresholds
	// Vector containing "pulse" info from each waveform
	// Each entry is a vector containing all peaks found in waveform
	// with time and amplitude specified as a pair
	std::vector< std::pair<double, double> > tpbAllSiPMPeaks;
	
	///Already defined threshRisingEdge
	///Width threshold to get rid of noise
	//double threshWidth = 1/100000.0;//controlWidthMean + discWidth*controlWidthSigma;
	
	std::cout << "\nFinding all pulses in TPB run...\n";
	
	for (int trigger = firstSiPMTrigger; trigger <= lastSiPMTrigger; trigger++) {
		
		///READ FROM SIPM WAVEFORMS AND DISCRIMINATE 
		///Define filename
		std::string temp = to_string(trigger);
		int numberOfDigits = temp.length();
		
		int numberOfZeros = 5 - numberOfDigits;
		std::string zeroTag = "";
		for (int i = 0; i < numberOfZeros; i++) {
			zeroTag = zeroTag + "0";
		}
		
		//std::cout << "Trigger: " << trigger << "    Number of digits: " << numberOfDigits << "   Number of zeros: " << numberOfZeros << "    zeroTag: " << zeroTag << std::endl;
		std::string filename = dataDirectory + sipmFile + zeroTag + to_string(trigger) + ".txt";
		
		///NEED TO FIND ALL MINIMUMS IN SIPM PULSE
		std::ifstream fileSecond(filename.c_str());
		if (!fileSecond) {
			std::cout << "Cannot open " << filename << std::endl;
		} else {
			///Read file
			std::string word = "";
			std::vector<double > time;
			std::vector<double > voltage;
			double min = 0;
			
			//std::cout << "Reading trigger " << trigger << std::endl;
			///Skip first text
			while (word != "Time,Ampl") {
				fileSecond >> word;
			}
			
			while(!fileSecond.eof()) {
				///Data starts
				std::string vTemp;
				std::string tTemp;
					
				std::getline(fileSecond, tTemp, ',');
				std::getline(fileSecond, vTemp);
				
				double v = atof(vTemp.c_str());
				double t = atof(tTemp.c_str());
				
				///Search for rising edge
				if (v < threshRisingEdge) {
					///Found start of pulse 
					double tRisingEdge = t;
					min = v;
					///Find falling edge or eof
					while (v < threshRisingEdge && !fileSecond.eof()) {
						std::getline(fileSecond, tTemp, ',');
						std::getline(fileSecond, vTemp);
						v = atof(vTemp.c_str());
						t = atof(tTemp.c_str());
						if (v < min) min = v;
					}
					if (fileSecond.eof()) continue;
					
					///Found falling edge
					double tFallingEdge = t;
					double width = abs(tFallingEdge - tRisingEdge);
					
					///Width threshold used to filter out noise
					if (width > threshWidth) {
						///Found local minimum and pulse
						std::pair<double, double> p;
						p = make_pair(tRisingEdge, min);
						tpbAllSiPMPeaks.push_back(p);
					}
				}
			}
		}
			
		fileSecond.close();
	}
	
	TH1D *tpbRisingTimeDist = new TH1D("tpbRisingTimeDist", "tpbRisingTimeDist", controlTimeDistBins, controlTimeDistMin, controlTimeDistMax);
	for (auto it = tpbAllSiPMPeaks.begin(); it != tpbAllSiPMPeaks.end(); it++) {
		tpbRisingTimeDist->Fill( it->first );
	}
	//TCanvas *c4 = new TCanvas("c4", "c4", 1000, 500);
	std::string title1 = "Time of Rising Edge SiPM Pulse (TPB Run " + RUN + ")";
	tpbRisingTimeDist->SetTitle(title1.c_str());
	//controlRisingTimeDist->Draw();
	tpbRisingTimeDist->Write();
	
	TH1D *tpbMinDist = new TH1D("tpbMinDist", "tpbMinDist", controlMinBins, controlMinMin, controlMinMax);
	for (auto it = tpbAllSiPMPeaks.begin(); it != tpbAllSiPMPeaks.end(); it++) {
		tpbMinDist->Fill( it->second );
	}
	///Divide hist by runtime
	for (int bin = 1; bin <= tpbMinDist->GetNbinsX(); bin++) {
		double contentNormalized = tpbMinDist->GetBinContent(bin)/run3Time;
		tpbMinDist->SetBinContent(bin, contentNormalized);
	}
	//TCanvas *c5 = new TCanvas("c5", "c5", 1000, 500);
	std::string title2 = "Minimum SiPM Amplitudes (TPB Run " + RUN + ")";
	tpbMinDist->SetTitle(title2.c_str());
	tpbMinDist->GetXaxis()->SetTitle("V");
	//c5->SetLogy();
	//minDist->Draw();
	tpbMinDist->Write();
	
	///
	/// Write filenames of waveforms of accepted pulses
	///
	
	std::cout << "\nWriting out filenames of accepted TPB waveforms...\n";
	
	std::string outputFileTPBAccepted = "./waveforms/tpbRun" + RUN + "acceptedWaveforms.txt";
	std::ofstream tpbOutput(outputFileTPBAccepted.c_str());
	
	for (int trigger = firstSiPMTrigger; trigger <= lastSiPMTrigger; trigger++) {
		
		///READ FROM SIPM WAVEFORMS TO FIND PEDESTAL
		///Define filename
		std::string temp = to_string(trigger);
		int numberOfDigits = temp.length();
		
		int numberOfZeros = 5 - numberOfDigits;
		std::string zeroTag = "";
		for (int i = 0; i < numberOfZeros; i++) {
			zeroTag = zeroTag + "0";
		}
		
		//std::cout << "Trigger: " << trigger << "    Number of digits: " << numberOfDigits << "   Number of zeros: " << numberOfZeros << "    zeroTag: " << zeroTag << std::endl;
		std::string filename = dataDirectory + sipmFile + zeroTag + to_string(trigger) + ".txt";
		
		std::ifstream fileSecond(filename.c_str());
		if (!fileSecond) {
			std::cout << "Cannot open " << filename << std::endl;
		} else {
			///Read file
			std::string word = "";
			std::vector<double > time;
			std::vector<double > voltage;
			double min = 0;
			double minTime;
			
			//std::cout << "Reading Filename: " << filename << "\n" << std::endl;
			///Skip first text
			while (word != "Time,Ampl") {
				fileSecond >> word;
			}
			
			while(!fileSecond.eof()) {
				///Data starts
				std::string vTemp;
				std::string tTemp;
					
				std::getline(fileSecond, tTemp, ',');
				std::getline(fileSecond, vTemp);
				
				double v = atof(vTemp.c_str());
				double t = atof(tTemp.c_str());
				
				///Search for rising edge
				if (v < threshRisingEdge) {
					///Found start of pulse 
					double tRisingEdge = t;
					min = v;
					///Find falling edge or eof
					while (v < threshRisingEdge && !fileSecond.eof()) {
						std::getline(fileSecond, tTemp, ',');
						std::getline(fileSecond, vTemp);
						v = atof(vTemp.c_str());
						t = atof(tTemp.c_str());
						if (v < min) min = v;
					}
					if (fileSecond.eof()) continue;
					
					///Found falling edge
					double tFallingEdge = t;
					double width = abs(tFallingEdge - tRisingEdge);
					
					///Width threshold used to filter out noise
					if (width > threshWidth) {
						//std::cout << "threshRisingEdge: " << threshRisingEdge << "   min: " << min << "     threshWidth: " << threshWidth << "    width: " << width << std::endl;
						///Found local minimum and pulse
						///Write out filename
						tpbOutput << filename << "\n";
					}
				}
			}
			fileSecond.close();
		}
	}
	tpbOutput.close();
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*///
	/// JUST THE MIMUMUM
	/// 
	
	std::string outputFileControl = "./waveforms/controlRun" + RUN + ".root";
	std::ofstream output(outputFileControl.c_str());
	
	std::multimap<double, double> controlSingleMinSipmPeaks; //(time, amplitude)
	for (int trigger = controlFirstSiPMTrigger; trigger <= controlLastSiPMTrigger; trigger++) {
		
		///READ FROM SIPM WAVEFORMS TO FIND PEDESTAL
		///Define filename
		std::string temp = to_string(trigger);
		int numberOfDigits = temp.length();
		
		int numberOfZeros = 5 - numberOfDigits;
		std::string zeroTag = "";
		for (int i = 0; i < numberOfZeros; i++) {
			zeroTag = zeroTag + "0";
		}
		
		//std::cout << "Trigger: " << trigger << "    Number of digits: " << numberOfDigits << "   Number of zeros: " << numberOfZeros << "    zeroTag: " << zeroTag << std::endl;
		std::string filename = dataDirectory + controlFile + zeroTag + to_string(trigger) + ".txt";
		
		///NEED TO FIND ALL MINIMUMS IN SIPM PULSE
		
		std::ifstream fileSecond(filename.c_str());
		if (!fileSecond) {
			std::cout << "Cannot open " << filename << std::endl;
		} else {
			///Read file
			std::string word = "";
			std::vector<double > time;
			std::vector<double > voltage;
			double min = 0;
			double minTime;
			
			std::cout << "Reading Filename: " << filename << "\n" << std::endl;
			///Skip first text
			while (word != "Time,Ampl") {
				fileSecond >> word;
			}
			
			while(!fileSecond.eof()) {
				///Data starts
				std::string vTemp;
				std::string tTemp;
					
				std::getline(fileSecond, tTemp, ',');
				std::getline(fileSecond, vTemp);
				
				double v = atof(vTemp.c_str());
				double t = atof(tTemp.c_str());
				
				if (v < min) {
					min = v;
					minTime = t;
				}
			}
				
			///Found minimum
			singleMinSipmPeaks.insert(std::pair<double, double>(minTime, min) );
				if (min <= -0.15) {
						output << filename << "\n";
				}
			fileSecond.close();
		}
	}
	output.close();*/
	
	/*TH1D *singleMinTimeDist = new TH1D("singleMinTimeDist", "singleMinTimeDist", singleMinTimeDistBins, singleMinTimeDistMin, singleMinTimeDistMax);
	for (auto it = singleMinSipmPeaks.begin(); it != singleMinSipmPeaks.end(); it++) {
		singleMinTimeDist->Fill( it->first );
	}
	TCanvas *c7 = new TCanvas("c7", "c7", 1000, 500);
	std::string title3 = "Time of Minimum SiPM Amplitudes (Run " + RUN + ")";
	singleMinTimeDist->SetTitle(title3.c_str());
	singleMinTimeDist->GetXaxis()->SetTitle("Seconds");
	singleMinTimeDist->Draw();
	singleMinTimeDist->Write();
	
	TH1D *singleMinMinDist = new TH1D("singleMinMinDist", "singleMinMinDist", singleMinMinDistBins, singleMinMinDistMin, singleMinMinDistMax);
	for (auto it = singleMinSipmPeaks.begin(); it != singleMinSipmPeaks.end(); it++) {
		singleMinMinDist->Fill( it->second );
	}
	///Divide hist by runtime
	for (int bin = 1; bin <= singleMinMinDist->GetNbinsX(); bin++) {
		double contentNormalized = singleMinMinDist->GetBinContent(bin)/runTime;
		singleMinMinDist->SetBinContent(bin, contentNormalized);
	}
	TCanvas *c8 = new TCanvas("c8", "c8", 1000, 500);
	std::string title4 = "Minimum SiPM Amplitudes (Run " + RUN + ")";
	singleMinMinDist->SetTitle(title4.c_str());
	singleMinMinDist->GetXaxis()->SetTitle("V");
	c8->SetLogy();
	singleMinMinDist->Draw();
	singleMinMinDist->Write();
	
	std::cout << "\n\nAnalyzed Run " << RUN << ". Runtime was " << runTime << " minutes. " << std::endl; 
}
	
	
	
	double runTime;
	if (RUN == "2") {
		runTime = run2Time;
	} else runTime = run3Time; 
	
	///PMT 1///
	//TCanvas *c1 = new TCanvas("c1", "c1", 1000, 500); 
	
	///
	/// OPEN PMT1 FILE
	///
	std::string PMT1 = dataDirectory + PMT1Filename;
	std::ifstream PMT1File(PMT1.c_str());
	if (!PMT1File) {
		std::cout << "Cannot open " << PMT1Filename << std::endl;
	} else {
		
		string word = "";
		///Skip first text
		while (word != "Time,Ampl") {
			//std::cout << word << std::endl;
			PMT1File >> word;
		}
		
		std::string valueTemp;
		std::string weightTemp;
		double minValue = 0;
		double maxValue = 0;
		double value;
		int weight;
		std::multimap<double, int> data;
		
		while(std::getline(PMT1File, valueTemp, ',')) {
		
			std::getline(PMT1File, weightTemp);
			
			value  = std::stod(valueTemp);
			weight = std::stoi(weightTemp);
			
			data.insert(make_pair(value, weight));
			
			if(value < minValue) {
				minValue = value;
			}
			
			if(value > maxValue) {
				maxValue = value;
			}
			
			//std::cout << value << "   " << weight << std::endl;
		}
		
		double numberOfEvents = 0.0;
		for (auto it = data.begin(); it != data.end(); it++) {
			numberOfEvents = numberOfEvents + it->second;
		}
		TH1D *PMT1Histo = new TH1D("PMT1Histo", "rPMT1Histo", data.size(), minValue, maxValue);
		
		int bin = 1;
		for (auto it = data.begin(); it != data.end(); it++) {
			double normalizedValue = it->second/numberOfEvents;
			//std::cout << it->second << "  " << data.size() << "   " << normalizedValue << std::endl;
			PMT1Histo->SetBinContent(bin, normalizedValue);
			bin++;
		}
		std::string title = "PMT 1 (Run " + RUN + ") Pulse Areas";
		PMT1Histo->SetTitle(title.c_str());
		PMT1Histo->GetXaxis()->SetTitle("Vs");
		PMT1Histo->SetFillColor(33);
		//run2PMT1Histo->Draw();
		PMT1Histo->Write();
		PMT1File.close();
	}
	
	std::cout << "\n\n";
	
	///
	/// PMT 2
	///
	
	//TCanvas *c2 = new TCanvas("c2", "c2", 1000, 500);
	///OPEN PMT2 FILE
	std::string PMT2 = dataDirectory + PMT2Filename;
	std::ifstream PMT2File(PMT2.c_str());
	if (!PMT2File) {
		std::cout << "Cannot open " << PMT2Filename << std::endl;
	} else {
		
		string word = "";
		///Skip first text
		while (word != "Time,Ampl") {
			//std::cout << word << std::endl;
			PMT2File >> word;
		}
		
		std::string valueTemp;
		std::string weightTemp;
		double minValue = 0;
		double maxValue = 0;
		double value;
		int weight;
		std::multimap<double, int> data;
		
		while(std::getline(PMT2File, valueTemp, ',')) {
		
			std::getline(PMT2File, weightTemp);
			
			value  = std::stod(valueTemp);
			weight = std::stoi(weightTemp);
			
			data.insert(make_pair(value, weight));
			
			if(value < minValue) {
				minValue = value;
			}
			
			if(value > maxValue) {
				maxValue = value;
			}
			
			//std::cout << value << "   " << weight << std::endl;
		}
		
		double numberOfEvents = 0.0;
		for (auto it = data.begin(); it != data.end(); it++) {
			numberOfEvents = numberOfEvents + it->second;
		}
		
		TH1D *PMT2Histo = new TH1D("PMT2Histo", "PMT2Histo", data.size(), minValue, maxValue);
		int bin = 1;
		for (auto it = data.begin(); it != data.end(); it++) {
			double normalizedValue = it->second/numberOfEvents;
			PMT2Histo->SetBinContent(bin, normalizedValue);
			bin++;
		}
		std::string title = "PMT 1 (Run " + RUN + ") Pulse Areas";
		PMT2Histo->SetTitle(title.c_str());
		PMT2Histo->GetXaxis()->SetTitle("Vs");
		PMT2Histo->SetFillColor(33);
		//PMT2Histo->Draw();
		PMT2Histo->Write();
		PMT2File.close();
	}
	
	/*///
	/*/// FINDING ALL PULSES IN EACH WAVEFORM
	/// 
	
	std::multimap<double, double> totalSipmPeaks; //(time, amplitude)
	for (int trigger = firstSiPMTrigger; trigger <= lastSiPMTrigger; trigger++) {
		
		///READ FROM SIPM WAVEFORMS TO FIND PEDESTAL
		///Define filename
		std::string temp = to_string(trigger);
		int numberOfDigits = temp.length();
		
		int numberOfZeros = 5 - numberOfDigits;
		std::string zeroTag = "";
		for (int i = 0; i < numberOfZeros; i++) {
			zeroTag = zeroTag + "0";
		}
		
		//std::cout << "Trigger: " << trigger << "    Number of digits: " << numberOfDigits << "   Number of zeros: " << numberOfZeros << "    zeroTag: " << zeroTag << std::endl;
		std::string filename = dataDirectory + sipmFile + zeroTag + to_string(trigger) + ".txt";
	
		///Open file to find threshold
		std::multimap< int, std::pair< double, double > > amplitudeParameters;  ///( trigger, ( mean, sigma )  )
		std::ifstream fileFirst(filename.c_str());
		if (!fileFirst) {
			std::cout << "Cannot open " << filename << std::endl;
		} else {
			///Read file
			std::cout << "Finding threshold for trigger: " << trigger << std::endl;
			std::string word = "";
			//std::vector<double > time;
			std::vector<double > voltage;
			//double min = 0;
			
			///Skip first text
			while (word != "Time,Ampl") {
				fileFirst >> word;
			}
			
			while(!fileFirst.eof()) {
				///Data starts
				std::string vTemp;
				std::string tTemp;
				
				std::getline(fileFirst, tTemp, ',');
				std::getline(fileFirst, vTemp);
				
				double v = atof(vTemp.c_str());
				//double t = atof(tTemp.c_str());
				voltage.push_back(v);
			}
			
			///Make amplitude distribution
			//TCanvas *c3 = new TCanvas("c3", "c3", 1000, 500);
			TH1D *amplitudeDist = new TH1D("amplitudeDist", "amplitudeDist", amplitudeDistributionBins, amplitudeDistributionMin, amplitudeDistributionMax);
			for (int i = 0; i < voltage.size(); i++) {
				amplitudeDist->Fill( voltage.at(i) );
			}
			//amplitudeDist->Draw();
			
			///Fit gaussian to pedastal
			TF1 *gaussian = new TF1("gaussian", "gaus");
			amplitudeDist->Fit("gaussian","0Q","",-0.05,0.05);
			double mean  = gaussian->GetParameter(1);
			double sigma = gaussian->GetParameter(2);
			//std::cout << mean << "  " << sigma << std::endl;
			
			std::pair<double, double> p;
			p = make_pair(mean, sigma);
			amplitudeParameters.insert(std::pair<int, std::pair<double, double > >(trigger, p) );
			delete amplitudeDist;
		}
		
		fileFirst.close();
		
		///NEED TO FIND ALL MINIMUMS IN SIPM PULSE
		std::ifstream fileSecond(filename.c_str());
		if (!fileSecond) {
			std::cout << "Cannot open " << filename << std::endl;
		} else {
			///Read file
			std::string word = "";
			std::vector<double > time;
			std::vector<double > voltage;
			double min = 0;
			
			std::cout << "Reading Filename: " << filename << "\n" << std::endl;
			///Skip first text
			while (word != "Time,Ampl") {
				fileSecond >> word;
			}
			
			///Rising Edge threshold for this trigger
			double risingEdge = amplitudeParameters.find(trigger)->second.first - discSigma*amplitudeParameters.find(trigger)->second.second;
			
			while(!fileSecond.eof()) {
				///Data starts
				std::string vTemp;
				std::string tTemp;
					
				std::getline(fileSecond, tTemp, ',');
				std::getline(fileSecond, vTemp);
				
				double v = atof(vTemp.c_str());
				double t = atof(tTemp.c_str());
				
				///Search for rising edge
				if (v < risingEdge) {
					///Found start of pulse 
					while (v < risingEdge && !fileSecond.eof()) {
						std::getline(fileSecond, tTemp, ',');
						std::getline(fileSecond, vTemp);
						v = atof(vTemp.c_str());
						t = atof(tTemp.c_str());
						
						if (v < min) {
							min = v;
						}
					}
					
					double fallingEdge = v;
					double width = abs(fallingEdge - risingEdge);
					
					///Width threshold used to filter out noise
					if (width > something) {
						///Found local minimum and pulse
						totalSipmPeaks.insert(std::pair<double, double>(t, min) );
					}
				}
			}
		}
			
		fileSecond.close();
	}
	
	TH1D *timeDist = new TH1D("timeDist", "timeDist", timeDistBins, timeDistMin, timeDistMax);
	for (auto it = totalSipmPeaks.begin(); it != totalSipmPeaks.end(); it++) {
		timeDist->Fill( it->first );
	}
	TCanvas *c4 = new TCanvas("c4", "c4", 1000, 500);
	std::string title1 = "Time of Minimum SiPM Amplitudes All Times (Run " + RUN + ")";
	timeDist->SetTitle(title1.c_str());
	timeDist->Draw();
	timeDist->Write();
	
	TH1D *minDist = new TH1D("minDist", "minDist", singleMinMinDistBins, singleMinMinDistMin, singleMinMinDistMax);
	for (auto it = totalSipmPeaks.begin(); it != totalSipmPeaks.end(); it++) {
		minDist->Fill( it->second );
	}
	///Divide hist by runtime
	for (int bin = 1; bin <= minDist->GetNbinsX(); bin++) {
		double contentNormalized = minDist->GetBinContent(bin)/runTime;
		minDist->SetBinContent(bin, contentNormalized);
	}
	TCanvas *c5 = new TCanvas("c5", "c5", 1000, 500);
	std::string title2 = "Minimum SiPM Amplitudes All Times (Run " + RUN + ")";
	minDist->SetTitle(title2.c_str());
	minDist->GetXaxis()->SetTitle("V");
	c5->SetLogy();
	minDist->Draw();
	minDist->Write();*/
	
	/*///
	/// JUST THE MIMUMUM
	///
	
	//std::string outputFile = "./waveforms/";
	std::ofstream output(outputWaveformFile.c_str());
	
	std::multimap<double, double> singleMinSipmPeaks; //(time, amplitude)
	for (int trigger = firstSiPMTrigger; trigger <= lastSiPMTrigger; trigger++) {
		
		///READ FROM SIPM WAVEFORMS TO FIND PEDESTAL
		///Define filename
		std::string temp = to_string(trigger);
		int numberOfDigits = temp.length();
		
		int numberOfZeros = 5 - numberOfDigits;
		std::string zeroTag = "";
		for (int i = 0; i < numberOfZeros; i++) {
			zeroTag = zeroTag + "0";
		}
		
		//std::cout << "Trigger: " << trigger << "    Number of digits: " << numberOfDigits << "   Number of zeros: " << numberOfZeros << "    zeroTag: " << zeroTag << std::endl;
		std::string filename = dataDirectory + sipmFile + zeroTag + to_string(trigger) + ".txt";
		
		///NEED TO FIND ALL MINIMUMS IN SIPM PULSE
		
		std::ifstream fileSecond(filename.c_str());
		if (!fileSecond) {
			std::cout << "Cannot open " << filename << std::endl;
		} else {
			///Read file
			std::string word = "";
			std::vector<double > time;
			std::vector<double > voltage;
			double min = 0;
			double minTime;
			
			std::cout << "Reading Filename: " << filename << "\n" << std::endl;
			///Skip first text
			while (word != "Time,Ampl") {
				fileSecond >> word;
			}
			
			while(!fileSecond.eof()) {
				///Data starts
				std::string vTemp;
				std::string tTemp;
					
				std::getline(fileSecond, tTemp, ',');
				std::getline(fileSecond, vTemp);
				
				double v = atof(vTemp.c_str());
				double t = atof(tTemp.c_str());
				
				if (v < min) {
					min = v;
					minTime = t;
				}
			}
				
			///Found minimum
			singleMinSipmPeaks.insert(std::pair<double, double>(minTime, min) );
				if (min <= -0.15) {
						output << filename << "\n";
				}
			fileSecond.close();
		}
	}
	output.close();
	
	TH1D *singleMinTimeDist = new TH1D("singleMinTimeDist", "singleMinTimeDist", singleMinTimeDistBins, singleMinTimeDistMin, singleMinTimeDistMax);
	for (auto it = singleMinSipmPeaks.begin(); it != singleMinSipmPeaks.end(); it++) {
		singleMinTimeDist->Fill( it->first );
	}
	TCanvas *c7 = new TCanvas("c7", "c7", 1000, 500);
	std::string title3 = "Time of Minimum SiPM Amplitudes (Run " + RUN + ")";
	singleMinTimeDist->SetTitle(title3.c_str());
	singleMinTimeDist->GetXaxis()->SetTitle("Seconds");
	singleMinTimeDist->Draw();
	singleMinTimeDist->Write();
	
	TH1D *singleMinMinDist = new TH1D("singleMinMinDist", "singleMinMinDist", singleMinMinDistBins, singleMinMinDistMin, singleMinMinDistMax);
	for (auto it = singleMinSipmPeaks.begin(); it != singleMinSipmPeaks.end(); it++) {
		singleMinMinDist->Fill( it->second );
	}
	///Divide hist by runtime
	for (int bin = 1; bin <= singleMinMinDist->GetNbinsX(); bin++) {
		double contentNormalized = singleMinMinDist->GetBinContent(bin)/runTime;
		singleMinMinDist->SetBinContent(bin, contentNormalized);
	}
	TCanvas *c8 = new TCanvas("c8", "c8", 1000, 500);
	std::string title4 = "Minimum SiPM Amplitudes (Run " + RUN + ")";
	singleMinMinDist->SetTitle(title4.c_str());
	singleMinMinDist->GetXaxis()->SetTitle("V");
	c8->SetLogy();
	singleMinMinDist->Draw();
	singleMinMinDist->Write();
	
	std::cout << "\n\nAnalyzed Run " << RUN << ". Runtime was " << runTime << " minutes. " << std::endl; */
}
