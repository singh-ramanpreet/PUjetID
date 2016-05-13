//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Feb 22 08:36:28 2016 by ROOT version 6.02/13
// from TTree events/events
// found on file: flatTree_QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8_0.root
//////////////////////////////////////////////////////////

#ifndef events_h
#define events_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TDirectory.h>
// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"

class events {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxrun = 1;
   const Int_t kMaxevt = 1;
   const Int_t kMaxlumi = 1;
   const Int_t kMaxnVtx = 1;
   const Int_t kMaxpvRho = 1;
   const Int_t kMaxpvz = 1;
   const Int_t kMaxpvchi2 = 1;
   const Int_t kMaxpvndof = 1;
   const Int_t kMaxrho = 1;
   const Int_t kMaxmet = 1;
   const Int_t kMaxsumet = 1;
   const Int_t kMaxnJets = 1;
   const Int_t kMaxnLeptons = 1;
   const Int_t kMaxnpu = 1;
   const Int_t kMaxgenEvtWeight = 1;

   // Declaration of leaf types
   Int_t           runNo;
   Int_t           evtNo;
   Int_t           lumi;
   Int_t           npv;
   Int_t           nJets; 
   Int_t           nLeptons; 
   Float_t         pvRho;
   Float_t         pvz;
   Float_t         pvchi2;
   Float_t         pvndof;
   Float_t         rho;
   Float_t         met;
   Float_t         sumet;
   Float_t         llMass;
   vector<int>     *lId;
   vector<float>   *lPt;
   vector<float>   *lEta;
   vector<float>   *lPhi;
   vector<float>   *lE;
   vector<float>   *lIso;
   vector<float>   *jetPt;
   vector<float>   *btag;
   vector<float>   *jetEta;
   vector<float>   *phi;
   vector<float>   *mass;
   vector<float>   *energy;
   vector<float>   *chf;
   vector<float>   *nhf;
   vector<float>   *phf;
   vector<float>   *muf;
   vector<float>   *elf;
   vector<float>   *HFHadf;
   vector<float>   *HFEmf;
   vector<float>   *dR2Mean;
   vector<float>   *majW;
   vector<float>   *minW;
   vector<float>   *frac01;
   vector<float>   *frac02;
   vector<float>   *frac03;
   vector<float>   *frac04;
   vector<float>   *ptD;
   vector<float>   *beta;
   vector<float>   *betaStar;
   vector<float>   *pull;
   vector<float>   *jetR;
   vector<float>   *jetRchg;
   vector<float>   *pumva;
   vector<int>     *nParticles;
   vector<int>     *nCharged;
   vector<int>     *npr;
   vector<int>     *chm;
   vector<int>     *nhm;
   vector<int>     *phm;
   vector<int>     *mum;
   vector<int>     *elm;
   vector<int>     *HFHadm;
   vector<int>     *HFEmm;
   vector<bool>    *triggerBit;
   vector<int>     *triggerPre;
   vector<bool>    *metFilterBit;
   vector<float>   *dRMatch;
   vector<float>   *jetGenPt;
   vector<int>     *jetFlavorParton;
   vector<int>     *jetFlavorHadron;
   Int_t           nTrueInt;
   Float_t         genEvtWeight;

