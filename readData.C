std::string dataDirectory = "/home/hunter/Desktop/TPBTests/data";
std::string outputWaveformFile = "./waveforms/waveformFiles.txt";
double run2Time = 741; ///min
double run3Time = 711; ///min 

///(Run3Equivalent) Control






///Run2
int firstSiPMTrigger      = 15;
int lastSiPMTrigger       = 983; 
std::string PMT1Filename  = "/Run2/pmt1/M1pmt1_00000.txt";
std::string PMT2Filename  = "/Run2/pmt2/M2pmt2_00000.txt";
std::string sipmFile      = "/Run2/sipm/C3Run2_coinSiPM_"; 

/*///Run3
int firstSiPMTrigger      = 0;
int lastSiPMTrigger       = 981;
std::string PMT1Filename  = "/Run3/pmt1/M1pmt_1_00000.txt";
std::string PMT2Filename  = "/Run3/pmt2/M2pmt_2_00000.txt";
std::string sipmFile      = "/Run3/sipm/C3sipm";*/

///Histogram parameters
int amplitudeDistributionBins   = 1000;
double amplitudeDistributionMin = -2;
double amplitudeDistributionMax = 2;

int timeDistBins   = 100;
double timeDistMin = -0.00002;
double timeDistMax = 0.00008;

int singleMinTimeDistBins   = 100;
double singleMinTimeDistMin = -0.00002;
double singleMinTimeDistMax = 0.00008;

int singleMinMinDistBins   = 100;
double singleMinMinDistMin = -0.5;
double singleMinMinDistMax = 0;

/*///Thresholds
double discSigma = 3; ///Probably should get this info from control run
double discMean  = ?; ///Probably should get this info from control run
double discWidth = ?; ///Probably should get this info from control run*/

void readData() {
	
	///File to write data to
	TFile *data = new TFile("./Run2Data.root", "RECREATE");	
	std::string RUN = "2";
	
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
	/// FINDING ALL PULSES IN EACH WAVEFORM
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
	
	///
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
	
	std::cout << "\n\nAnalyzed Run " << RUN << ". Runtime was " << runTime << " minutes. " << std::endl; 
}
