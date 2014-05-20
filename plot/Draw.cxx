TH1F * DrawOverflow(TH1F *h) {
 // This function paint the histogram h with an extra bin for overflows
 UInt_t nx    = h->GetNbinsX()+1;
 Double_t *xbins= new Double_t[nx+1];
 for (UInt_t i=0;i<nx;i++)
  xbins[i]=h->GetBinLowEdge(i+1);
 xbins[nx]=xbins[nx-1]+h->GetBinWidth(nx);
 char *tempName= new char[strlen(h->GetName())+10];
 sprintf(tempName,"%swtOverFlow",h->GetName());
 // Book a temporary histogram having ab extra bin for overflows
 TH1F *htmp = new TH1F(tempName, h->GetTitle(), nx, xbins);
 //---- style
 htmp->SetLineColor(h->GetLineColor());
 htmp->SetLineWidth(h->GetLineWidth());
 htmp->SetLineStyle(h->GetLineStyle());
 
 // Reset the axis labels
 htmp->SetXTitle(h->GetXaxis()->GetTitle());
 htmp->SetYTitle(h->GetYaxis()->GetTitle());
 // Fill the new hitogram including the extra bin for overflows
 for (UInt_t i=1; i<=nx; i++)
  htmp->Fill(htmp->GetBinCenter(i), h->GetBinContent(i));
 // Fill the underflows
 htmp->Fill(h->GetBinLowEdge(1)-1, h->GetBinContent(0));
 // Restore the number of entries
 htmp->SetEntries(h->GetEntries());
 // FillStyle and color
 htmp->SetFillStyle(h->GetFillStyle());
 htmp->SetFillColor(h->GetFillColor());
 return htmp;
}