   // List of branches
   TBranch        *b_nLeptons_;
   TBranch        *b_nJets_;
   TBranch        *b_llMass_;
   TBranch        *b_lId_;
   TBranch        *b_lPt_;
   TBranch        *b_lEta_;
   TBranch        *b_lPhi_;
   TBranch        *b_lE_;
   TBranch        *b_lIso_;
   TBranch        *b_run_;   //!
   TBranch        *b_evt_;   //!
   TBranch        *b_lumi_;   //!
   TBranch        *b_nVtx_;   //!
   TBranch        *b_pvRho_;   //!
   TBranch        *b_pvz_;   //!
   TBranch        *b_pvchi2_;   //!
   TBranch        *b_pvndof_;   //!
   TBranch        *b_rho_;   //!
   TBranch        *b_met_;   //!
   TBranch        *b_sumet_;   //!
   TBranch        *b_jetPt;   //!
   TBranch        *b_btag;   //!
   TBranch        *b_jetEta;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_mass;   //!
   TBranch        *b_energy;   //!
   TBranch        *b_chf;   //!
   TBranch        *b_nhf;   //!
   TBranch        *b_phf;   //!
   TBranch        *b_muf;   //!
   TBranch        *b_elf;   //!
   TBranch        *b_HFHadf;   //!
   TBranch        *b_HFEmf;   //!
   TBranch        *b_dR2Mean;   //!
   TBranch        *b_majW;   //!
   TBranch        *b_minW;   //!
   TBranch        *b_frac01;   //!
   TBranch        *b_frac02;   //!
   TBranch        *b_frac03;   //!
   TBranch        *b_frac04;   //!
   TBranch        *b_ptD;   //!
   TBranch        *b_beta;   //!
   TBranch        *b_betaStar;   //!
   TBranch        *b_pull;   //!
   TBranch        *b_jetR;   //!
   TBranch        *b_jetRchg;   //!
   TBranch        *b_pumva;   //!
   TBranch        *b_nParticles;   //!
   TBranch        *b_nCharged;   //!
   TBranch        *b_npr;   //!
   TBranch        *b_chm;   //!
   TBranch        *b_nhm;   //!
   TBranch        *b_phm;   //!
   TBranch        *b_mum;   //!
   TBranch        *b_elm;   //!
   TBranch        *b_HFHadm;   //!
   TBranch        *b_HFEmm;   //!
   TBranch        *b_triggerBit;   //!
   TBranch        *b_triggerPre;   //!
   TBranch        *b_metFilterBit;   //!
   TBranch        *b_dRMatch;   //!
   TBranch        *b_jetGenPt;   //!
   TBranch        *b_jetFlavorParton;   //!
   TBranch        *b_jetFlavorHadron;   //!
   TBranch        *b_npu_;   //!
   TBranch        *b_genEvtWeight_;   //!

   events(TTree *tree=0);
   virtual ~events();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TDirectory *DIR,bool isMC);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef events_cxx
events::events(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("flatTree_QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8_0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("flatTree_QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8_0.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("flatTree_QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8_0.root:/jetmet");
      dir->GetObject("events",tree);

   }
   Init(tree);
}

