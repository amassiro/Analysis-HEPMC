// to compile:
// c++ -o ntupleMakerHEPMC.exe   ntupleMakerHEPMC.cpp -lm `root-config --cflags --glibs`
//
// to use:
// ./ntupleMakerHEPMC.exe fileHEPMC outputFileRoot
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <assert.h>


#include "TTree.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"

#include "TRandom.h"


struct ptsort: public std::binary_function<TLorentzVector, TLorentzVector, bool> {
 bool operator () (const TLorentzVector & x, const TLorentzVector & y) {
  return (x.Perp () < y.Perp () ) ;
 }
} ;

// TLorentzVector buildP (const LHEF::HEPEUP & event, int iPart) {
//  TLorentzVector dummy ;
//  dummy.SetPxPyPzE (
//    event.PUP.at (iPart).at (0), // px
//    event.PUP.at (iPart).at (1), // py
//    event.PUP.at (iPart).at (2), // pz
//    event.PUP.at (iPart).at (3) // E
//    ) ;
//  return dummy ;
// }


float SmearMET = 0.10; //---- 10% flat
float SmearJES = 0.10; //---- 1% flat


void smearVectorKeepMass (TLorentzVector& part, float smear){
 //---- smear = 0.10 ---> 10%
 float scale = -1;
 while (scale <= 0) { //---- no negative values!
  scale = gRandom->Gaus(1,smear);
 }
 part.SetXYZM(scale * part.X(), scale * part.Y(), scale * part.Z(), part.M() );
}


void smearVector (TLorentzVector& part, float smear){
 //---- smear = 0.10 ---> 10%
 float scale = -1;
 while (scale <= 0) { //---- no negative values!
  scale = gRandom->Gaus(1,smear);
 }
 part.SetPxPyPzE(scale * part.X(), scale * part.Y(), scale * part.Z(), part.E() );
}


void setMassLess (TLorentzVector& part){
 part.SetXYZM(part.X(), part.Y(), part.Z(), 0 );
}



class myParticle: public TLorentzVector {

 public:

  myParticle(): TLorentzVector() {};
  myParticle( const myParticle& other ) : TLorentzVector( other ) {
   pdgId_ = other.GetPdgId();
  };

  void SetPdgId(int pdgId) {pdgId_ = pdgId;}
  int GetPdgId() const {return pdgId_;}

 private :
  int pdgId_;
};


class myTree {

 public:

  myTree();
  ~myTree() {};

  TTree* tree;

  int njet_;

  float mjj_;
  float detajj_;

  float jetpt1_;
  float jeteta1_;
  float jetphi1_;
  float jetmass1_;

  float jetpt2_;
  float jeteta2_;
  float jetphi2_;
  float jetmass2_;

  float jetpt3_;
  float jeteta3_;
  float jetphi3_;
  float jetmass3_;

  float jetpt4_;
  float jeteta4_;
  float jetphi4_;
  float jetmass4_;

  float jetpt5_;
  float jeteta5_;
  float jetphi5_;
  float jetmass5_;

  float jetpt6_;
  float jeteta6_;
  float jetphi6_;
  float jetmass6_;


  float bjetpt1_;
  float bjeteta1_;
  float bjetphi1_;
  float bjetmass1_;

  float bjetpt2_;
  float bjeteta2_;
  float bjetphi2_;
  float bjetmass2_;

  float bjetpt3_;
  float bjeteta3_;
  float bjetphi3_;
  float bjetmass3_;

  float bjetpt4_;
  float bjeteta4_;
  float bjetphi4_;
  float bjetmass4_;

  // hbb
  float hbb_pt_;
  float hbb_phi_;
  float hbb_eta_;
  float hbb_mass_;

  float hbb_gen_pt_;
  float hbb_gen_phi_;
  float hbb_gen_eta_;
  float hbb_gen_mass_;

  // hww
  float pt1_;
  float eta1_;
  float phi1_;
  float mass1_;
  float id1_;

  float pt2_;
  float eta2_;
  float phi2_;
  float mass2_;
  float id2_;

  float met_pt_;
  float met_phi_;
  float met_eta_;

