void Run2andRun3Ampltiudes()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Dec 12 01:27:09 2017) by ROOT version6.06/08
   TCanvas *c1 = new TCanvas("c1", "c1",1981,24,1859,1056);
   gStyle->SetOptStat(0);
   c1->Range(-0.5625,-3.581189,0.06250001,0.5222224);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLogy();
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *singleMinMinDist__1 = new TH1D("singleMinMinDist__1","Minimum SiPM Amplitudes",100,-0.5,0);
   singleMinMinDist__1->SetBinContent(0,36);
   singleMinMinDist__1->SetBinContent(3,0.001349528);
   singleMinMinDist__1->SetBinContent(4,0.001349528);
   singleMinMinDist__1->SetBinContent(8,0.001349528);
   singleMinMinDist__1->SetBinContent(16,0.002699055);
   singleMinMinDist__1->SetBinContent(23,0.001349528);
   singleMinMinDist__1->SetBinContent(25,0.002699055);
   singleMinMinDist__1->SetBinContent(26,0.001349528);
   singleMinMinDist__1->SetBinContent(29,0.002699055);
   singleMinMinDist__1->SetBinContent(31,0.001349528);
   singleMinMinDist__1->SetBinContent(34,0.001349528);
   singleMinMinDist__1->SetBinContent(35,0.001349528);
   singleMinMinDist__1->SetBinContent(36,0.001349528);
   singleMinMinDist__1->SetBinContent(38,0.004048583);
   singleMinMinDist__1->SetBinContent(39,0.005398111);
   singleMinMinDist__1->SetBinContent(41,0.002699055);
   singleMinMinDist__1->SetBinContent(43,0.001349528);
   singleMinMinDist__1->SetBinContent(47,0.001349528);
   singleMinMinDist__1->SetBinContent(49,0.001349528);
   singleMinMinDist__1->SetBinContent(51,0.004048583);
   singleMinMinDist__1->SetBinContent(56,0.001349528);
   singleMinMinDist__1->SetBinContent(58,0.005398111);
   singleMinMinDist__1->SetBinContent(59,0.001349528);
   singleMinMinDist__1->SetBinContent(62,0.001349528);
   singleMinMinDist__1->SetBinContent(63,0.001349528);
   singleMinMinDist__1->SetBinContent(64,0.001349528);
   singleMinMinDist__1->SetBinContent(65,0.002699055);
   singleMinMinDist__1->SetBinContent(66,0.002699055);
   singleMinMinDist__1->SetBinContent(67,0.004048583);
   singleMinMinDist__1->SetBinContent(68,0.001349528);
   singleMinMinDist__1->SetBinContent(69,0.006747638);
   singleMinMinDist__1->SetBinContent(71,0.004048583);
   singleMinMinDist__1->SetBinContent(72,0.002699055);
   singleMinMinDist__1->SetBinContent(75,0.004048583);
   singleMinMinDist__1->SetBinContent(77,0.006747638);
   singleMinMinDist__1->SetBinContent(79,0.001349528);
   singleMinMinDist__1->SetBinContent(80,0.002699055);
   singleMinMinDist__1->SetBinContent(81,0.005398111);
   singleMinMinDist__1->SetBinContent(82,0.002699055);
   singleMinMinDist__1->SetBinContent(84,0.002699055);
   singleMinMinDist__1->SetBinContent(85,0.002699055);
   singleMinMinDist__1->SetBinContent(87,0.005398111);
   singleMinMinDist__1->SetBinContent(88,0.001349528);
   singleMinMinDist__1->SetBinContent(89,0.001349528);
   singleMinMinDist__1->SetBinContent(90,0.006747638);
   singleMinMinDist__1->SetBinContent(91,0.02564103);
   singleMinMinDist__1->SetBinContent(92,0.05263158);
   singleMinMinDist__1->SetBinContent(93,0.1093117);
   singleMinMinDist__1->SetBinContent(94,0.1997301);
   singleMinMinDist__1->SetBinContent(95,0.682861);
   singleMinMinDist__1->SetBinContent(96,0.06882591);
   singleMinMinDist__1->SetEntries(1069);
   singleMinMinDist__1->SetFillColor(38);
   singleMinMinDist__1->SetFillStyle(3002);
   singleMinMinDist__1->SetLineColor(4);
   singleMinMinDist__1->SetLineWidth(2);
   singleMinMinDist__1->GetXaxis()->SetTitle("V");
   singleMinMinDist__1->GetXaxis()->SetLabelFont(42);
   singleMinMinDist__1->GetXaxis()->SetLabelSize(0.035);
   singleMinMinDist__1->GetXaxis()->SetTitleSize(0.035);
   singleMinMinDist__1->GetXaxis()->SetTitleFont(42);
   singleMinMinDist__1->GetYaxis()->SetLabelFont(42);
   singleMinMinDist__1->GetYaxis()->SetLabelSize(0.035);
   singleMinMinDist__1->GetYaxis()->SetTitleSize(0.035);
   singleMinMinDist__1->GetYaxis()->SetTitleFont(42);
   singleMinMinDist__1->GetZaxis()->SetLabelFont(42);
   singleMinMinDist__1->GetZaxis()->SetLabelSize(0.035);
   singleMinMinDist__1->GetZaxis()->SetTitleSize(0.035);
   singleMinMinDist__1->GetZaxis()->SetTitleFont(42);
   singleMinMinDist__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.3069467,0.9172347,0.6925148,0.9776047,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *AText = pt->AddText("Minimum SiPM Amplitudes");
   pt->Draw();
   
   TH1D *singleMinMinDist__2 = new TH1D("singleMinMinDist__2","Time of Mimumum SiPM Amplitudes (Run 3)",100,-0.5,0);
   singleMinMinDist__2->SetBinContent(0,16);
   singleMinMinDist__2->SetBinContent(17,0.00281294);
   singleMinMinDist__2->SetBinContent(21,0.00140647);
   singleMinMinDist__2->SetBinContent(27,0.00140647);
   singleMinMinDist__2->SetBinContent(28,0.00140647);
   singleMinMinDist__2->SetBinContent(33,0.00281294);
   singleMinMinDist__2->SetBinContent(36,0.00140647);
   singleMinMinDist__2->SetBinContent(40,0.00140647);
   singleMinMinDist__2->SetBinContent(41,0.004219409);
   singleMinMinDist__2->SetBinContent(42,0.00281294);
   singleMinMinDist__2->SetBinContent(43,0.00140647);
   singleMinMinDist__2->SetBinContent(46,0.00140647);
   singleMinMinDist__2->SetBinContent(53,0.00140647);
   singleMinMinDist__2->SetBinContent(54,0.00281294);
   singleMinMinDist__2->SetBinContent(55,0.00140647);
   singleMinMinDist__2->SetBinContent(56,0.00140647);
   singleMinMinDist__2->SetBinContent(57,0.00281294);
   singleMinMinDist__2->SetBinContent(58,0.00281294);
   singleMinMinDist__2->SetBinContent(59,0.00140647);
   singleMinMinDist__2->SetBinContent(61,0.00281294);
   singleMinMinDist__2->SetBinContent(63,0.004219409);
   singleMinMinDist__2->SetBinContent(64,0.00140647);
   singleMinMinDist__2->SetBinContent(65,0.00281294);
   singleMinMinDist__2->SetBinContent(66,0.00140647);
   singleMinMinDist__2->SetBinContent(67,0.00281294);
   singleMinMinDist__2->SetBinContent(68,0.00140647);
   singleMinMinDist__2->SetBinContent(69,0.00140647);
   singleMinMinDist__2->SetBinContent(70,0.00281294);
   singleMinMinDist__2->SetBinContent(72,0.004219409);
   singleMinMinDist__2->SetBinContent(73,0.00140647);
   singleMinMinDist__2->SetBinContent(74,0.00281294);
   singleMinMinDist__2->SetBinContent(75,0.004219409);
   singleMinMinDist__2->SetBinContent(76,0.005625879);
   singleMinMinDist__2->SetBinContent(78,0.00281294);
   singleMinMinDist__2->SetBinContent(80,0.00281294);
   singleMinMinDist__2->SetBinContent(81,0.004219409);
   singleMinMinDist__2->SetBinContent(82,0.00140647);
   singleMinMinDist__2->SetBinContent(83,0.005625879);
   singleMinMinDist__2->SetBinContent(84,0.00281294);
   singleMinMinDist__2->SetBinContent(85,0.004219409);
   singleMinMinDist__2->SetBinContent(86,0.00281294);
   singleMinMinDist__2->SetBinContent(87,0.01125176);
   singleMinMinDist__2->SetBinContent(88,0.01125176);
   singleMinMinDist__2->SetBinContent(89,0.004219409);
   singleMinMinDist__2->SetBinContent(90,0.009845288);
   singleMinMinDist__2->SetBinContent(91,0.02250352);
   singleMinMinDist__2->SetBinContent(92,0.02672293);
   singleMinMinDist__2->SetBinContent(93,0.04500703);
   singleMinMinDist__2->SetBinContent(94,0.09563994);
   singleMinMinDist__2->SetBinContent(95,0.1448664);
   singleMinMinDist__2->SetBinContent(96,0.3881857);
   singleMinMinDist__2->SetBinContent(97,0.4781997);
   singleMinMinDist__2->SetBinContent(98,0.01828411);
   singleMinMinDist__2->SetEntries(1082);
   singleMinMinDist__2->SetFillColor(13);
   singleMinMinDist__2->SetFillStyle(3001);
   singleMinMinDist__2->SetLineColor(13);
   singleMinMinDist__2->SetLineWidth(2);
   singleMinMinDist__2->GetXaxis()->SetTitle("V");
   singleMinMinDist__2->GetXaxis()->SetLabelFont(42);
   singleMinMinDist__2->GetXaxis()->SetLabelSize(0.035);
   singleMinMinDist__2->GetXaxis()->SetTitleSize(0.035);
   singleMinMinDist__2->GetXaxis()->SetTitleFont(42);
   singleMinMinDist__2->GetYaxis()->SetLabelFont(42);
   singleMinMinDist__2->GetYaxis()->SetLabelSize(0.035);
   singleMinMinDist__2->GetYaxis()->SetTitleSize(0.035);
   singleMinMinDist__2->GetYaxis()->SetTitleFont(42);
   singleMinMinDist__2->GetZaxis()->SetLabelFont(42);
   singleMinMinDist__2->GetZaxis()->SetLabelSize(0.035);
   singleMinMinDist__2->GetZaxis()->SetTitleSize(0.035);
   singleMinMinDist__2->GetZaxis()->SetTitleFont(42);
   singleMinMinDist__2->Draw("same");
   
   TLegend *leg = new TLegend(0.1825525,0.6348588,0.3241788,0.7487829,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("singleMinMinDist","Run2","f");
   entry->SetFillColor(38);
   entry->SetFillStyle(3002);
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("singleMinMinDist","Run3","f");
   entry->SetFillColor(13);
   entry->SetFillStyle(3001);
   entry->SetLineColor(13);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
