#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
using std::cin;
using std::cout;
using std::endl;

void CreateTreeForPileupJetIdTraining()
{
  TFile *inf    = TFile::Open("flatTree_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_0.root");
  TTree *trIN   = (TTree*)inf->Get("jetmet/events");
  TFile *outf   = TFile::Open("pileupJetId_Train.root","RECREATE");
  TTree *trOUT1 = new TTree("jetsMatchedEta0to2p5","jetsMatchedEta0to2p5");
  TTree *trOUT2 = new TTree("jetsUnMatchedEta0to2p5","jetsUnMatchedEta0to2p5");
  TTree *trOUT3 = new TTree("jetsMatchedEta2p5to2p75","jetsMatchedEta2p5to2p75");
  TTree *trOUT4 = new TTree("jetsUnMatchedEta2p5to2p75","jetsUnMatchedEta2p5to2p75");
  TTree *trOUT5 = new TTree("jetsMatchedEta2p75to3","jetsMatchedEta2p75to3");
  TTree *trOUT6 = new TTree("jetsUnMatchedEta2p75to3","jetsUnMatchedEta2p75to3");
  TTree *trOUT7 = new TTree("jetsMatchedEta3to5","jetsMatchedEta3to5");
  TTree *trOUT8 = new TTree("jetsUnMatchedEta3to5","jetsUnMatchedEta3to5");

  int nVtx,npu,nLeptons;
  float rho,llMass;
  vector<int>   *flavorParton(0),*nParticles(0),*nCharged(0);
  vector<float> *pt(0),*eta(0),*genDR(0),*genPt(0);
  vector<float> *dR2Mean(0),*majW(0),*minW(0),*frac01(0),*frac02(0),*frac03(0),*frac04(0),*ptD(0),
                *beta(0),*betaStar(0),*pull(0),*jetR(0),*jetRchg(0);
 
  int nVtx_,npu_,flavorParton_,nParticles_,nCharged_;
  float rho_,pt_,eta_,genDR_,genPt_,beta_,betaStar_,pull_,jetR_,jetRchg_;
  float dR2Mean_,majW_,minW_,frac01_,frac02_,frac03_,frac04_,ptD_;
                
  //------- input tree --------------
  trIN->SetBranchAddress("npv"            ,&nVtx);
  trIN->SetBranchAddress("rho"            ,&rho);
  trIN->SetBranchAddress("jetPt"          ,&pt);
  trIN->SetBranchAddress("jetEta"         ,&eta);
  trIN->SetBranchAddress("dR2Mean"        ,&dR2Mean);
  trIN->SetBranchAddress("majW"           ,&majW);
  trIN->SetBranchAddress("minW"           ,&minW);
  trIN->SetBranchAddress("frac01"         ,&frac01);
  trIN->SetBranchAddress("frac02"         ,&frac02);
  trIN->SetBranchAddress("frac03"         ,&frac03);
  trIN->SetBranchAddress("frac04"         ,&frac04);
  trIN->SetBranchAddress("ptD"            ,&ptD);
  trIN->SetBranchAddress("beta"           ,&beta);
  trIN->SetBranchAddress("betaStar"       ,&betaStar);
  trIN->SetBranchAddress("pull"           ,&pull);
  trIN->SetBranchAddress("jetR"           ,&jetR);
  trIN->SetBranchAddress("jetRchg"        ,&jetRchg);
  trIN->SetBranchAddress("nParticles"     ,&nParticles);
  trIN->SetBranchAddress("nCharged"       ,&nCharged);
  trIN->SetBranchAddress("dRMatch"        ,&genDR);
  trIN->SetBranchAddress("jetGenPt"       ,&genPt);
  trIN->SetBranchAddress("jetFlavorParton",&flavorParton);
  trIN->SetBranchAddress("nTrueInt"       ,&npu);  
  trIN->SetBranchAddress("nLeptons"       ,&nLeptons);
  trIN->SetBranchAddress("llMass"         ,&llMass);

  //------- output trees --------------
  trOUT1->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
  trOUT1->Branch("rho"               ,&rho_         ,"rho_/F");
  trOUT1->Branch("jetPt"             ,&pt_          ,"pt_/F");
  trOUT1->Branch("jetEta"            ,&eta_         ,"eta_/F");
  trOUT1->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
  trOUT1->Branch("majW"              ,&majW_        ,"majW_/F");
  trOUT1->Branch("minW"              ,&minW_        ,"minW_/F");
  trOUT1->Branch("frac01"            ,&frac01_      ,"frac01_/F");
  trOUT1->Branch("frac02"            ,&frac02_      ,"frac01_/F");
  trOUT1->Branch("frac03"            ,&frac03_      ,"frac01_/F");
  trOUT1->Branch("frac04"            ,&frac04_      ,"frac01_/F");
  trOUT1->Branch("ptD"               ,&ptD_         ,"ptD_/F");
  trOUT1->Branch("beta"              ,&beta_        ,"beta_/F");
  trOUT1->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
  trOUT1->Branch("pull"              ,&pull_        ,"pull_/F");
  trOUT1->Branch("jetR"              ,&jetR_        ,"jetR_/F");
  trOUT1->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
  trOUT1->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
  trOUT1->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
  trOUT1->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
  trOUT1->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
  trOUT1->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
  trOUT1->Branch("nTrueInt"          ,&npu_         ,"npu_/I");
  
  trOUT2->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
  trOUT2->Branch("rho"               ,&rho_         ,"rho_/F");
  trOUT2->Branch("jetPt"             ,&pt_          ,"pt_/F");
  trOUT2->Branch("jetEta"            ,&eta_         ,"eta_/F");
  trOUT2->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
  trOUT2->Branch("majW"              ,&majW_        ,"majW_/F");
  trOUT2->Branch("minW"              ,&minW_        ,"minW_/F");
  trOUT2->Branch("frac01"            ,&frac01_      ,"frac01_/F");
  trOUT2->Branch("frac02"            ,&frac02_      ,"frac01_/F");
  trOUT2->Branch("frac03"            ,&frac03_      ,"frac01_/F");
  trOUT2->Branch("frac04"            ,&frac04_      ,"frac01_/F");
  trOUT2->Branch("ptD"               ,&ptD_         ,"ptD_/F");
  trOUT2->Branch("beta"              ,&beta_        ,"beta_/F");
  trOUT2->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
  trOUT2->Branch("pull"              ,&pull_        ,"pull_/F");
  trOUT2->Branch("jetR"              ,&jetR_        ,"jetR_/F");
  trOUT2->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
  trOUT2->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
  trOUT2->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
  trOUT2->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
  trOUT2->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
  trOUT2->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
  trOUT2->Branch("nTrueInt"          ,&npu_         ,"npu_/I");

  trOUT3->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
  trOUT3->Branch("rho"               ,&rho_         ,"rho_/F");
  trOUT3->Branch("jetPt"             ,&pt_          ,"pt_/F");
  trOUT3->Branch("jetEta"            ,&eta_         ,"eta_/F");
  trOUT3->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
  trOUT3->Branch("majW"              ,&majW_        ,"majW_/F");
  trOUT3->Branch("minW"              ,&minW_        ,"minW_/F");
  trOUT3->Branch("frac01"            ,&frac01_      ,"frac01_/F");
  trOUT3->Branch("frac02"            ,&frac02_      ,"frac01_/F");
  trOUT3->Branch("frac03"            ,&frac03_      ,"frac01_/F");
  trOUT3->Branch("frac04"            ,&frac04_      ,"frac01_/F");
  trOUT3->Branch("ptD"               ,&ptD_         ,"ptD_/F");
  trOUT3->Branch("beta"              ,&beta_        ,"beta_/F");
  trOUT3->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
  trOUT3->Branch("pull"              ,&pull_        ,"pull_/F");
  trOUT3->Branch("jetR"              ,&jetR_        ,"jetR_/F");
  trOUT3->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
  trOUT3->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
  trOUT3->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
  trOUT3->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
  trOUT3->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
  trOUT3->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
  trOUT3->Branch("nTrueInt"          ,&npu_         ,"npu_/I");

  trOUT4->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
  trOUT4->Branch("rho"               ,&rho_         ,"rho_/F");
  trOUT4->Branch("jetPt"             ,&pt_          ,"pt_/F");
  trOUT4->Branch("jetEta"            ,&eta_         ,"eta_/F");
  trOUT4->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
  trOUT4->Branch("majW"              ,&majW_        ,"majW_/F");
  trOUT4->Branch("minW"              ,&minW_        ,"minW_/F");
  trOUT4->Branch("frac01"            ,&frac01_      ,"frac01_/F");
  trOUT4->Branch("frac02"            ,&frac02_      ,"frac01_/F");
  trOUT4->Branch("frac03"            ,&frac03_      ,"frac01_/F");
  trOUT4->Branch("frac04"            ,&frac04_      ,"frac01_/F");
  trOUT4->Branch("ptD"               ,&ptD_         ,"ptD_/F");
  trOUT4->Branch("beta"              ,&beta_        ,"beta_/F");
  trOUT4->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
  trOUT4->Branch("pull"              ,&pull_        ,"pull_/F");
  trOUT4->Branch("jetR"              ,&jetR_        ,"jetR_/F");
  trOUT4->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
  trOUT4->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
  trOUT4->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
  trOUT4->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
  trOUT4->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
  trOUT4->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
  trOUT4->Branch("nTrueInt"          ,&npu_         ,"npu_/I"); 
 
  trOUT5->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
  trOUT5->Branch("rho"               ,&rho_         ,"rho_/F");
  trOUT5->Branch("jetPt"             ,&pt_          ,"pt_/F");
  trOUT5->Branch("jetEta"            ,&eta_         ,"eta_/F");
  trOUT5->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
  trOUT5->Branch("majW"              ,&majW_        ,"majW_/F");
  trOUT5->Branch("minW"              ,&minW_        ,"minW_/F");
  trOUT5->Branch("frac01"            ,&frac01_      ,"frac01_/F");
  trOUT5->Branch("frac02"            ,&frac02_      ,"frac01_/F");
  trOUT5->Branch("frac03"            ,&frac03_      ,"frac01_/F");
  trOUT5->Branch("frac04"            ,&frac04_      ,"frac01_/F");
  trOUT5->Branch("ptD"               ,&ptD_         ,"ptD_/F");
  trOUT5->Branch("beta"              ,&beta_        ,"beta_/F");
  trOUT5->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
  trOUT5->Branch("pull"              ,&pull_        ,"pull_/F");
  trOUT5->Branch("jetR"              ,&jetR_        ,"jetR_/F");
  trOUT5->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
  trOUT5->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
  trOUT5->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
  trOUT5->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
  trOUT5->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
  trOUT5->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
  trOUT5->Branch("nTrueInt"          ,&npu_         ,"npu_/I");

  trOUT6->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
  trOUT6->Branch("rho"               ,&rho_         ,"rho_/F");
  trOUT6->Branch("jetPt"             ,&pt_          ,"pt_/F");
  trOUT6->Branch("jetEta"            ,&eta_         ,"eta_/F");
  trOUT6->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
  trOUT6->Branch("majW"              ,&majW_        ,"majW_/F");
  trOUT6->Branch("minW"              ,&minW_        ,"minW_/F");
  trOUT6->Branch("frac01"            ,&frac01_      ,"frac01_/F");
  trOUT6->Branch("frac02"            ,&frac02_      ,"frac01_/F");
  trOUT6->Branch("frac03"            ,&frac03_      ,"frac01_/F");
  trOUT6->Branch("frac04"            ,&frac04_      ,"frac01_/F");
  trOUT6->Branch("ptD"               ,&ptD_         ,"ptD_/F");
  trOUT6->Branch("beta"              ,&beta_        ,"beta_/F");
  trOUT6->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
  trOUT6->Branch("pull"              ,&pull_        ,"pull_/F");
  trOUT6->Branch("jetR"              ,&jetR_        ,"jetR_/F");
  trOUT6->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
  trOUT6->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
  trOUT6->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
  trOUT6->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
  trOUT6->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
  trOUT6->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
  trOUT6->Branch("nTrueInt"          ,&npu_         ,"npu_/I");

  trOUT7->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
  trOUT7->Branch("rho"               ,&rho_         ,"rho_/F");
  trOUT7->Branch("jetPt"             ,&pt_          ,"pt_/F");
  trOUT7->Branch("jetEta"            ,&eta_         ,"eta_/F");
  trOUT7->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
  trOUT7->Branch("majW"              ,&majW_        ,"majW_/F");
  trOUT7->Branch("minW"              ,&minW_        ,"minW_/F");
  trOUT7->Branch("frac01"            ,&frac01_      ,"frac01_/F");
  trOUT7->Branch("frac02"            ,&frac02_      ,"frac01_/F");
  trOUT7->Branch("frac03"            ,&frac03_      ,"frac01_/F");
  trOUT7->Branch("frac04"            ,&frac04_      ,"frac01_/F");
  trOUT7->Branch("ptD"               ,&ptD_         ,"ptD_/F");
  trOUT7->Branch("beta"              ,&beta_        ,"beta_/F");
  trOUT7->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
  trOUT7->Branch("pull"              ,&pull_        ,"pull_/F");
  trOUT7->Branch("jetR"              ,&jetR_        ,"jetR_/F");
  trOUT7->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
  trOUT7->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
  trOUT7->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
  trOUT7->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
  trOUT7->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
  trOUT7->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
  trOUT7->Branch("nTrueInt"          ,&npu_         ,"npu_/I");

  trOUT8->Branch("nvtx"              ,&nVtx_        ,"nVtx_/I");
  trOUT8->Branch("rho"               ,&rho_         ,"rho_/F");
  trOUT8->Branch("jetPt"             ,&pt_          ,"pt_/F");
  trOUT8->Branch("jetEta"            ,&eta_         ,"eta_/F");
  trOUT8->Branch("dR2Mean"           ,&dR2Mean_     ,"dR2Mean_/F");
  trOUT8->Branch("majW"              ,&majW_        ,"majW_/F");
  trOUT8->Branch("minW"              ,&minW_        ,"minW_/F");
  trOUT8->Branch("frac01"            ,&frac01_      ,"frac01_/F");
  trOUT8->Branch("frac02"            ,&frac02_      ,"frac01_/F");
  trOUT8->Branch("frac03"            ,&frac03_      ,"frac01_/F");
  trOUT8->Branch("frac04"            ,&frac04_      ,"frac01_/F");
  trOUT8->Branch("ptD"               ,&ptD_         ,"ptD_/F");
  trOUT8->Branch("beta"              ,&beta_        ,"beta_/F");
  trOUT8->Branch("betaStar"          ,&betaStar_    ,"betaStar_/F");
  trOUT8->Branch("pull"              ,&pull_        ,"pull_/F");
  trOUT8->Branch("jetR"              ,&jetR_        ,"jetR_/F");
  trOUT8->Branch("jetRchg"           ,&jetRchg_     ,"jetRchg_/F");
  trOUT8->Branch("nParticles"        ,&nParticles_  ,"nParticles_/I");
  trOUT8->Branch("nCharged"          ,&nCharged_    ,"nCharged_/I");
  trOUT8->Branch("dRMatch"           ,&genDR_       ,"genDR_/F");
  trOUT8->Branch("refdrjt"           ,&genPt_       ,"genPt_/F");
  trOUT8->Branch("jetFlavorParton"   ,&flavorParton_,"flavorParton_/I");
  trOUT8->Branch("nTrueInt"          ,&npu_         ,"npu_/I");

  int decade(0);
  int NN = trIN->GetEntries();
  cout<<"Reading "<<NN<<" entries"<<endl;
  for(int iev=0;iev<NN;iev++) {
    double progress = 10.0*iev/(1.0*NN);
    int k = TMath::FloorNint(progress); 
    if (k > decade) 
      cout<<10*k<<" %"<<endl;
    decade = k; 
    trIN->GetEntry(iev);
    
    for(unsigned j=0;j<pt->size();j++) {
      nVtx_         = nVtx;
      npu_          = npu;
      rho_          = rho;
      flavorParton_ = (*flavorParton)[j];
      nParticles_   = (*nParticles)[j];
      nCharged_     = (*nCharged)[j];
      pt_           = (*pt)[j];
      eta_          = (*eta)[j];
      genDR_        = (*genDR)[j];
      genPt_        = (*genPt)[j];
      beta_         = (*beta)[j]; 
      betaStar_     = (*betaStar)[j];
      pull_         = (*pull)[j];
      jetR_         = (*jetR)[j];
      jetRchg_      = (*jetRchg)[j];
      dR2Mean_      = (*dR2Mean)[j];
      majW_         = (*majW)[j];
      minW_         = (*minW)[j];
      frac01_       = (*frac01)[j];
      frac02_       = (*frac02)[j];
      frac03_       = (*frac03)[j];
      frac04_       = (*frac04)[j];
      ptD_          = (*ptD)[j];

      float abs_eta = fabs(eta_);

      if (nLeptons != 2) continue;
      if (fabs(llMass - 90) > 20) continue;
      if (pt_ > 100) continue;

      if (genDR_ < 0.2) {
        if (abs_eta < 2.5) { 
          trOUT1->Fill();
        }
        else if (abs_eta > 2.5 && abs_eta < 2.75) {
          trOUT3->Fill();
        }
        else if (abs_eta > 2.75 && abs_eta < 3.0) {
          trOUT5->Fill();
        }
        else {
          trOUT7->Fill();
        } 
      }
      if ((genDR_ > 0.3) && (flavorParton_ == 0)) {
        if (abs_eta < 2.5) { 
          trOUT2->Fill();
        }
        else if (abs_eta > 2.5 && abs_eta < 2.75) {
          trOUT4->Fill();
        }
        else if (abs_eta > 2.75 && abs_eta < 3.0) {
          trOUT6->Fill();
        }
        else {
          trOUT8->Fill();
        }
      }
    }
  } 
  cout<<"==== Number of jets ===="<<endl;
  cout<<"0.0  - 2.5  sig: "<<trOUT1->GetEntries()<<", bkg: "<<trOUT2->GetEntries()<<endl;
  cout<<"2.5  - 2.75 sig: "<<trOUT3->GetEntries()<<", bkg: "<<trOUT4->GetEntries()<<endl;
  cout<<"2.75 - 3.0  sig: "<<trOUT5->GetEntries()<<", bkg: "<<trOUT6->GetEntries()<<endl;
  cout<<"3.0  - 5.0  sig: "<<trOUT7->GetEntries()<<", bkg: "<<trOUT8->GetEntries()<<endl; 
  outf->cd();
  trOUT1->Write();
  trOUT2->Write();
  trOUT3->Write();
  trOUT4->Write();
  trOUT5->Write();
  trOUT6->Write();
  trOUT7->Write();
  trOUT8->Write();
  outf->Close();
  inf->Close();
}






















