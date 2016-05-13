#define events_cxx
#include "events.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void events::Loop(TDirectory *DIR,bool isMC)
{
  char name[1000];
  const int NVAR = 5;
  TString var[NVAR] = {"nvtx","rho","pvz","met_ov_sumet","llMass"}; 
  double dX[NVAR]   = {1,0.2,0.1,0.01,0.1};
  double XMIN[NVAR] = {0,0,-30,0,60};
  double XMAX[NVAR] = {50,30,30,1,120};
   
  DIR->cd();

  //--------------------------------------- 
  TH1F *hVar[NVAR];
  cout<<"Booking histograms.........."<<endl;
  for(int ivar=0;ivar<NVAR;ivar++) {
    int NBINS = (XMAX[ivar]-XMIN[ivar])/dX[ivar];
    sprintf(name,"h_%s",var[ivar].Data()); 
    hVar[ivar] = new TH1F(name,name,NBINS,XMIN[ivar],XMAX[ivar]);
  }
  
  const int NJETVAR = 18;

  TString varJet[NJETVAR] = {"pt","eta","npv","dR2Mean","nParticles","nCharged","majW","minW",
                             "frac01","frac02","frac03","frac04","ptD","beta","pull","jetR","jetRchg","pumva"}; 
  double dXJET[NJETVAR]   = {1,0.1,1,0.001,1,1,0.001,0.001,0.01,0.01,0.01,0.01,0.01,0.01,0.001,0.01,0.01,0.01};
  double XMINJET[NJETVAR] = {0,-4.7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1};
  double XMAXJET[NJETVAR] = {100,4.7,50,0.1,60,40,0.3,0.2,1,1,1,1,1,1,0.025,1,1,1};
  TH1F *hJetVar[NJETVAR][4][3][3];
  TProfile *pJetVar[NJETVAR];

  cout<<"Booking jet histograms.........."<<endl;
  for(int ivar=0;ivar<NJETVAR;ivar++) {
    cout<<varJet[ivar].Data()<<endl;
    int NBINS = (XMAXJET[ivar]-XMINJET[ivar])/dXJET[ivar];
    for(int ieta=0;ieta<4;ieta++) {
      for(int ipt=0;ipt<3;ipt++) {
        for(int k=0;k<3;k++) {
          sprintf(name,"h_%s_Type%d_Pt%d_Eta%d",varJet[ivar].Data(),k,ipt,ieta);
          hJetVar[ivar][ieta][ipt][k] = new TH1F(name,name,NBINS,XMINJET[ivar],XMAXJET[ivar]);
        }
      }
    } 

    sprintf(name,"p_%s_vs_nvtx",varJet[ivar].Data());
    pJetVar[ivar] = new TProfile(name,name,50,0,50,XMINJET[ivar],XMAXJET[ivar]);
  }
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  cout<<"Reading "<<nentries<<" events"<<endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    if (jentry % (nentries/10) == 0) cout<<100*jentry/nentries<<"%"<<endl;
    fChain->GetEntry(jentry);
    
    float x[NVAR] = {float(npv),rho,pvz,met/sumet,llMass};
    
    float wt = 1.0;
    if (isMC) wt = genEvtWeight;
 
    if (nLeptons != 2) continue;
    if (fabs(llMass - 90) > 20) continue;

    for(int ivar=0;ivar<NVAR;ivar++) {
      hVar[ivar]->Fill(x[ivar],wt);
    }
    for(unsigned int j=0;j<jetPt->size();j++) {
      float xJet[NJETVAR] = {(*jetPt)[j],(*jetEta)[j],float(npv),(*dR2Mean)[j],float((*nParticles)[j]),float((*nCharged)[j]),
                             (*majW)[j],(*minW)[j],(*frac01)[j],(*frac02)[j],(*frac03)[j],(*frac04)[j],
                             (*ptD)[j],(*beta)[j],(*pull)[j],(*jetR)[j],(*jetRchg)[j],(*pumva)[j]}; 
      float eta  = fabs((*jetEta)[j]);
      float pt   = (*jetPt)[j];
      float dR   = (*dRMatch)[j];
      int   flav = fabs((*jetFlavorParton)[j]); 
      int ipt(-1),ieta(-1),iflav(-1);
      
      if (pt > 20 && pt < 30) {
        ipt = 0;
      }
      if (pt > 30 && pt < 50) {
        ipt = 1;
      }
      if (pt > 50 && pt < 100) {
        ipt = 2;
      }
      if (eta < 2.5) {
        ieta = 0;
      }
      if (eta > 2.5 && eta < 2.75) {
        ieta = 1;
      }
      if (eta > 2.75 && eta < 3) {
        ieta = 2;
      }
      if (eta > 3) {
        ieta = 3;
      }
      if (flav>0 && flav < 6 && dR < 0.2) {
        iflav = 0;
      }
      if (flav == 21 && dR < 0.2) {
        iflav = 1;
      }
      if (flav == 0 && dR > 0.3) {
        iflav = 2;
      }
      for(int ivar=0;ivar<NJETVAR;ivar++) {
        if (eta < 2.4 && pt > 70) {
          pJetVar[ivar]->Fill(npv,xJet[ivar],wt);
        } 
        if (ipt >= 0 && ieta >= 0 && iflav >= 0) {
          hJetVar[ivar][ieta][ipt][iflav]->Fill(xJet[ivar],wt);
        }  
      }
    }    
  }
  DIR->Write();
}
