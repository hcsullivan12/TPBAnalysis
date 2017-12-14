double controlRuntime = 796.764; ///min
double tpbRuntime     = 578.00; ///min

///DATAFILE NAME
std::string dataFilename                   = "/home/hunter/Desktop/TPBTests/Results/controldataFile.root";

///CONTROL RUN
std::string pmt1Filename                   = "/home/hunter/Desktop/TPBTests/ControlRunData/M3control_PMT_C1_area00000.txt";
std::string pmt2Filename                   = "/home/hunter/Desktop/TPBTests/ControlRunData/M4control_PMT_C2_area00000.txt";
std::string SiPMMinFilename                = "/home/hunter/Desktop/TPBTests/ControlRunData/M1sipm_minV_360mV_00000.txt";
std::string SiPMAreaFilename               = "/home/hunter/Desktop/TPBTests/ControlRunData/M2sipm_area_360mV_00000.txt";
std::string SiPMMinCoincidTriggerFilename  = "/home/hunter/Desktop/TPBTests/ControlRunData/M1control_SiPM_minV00000.txt";
std::string SiPMAreaCoincidTriggerFilename = "/home/hunter/Desktop/TPBTests/ControlRunData/M2control_SiPM_area00000.txt";

/*///RUN1
std::string pmt1Filename                   = "/home/hunter/Desktop/TPBTests/Run1/M1Run1_pmt1_area_360mV_trigger00000.txt";
std::string pmt2Filename                   = "/home/hunter/Desktop/TPBTests/Run1/M4Run1_pmt2_area_360mV_trigger00000.txt";
std::string SiPMMinFilename                = "/home/hunter/Desktop/TPBTests/Run1/7/M1Run1_sipm_min_360mV_700000.txt";
std::string SiPMAreaFilename               = "/home/hunter/Desktop/TPBTests/Run1/7/M2Run1_sipm_area_360mV_700000.txt";
std::string SiPMMinCoincidTriggerFilename  = "/home/hunter/Desktop/TPBTests/Run1/M1Run1_sipm_min_360mV_trigger00000.txt";
std::string SiPMAreaCoincidTriggerFilename = "/home/hunter/Desktop/TPBTests/Run1/M2Run1_sipm_area_360mV_trigger00000.txt";*/

