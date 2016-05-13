#include "TMVA/Factory.h"
#include "TFile.h"
#include "TTree.h"

using namespace TMVA;
using namespace TMath;

void trainPileupJetID(TString ETA);
void trainPileupJetIDAll();

void trainPileupJetIDAll()
{
  trainPileupJetID("Eta0to2p5");
  trainPileupJetID("Eta2p5to2p75");
  trainPileupJetID("Eta2p75to3");
  trainPileupJetID("Eta3to5"); 
}

void trainPileupJetID(TString ETA)
{
  TFile *inf = TFile::Open("pileupJetId_Train.root");
  TTree *sigTree = (TTree*)inf->Get("jetsMatched"+ETA); 
  TTree *bkgTree = (TTree*)inf->Get("jetsUnMatched"+ETA); 
  
  TFile *outf = new TFile("pileupJetId_DY_mva_"+ETA+".root","RECREATE");
  TMVA::Factory* factory = new TMVA::Factory("pileupJetId_DY_"+ETA,outf,"!V:!Silent:Color:DrawProgressBar:Transformations=I;G:AnalysisType=Classification");
  factory->AddSignalTree(sigTree);
  factory->AddBackgroundTree(bkgTree);
  
  int N_SIG(sigTree->GetEntries());
  int N_BKG(bkgTree->GetEntries());
  int N = TMath::Min(TMath::Min(N_SIG,N_BKG),200000);

  cout<<N_SIG<<" "<<N_BKG<<endl;
  
  const int NVARC = 15;
  TString VARC[NVARC] = {
    "nvtx",
    "dR2Mean",
    "nParticles",
    "nCharged",
    "majW",
    "minW",
    "frac01",
    "frac02",
    "frac03",
    "frac04",
    "ptD",
    "beta",
    "pull",
    "jetR",
    "jetRchg"
  };
  char TYPEC[NVARC] = {'I','F','I','I','F','F','F','F','F','F','F','F','F','F','F'};

  const int NVARF = 12;
  TString VARF[NVARF] = {
    "nvtx",
    "dR2Mean",
    "nParticles",
    "majW",
    "minW",
    "frac01",
    "frac02",
    "frac03",
    "frac04",
    "ptD",
    "pull",
    "jetR"
  };
  char TYPEF[NVARC] = {'I','F','I','F','F','F','F','F','F','F','F','F'};

  if (ETA == "Eta3to5") {
    for(int i=0;i<NVARF;i++) {
      factory->AddVariable(VARF[i],TYPEF[i]);
    }
  }
  else {
    for(int i=0;i<NVARC;i++) {
      factory->AddVariable(VARC[i],TYPEC[i]);
    }
  }
  
  factory->AddSpectator("jetPt",'F');
  factory->AddSpectator("jetEta",'F');

  char name[1000];
  sprintf(name,"nTrain_Signal=%d:nTrain_Background=%d:nTest_Signal=%d:nTest_Background=%d",N/2,N/2,N/2,N/2);
  factory->PrepareTrainingAndTestTree("",name);

  factory->BookMethod(TMVA::Types::kBDT,"BDT","NTrees=500:BoostType=Grad:Shrinkage=0.1:DoBoostMonitor=True");
  
  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods(); 
  outf->Close();
}
