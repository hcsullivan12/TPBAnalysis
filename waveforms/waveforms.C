
						 
void waveforms() {
	//std::cout << "asdf: " << files[3] << std::endl;
	
	std::vector<std::string> files;
	
	///Read waveform files
	std::string file = "./controlRun3acceptedWaveforms.txt";
	std::ifstream fileFirst(file.c_str());
	if (!fileFirst) {
			std::cout << "Cannot open " << file << std::endl;
	} else {
		std::string line;
		while (std::getline(fileFirst, line)) {
			files.push_back(line);
			//std:cout << line << std::endl;
		}
	}
	
	
	TFile *f = new TFile("./controlRun3acceptedWaveforms.root", "RECREATE");
	
	for (int i = 0; i < files.size(); i++) {
		
		std::ifstream fileSecond(files.at(i).c_str());
		if (!fileSecond) {
			std::cout << "Cannot open " << files.at(i) << std::endl;
		} else {
			///Read file
			std::string word = "";
			std::vector<double > time;
			std::vector<double > voltage;
			
			std::cout << "Reading Filename: " << files.at(i) << "\n" << std::endl;
			
			while(!fileSecond.eof()) {
				///Data starts
				std::string vTemp;
				std::string tTemp;
				
				///Skip first text
				while (word != "Time,Ampl") {
					fileSecond >> word;
				}
					
				std::getline(fileSecond, tTemp, ',');
				std::getline(fileSecond, vTemp);
				
				//std::cout << tTemp << "  " << vTemp << std::endl;
				
				double v = atof(vTemp.c_str());
				double t = atof(tTemp.c_str());
				
				time.push_back(t);
				voltage.push_back(v);
			}
			fileSecond.close();
			
			///Plot
			TGraph *graph = new TGraph(time.size(), &time[0], &voltage[0]);
			graph->Write();
		}
	}
	f->Close();
}