events::~events()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t events::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t events::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void events::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   lId = 0;
   lPt = 0;
   lEta = 0;
   lPhi = 0;
   lE = 0;
   lIso = 0;
   jetPt = 0;
   btag = 0;
   jetEta = 0;
   phi = 0;
   mass = 0;
   energy = 0;
   chf = 0;
   nhf = 0;
   phf = 0;
   muf = 0;
   elf = 0;
   HFHadf = 0;
   HFEmf = 0;
   dR2Mean = 0;
   majW = 0;
   minW = 0;
   frac01 = 0;
   frac02 = 0;
   frac03 = 0;
   frac04 = 0;
   ptD = 0;
   beta = 0;
   betaStar = 0;
   pull = 0;
   jetR = 0;
   jetRchg = 0;
   pumva = 0;
   nParticles = 0;
   nCharged = 0;
   npr = 0;
   chm = 0;
   nhm = 0;
   phm = 0;
   mum = 0;
   elm = 0;
   HFHadm = 0;
   HFEmm = 0;
   triggerBit = 0;
   triggerPre = 0;
   metFilterBit = 0;
   dRMatch = 0;
   jetGenPt = 0;
   jetFlavorParton = 0;
   jetFlavorHadron = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nLeptons", &nLeptons, &b_nLeptons_);
   fChain->SetBranchAddress("nJets", &nJets, &b_nJets_);
   fChain->SetBranchAddress("llMass", &llMass, &b_llMass_);
   fChain->SetBranchAddress("lepId", &lId, &b_lId_);
   fChain->SetBranchAddress("lepPt", &lPt, &b_lPt_);
   fChain->SetBranchAddress("lepEta", &lEta, &b_lEta_);
   fChain->SetBranchAddress("lepPhi", &lPhi, &b_lPhi_);
   fChain->SetBranchAddress("lepEnergy", &lE, &b_lE_);
   fChain->SetBranchAddress("lepIso", &lIso, &b_lIso_);
   fChain->SetBranchAddress("runNo", &runNo, &b_run_);
   fChain->SetBranchAddress("evtNo", &evtNo, &b_evt_);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi_);
   fChain->SetBranchAddress("npv", &npv, &b_nVtx_);
   fChain->SetBranchAddress("pvRho", &pvRho, &b_pvRho_);
   fChain->SetBranchAddress("pvz", &pvz, &b_pvz_);
   fChain->SetBranchAddress("pvchi2", &pvchi2, &b_pvchi2_);
   fChain->SetBranchAddress("pvndof", &pvndof, &b_pvndof_);
   fChain->SetBranchAddress("rho", &rho, &b_rho_);
   fChain->SetBranchAddress("met", &met, &b_met_);
   fChain->SetBranchAddress("sumet", &sumet, &b_sumet_);
   fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
   fChain->SetBranchAddress("btag", &btag, &b_btag);
   fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
   fChain->SetBranchAddress("phi", &phi, &b_phi);
   fChain->SetBranchAddress("mass", &mass, &b_mass);
   fChain->SetBranchAddress("energy", &energy, &b_energy);
   fChain->SetBranchAddress("chf", &chf, &b_chf);
   fChain->SetBranchAddress("nhf", &nhf, &b_nhf);
   fChain->SetBranchAddress("phf", &phf, &b_phf);
   fChain->SetBranchAddress("muf", &muf, &b_muf);
   fChain->SetBranchAddress("elf", &elf, &b_elf);
   fChain->SetBranchAddress("HFHadf", &HFHadf, &b_HFHadf);
   fChain->SetBranchAddress("HFEmf", &HFEmf, &b_HFEmf);
   fChain->SetBranchAddress("dR2Mean", &dR2Mean, &b_dR2Mean);
   fChain->SetBranchAddress("majW", &majW, &b_majW);
   fChain->SetBranchAddress("minW", &minW, &b_minW);
   fChain->SetBranchAddress("frac01", &frac01, &b_frac01);
   fChain->SetBranchAddress("frac02", &frac02, &b_frac02);
   fChain->SetBranchAddress("frac03", &frac03, &b_frac03);
   fChain->SetBranchAddress("frac04", &frac04, &b_frac04);
   fChain->SetBranchAddress("ptD", &ptD, &b_ptD);
   fChain->SetBranchAddress("beta", &beta, &b_beta);
   fChain->SetBranchAddress("betaStar", &betaStar, &b_betaStar);
   fChain->SetBranchAddress("pull", &pull, &b_pull);
   fChain->SetBranchAddress("jetR", &jetR, &b_jetR);
   fChain->SetBranchAddress("jetRchg", &jetRchg, &b_jetRchg);
   fChain->SetBranchAddress("pumva", &pumva, &b_pumva);
   fChain->SetBranchAddress("nParticles", &nParticles, &b_nParticles);
   fChain->SetBranchAddress("nCharged", &nCharged, &b_nCharged);
   fChain->SetBranchAddress("npr", &npr, &b_npr);
   fChain->SetBranchAddress("chm", &chm, &b_chm);
   fChain->SetBranchAddress("nhm", &nhm, &b_nhm);
   fChain->SetBranchAddress("phm", &phm, &b_phm);
   fChain->SetBranchAddress("mum", &mum, &b_mum);
   fChain->SetBranchAddress("elm", &elm, &b_elm);
   fChain->SetBranchAddress("HFHadm", &HFHadm, &b_HFHadm);
   fChain->SetBranchAddress("HFEmm", &HFEmm, &b_HFEmm);
   fChain->SetBranchAddress("triggerBit", &triggerBit, &b_triggerBit);
   fChain->SetBranchAddress("triggerPre", &triggerPre, &b_triggerPre);
   fChain->SetBranchAddress("metFilterBit", &metFilterBit, &b_metFilterBit);
   fChain->SetBranchAddress("dRMatch", &dRMatch, &b_dRMatch);
   fChain->SetBranchAddress("jetGenPt", &jetGenPt, &b_jetGenPt);
   fChain->SetBranchAddress("jetFlavorParton", &jetFlavorParton, &b_jetFlavorParton);
   fChain->SetBranchAddress("jetFlavorHadron", &jetFlavorHadron, &b_jetFlavorHadron);
   fChain->SetBranchAddress("nTrueInt", &nTrueInt, &b_npu_);
   fChain->SetBranchAddress("genEvtWeight", &genEvtWeight, &b_genEvtWeight_);
   Notify();
}

Bool_t events::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void events::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t events::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef events_cxx