  float hww_gen_pt_;
  float hww_gen_eta_;
  float hww_gen_phi_;
  float hww_gen_mass_;

  float hww_pt_;
  float hww_phi_;
  float hww_mt_;
  float hww_eta_m_;
  float hww_eta_p_;
  float mll_;
  float ptll_;

  float m_llbb_ ;

  float xhh_m_ww_pt_ ;
  float xhh_m_ww_eta_ ;
  float xhh_m_ww_phi_ ;
  float xhh_m_ww_m_ ;
  float xhh_p_ww_pt_ ;
  float xhh_p_ww_eta_ ;
  float xhh_p_ww_phi_ ;
  float xhh_p_ww_m_ ;
  float xhh_ww_mt_ ;





  void fillTree (std::string fileNameHEPMC);
  void Write(TFile& out);
  void Init();

};


myTree::myTree(){
 tree = new TTree("tree","tree");

 //---- hbb
 tree->Branch("hbb_pt",&hbb_pt_,"hbb_pt/F");
 tree->Branch("hbb_eta",&hbb_eta_,"hbb_eta/F");
 tree->Branch("hbb_phi",&hbb_phi_,"hbb_phi/F");
 tree->Branch("hbb_mass",&hbb_mass_,"hbb_mass/F");

 tree->Branch("hbb_gen_pt",&hbb_gen_pt_,"hbb_gen_pt/F");
 tree->Branch("hbb_gen_eta",&hbb_gen_eta_,"hbb_gen_eta/F");
 tree->Branch("hbb_gen_phi",&hbb_gen_phi_,"hbb_gen_phi/F");
 tree->Branch("hbb_gen_mass",&hbb_gen_mass_,"hbb_gen_mass/F");

 //---- hww
 tree->Branch("pt1",&pt1_,"pt1/F");
 tree->Branch("eta1",&eta1_,"eta1/F");
 tree->Branch("phi1",&phi1_,"phi1/F");
 tree->Branch("mass1",&mass1_,"mass1/F");
 tree->Branch("id1",&id1_,"id1/F");

 tree->Branch("pt2",&pt2_,"pt2/F");
 tree->Branch("eta2",&eta2_,"eta2/F");
 tree->Branch("phi2",&phi2_,"phi2/F");
 tree->Branch("mass2",&mass2_,"mass2/F");
 tree->Branch("id2",&id2_,"id2/F");

 tree->Branch("met_pt",&met_pt_,"met_pt/F");
 tree->Branch("met_phi",&met_phi_,"met_phi/F");
 tree->Branch("met_eta",&met_eta_,"met_eta/F");

 tree->Branch("mll",&mll_,"mll/F");
 tree->Branch("ptll",&ptll_,"ptll/F");
 tree->Branch("m_llbb",&m_llbb_,"m_llbb/F");

 tree->Branch("hww_gen_pt",&hww_gen_pt_,"hww_gen_pt/F");
 tree->Branch("hww_gen_eta",&hww_gen_eta_,"hww_gen_eta/F");
 tree->Branch("hww_gen_phi",&hww_gen_phi_,"hww_gen_phi/F");
 tree->Branch("hww_gen_mass",&hww_gen_mass_,"hww_gen_mass/F");

 tree->Branch("hww_pt",&hww_pt_,"hww_pt/F");
 tree->Branch("hww_phi",&hww_phi_,"hww_phi/F");
 tree->Branch("hww_mt",&hww_mt_,"hww_mt/F");
 tree->Branch("hww_eta_m",&hww_eta_m_,"hww_eta_m/F");
 tree->Branch("hww_eta_p",&hww_eta_p_,"hww_eta_p/F");

 tree->Branch("xhh_m_ww_pt",&xhh_m_ww_pt_,"xhh_m_ww_pt/F");
 tree->Branch("xhh_m_ww_eta",&xhh_m_ww_eta_,"xhh_m_ww_eta/F");
 tree->Branch("xhh_m_ww_phi",&xhh_m_ww_phi_,"xhh_m_ww_phi/F");
 tree->Branch("xhh_m_ww_m",&xhh_m_ww_m_,"xhh_m_ww_m/F");

 tree->Branch("xhh_p_ww_pt",&xhh_p_ww_pt_,"xhh_p_ww_pt/F");
 tree->Branch("xhh_p_ww_eta",&xhh_p_ww_eta_,"xhh_p_ww_eta/F");
 tree->Branch("xhh_p_ww_phi",&xhh_p_ww_phi_,"xhh_p_ww_phi/F");
 tree->Branch("xhh_p_ww_m",&xhh_p_ww_m_,"xhh_p_ww_m/F");
 tree->Branch("xhh_ww_mt",&xhh_ww_mt_,"xhh_ww_mt/F");


 //---- jets
 tree->Branch("njet",&njet_,"njet/I");

 tree->Branch("mjj",&mjj_,"mjj/F");
 tree->Branch("detajj",&detajj_,"detajj/F");

 tree->Branch("jetpt1",&jetpt1_,"jetpt1/F");
 tree->Branch("jeteta1",&jeteta1_,"jeteta1/F");
 tree->Branch("jetphi1",&jetphi1_,"jetphi1/F");
 tree->Branch("jetmass1",&jetmass1_,"jetmass1/F");

 tree->Branch("jetpt2",&jetpt2_,"jetpt2/F");
 tree->Branch("jeteta2",&jeteta2_,"jeteta2/F");
 tree->Branch("jetphi2",&jetphi2_,"jetphi2/F");
 tree->Branch("jetmass2",&jetmass2_,"jetmass2/F");

 tree->Branch("jetpt3",&jetpt3_,"jetpt3/F");
 tree->Branch("jeteta3",&jeteta3_,"jeteta3/F");
 tree->Branch("jetphi3",&jetphi3_,"jetphi3/F");
 tree->Branch("jetmass3",&jetmass3_,"jetmass3/F");

 tree->Branch("jetpt4",&jetpt4_,"jetpt4/F");
 tree->Branch("jeteta4",&jeteta4_,"jeteta4/F");
 tree->Branch("jetphi4",&jetphi4_,"jetphi4/F");
 tree->Branch("jetmass4",&jetmass4_,"jetmass4/F");

 tree->Branch("jetpt5",&jetpt5_,"jetpt5/F");
 tree->Branch("jeteta5",&jeteta5_,"jeteta5/F");
 tree->Branch("jetphi5",&jetphi5_,"jetphi5/F");
 tree->Branch("jetmass5",&jetmass5_,"jetmass5/F");

 tree->Branch("jetpt6",&jetpt6_,"jetpt6/F");
 tree->Branch("jeteta6",&jeteta6_,"jeteta6/F");
 tree->Branch("jetphi6",&jetphi6_,"jetphi6/F");
 tree->Branch("jetmass6",&jetmass6_,"jetmass6/F");

 tree->Branch("bjetpt1",&bjetpt1_,"bjetpt1/F");
 tree->Branch("bjeteta1",&bjeteta1_,"bjeteta1/F");
 tree->Branch("bjetphi1",&bjetphi1_,"bjetphi1/F");
 tree->Branch("bjetmass1",&bjetmass1_,"bjetmass1/F");

 tree->Branch("bjetpt2",&bjetpt2_,"bjetpt2/F");
 tree->Branch("bjeteta2",&bjeteta2_,"bjeteta2/F");
 tree->Branch("bjetphi2",&bjetphi2_,"bjetphi2/F");
 tree->Branch("bjetmass2",&bjetmass2_,"bjetmass2/F");

 tree->Branch("bjetpt3",&bjetpt3_,"bjetpt3/F");
 tree->Branch("bjeteta3",&bjeteta3_,"bjeteta3/F");
 tree->Branch("bjetphi3",&bjetphi3_,"bjetphi3/F");
 tree->Branch("bjetmass3",&bjetmass3_,"bjetmass3/F");

 tree->Branch("bjetpt4",&bjetpt4_,"bjetpt4/F");
 tree->Branch("bjeteta4",&bjeteta4_,"bjeteta4/F");
 tree->Branch("bjetphi4",&bjetphi4_,"bjetphi4/F");
 tree->Branch("bjetmass4",&bjetmass4_,"bjetmass4/F");

}