void tpbTests() {
	
	TFile *dataFile = new TFile(dataFilename.c_str(), "RECREATE");
	
	///Open pmt1 file
	std::ifstream pmt1File(pmt1Filename.c_str());
	if (!pmt1File) {
		std::cout << "Cannot open " << pmt1Filename << std::endl;
	} else {
		
		string word = "";
		///Skip first text
		while (word != "Time,Ampl") {
			//std::cout << word << std::endl;
			pmt1File >> word;
		}
		
		std::string valueTemp;
		std::string weightTemp;
		double minValue = 0;
		double maxValue = 0;
		double value;
		int weight;
		std::multimap<double, int> data;
		
		while(std::getline(pmt1File, valueTemp, ',')) {
		
			std::getline(pmt1File, weightTemp);
			
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
		
		//TCanvas *c1 = new TCanvas("c1", "c1", 1000, 500);
		TH1D *pmt1Histo = new TH1D("pmt1Histo", "pmt1Histo", data.size(), minValue, maxValue);
		double numberOfEvents = 0.0;
		for (auto it = data.begin(); it != data.end(); it++) {
			numberOfEvents = numberOfEvents + it->second;
		}
		int bin = 1;
		for (auto it = data.begin(); it != data.end(); it++) {
			double normalizedValue = it->second/numberOfEvents;
			//std::cout << it->second << "  " << data.size() << "   " << normalizedValue << std::endl;
			pmt1Histo->SetBinContent(bin, normalizedValue);
			bin++;
		}
		pmt1Histo->SetTitle("PMT 1 Pulse Areas");
		pmt1Histo->GetXaxis()->SetTitle("Vs");
		pmt1Histo->SetFillColor(33);
		//pmt1Histo->Draw();
		pmt1Histo->Write();
		pmt1File.close();
	}
	
	std::cout << "\n\n";
	
	///Open pmt2 file
	std::ifstream pmt2File(pmt2Filename.c_str());
	if (!pmt2File) {
		std::cout << "Cannot open " << pmt2Filename << std::endl;
	} else {
		
		string word = "";
		///Skip first text
		while (word != "Time,Ampl") {
			//std::cout << word << std::endl;
			pmt2File >> word;
		}
		
		std::string valueTemp;
		std::string weightTemp;
		double minValue = 0;
		double maxValue = 0;
		double value;
		int weight;
		std::multimap<double, int> data;
		
		while(std::getline(pmt2File, valueTemp, ',')) {
		
			std::getline(pmt2File, weightTemp);
			
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
		
		//TCanvas *c2 = new TCanvas("c2", "c2", 1000, 500);
		TH1D *pmt2Histo = new TH1D("pmt2Histo", "pmt2Histo", data.size(), minValue, maxValue);
		double numberOfEvents = 0.0;
		for (auto it = data.begin(); it != data.end(); it++) {
			numberOfEvents = numberOfEvents + it->second;
		}
		int bin = 1;
		for (auto it = data.begin(); it != data.end(); it++) {
			double normalizedValue = it->second/numberOfEvents;
			pmt2Histo->SetBinContent(bin, normalizedValue);
			bin++;
		}
		pmt2Histo->SetTitle("PMT 2 Pulse Areas");
		pmt2Histo->GetXaxis()->SetTitle("Vs");
		pmt2Histo->SetFillColor(33);
		//pmt2Histo->Draw();
		pmt2Histo->Write();
		pmt2File.close();
	}
	
	///Open SiPM min file
	std::ifstream sipmMinFile(SiPMMinFilename.c_str());
	if (!sipmMinFile) {
		std::cout << "Cannot open " << SiPMMinFilename << std::endl;
	} else {
		
		string word = "";
		///Skip first text
		while (word != "Time,Ampl") {
			//std::cout << word << std::endl;
			sipmMinFile >> word;
		}
		
		std::string valueTemp;
		std::string weightTemp;
		double minValue = 0;
		double maxValue = 0;
		double value;
		int weight;
		std::multimap<double, int> data;
		
		while(std::getline(sipmMinFile, valueTemp, ',')) {
		
			std::getline(sipmMinFile, weightTemp);
			
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
		
		//TCanvas *c3 = new TCanvas("c3", "c3", 1000, 500);
		TH1D *sipmMinHisto = new TH1D("sipmMinHisto", "sipmMinHisto", data.size(), minValue, maxValue);
		double numberOfEvents = 0.0;
		for (auto it = data.begin(); it != data.end(); it++) {
			numberOfEvents = numberOfEvents + it->second;
		}
		int bin = 1;
		for (auto it = data.begin(); it != data.end(); it++) {
			double normalizedValue = it->second/numberOfEvents;
			//double normalizedValue = it->second/tpbRuntime;
			sipmMinHisto->SetBinContent(bin, normalizedValue);
			bin++;
		}
		sipmMinHisto->SetTitle("SiPM Minimum Voltage (SiPM Trigger)");
		sipmMinHisto->GetXaxis()->SetTitle("V");
		sipmMinHisto->SetFillColor(33);
		//sipmMinHisto->Draw();
		sipmMinHisto->Write();
		sipmMinFile.close();
	}
	
	///Open SiPM area file
	std::ifstream sipmAreaFile(SiPMAreaFilename.c_str());
	if (!sipmAreaFile) {
		std::cout << "Cannot open " << SiPMAreaFilename << std::endl;
	} else {
		
		string word = "";
		///Skip first text
		while (word != "Time,Ampl") {
			//std::cout << word << std::endl;
			sipmAreaFile >> word;
		}
		
		std::string valueTemp;
		std::string weightTemp;
		double minValue = 0;
		double maxValue = 0;
		double value;
		int weight;
		std::multimap<double, int> data;
		
		while(std::getline(sipmAreaFile, valueTemp, ',')) {
		
			std::getline(sipmAreaFile, weightTemp);
			
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
		
		//TCanvas *c4 = new TCanvas("c4", "c4", 1000, 500);
		TH1D *sipmAreaHisto = new TH1D("sipmAreaHisto", "sipmAreaHisto", data.size(), minValue, maxValue);
		double numberOfEvents = 0.0;
		for (auto it = data.begin(); it != data.end(); it++) {
			numberOfEvents = numberOfEvents + it->second;
		}
		int bin = 1;
		for (auto it = data.begin(); it != data.end(); it++) {
			double normalizedValue = it->second/numberOfEvents;
			sipmAreaHisto->SetBinContent(bin, normalizedValue);
			bin++;
		}
		sipmAreaHisto->SetTitle("SiPM Pulse Area (SiPM Trigger)");
		sipmAreaHisto->GetXaxis()->SetTitle("Vs");
		sipmAreaHisto->SetFillColor(33);
		//sipmAreaHisto->Draw();
		sipmAreaHisto->Write();
		sipmAreaFile.close();
	}
	
	///Open SiPM min (Coincidence Trigger) file
	std::ifstream sipmMinCoincidenceFile(SiPMMinCoincidTriggerFilename.c_str());
	if (!sipmMinCoincidenceFile) {
		std::cout << "Cannot open " << SiPMMinCoincidTriggerFilename << std::endl;
	} else {
		
		string word = "";
		///Skip first text
		while (word != "Time,Ampl") {
			//std::cout << word << std::endl;
			sipmMinCoincidenceFile >> word;
		}
		
		std::string valueTemp;
		std::string weightTemp;
		double minValue = 0;
		double maxValue = 0;
		double value;
		int weight;
		std::multimap<double, int> data;
		
		while(std::getline(sipmMinCoincidenceFile, valueTemp, ',')) {
		
			std::getline(sipmMinCoincidenceFile, weightTemp);
			
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
		
		//TCanvas *c5 = new TCanvas("c5", "c5", 1000, 500);
		TH1D *sipmMinCoincidenceHisto = new TH1D("sipmMinCoincidenceHisto", "sipmMinCoincidenceHisto", data.size(), minValue, maxValue);
		double numberOfEvents = 0.0;
		double binWidth = 0;
		for (auto it = data.begin(); it != data.end(); it++) {
			numberOfEvents = numberOfEvents + it->second;
			binWidth = binWidth - it->first;
		}
		int bin = 1;
		
		for (auto it = data.begin(); it != data.end(); it++) {
			//double normalizedValue = it->second/numberOfEvents;
			double normalizedValue = it->second/(controlRuntime*binWidth);
			sipmMinCoincidenceHisto->SetBinContent(bin, normalizedValue);
			bin++;
		}
		sipmMinCoincidenceHisto->SetTitle("SiPM Minimum Voltage (Coincidence Trigger)");
		sipmMinCoincidenceHisto->GetXaxis()->SetTitle("V");
		sipmMinCoincidenceHisto->SetFillColor(33);
		//sipmMinCoincidenceHisto->Draw();
		sipmMinCoincidenceHisto->Write();
		sipmMinCoincidenceFile.close();
	}
	
	///Open SiPM area (Coincidence Trigger) file
	std::ifstream sipmAreaCoincidenceFile(SiPMAreaCoincidTriggerFilename.c_str());
	if (!sipmAreaCoincidenceFile) {
		std::cout << "Cannot open " << SiPMAreaCoincidTriggerFilename << std::endl;
	} else {
		
		string word = "";
		///Skip first text
		while (word != "Time,Ampl") {
			//std::cout << word << std::endl;
			sipmAreaCoincidenceFile >> word;
		}
		
		std::string valueTemp;
		std::string weightTemp;
		double minValue = 0;
		double maxValue = 0;
		double value;
		int weight;
		std::multimap<double, int> data;
		
		while(std::getline(sipmAreaCoincidenceFile, valueTemp, ',')) {
		
			std::getline(sipmAreaCoincidenceFile, weightTemp);
			
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
		
		//TCanvas *c6 = new TCanvas("c6", "c6", 1000, 500);
		TH1D *sipmAreaCoincidenceHisto = new TH1D("sipmAreaCoincidenceHisto", "sipmAreaCoincidenceHisto", data.size(), minValue, maxValue);
		double numberOfEvents = 0.0;
		for (auto it = data.begin(); it != data.end(); it++) {
			numberOfEvents = numberOfEvents + it->second;
		}
		int bin = 1;
		for (auto it = data.begin(); it != data.end(); it++) {
			double normalizedValue = it->second/numberOfEvents;
			sipmAreaCoincidenceHisto->SetBinContent(bin, normalizedValue);
			bin++;
		}
		sipmAreaCoincidenceHisto->SetTitle("SiPM Pulse Area (Coincidence Trigger)");
		sipmAreaCoincidenceHisto->GetXaxis()->SetTitle("Vs");
		sipmAreaCoincidenceHisto->SetFillColor(33);
		//sipmAreaCoincidenceHisto->Draw();
		sipmAreaCoincidenceHisto->Write();
		sipmAreaCoincidenceFile.close();
	}
	
}