void Draw(std::string var = "hbb_mass", int NBIN = 1000, int MIN = 0, int MAX = 1000, std::string varHR = "", int Energy) {
 
 if (varHR == "") {
  varHR = var;
 }
 
 gStyle->SetOptStat(0);
 
 int nSig = 5;
 TFile* f_Sig[100];
 TTree* t_Sig[100];
 TH1F* h_Sig[100];
 
 std::vector<std::string> vNameSig;
 std::vector<std::string> vNameSigHR;
 std::vector<double> vXsecSig;
 
 //
 // BR Hbb = 5.77E-01
 // BR Hww = 2.15E-01
 // BR Hwwlvlv = 1.0105e-02 = 2.15E-01*0.047 // l = e/m
 // BH hh>bbww>bblvlv = 2 * 5.77E-01 * 2.15E-01 * 0.047 = 1.166e-02
 //
 // *1000.--> fb
 //
 double LUMI = 3000. * 1000.; //---- 3 ab
 
//  HHvbf_##tev_bbww_CV-i-C2V-j-C3-k.lhe
//  CV = 1.0
//  
//  C2V = 0.0, 0.4, 0.8, 1.2, 1.6, 2.0 (j=1,2,3,4,5,6)
//  
//  C3 = -4.0, -1.5, 3.5, 6.0 (k=7,8,9,10)
 
 
 std::cout << " Center of mass energy = " << Energy << std::endl;
 
 if (Energy == 14) {

  vNameSig.push_back("data/trees/HHvbf_14tev_bbww_CV-1-C2V-1-C3-7.lhe.hepmc.delphes.root.trees.root"); vNameSigHR.push_back("HH cv=1.0 c2v=0.0 c3=-4.0");
  vXsecSig.push_back(0.69676E-05/11784.); //---- pb

  vNameSig.push_back("data/trees/HHvbf_14tev_bbww_CV-1-C2V-1-C3-8.lhe.hepmc.delphes.root.trees.root"); vNameSigHR.push_back("HH cv=1.0 c2v=0.0 c3=-1.5");
  vXsecSig.push_back(0.42130E-05/11784.); //---- pb

  vNameSig.push_back("data/trees/HHvbf_14tev_bbww_CV-1-C2V-1-C3-9.lhe.hepmc.delphes.root.trees.root"); vNameSigHR.push_back("HH cv=1.0 c2v=0.0 c3=3.5");
  vXsecSig.push_back(0.13748E-05/11784.); //---- pb

  vNameSig.push_back("data/trees/HHvbf_14tev_bbww_CV-1-C2V-1-C3-10.lhe.hepmc.delphes.root.trees.root"); vNameSigHR.push_back("HH cv=1.0 c2v=0.0 c3=6.0");
  vXsecSig.push_back(0.14491E-05/11784.); //---- pb
  
  vNameSig.push_back("data/trees/HHvbf_14tev_bbww_CV-1-C2V-2-C3-7.lhe.hepmc.delphes.root.trees.root"); vNameSigHR.push_back("HH cv=1.0 c2v=0.4 c3=-4.0");
  vXsecSig.push_back(0.47575E-05/11784.); //---- pb
  
  
 }
 else {
  
  vNameSig.push_back("data/trees/HHvbf_100tev_bbww_CV-1-C2V-1-C3-10.lhe.hepmc.delphes.root.trees.root"); vNameSigHR.push_back("HH cv=1.0 c2v=0.0 c3=6.0");
  vXsecSig.push_back(0.15175E-04/25000.); //---- pb
  
  vNameSig.push_back("data/trees/HHvbf_100tev_bbww_CV-1-C2V-1-C3-7.lhe.hepmc.delphes.root.trees.root"); vNameSigHR.push_back("HH cv=1.0 c2v=0.0 c3=-4.0");
  vXsecSig.push_back(0.42070E-04/25000.); //---- pb
  
  vNameSig.push_back("data/trees/HHvbf_100tev_bbww_CV-1-C2V-1-C3-9.lhe.hepmc.delphes.root.trees.root"); vNameSigHR.push_back("HH cv=1.0 c2v=0.0 c3=3.5");
  vXsecSig.push_back(0.15547E-04/25000.); //---- pb

  vNameSig.push_back("data/trees/HHvbf_100tev_bbww_CV-1-C2V-2-C3-10.lhe.hepmc.delphes.root.trees.root"); vNameSigHR.push_back("HH cv=1.0 c2v=0.4 c3=6.0");
  vXsecSig.push_back(0.77973E-05/25000.); //---- pb
  

 }
 
 nSig = vXsecSig.size();
 
 TString name;
 for (int iSig = 0; iSig < nSig; iSig++) {
  f_Sig[iSig] = new TFile (vNameSig.at(iSig).c_str());
 }
 
 
 //---- background
 
//  TFile* f_ttjj = new TFile ("data/trees/unweighted_events_ttjj_14TeV.103.hepmc.delphes.root.trees.root"); //---- 1k events

// BR wwlvlv = BRW>ln*BRW>ln = 0.047 = 4.67e-02 = 0.1080*2*0.1080*2 // l = e/m

 double ttjj_xsec; 

 if (Energy == 14) {
  ttjj_xsec =  2.84017E+01*0.047/260000.; //---- pb  BR W>e/m = 0.047
 }
 else { //---- 100 TeV
  ttjj_xsec =  2.89324E+03*0.047/98000.; //---- pb  BR W>e/m = 0.047
 }
 
 // double ttjj_xsec = 2.0715/10000.; //---- pb
//  double wwbbjj_xsec = 456.11/10000.; //---- pb
 
 
 
 //---- trees
//  TTree* t_ttjj = (TTree*) f_ttjj -> Get ("ntu");
 TChain* t_ttjj = new TChain("ntu");
 if (Energy == 14) {
  t_ttjj->Add("data/trees/unweighted_events_ttjj_14TeV.*.hepmc.delphes.root.trees.root");
 }
 else {
  t_ttjj->Add("data/trees/unweighted_events_ttjj_100TeV.*.hepmc.delphes.root.trees.root");
 }
 
 
 //  TTree* t_wwbbjj = (TTree*) f_wwbbjj -> Get ("tree");
 for (int iSig = 0; iSig < nSig; iSig++) {
  t_Sig[iSig] = (TTree*) f_Sig[iSig] -> Get ("ntu");
 }
 
 
 //--------------------------
 TH1F* h_ttjj = new TH1F("ttjj","",NBIN,MIN,MAX);
//  TH1F* h_wwbbjj = new TH1F("wwbbjj","",NBIN,MIN,MAX);
 for (int iSig = 0; iSig < nSig; iSig++) {
  name = Form ("hSig_%d",iSig);
  h_Sig[iSig] = new TH1F(name.Data(),vNameSigHR.at(iSig).c_str(),NBIN,MIN,MAX);
 }
 
 
 // TString cut = Form ("jetpt1>30 && jetpt2>30 && mjj>400 && detajj>3.5");
 TString cut = Form ("1");

 if (Energy == 14) {
  cut = Form (" \
  jetpt1>30 && jetpt2>30 \
  && mjj>700 && detajj>4.0 \
  && ((bjetpt1>30 && bjetpt2>30 && abs(bjeteta1)<2.5 && abs(bjeteta2)<2.5) || (hbb_pt>50 && abs(hbb_eta)<2.5)) \
  && abs(jeteta1)<4.5 && abs(jeteta2)<4.5 \
  && pt1>20 && pt2>10 && abs(eta1)<2.5 && abs(eta2)<2.5 \
  && mll < 50 \
  && hww_mt < 125 \
  && hbb_pt > 200 \
  && mbb>105 && mbb<145 \
  ");
  
//   && mllbb > 200 \
  
//   cut = Form (" \
  jetpt1>30 && jetpt2>30 \
  && mjj>700 && detajj>4.0 \
  && ((bjetpt1>30 && bjetpt2>30 && abs(bjeteta1)<2.5 && abs(bjeteta2)<2.5) || (hbb_pt>50 && abs(hbb_eta)<2.5)) \
  && abs(jeteta1)<4.5 && abs(jeteta2)<4.5 \
  && pt1>20 && pt2>10 && abs(eta1)<2.5 && abs(eta2)<2.5 \
  ");
 }
 else {
//   cut = Form (" \
  mjj>700 && detajj>4.0 \
  && ((bjetpt1>50 && bjetpt2>50 && abs(bjeteta1)<2.5 && abs(bjeteta2)<2.5) || (hbb_pt>70 && abs(hbb_eta)<2.5)) \
  && abs(jeteta1)<4.5 && abs(jeteta2)<4.5 \
  && pt1>20 && pt2>10 && abs(eta1)<2.5 && abs(eta2)<2.5 \
  ");
  cut = Form (" \
  jetpt1>50 && jetpt2>50 \
  && mjj>700 && detajj>4.0 \
  && ((bjetpt1>50 && bjetpt2>50 && abs(bjeteta1)<2.5 && abs(bjeteta2)<2.5) || (hbb_pt>70 && abs(hbb_eta)<2.5)) \
  && abs(jeteta1)<4.5 && abs(jeteta2)<4.5 \
  && pt1>20 && pt2>10 && abs(eta1)<2.5 && abs(eta2)<2.5 \
  && mll < 70 \
  && hww_mt < 125 \
  && hbb_pt > 500 \
  ");

//   && mllbb > 600 \
  
  
 }
 
 
//  && hbb_mass > 110 && hbb_mass < 140 \
 
//  TString cut = Form (" \
//  jetpt1>30 && jetpt2>30 \
//  && mjj>400 && detajj>4.0 \
//  && bjetpt1>25 && bjetpt2>25 \
//  && abs(bjeteta1)<2.5 && abs(bjeteta2)<2.5 \
//  && abs(jeteta1)<4.5 && abs(jeteta2)<4.5 \
//  && pt1>20 && pt2>10 && abs(eta1)<2.5 && abs(eta2)<2.5 \
//  && hbb_mass > 110 && hbb_mass < 140 \
//  && mll < 70 \
//  && hww_mt < 125 \
//  && hbb_pt > 200 \
//  ");
 
//  TString cut = Form (" \
//  jetpt1>30 && jetpt2>30 \
//  && mjj>400 && detajj>4.0 \
//  && ((bjetpt1>25 && bjetpt2>25 && abs(bjeteta1)<2.5 && abs(bjeteta2)<2.5) || (hbb_pt>50 && abs(hbb_eta)<2.5)) \
//  && abs(jeteta1)<4.5 && abs(jeteta2)<4.5 \
//  && pt1>20 && pt2>10 && abs(eta1)<2.5 && abs(eta2)<2.5 \
//  && hbb_mass > 110 && hbb_mass < 140 \
//  && mll < 70 \
//  && hww_mt < 125 \
//  && hbb_pt > 200 \
//  ");
 
 // && ptll > 50 \
 
 
 TString toDraw;
 TString weight = Form ("1");
 
 for (int iSig = 0; iSig < nSig; iSig++) {
  // std::cout << t_Sig[iSig] -> GetEntries() << std::endl;
  toDraw = Form ("%s >> hSig_%d",var.c_str(),iSig);
  // std::cout << "toDraw = " << toDraw.Data() << std::endl;
  
  weight = Form ("(%s) * %f",cut.Data(),vXsecSig.at(iSig)*LUMI);
  t_Sig[iSig]->Draw(toDraw.Data(),weight.Data(),"goff");
 }
 
 toDraw = Form ("%s >> ttjj",var.c_str());
 weight = Form ("(%s) * %f",cut.Data(),ttjj_xsec*LUMI);
 t_ttjj->Draw(toDraw.Data(),weight.Data(),"goff");
//  toDraw = Form ("%s >> wwbbjj",var.c_str());
//  weight = Form ("(%s) * %f",cut.Data(),wwbbjj_xsec*LUMI);
//  t_wwbbjj->Draw(toDraw.Data(),weight.Data(),"goff");
 
 
 
 //---- estetica
 for (int iSig = 0; iSig < nSig; iSig++) {
  h_Sig[iSig]->SetMarkerColor (kRed+iSig);
  h_Sig[iSig]->SetLineColor (kRed+iSig);
  h_Sig[iSig]->SetLineWidth(3);
  h_Sig[iSig]->SetLineStyle(1+iSig);
  h_Sig[iSig]->SetMarkerSize (0);
  h_Sig[iSig]->GetXaxis()->SetTitle(varHR.c_str());
 }
 
 h_ttjj->SetMarkerColor(kBlue);
 h_ttjj->SetLineColor(kBlue);
 h_ttjj->SetLineWidth(2);
 h_ttjj->GetXaxis()->SetTitle(varHR.c_str());
 
//  h_wwbbjj->SetMarkerColor(kGreen);
//  h_wwbbjj->SetLineColor(kGreen);
//  h_wwbbjj->SetLineWidth(2);
 
 TLegend* leg = new TLegend(0.5,0.7,0.9,0.9);
 for (int iSig = 0; iSig < nSig; iSig++) {
  leg->AddEntry(h_Sig[iSig],vNameSigHR.at(iSig).c_str(),"l");
 }
 leg->AddEntry(h_ttjj,"ttjj","l");
//  leg->AddEntry(h_wwbbjj,"wwbbjj","l");
 leg->SetFillStyle(0);
 
 
 //---- overflow bin
 h_ttjj = DrawOverflow(h_ttjj);
 for (int iSig = 0; iSig < nSig; iSig++) {
  h_Sig[iSig] = DrawOverflow(h_Sig[iSig]);
 }
 
 
 //---- normalized
 TCanvas* cn = new TCanvas ("cn","cn",800,600);
 for (int iSig = 0; iSig < nSig; iSig++) {
  if (iSig ==0) h_Sig[iSig]->DrawNormalized();
  else h_Sig[iSig]->DrawNormalized("same");
 }
 h_ttjj->DrawNormalized("same");
//  h_wwbbjj->DrawNormalized("same");
 leg->Draw();
 cn->SetGrid();
  
 //---- lumi scaled
 TCanvas* cnlumi = new TCanvas ("cnlumi","cnlumi",800,600);
 h_ttjj->Draw();
//  h_wwbbjj->Draw("same");
 for (int iSig = 0; iSig < nSig; iSig++) {
  h_Sig[iSig]->Draw("same");
 }
 leg->Draw();
 cnlumi->SetGrid();
 
 
 //--------------
 //---- dump ----
 std::cout << std::endl << std::endl << std::endl;
 for (int iSig = 0; iSig < nSig; iSig++) {
  for (int iBin=0; iBin<NBIN; iBin++) {
   std::cout << h_Sig[iSig]->GetBinContent(iBin+1) << " : " ;
  }
  std::cout << std::endl;
 }

 std::cout << "~~~~" << std::endl;
 for (int iBin=0; iBin<NBIN; iBin++) {
  std::cout << h_ttjj->GetBinContent(iBin+1) << " : " ;
 }
 std::cout << std::endl;
 
 std::cout << std::endl << std::endl << std::endl;
 
}