void myTree::Init(){

 hbb_pt_ = -99;
 hbb_eta_ = -99;
 hbb_phi_ = -99;
 hbb_mass_ = -99;

 hbb_gen_pt_ = -99;
 hbb_gen_eta_ = -99;
 hbb_gen_phi_ = -99;
 hbb_gen_mass_ = -99;

 hww_gen_pt_ = -99;
 hww_gen_eta_ = -99;
 hww_gen_mass_ = -99;

 hww_pt_ = -99;
 hww_phi_ = -99;
 hww_mt_ = -99;
 hww_eta_m_ = -99;
 hww_eta_p_ = -99;
 hww_gen_phi_ = -99;

 m_llbb_ = -99;
 mll_ = -99;
 ptll_ = -99;
 met_pt_ = -99;
 met_phi_ = -99;
 met_eta_ = -99;

 pt1_ = -99;
 eta1_ = -99;
 phi1_ = -99;
 mass1_ = -99;
 id1_ = -99;

 pt2_ = -99;
 eta2_ = -99;
 phi2_ = -99;
 mass2_ = -99;
 id2_ = -99;


 xhh_m_ww_pt_ = -99 ;
 xhh_m_ww_eta_ = -99 ;
 xhh_m_ww_phi_ = -99 ;
 xhh_m_ww_m_ = -99 ;
 xhh_p_ww_pt_ = -99 ;
 xhh_p_ww_eta_ = -99 ;
 xhh_p_ww_phi_ = -99 ;
 xhh_p_ww_m_ = -99 ;
 xhh_ww_mt_ = -99 ;


 //---- jets
 mjj_ = -99;
 detajj_ = -99;

 jetpt1_ = -99;
 jeteta1_ = -99;
 jetphi1_ = -99;
 jetmass1_ = -99;

 jetpt2_ = -99;
 jeteta2_ = -99;
 jetphi2_ = -99;
 jetmass2_ = -99;

 jetpt3_ = -99;
 jeteta3_ = -99;
 jetphi3_ = -99;
 jetmass3_ = -99;

 jetpt4_ = -99;
 jeteta4_ = -99;
 jetphi4_ = -99;
 jetmass4_ = -99;

 jetpt5_ = -99;
 jeteta5_ = -99;
 jetphi5_ = -99;
 jetmass5_ = -99;

 jetpt6_ = -99;
 jeteta6_ = -99;
 jetphi6_ = -99;
 jetmass6_ = -99;

 njet_ = 0;

}


