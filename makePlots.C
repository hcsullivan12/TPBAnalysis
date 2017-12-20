void makePlots() {
	TFile *f = new TFile("./Run3Data.root", "READ");
	
	TH1D* controlMin = nullptr;
	TH1D* tpbMin = nullptr;
	
	TH1D* controlArea = nullptr;
	TH1D* tpbArea = nullptr;
	
	TH1D* controlRisingTime = nullptr;
	TH1D* tpbRisingTime = nullptr;
	
	f->GetObject("controlMinDist", controlMin);
	f->GetObject("tpbMinDist", tpbMin);
	
	f->GetObject("controlAreaDist", controlArea);
	f->GetObject("tpbAreaDist", tpbArea);
	
	f->GetObject("controlRisingTimeDist", controlRisingTime);
	f->GetObject("tpbRisingTimeDist", tpbRisingTime);
	
	///Plot min amplitude dist
	TCanvas *c1 = new TCanvas("c1", "c1", 1000, 1000);
	tpbMin->SetTitle("SiPM Minimum Amplitudes");
	tpbMin->GetXaxis()->SetTitle("V");
	tpbMin->GetYaxis()->SetTitle("Rate");
	tpbMin->GetYaxis()->SetTitleOffset(1.5);
	tpbMin->Draw();
	gStyle->SetOptStat(0);
	controlMin->Draw("same");
	
	TLegend *leg1 = new TLegend(0.1,0.7,0.48,0.9);
	leg1->AddEntry(controlMin,"Control","f");
	leg1->AddEntry(tpbMin, "TPB", "f");
	leg1->Draw("same");
	
	///Plot area dist
	TCanvas *c2 = new TCanvas("c2", "c2", 1000, 1000);
	tpbArea->SetTitle("SiPM Pulse Areas");
	tpbArea->GetXaxis()->SetTitle("Vs");
	tpbArea->GetYaxis()->SetTitle("Rate");
	tpbArea->GetYaxis()->SetTitleOffset(1.5);
	tpbArea->Draw();
	gStyle->SetOptStat(0);
	controlArea->Draw("same");
	
	TLegend *leg2 = new TLegend(0.1,0.7,0.48,0.9);
	leg2->AddEntry(controlArea,"Control","f");
	leg2->AddEntry(tpbArea, "TPB", "f");
	leg2->Draw("same");
	
	///Plot rising edge time dist
	TCanvas *c3 = new TCanvas("c3", "c3", 1000, 1000);
	tpbRisingTime->SetTitle("SiPM Time of Rising Edge");
	tpbRisingTime->GetXaxis()->SetTitle("Time Relative to PMT Trigger (s)");
	tpbRisingTime->GetYaxis()->SetTitle("Rate");
	tpbRisingTime->GetYaxis()->SetTitleOffset(1.5);
	tpbRisingTime->Draw();
	gStyle->SetOptStat(0);
	controlRisingTime->Draw("same");
	
	TLegend *leg3 = new TLegend(0.1,0.7,0.48,0.9);
	leg3->AddEntry(controlRisingTime,"Control","f");
	leg3->AddEntry(tpbRisingTime, "TPB", "f");
	leg3->Draw("same");
	
}