void myTree::fillTree(std::string fileNameHEPMC){
 
 /**
 std::ifstream ifs (fileNameHEPMC.c_str ()) ;
 LHEF::Reader reader (ifs) ;

 long ieve = 0 ;
 long selected = 0 ;
 double jetsNum = 0. ;

 float HiggsMass = 125.0;

 std::cout << " reading " << fileNameHEPMC << std::endl;

 // loop over events
 while ( reader.readEvent () ) {
  ieve++;
  if (ieve % 10000 == 0) std::cout << "event " << ieve << "\n" ;

  //---- initialize variables in tree
  Init();

  TLorentzVector HiggsA, HiggsB;
  int iPartHiggs = -1;

  std::vector<int> finalJets ;
  std::vector<TLorentzVector> v_tlv_all_quarks ; //---- tlv = TLorentzVector
  std::vector<TLorentzVector> v_tlv_quarks ; //---- non b-quarks
  std::vector<TLorentzVector> v_tlv_bquarks ;
  std::vector<TLorentzVector> v_tlv_leptons ;
  std::vector<TLorentzVector> v_tlv_neutrinos ;
  std::vector<myParticle> v_p_leptons ; //---- p = myParticle

  // loop over particles in the event
  // and fill the variables of leptons and quarks
  for (int iPart = 0 ; iPart < reader.hepeup.IDUP.size (); ++iPart) {

   // look for the Higgs
   if (abs (reader.hepeup.IDUP.at (iPart)) == 35) { //---- 35 into bb
    iPartHiggs = iPart;
    HiggsA.SetPxPyPzE (
      reader.hepeup.PUP.at (iPart).at (0), // px
    reader.hepeup.PUP.at (iPart).at (1), // py
    reader.hepeup.PUP.at (iPart).at (2), // pz
    reader.hepeup.PUP.at (iPart).at (3) // E
                      );
    hbb_gen_pt_ = HiggsA.Pt();
    hbb_gen_eta_ = HiggsA.Eta();
    hbb_gen_phi_ = HiggsA.Phi();
    hbb_gen_mass_ = HiggsA.M();
   }

   if (abs (reader.hepeup.IDUP.at (iPart)) == 25) { //---- 25 into WW/bb/aa
    iPartHiggs = iPart;
    HiggsB.SetPxPyPzE (
      reader.hepeup.PUP.at (iPart).at (0), // px
    reader.hepeup.PUP.at (iPart).at (1), // py
    reader.hepeup.PUP.at (iPart).at (2), // pz
    reader.hepeup.PUP.at (iPart).at (3) // E
                       );
    hww_gen_pt_ = HiggsB.Pt();
    hww_gen_eta_ = HiggsB.Eta();
    hww_gen_phi_ = HiggsB.Phi();
    hww_gen_mass_ = HiggsB.M();
   }

   // outgoing particles
   if (reader.hepeup.ISTUP.at (iPart) == 1) {
    // quarks
    if (abs (reader.hepeup.IDUP.at (iPart)) < 7) {
     finalJets.push_back (iPart) ;
     TLorentzVector dummy (
       reader.hepeup.PUP.at (iPart).at (0), // px
     reader.hepeup.PUP.at (iPart).at (1), // py
     reader.hepeup.PUP.at (iPart).at (2), // pz
     reader.hepeup.PUP.at (iPart).at (3) // E
                          ) ;

     smearVectorKeepMass(dummy,SmearJES); //---- smear jet energy scale

     if (abs (reader.hepeup.IDUP.at (iPart)) != 5) {
      //---- set massless quarks!
      setMassLess(dummy);
     }

     v_tlv_all_quarks.push_back (dummy) ;

     if (abs (reader.hepeup.IDUP.at (iPart)) == 5) {
      v_tlv_bquarks.push_back (dummy) ;
     }
     else {
      v_tlv_quarks.push_back (dummy) ;
     }

    } // quarks
    else if (abs (reader.hepeup.IDUP.at (iPart)) == 11 || abs (reader.hepeup.IDUP.at (iPart)) == 13 || abs (reader.hepeup.IDUP.at (iPart)) == 15) { // e = 11, mu = 13, tau = 15
     TLorentzVector dummy (
       reader.hepeup.PUP.at (iPart).at (0), // px
     reader.hepeup.PUP.at (iPart).at (1), // py
     reader.hepeup.PUP.at (iPart).at (2), // pz
     reader.hepeup.PUP.at (iPart).at (3) // E
                          ) ;
     v_tlv_leptons.push_back (dummy) ;

// if (reader.hepeup.IDUP.at (iPart) == 15 || reader.hepeup.IDUP.at (iPart) == -15 ) std::cout << " tau " << std::endl;
     myParticle dummyP;
     dummyP.SetPxPyPzE( reader.hepeup.PUP.at (iPart).at (0), // px
                               reader.hepeup.PUP.at (iPart).at (1), // py
                               reader.hepeup.PUP.at (iPart).at (2), // pz
                               reader.hepeup.PUP.at (iPart).at (3) // E
                       );
     dummyP.SetPdgId(reader.hepeup.IDUP.at (iPart));
     v_p_leptons.push_back (dummyP) ;
    }
    else if (abs (reader.hepeup.IDUP.at (iPart)) == 12 || abs (reader.hepeup.IDUP.at (iPart)) == 14 || abs (reader.hepeup.IDUP.at (iPart)) == 16) { // ve = 12, vmu = 14, vtau = 16
     TLorentzVector dummy
       (
       reader.hepeup.PUP.at (iPart).at (0), // px
     reader.hepeup.PUP.at (iPart).at (1), // py
     reader.hepeup.PUP.at (iPart).at (2), // pz
     reader.hepeup.PUP.at (iPart).at (3) // E
       ) ;
     v_tlv_neutrinos.push_back (dummy) ;
    }
   } // outgoing particles
  } // loop over particles in the event

  // sorting in pt
  sort (v_tlv_all_quarks.rbegin (), v_tlv_all_quarks.rend (), ptsort ()) ;
  sort (v_tlv_quarks.rbegin (), v_tlv_quarks.rend (), ptsort ()) ;
  sort (v_tlv_leptons.rbegin (), v_tlv_leptons.rend (), ptsort ()) ;
  sort (v_p_leptons.rbegin (), v_p_leptons.rend (), ptsort ()) ;

// TLorentzVector diLepton = v_tlv_leptons.at (0) + v_tlv_leptons.at (1) ;
// TLorentzVector dilepton_plus_dineutrinos = v_tlv_leptons.at (0) + v_tlv_leptons.at (1) + v_tlv_neutrinos.at (0) + v_tlv_neutrinos.at (1) ;


  //---- fill the ntuple

  if (v_tlv_quarks.size()>0) {
   jetpt1_ = v_tlv_quarks.at (0).Pt ();
   jeteta1_ = v_tlv_quarks.at (0).Eta ();
   jetphi1_ = v_tlv_quarks.at (0).Phi ();
   jetmass1_ = v_tlv_quarks.at (0).M ();
  }
  if (v_tlv_quarks.size()>1) {
   jetpt2_ = v_tlv_quarks.at (1).Pt ();
   jeteta2_ = v_tlv_quarks.at (1).Eta ();
   jetphi2_ = v_tlv_quarks.at (1).Phi ();
   jetmass2_ = v_tlv_quarks.at (1).M ();

   mjj_ = (v_tlv_quarks.at (0) + v_tlv_quarks.at (1) ).M();
   detajj_ = fabs (v_tlv_quarks.at (0).Eta() - v_tlv_quarks.at (1).Eta() );
  }

  if (v_tlv_quarks.size()>2) {
   jetpt3_ = v_tlv_quarks.at (2).Pt ();
   jeteta3_ = v_tlv_quarks.at (2).Eta ();
   jetphi3_ = v_tlv_quarks.at (2).Phi ();
   jetmass3_ = v_tlv_quarks.at (2).M ();
  }

  if (v_tlv_quarks.size()>3) {
   jetpt4_ = v_tlv_quarks.at (3).Pt ();
   jeteta4_ = v_tlv_quarks.at (3).Eta ();
   jetphi4_ = v_tlv_quarks.at (3).Phi ();
   jetmass4_ = v_tlv_quarks.at (3).M ();
  }

  if (v_tlv_quarks.size()>4) {
   jetpt5_ = v_tlv_quarks.at (4).Pt ();
   jeteta5_ = v_tlv_quarks.at (4).Eta ();
   jetphi5_ = v_tlv_quarks.at (4).Phi ();
   jetmass5_ = v_tlv_quarks.at (4).M ();
  }

  if (v_tlv_quarks.size()>5) {
   jetpt6_ = v_tlv_quarks.at (5).Pt ();
   jeteta6_ = v_tlv_quarks.at (5).Eta ();
   jetphi6_ = v_tlv_quarks.at (5).Phi ();
   jetmass6_ = v_tlv_quarks.at (5).M ();
  }

  if (v_tlv_bquarks.size()>0) {
   bjetpt1_ = v_tlv_bquarks.at (0).Pt ();
   bjeteta1_ = v_tlv_bquarks.at (0).Eta ();
   bjetphi1_ = v_tlv_bquarks.at (0).Phi ();
   bjetmass1_ = v_tlv_bquarks.at (0).M ();
  }
  if (v_tlv_bquarks.size()>1) {
   bjetpt2_ = v_tlv_bquarks.at (1).Pt ();
   bjeteta2_ = v_tlv_bquarks.at (1).Eta ();
   bjetphi2_ = v_tlv_bquarks.at (1).Phi ();
   bjetmass2_ = v_tlv_bquarks.at (1).M ();
  }

  if (v_tlv_bquarks.size()>2) {
   bjetpt3_ = v_tlv_bquarks.at (2).Pt ();
   bjeteta3_ = v_tlv_bquarks.at (2).Eta ();
   bjetphi3_ = v_tlv_bquarks.at (2).Phi ();
   bjetmass3_ = v_tlv_bquarks.at (2).M ();
  }

  if (v_tlv_bquarks.size()>3) {
   bjetpt4_ = v_tlv_bquarks.at (3).Pt ();
   bjeteta4_ = v_tlv_bquarks.at (3).Eta ();
   bjetphi4_ = v_tlv_bquarks.at (3).Phi ();
   bjetmass4_ = v_tlv_bquarks.at (3).M ();
  }

  for (unsigned int iq = 0; iq < v_tlv_quarks.size(); iq++){
   if (v_tlv_quarks.at(iq).Pt () > 30) njet_++;
  }

  TLorentzVector hbb;
// std::cout << "v_tlv_bquarks.size() = " << v_tlv_bquarks.size() << std::endl;
  if (v_tlv_bquarks.size()>1) {
   hbb = v_tlv_bquarks.at (0) + v_tlv_bquarks.at (1);
   hbb_pt_ = hbb.Pt();
   hbb_eta_ = hbb.Eta();
   hbb_phi_ = hbb.Phi();
   hbb_mass_ = hbb.M();
  }


  //---- hww
  if (v_p_leptons.size()>0) {
   pt1_ = v_p_leptons.at (0).Pt ();
   eta1_ = v_p_leptons.at (0).Eta ();
   phi1_ = v_p_leptons.at (0).Phi ();
   mass1_ = v_p_leptons.at (0).M ();
   id1_ = v_p_leptons.at (0).GetPdgId ();
  }
  if (v_p_leptons.size()>1) {
   pt2_ = v_p_leptons.at (1).Pt ();
   eta2_ = v_p_leptons.at (1).Eta ();
   phi2_ = v_p_leptons.at (1).Phi ();
   mass2_ = v_p_leptons.at (1).M ();
   id2_ = v_p_leptons.at (1).GetPdgId ();

   mll_ = (v_p_leptons.at (0) + v_p_leptons.at (1)).M();
   ptll_ = (v_p_leptons.at (0) + v_p_leptons.at (1)).Pt();
  }

  TLorentzVector missingEnergy;
  for (unsigned int iv = 0; iv < v_tlv_neutrinos.size(); iv++){
   missingEnergy = missingEnergy + v_tlv_neutrinos.at(iv);
  }

  smearVector(missingEnergy,SmearMET); //---- smear MET

  met_pt_ = missingEnergy.Pt();
  met_phi_ = missingEnergy.Phi();
  met_eta_ = missingEnergy.Eta();

  if (v_p_leptons.size()>1) {
    //--- IMPORTANT: h>ww, mll ~ mvv, otherwise something missing in higgs kinematic reconstruction
   missingEnergy.SetPtEtaPhiM(met_pt_, 0, met_phi_, mll_);

   TLorentzVector hww;
   TLorentzVector hwwp;
   TLorentzVector hwwm;

   hww = missingEnergy + v_p_leptons.at (0) + v_p_leptons.at (1) ;
   hww_pt_ = hww.Pt();
   hww_phi_ = hww.Phi();

   //--- transverse mass
   hww_mt_ = sqrt((v_p_leptons.at (0).Pt() + v_p_leptons.at (1).Pt() + missingEnergy.Pt())*(v_p_leptons.at (0).Pt() + v_p_leptons.at (1).Pt() + missingEnergy.Pt()) - hww_pt_ * hww_pt_);

   //---- kinematic fit for eta
   float sintheta2 = (hww_pt_*hww_pt_ / (hww.E() * hww.E() - HiggsMass*HiggsMass ));
   float sintheta;
   if (sintheta2 > 1) sintheta2 = 1; //---- how it may be > 1, you never know ... but if it happens, then put the Higgs in the transverse plane! --> sin = 1
   if (sintheta2 > 0) sintheta = sqrt (sintheta2);
   if (sintheta2 > 0) {
    hww_eta_p_ = - log (tan ( asin ( sintheta ) / 2. )) ;
    hww_eta_m_ = + log (tan ( asin ( sintheta ) / 2. )) ;
    hwwp.SetPtEtaPhiM(hww_pt_, hww_eta_p_, hww_phi_, HiggsMass);
    hwwm.SetPtEtaPhiM(hww_pt_, hww_eta_m_, hww_phi_, HiggsMass);
   }
   else {
    //---- if I cannot solve, put the Higgs in the transverse plane
    hww_eta_p_ = 0.;
    hww_eta_m_ = 0.;
    hwwp.SetPtEtaPhiM(hww_pt_, hww_eta_p_, hww_phi_, HiggsMass);
    hwwm.SetPtEtaPhiM(hww_pt_, hww_eta_m_, hww_phi_, HiggsMass);
   }

   TLorentzVector xhh;
   xhh = hww + hbb;

   TLorentzVector xhh_p;
   TLorentzVector xhh_m;
   xhh_p = hwwm + hbb;
   xhh_m = hwwp + hbb;

// std::cout << " xhh_m.Eta() = " << xhh_m.Eta();
// std::cout << " xhh_p.Eta() = " << xhh_p.Eta();
// std::cout << " hww_pt_ = " << hww_pt_;
// std::cout << " hbb_pt_ = " << hbb_pt_;
// std::cout << std::endl;
// std::cout << " - log (tan ( asin ( sintheta ) / 2. )) = " << sintheta << " :: " << asin ( sintheta ) << " :: " << tan ( asin ( sintheta ) / 2. );
// std::cout << std::endl;
//
// std::cout << " hww_eta_p_ = " << hww_eta_p_;
// std::cout << " hww_eta_m_ = " << hww_eta_m_;
// std::cout << " hww_phi_ = " << hww_phi_;
// std::cout << " hbb_phi_ = " << hbb_phi_;
// std::cout << std::endl;

   xhh_m_ww_pt_ = xhh_m.Pt();
   xhh_m_ww_eta_ = xhh_m.Eta();
   xhh_m_ww_phi_ = xhh_m.Phi();
   xhh_m_ww_m_ = xhh_m.M();

   xhh_p_ww_pt_ = xhh_p.Pt();
   xhh_p_ww_eta_ = xhh_p.Eta();
   xhh_p_ww_phi_ = xhh_p.Phi();
   xhh_p_ww_m_ = xhh_p.M();

   //--- transverse mass
   if (v_tlv_bquarks.size()>1) {

   m_llbb_ = (v_tlv_bquarks.at (0) + v_tlv_bquarks.at (1) + v_p_leptons.at (0) + v_p_leptons.at (1) ) .M();
   xhh_ww_mt_ = sqrt(
     (v_p_leptons.at (0).Pt() + v_p_leptons.at (1).Pt() + missingEnergy.Pt() + v_tlv_bquarks.at (0).Pt() + v_tlv_bquarks.at (1).Pt())*
     (v_p_leptons.at (0).Pt() + v_p_leptons.at (1).Pt() + missingEnergy.Pt() + v_tlv_bquarks.at (0).Pt() + v_tlv_bquarks.at (1).Pt()) - xhh.Pt()*xhh.Pt());
   }
  }

  tree->Fill();
 }
 **/
 
}


void myTree::Write(TFile& out){
 out.cd();
 tree->Write();
}


int main (int argc, char **argv) {
 // Open a stream connected to an event file:
 if (argc < 3) exit (1) ;

 std::cout << " Input LHE = " << argv[1] << std::endl;
 std::cout << " Output ROOT = " << argv[2] << std::endl;

 myTree myT;
 myT.fillTree (std::string(argv[1])) ;

 TFile output (argv[2], "recreate") ;
 output.cd() ;
 myT.Write(output);
 output.Close();

}



